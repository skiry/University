USE ITCompany
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables

GO


if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRuns]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tests]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Views]

GO



CREATE TABLE [Tables] (

	[TableID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunTables] (

	[TestRunID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunViews] (

	[TestRunID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRuns] (

	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,

	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,

	[StartAt] [datetime] NULL ,

	[EndAt] [datetime] NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestTables] (

	[TestID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[NoOfRows] [int] NOT NULL ,

	[Position] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestViews] (

	[TestID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Tests] (

	[TestID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Views] (

	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



ALTER TABLE [Tables] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 

	(

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRuns] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Tests] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 

	(

		[TestID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Views] WITH NOCHECK ADD 

	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 

	(

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] ADD 

	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestRunViews] ADD 

	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestTables] ADD 

	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestViews] ADD 

	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	),

	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	)

GO


DROP PROCEDURE IF EXISTS [Restart]
GO

CREATE PROCEDURE [Restart]
AS
	DELETE FROM WorkTimes
	DELETE FROM ContractECs
	DELETE FROM ProjectInfos
	DELETE FROM Employees
	DELETE FROM Breaks
	DELETE FROM [Tables]
	DELETE FROM TestViews
	DELETE FROM Tests
	DELETE FROM [Views]
	DELETE FROM TestRuns
	DELETE FROM TestTables
	DELETE FROM TestRunViews
	DELETE FROM TestRunTables
	DELETE FROM Computers
	DELETE FROM Desks
	DELETE FROM Teams
	DELETE FROM ProjectManagers
	DELETE FROM DepartmentDirectors
	DELETE FROM MainDepartments
	DELETE FROM CEOs

	DBCC CHECKIDENT ('[CEOs]', RESEED, 0)
	DBCC CHECKIDENT ('[MainDepartments]', RESEED, 0)
	DBCC CHECKIDENT ('[DepartmentDirectors]', RESEED, 0)
	DBCC CHECKIDENT ('[ProjectManagers]', RESEED, 0)
	DBCC CHECKIDENT ('[Teams]', RESEED, 0)

	DBCC CHECKIDENT ('[Tables]', RESEED, 1)
	DBCC CHECKIDENT ('[Views]', RESEED, 1)
	DBCC CHECKIDENT ('[Tests]', RESEED, 1)
	DBCC CHECKIDENT ('[TestRuns]', RESEED, 1)
	INSERT INTO CEOs VALUES ('Ion', 13)
	INSERT INTO MainDepartments VALUES ('Maintenance', 1)
	INSERT INTO DepartmentDirectors VALUES ('Ionut', 1)
	INSERT INTO ProjectManagers VALUES (15, 1)
	INSERT INTO Teams VALUES (4980, 1)
GO

EXEC [Restart]

DROP PROC IF EXISTS InsertTables
GO

CREATE PROCEDURE InsertTables
AS
	INSERT INTO Tables VALUES ('Breaks')
	INSERT INTO Tables VALUES ('WorkTimes')
	INSERT INTO Tables VALUES ('Employees')
	INSERT INTO Tables VALUES ('ContractECs')
	INSERT INTO Tables VALUES ('ProjectInfos')
	INSERT INTO Tables VALUES ('Teams')
	INSERT INTO Tables VALUES ('Desks')
	INSERT INTO Tables VALUES ('Computers')
	INSERT INTO Tables VALUES ('ProjectManagers')
	INSERT INTO Tables VALUES ('DepartmentDirectors')
	INSERT INTO Tables VALUES ('MainDepartments')
	INSERT INTO Tables VALUES ('CEOs')
GO
EXEC InsertTables
--SELECT * FROM Tables


DROP PROC IF EXISTS InsertViews
GO

CREATE PROCEDURE InsertViews
AS
	INSERT INTO Views VALUES ('ViewBreaks')
	INSERT INTO Views VALUES ('ViewWorkTimes')
	INSERT INTO Views VALUES ('ViewContractECs')
	INSERT INTO Views VALUES ('ViewCEOs')
	INSERT INTO Views VALUES ('ViewMainDepartments')

	INSERT INTO Views VALUES ('ViewEmployees')
	INSERT INTO Views VALUES ('ViewProjectInfos')
	INSERT INTO Views VALUES ('ViewTeams')
	INSERT INTO Views VALUES ('ViewDesks')
	INSERT INTO Views VALUES ('ViewComputers')
	INSERT INTO Views VALUES ('ViewProjectManagers')
	INSERT INTO Views VALUES ('ViewDepartmentDirectors')
	
GO
EXEC InsertViews
--SELECT * FROM Views


DROP PROC IF EXISTS InsertTests
GO

CREATE PROCEDURE InsertTests
AS
	/*
	INSERT INTO Tests VALUES ('Insert_100')
	INSERT INTO Tests VALUES ('Insert_2000')
	INSERT INTO Tests VALUES ('Insert_50000')
	INSERT INTO Tests VALUES ('Delete_100')
	INSERT INTO Tests VALUES ('Delete_2000')
	INSERT INTO Tests VALUES ('Delete_50000')
	INSERT INTO Tests VALUES ('Select_View')
	*/
	INSERT INTO Tests VALUES ('TestBreaks')
	INSERT INTO Tests VALUES ('TestCEOs')
GO
EXEC InsertTests
--SELECT * FROM Tests

DROP PROC IF EXISTS InsertTestViews
GO

CREATE PROCEDURE InsertTestViews
AS
	/*
	INSERT INTO TestViews VALUES (7, 1)
	INSERT INTO TestViews VALUES (7, 2)
	INSERT INTO TestViews VALUES (7, 4)
	*/
	INSERT INTO TestViews VALUES (1, 1)
	INSERT INTO TestViews VALUES (1, 2)
	INSERT INTO TestViews VALUES (1, 4)
	INSERT INTO TestViews VALUES (2, 4)
	INSERT INTO TestViews VALUES (2, 5)
	INSERT INTO TestViews VALUES (2, 3)
GO
EXEC InsertTestViews
--SELECT * FROM TestViews


DROP PROC IF EXISTS InsertTestTables
GO

CREATE PROCEDURE InsertTestTables
AS
	INSERT INTO TestTables VALUES (1, 1, 1000, 1)
	INSERT INTO TestTables VALUES (1, 3, 1000, 2)
	INSERT INTO TestTables VALUES (1, 5, 1000, 3)
	INSERT INTO TestTables VALUES (1, 2, 1000, 4)
	INSERT INTO TestTables VALUES (1, 4, 1000, 5)

	INSERT INTO TestTables VALUES (2, 12, 2000, 1)
	INSERT INTO TestTables VALUES (2, 11, 2000, 2)
	INSERT INTO TestTables VALUES (2, 3, 2000, 3)
	INSERT INTO TestTables VALUES (2, 5, 2000, 4)
	INSERT INTO TestTables VALUES (2, 4, 2000, 5)

	/*
	INSERT INTO TestTables VALUES (4, 1, 100, 5)
	INSERT INTO TestTables VALUES (4, 3, 100, 4)
	INSERT INTO TestTables VALUES (4, 5, 100, 3)
	INSERT INTO TestTables VALUES (4, 2, 100, 2)
	INSERT INTO TestTables VALUES (4, 4, 100, 1)
	*/
GO
EXEC InsertTestTables
--SELECT * FROM TestTables

/*
DELETE FROM Tables
DELETE FROM Tests

DELETE FROM TestViews
DELETE FROM Views
DELETE FROM TestRuns
DELETE FROM TestTables
DELETE FROM TestRunViews
DELETE FROM TestRunTables
*/

DROP VIEW IF EXISTS ViewBreaks
GO

CREATE VIEW ViewBreaks
AS
	SELECT *
	FROM Breaks
GO
--SELECT * FROM ViewBreaks


DROP VIEW IF EXISTS ViewWorkTimes
GO

CREATE VIEW ViewWorkTimes
AS
	SELECT *
	FROM WorkTimes W
	INNER JOIN Breaks B ON W.break_id = B.id 
GO
--SELECT * FROM ViewWorkTimes


DROP VIEW IF EXISTS ViewContractECs
GO

CREATE VIEW ViewContractECs
AS
	SELECT C.constraints AS [Constraint], P.description_of_project AS Description
	FROM ContractECs C
	INNER JOIN ProjectInfos P ON C.project_info_id = P.id
	WHERE P.description_of_project LIKE '%'
	GROUP BY C.constraints, P.description_of_project
GO
--SELECT * FROM ViewContractECs


DROP VIEW IF EXISTS ViewCEOs
GO

CREATE VIEW ViewCEOs
AS
	SELECT *
	FROM CEOs
GO
--SELECT * FROM ViewCEOs


DROP VIEW IF EXISTS ViewMainDepartments
GO

CREATE VIEW ViewMainDepartments
AS
	SELECT M.*
	FROM MainDepartments M
	INNER JOIN DepartmentDirectors D ON D.main_department_id = M.id
GO
--SELECT * FROM ViewMainDepartments

DROP PROC IF EXISTS InsertBreaks
GO

CREATE PROCEDURE InsertBreaks
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO Breaks VALUES (1000 * @i + (3 * @i) - @i % 7 + @i % 23)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteBreaks
GO

CREATE PROCEDURE DeleteBreaks
AS
	DELETE
	FROM Breaks
	WHERE minutes_taken > 900
GO


DROP PROC IF EXISTS InsertBreaks
GO

CREATE PROCEDURE InsertBreaks
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO Breaks VALUES (1000 * @i + (3 * @i) - @i % 7 + @i % 23)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteBreaks
GO

CREATE PROCEDURE DeleteBreaks
AS
	DELETE
	FROM Breaks
	WHERE minutes_taken > 900
GO


DROP PROC IF EXISTS InsertEmployees
GO

CREATE PROCEDURE InsertEmployees
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO Employees VALUES (1)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteEmployees
GO

CREATE PROCEDURE DeleteEmployees
AS
	DELETE
	FROM Employees
	WHERE team_id = 1
GO

DROP PROC IF EXISTS InsertProjectInfos
GO

CREATE PROCEDURE InsertProjectInfos
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO ProjectInfos VALUES ('Project Info that is indexed with ' + CONVERT(VARCHAR(2), @i))
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteProjectInfos
GO

CREATE PROCEDURE DeleteProjectInfos
AS
	DELETE
	FROM ProjectInfos
	WHERE description_of_project LIKE '%indexed%'
GO


DROP PROC IF EXISTS InsertContractECs
GO

CREATE PROCEDURE InsertContractECs
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO ContractECs VALUES (@i, @i, 'Has pure code, but ' + CONVERT(VARCHAR(10), @i) + ' errors.')
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteContractECs
GO

CREATE PROCEDURE DeleteContractECs
AS
	DELETE
	FROM ContractECs
	WHERE constraints LIKE '%errors%'
GO


DROP PROC IF EXISTS InsertWorkTimes
GO

CREATE PROCEDURE InsertWorkTimes
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO WorkTimes VALUES (@i, @i, 217 * @i)
		SET @i = @i + 1
	END
GO

DROP PROC IF EXISTS DeleteWorkTimes
GO

CREATE PROCEDURE DeleteWorkTimes
AS
	DELETE
	FROM WorkTimes
	WHERE work_time % 217 = 0
GO


DROP PROC IF EXISTS InsertCEOs
GO

CREATE PROCEDURE InsertCEOs
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO CEOs VALUES ('CEO Number ' + CONVERT(VARCHAR(20), @i), @i *2 - 5)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteCEOs
GO

CREATE PROCEDURE DeleteCEOs
AS
	DELETE
	FROM CEOs
	WHERE [name] LIKE '%CEO%'
GO


DROP PROC IF EXISTS InsertMainDepartments
GO

CREATE PROCEDURE InsertMainDepartments
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO MainDepartments VALUES ('Activity Number ' + CONVERT(VARCHAR(20), @i), @i)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteMainDepartments
GO

CREATE PROCEDURE DeleteMainDepartments
AS
	DELETE
	FROM MainDepartments
	WHERE [activity] LIKE '%Activity%'
GO



DROP VIEW IF EXISTS ViewBreaks
GO

CREATE VIEW ViewBreaks
AS
	SELECT *
	FROM Breaks
GO
--SELECT * FROM ViewBreaks


DROP VIEW IF EXISTS ViewWorkTimes
GO

CREATE VIEW ViewWorkTimes
AS
	SELECT *
	FROM WorkTimes W
	INNER JOIN Breaks B ON W.break_id = B.id 
GO
--SELECT * FROM ViewWorkTimes


DROP VIEW IF EXISTS ViewContractECs
GO

CREATE VIEW ViewContractECs
AS
	SELECT C.constraints AS [Constraint], P.description_of_project AS Description
	FROM ContractECs C
	INNER JOIN ProjectInfos P ON C.project_info_id = P.id
	WHERE P.description_of_project LIKE '%'
	GROUP BY C.constraints, P.description_of_project
GO
--SELECT * FROM ViewContractECs


DROP VIEW IF EXISTS ViewCEOs
GO

CREATE VIEW ViewCEOs
AS
	SELECT *
	FROM CEOs
GO
--SELECT * FROM ViewCEOs


DROP VIEW IF EXISTS ViewMainDepartments
GO

CREATE VIEW ViewMainDepartments
AS
	SELECT M.*
	FROM MainDepartments M
	INNER JOIN DepartmentDirectors D ON D.main_department_id = M.id
GO
--SELECT * FROM ViewMainDepartments

DROP PROC IF EXISTS InsertBreaks
GO

CREATE PROCEDURE InsertBreaks
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO Breaks VALUES (1000 * @i + (3 * @i) - @i % 7 + @i % 23)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteBreaks
GO

CREATE PROCEDURE DeleteBreaks
AS
	DELETE
	FROM Breaks
	WHERE minutes_taken > 900
GO


DROP PROC IF EXISTS InsertEmployees
GO

CREATE PROCEDURE InsertEmployees
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO Employees VALUES (1)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteEmployees
GO

CREATE PROCEDURE DeleteEmployees
AS
	DELETE
	FROM Employees
	WHERE team_id = 1
GO

DROP PROC IF EXISTS InsertProjectInfos
GO

CREATE PROCEDURE InsertProjectInfos
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO ProjectInfos VALUES ('Project Info that is indexed with ' + CONVERT(VARCHAR(2), @i))
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteProjectInfos
GO

CREATE PROCEDURE DeleteProjectInfos
AS
	DELETE
	FROM ProjectInfos
	WHERE description_of_project LIKE '%indexed%'
GO


DROP PROC IF EXISTS InsertContractECs
GO

CREATE PROCEDURE InsertContractECs
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO ContractECs VALUES (@i, @i, 'Has pure code, but ' + CONVERT(VARCHAR(10), @i) + ' errors.')
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteContractECs
GO

CREATE PROCEDURE DeleteContractECs
AS
	DELETE
	FROM ContractECs
	WHERE constraints LIKE '%errors%'
GO


DROP PROC IF EXISTS InsertWorkTimes
GO

CREATE PROCEDURE InsertWorkTimes
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO WorkTimes VALUES (@i, @i, 217 * @i)
		SET @i = @i + 1
	END
GO

DROP PROC IF EXISTS DeleteWorkTimes
GO

CREATE PROCEDURE DeleteWorkTimes
AS
	DELETE
	FROM WorkTimes
	WHERE work_time % 217 = 0
GO


DROP PROC IF EXISTS InsertCEOs
GO

CREATE PROCEDURE InsertCEOs
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO CEOs VALUES ('CEO Number ' + CONVERT(VARCHAR(20), @i), @i *2 - 5)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteCEOs
GO

CREATE PROCEDURE DeleteCEOs
AS
	DELETE
	FROM CEOs
	WHERE [name] LIKE '%CEO%'
GO


DROP PROC IF EXISTS InsertMainDepartments
GO

CREATE PROCEDURE InsertMainDepartments
@rows INT
AS
	DECLARE @i INT
	SET @i = 11

	WHILE @i < @rows + 11
	BEGIN
		INSERT INTO MainDepartments VALUES ('Activity Number ' + CONVERT(VARCHAR(20), @i), 1)
		SET @i = @i + 1
	END
GO


DROP PROC IF EXISTS DeleteMainDepartments
GO

CREATE PROCEDURE DeleteMainDepartments
AS
	DELETE
	FROM MainDepartments
	WHERE [activity] LIKE '%Activity%'
GO

--------------------------------------------------------------------------------------------

DROP PROC IF EXISTS TestBreaks
GO
--EXEC [RestartAll]
CREATE PROCEDURE TestBreaks
AS
	DBCC CHECKIDENT ('[Employees]', RESEED, 10)
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 10)
	DBCC CHECKIDENT ('[Breaks]', RESEED, 10)
	
	DECLARE @beforeAll DATETIME
	DECLARE @beforeView DATETIME 
	DECLARE @afterView DATETIME
	DECLARE @afterAll DATETIME
	DECLARE @beforeQueries DATETIME
	DECLARE @afterQueries DATETIME

	SET @beforeAll = GETDATE()
	EXEC InsertBreaks 1000
	EXEC InsertEmployees 1000
	EXEC InsertProjectInfos 1000
	EXEC InsertContractECs 1000
	EXEC InsertWorkTimes 1000

	
	SELECT * 
	FROM ViewBreaks
	SELECT * 
	FROM ViewContractECs
	SELECT * 
	FROM ViewWorkTimes

	EXEC DeleteWorkTimes
	EXEC DeleteContractECs
	EXEC DeleteProjectInfos
	EXEC DeleteBreaks
	EXEC DeleteEmployees
	SET @afterAll = GETDATE()

	DBCC CHECKIDENT ('[Employees]', RESEED, 10)
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 10)
	DBCC CHECKIDENT ('[Breaks]', RESEED, 10)

	INSERT INTO TestRuns VALUES ('Test the processing time of the Breaks, Working Hours and Contract ECS tables', @beforeAll, @afterAll)
	
	SET @beforeQueries = GETDATE()
	EXEC InsertBreaks 1000
	SET @afterQueries = GETDATE()
	INSERT INTO TestRunTables VALUES (1, 1, @beforeQueries, @afterQueries)

	SET @beforeQueries = GETDATE()
	EXEC InsertEmployees 1000
	SET @afterQueries = GETDATE()
	INSERT INTO TestRunTables VALUES (1, 3, @beforeQueries, @afterQueries)

	SET @beforeQueries = GETDATE()
	EXEC InsertProjectInfos 1000
	SET @afterQueries = GETDATE()
	INSERT INTO TestRunTables VALUES (1, 5, @beforeQueries, @afterQueries)

	SET @beforeQueries = GETDATE()
	EXEC InsertContractECs 1000
	SET @afterQueries = GETDATE()
	INSERT INTO TestRunTables VALUES (1, 4, @beforeQueries, @afterQueries)

	SET @beforeQueries = GETDATE()
	EXEC InsertWorkTimes 1000
	SET @afterQueries = GETDATE()
	INSERT INTO TestRunTables VALUES (1, 2, @beforeQueries, @afterQueries)

	SET @beforeView = GETDATE()
	SELECT * 
	FROM ViewBreaks
	SET @afterView = GETDATE()
	INSERT INTO TestRunViews VALUES (1, 1, @beforeView, @afterView)
	
	SET @beforeView = GETDATE()
	SELECT * 
	FROM ViewWorkTimes
	SET @afterView = GETDATE()
	INSERT INTO TestRunViews VALUES (1, 2, @beforeView, @afterView)

	SET @beforeView = GETDATE()
	SELECT * 
	FROM ViewContractECs
	SET @afterView = GETDATE()
	INSERT INTO TestRunViews VALUES (1, 3, @beforeView, @afterView)

	EXEC DeleteWorkTimes
	EXEC DeleteContractECs
	EXEC DeleteProjectInfos
	EXEC DeleteBreaks
	EXEC DeleteEmployees

	DBCC CHECKIDENT ('[Employees]', RESEED, 10)
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 10)
	DBCC CHECKIDENT ('[Breaks]', RESEED, 10)

