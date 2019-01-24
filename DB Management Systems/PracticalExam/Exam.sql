--U - user defined table
USE StudentInternships
GO

IF OBJECT_ID('Students', 'U') IS NOT NULL
	DROP TABLE Students
IF OBJECT_ID('Internships', 'U') IS NOT NULL
	DROP TABLE Internships
IF OBJECT_ID('AcademicSupervisors', 'U') IS NOT NULL
	DROP TABLE AcademicSupervisors
IF OBJECT_ID('Companies', 'U') IS NOT NULL
	DROP TABLE Companies
IF OBJECT_ID('UniversityDepartments', 'U') IS NOT NULL
	DROP TABLE UniversityDepartments



CREATE TABLE UniversityDepartments (
	ID INT PRIMARY KEY IDENTITY(1, 1),
	DName VARCHAR(100)
)

CREATE TABLE Companies (
	ID INT PRIMARY KEY IDENTITY(1, 1),
	CName VARCHAR(100),
	PhoneNumber VARCHAR(15),
	Website VARCHAR(50)
)

CREATE TABLE AcademicSupervisors (
	ID INT PRIMARY KEY IDENTITY(1, 1),
	DeptID INT REFERENCES UniversityDepartments(ID)
)

CREATE TABLE Internships (
	ID INT PRIMARY KEY IDENTITY(1, 1),
	Title VARCHAR(100),
	[Description] VARCHAR(500),
	Credits INTEGER,
	TotalHours INTEGER,
	CID INT REFERENCES Companies(ID)
)

CREATE TABLE Students (
	InternshipID INT REFERENCES Internships(ID),
	SupervisorID INT REFERENCES AcademicSupervisors(ID),
	SName VARCHAR(50),
	PRIMARY KEY(InternshipID, SupervisorID)
)

GO

INSERT Companies(CName, PhoneNumber, Website) VALUES('Sector Labs', '+(407)-425', 'www.sectorlabs.ro/careers');
INSERT Companies(CName, PhoneNumber, Website) VALUES('Facebook', '+(333)-5421', 'www.facebook.com/careers');
INSERT Internships(Title, [Description], Credits, TotalHours, CID) VALUES('Full Stack Software Engineer', 'Perform different tasks', 6, 120, 3);

SELECT * FROM Companies
SELECT * FROM Internships

INSERT INTO UniversityDepartments(DName) VALUES('IT');
INSERT INTO AcademicSupervisors(DeptID) VALUES(1);
INSERT INTO AcademicSupervisors(DeptID) VALUES(1);
INSERT INTO Students(InternshipID, SupervisorID, SName) VALUES(2, 1, 'John');

DROP PROCEDURE IF EXISTS DeadlockA
GO	

CREATE PROCEDURE DeadlockA
AS
--run first, both from second, last from here
	BEGIN TRANSACTION DL WITH MARK
	SET DEADLOCK_PRIORITY NORMAL
	DELETE FROM Students
	WHERE SName LIKE '%J'
	DELETE FROM AcademicSupervisors
	WHERE id % 2 = 0
	COMMIT TRANSACTION
GO

--EXEC DeadlockA