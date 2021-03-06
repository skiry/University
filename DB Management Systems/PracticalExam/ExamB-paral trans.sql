USE StudentInternships
GO

DROP PROCEDURE IF EXISTS DeadlockB
GO

CREATE PROCEDURE DeadlockB
AS
	BEGIN TRANSACTION DL WITH MARK
	SET DEADLOCK_PRIORITY LOW
	DELETE FROM AcademicSupervisors
	WHERE id % 2 = 0
	DELETE FROM Students
	WHERE SName LIKE '%J'
	COMMIT TRANSACTION
GO

--EXEC DeadlockB