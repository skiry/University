USE ITCompany

--setup a logging system to track executed actions for all scenarios.
--don t use ids as parameters
--happy scenarios + error scenarios
--validate parameters
--try/catch

--create a stored procedure that inserts data in tables that are in a m:n relationship;
--if one insert fails, all the operations performed by the procedure must be rolled back
DROP PROCEDURE IF EXISTS InsertAndRollbackError
GO

CREATE PROCEDURE InsertAndRollbackError
AS	
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION RB1 WITH MARK
		INSERT INTO Breaks VALUES(100)
		INSERT INTO Employees VALUES(3)
		INSERT INTO WorkTimes VALUES(19412, 241, 20)
		COMMIT TRANSACTION
	END TRY
	--if the transaction failed, trancount is still 1
	BEGIN CATCH
		IF @@TRANCOUNT > 0
			PRINT 'ROLLBACKING error - ok'
			ROLLBACK TRANSACTION
	END CATCH
END
GO

DROP PROCEDURE IF EXISTS InsertAndRollbackSuccess
GO

CREATE PROCEDURE InsertAndRollbackSuccess
AS	
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION RB2 WITH MARK
		INSERT INTO Breaks VALUES(72)
		INSERT INTO Employees VALUES(2)
		INSERT INTO WorkTimes VALUES(4, 1, 7)
		COMMIT TRANSACTION
	END TRY

	BEGIN CATCH
		IF @@TRANCOUNT > 0
			PRINT 'ROLLBACKING success - not ok' 
			ROLLBACK TRANSACTION
	END CATCH
END
GO

DROP PROCEDURE IF EXISTS FirstExample
GO

CREATE PROCEDURE FirstExample
AS
	SELECT * FROM Breaks
	SELECT * FROM WorkTimes
	SELECT * FROM Employees

	EXEC InsertAndRollbackError

	SELECT * FROM Breaks
	SELECT * FROM WorkTimes
	SELECT * FROM Employees

	EXEC InsertAndRollbackSuccess

	SELECT * FROM Breaks
	SELECT * FROM WorkTimes
	SELECT * FROM Employees
GO

--EXEC FirstExample

--create a stored procedure that inserts data in tables that are in a m:n relationship; 
--if an insert fails, try to recover as much as possible from the entire operation: 
--for example, if the user wants to add a book and its authors, 
--succeeds creating the authors, but fails with the book, the authors should remain in the database
DROP PROCEDURE IF EXISTS InsertAndRollbackToSaved
GO

CREATE PROCEDURE InsertAndRollbackToSaved
AS	
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION RBS WITH MARK
		INSERT INTO Breaks VALUES(100)
		SAVE TRANSACTION GoodEnoughPoint
		INSERT INTO Employees VALUES(3)
		SAVE TRANSACTION GoodEnoughPoint
		INSERT INTO WorkTimes VALUES(19412, 241, 20)
		COMMIT TRANSACTION
	END TRY

	BEGIN CATCH
		IF @@TRANCOUNT > 0
			PRINT 'ROLLBACKING to the last checkpoint - ok'
			ROLLBACK TRANSACTION GoodEnoughPoint
			COMMIT TRANSACTION
	END CATCH
END
GO

DROP PROCEDURE IF EXISTS SecondExample
GO

CREATE PROCEDURE SecondExample
AS
	SELECT * FROM Breaks
	SELECT * FROM WorkTimes
	SELECT * FROM Employees

	EXEC InsertAndRollbackToSaved

	SELECT * FROM Breaks
	SELECT * FROM WorkTimes
	SELECT * FROM Employees
GO

--EXEC SecondExample


--create 4 scenarios that reproduce the following concurrency issues under pessimistic isolation levels:
--dirty reads, non-repeatable reads, phantom reads, and a deadlock; 
--you can use stored procedures and / or stand-alone queries; 
--find solutions to solve / workaround the concurrency issues

DROP PROCEDURE IF EXISTS DirtyReadsA
GO

CREATE PROCEDURE DirtyReadsA
AS
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenBeforeT
	FROM Breaks
	BEGIN TRANSACTION DR WITH MARK
	UPDATE Breaks
	SET minutes_taken = 5
	WAITFOR DELAY '00:00:05';
	ROLLBACK TRANSACTION
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterT
	FROM Breaks
GO

--EXEC DirtyReadsA

DROP PROCEDURE IF EXISTS DirtyReadsASolved
GO

CREATE PROCEDURE DirtyReadsASolved
AS
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenBeforeT
	FROM Breaks
	BEGIN TRANSACTION DRS WITH MARK
	UPDATE Breaks
	SET minutes_taken = 5
	WAITFOR DELAY '00:00:05';
	ROLLBACK TRANSACTION
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterT
	FROM Breaks
GO

--EXEC DirtyReadsASolved

DROP PROCEDURE IF EXISTS NonRepeatableReadsA
GO

CREATE PROCEDURE NonRepeatableReadsA
AS
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRANSACTION NRR WITH MARK
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenBeforeT
	FROM Breaks

	WAITFOR DELAY '00:00:05';

	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterT
	FROM Breaks

	COMMIT TRANSACTION
GO

--EXEC NonRepeatableReadsA

DROP PROCEDURE IF EXISTS NonRepeatableReadsASolved
GO

CREATE PROCEDURE NonRepeatableReadsASolved
AS
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRANSACTION NRR WITH MARK
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenBeforeT
	FROM Breaks

	WAITFOR DELAY '00:00:05';

	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterT
	FROM Breaks

	COMMIT TRANSACTION
GO		

--EXEC NonRepeatableReadsASolved


DROP PROCEDURE IF EXISTS PhantomReadsA
GO

CREATE PROCEDURE PhantomReadsA
AS
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRANSACTION PR WITH MARK
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenBeforeT
	FROM Breaks

	WAITFOR DELAY '00:00:05';

	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterT
	FROM Breaks

	COMMIT TRANSACTION
GO

--EXEC PhantomReadsA

DROP PROCEDURE IF EXISTS PhantomReadsASolved
GO

CREATE PROCEDURE PhantomReadsASolved
AS
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRANSACTION PRS WITH MARK
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenBeforeT
	FROM Breaks

	WAITFOR DELAY '00:00:05';

	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterT
	FROM Breaks

	COMMIT TRANSACTION

	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterCommitDebug
	FROM Breaks
GO		

--EXEC PhantomReadsASolved

DROP PROCEDURE IF EXISTS DeadlockA
GO

CREATE PROCEDURE DeadlockA
AS
--run first, both from second, last from here
	BEGIN TRANSACTION DL WITH MARK
	SET DEADLOCK_PRIORITY NORMAL
	DELETE FROM WorkTimes
	WHERE work_time = 8
	DELETE FROM Computers
	WHERE id = 1
	SELECT COUNT(DISTINCT minutes_taken) AS IfShownNoDeadlock
	FROM Breaks
	COMMIT TRANSACTION
GO

--EXEC DeadlockA