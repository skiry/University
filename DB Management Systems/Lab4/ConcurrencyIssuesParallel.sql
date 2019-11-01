USE ITCompany
GO

DROP PROCEDURE IF EXISTS DirtyReadsB
GO

CREATE PROCEDURE DirtyReadsB
AS
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterTBeforeRB
	FROM Breaks
GO

--EXEC DirtyReadsB

DROP PROCEDURE IF EXISTS DirtyReadsBSolved
GO

CREATE PROCEDURE DirtyReadsBSolved
AS
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	SELECT COUNT(DISTINCT minutes_taken) AS MinutesTakenAfterTBeforeRB
	FROM Breaks
GO

--EXEC DirtyReadsBSolved

DROP PROCEDURE IF EXISTS NonRepeatableReadsB
GO

CREATE PROCEDURE NonRepeatableReadsB
AS
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRANSACTION NRRB WITH MARK
	UPDATE Breaks
	SET minutes_taken = 5
	COMMIT TRANSACTION
GO

--EXEC NonRepeatableReadsB

DROP PROCEDURE IF EXISTS NonRepeatableReadsBSolved
GO

CREATE PROCEDURE NonRepeatableReadsBSolved
AS
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRANSACTION NRRBS WITH MARK
	UPDATE Breaks
	SET minutes_taken = 5
	COMMIT TRANSACTION
GO

--EXEC NonRepeatableReadsBSolved

DROP PROCEDURE IF EXISTS PhantomReadsB
GO

CREATE PROCEDURE PhantomReadsB
AS
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRANSACTION PRB WITH MARK
	INSERT INTO Breaks VALUES(9171)
	COMMIT TRANSACTION
GO

--EXEC PhantomReadsB

DROP PROCEDURE IF EXISTS PhantomReadsBSolved
GO

CREATE PROCEDURE PhantomReadsBSolved
AS
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRANSACTION PRBS WITH MARK
	INSERT INTO Breaks VALUES(9172)
	COMMIT TRANSACTION
GO

--EXEC PhantomReadsBSolved

DROP PROCEDURE IF EXISTS DeadlockB
GO

CREATE PROCEDURE DeadlockB
AS
	BEGIN TRANSACTION DLB WITH MARK
	SET DEADLOCK_PRIORITY LOW
	DELETE FROM Computers
	WHERE id = 1
	DELETE FROM WorkTimes
	WHERE work_time = 8
	SELECT COUNT(DISTINCT minutes_taken) AS IfShownNoDeadlock
	FROM Breaks
	COMMIT TRANSACTION
GO

--EXEC DeadlockB