GO
EXEC TestBreaks

DROP PROC IF EXISTS TestCEOs
GO

CREATE PROCEDURE TestCEOs
AS
	DBCC CHECKIDENT ('[Employees]', RESEED, 10)
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 10)
	DBCC CHECKIDENT ('[CEOs]', RESEED, 10)
	GO

	DECLARE @beforeAll DATETIME
	DECLARE @beforeView DATETIME
	DECLARE @afterView DATETIME
	DECLARE @afterAll DATETIME
	DECLARE @beforeQueries DATETIME
	DECLARE @afterQueries DATETIME

	SET @beforeAll = GETDATE()
	EXEC InsertCEOs 200
	EXEC InsertEmployees 200
	EXEC InsertMainDepartments 200
	EXEC InsertProjectInfos 200
	EXEC InsertContractECs 200

	SELECT * 
	FROM ViewCEOs
	SELECT * 
	FROM ViewMainDepartments
	SELECT * 
	FROM ViewContractECs

	EXEC DeleteContractECs
	EXEC DeleteProjectInfos
	EXEC DeleteMainDepartments
	EXEC DeleteCEOs
	EXEC DeleteEmployees
	SET @afterAll = GETDATE()

	DBCC CHECKIDENT ('[Employees]', RESEED, 10)
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 10)
	DBCC CHECKIDENT ('[CEOs]', RESEED, 10)

	INSERT INTO TestRuns VALUES ('Test the processing time of the CEOs, Main Departments and Contract ECS tables', @beforeAll, @afterAll)

	SET @beforeQueries = GETDATE()
	EXEC InsertCEOs 200
	SET @afterQueries = GETDATE()
	INSERT INTO TestRunTables VALUES (2, 12, @beforeQueries, @afterQueries)
								  
	SET @beforeQueries = GETDATE()	  
	EXEC InsertEmployees 200		  
	SET @afterQueries = GETDATE()	  
	INSERT INTO TestRunTables VALUES (2, 3, @beforeQueries, @afterQueries)

	SET @beforeQueries = GETDATE()	  
	EXEC InsertMainDepartments 200	  
	SET @afterQueries = GETDATE()	  
	INSERT INTO TestRunTables VALUES (2, 11, @beforeQueries, @afterQueries)
									  
	SET @beforeQueries = GETDATE()	  
	EXEC InsertProjectInfos 200	  
	SET @afterQueries = GETDATE()	  
	INSERT INTO TestRunTables VALUES (2, 5, @beforeQueries, @afterQueries)
									  
	SET @beforeQueries = GETDATE()	  
	EXEC InsertContractECs 200		  
	SET @afterQueries = GETDATE()	  
	INSERT INTO TestRunTables VALUES (2, 4, @beforeQueries, @afterQueries)
									  
	

	SET @beforeView = GETDATE()
	SELECT * 
	FROM ViewCEOs
	SET @afterView = GETDATE()
	INSERT INTO TestRunViews VALUES (2, 4, @beforeView, @afterView)
	
	SET @beforeView = GETDATE()
	SELECT * 
	FROM ViewMainDepartments
	SET @afterView = GETDATE()
	INSERT INTO TestRunViews VALUES (2, 5, @beforeView, @afterView)

	SET @beforeView = GETDATE()
	SELECT * 
	FROM ViewContractECs
	SET @afterView = GETDATE()
	INSERT INTO TestRunViews VALUES (2, 6, @beforeView, @afterView)

	EXEC DeleteContractECs
	EXEC DeleteProjectInfos
	EXEC DeleteMainDepartments
	EXEC DeleteCEOs
	EXEC DeleteEmployees

	DBCC CHECKIDENT ('[Employees]', RESEED, 10)
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 10)
	DBCC CHECKIDENT ('[CEOs]', RESEED, 10)

GO

/*

EXEC TestCEOs
*/
--call function
/*
SELECT * FROM Breaks
SELECT * FROM TestRuns
SELECT * FROM ProjectInfos
SELECT * FROM ContractECs
SELECT * FROM Employees
SELECT * FROM CEOs
SELECT * FROM MainDepartments
*/
SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
GO
--insereaza cate un exemplar, foloseste pentru inserturile necesare
