USE [ITCompany]

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
	DBCC CHECKIDENT ('[ProjectInfos]', RESEED, 0)
	DBCC CHECKIDENT ('[Breaks]', RESEED, 0)
	DBCC CHECKIDENT ('[Employees]', RESEED, 0)
	DBCC CHECKIDENT ('[Computers]', RESEED, 0)

	INSERT INTO CEOs VALUES ('Ion', 13)
	INSERT INTO CEOs VALUES ('Ionut Corneliu', 20)
	INSERT INTO CEOs VALUES ('Alex Manea', 29)
	INSERT INTO CEOs VALUES ('Ionut Gingu', 34)
	INSERT INTO CEOs VALUES ('Sabina', 28)
	INSERT INTO MainDepartments VALUES ('All activities', 1)
	INSERT INTO MainDepartments VALUES ('PE Section', 4)
	INSERT INTO MainDepartments VALUES ('Maintenance', 1)
	INSERT INTO MainDepartments VALUES ('HR', 2)
	INSERT INTO MainDepartments VALUES ('Tehnical Dept', 1)
	INSERT INTO DepartmentDirectors(main_department_id) VALUES (1)
	INSERT INTO DepartmentDirectors VALUES ('Andreea Schiriac', 2)
	INSERT INTO DepartmentDirectors VALUES ('Cristi Gabriel', 2)
	INSERT INTO DepartmentDirectors VALUES ('Ionut', 1)
	INSERT INTO ProjectManagers VALUES (15, 2)
	INSERT INTO ProjectManagers VALUES (7, 3)
	INSERT INTO ProjectManagers VALUES (3, 4)
	INSERT INTO Teams VALUES (132, 2)
	INSERT INTO Teams VALUES (64, 3)
	INSERT INTO Teams VALUES (554, 1)
	INSERT INTO Employees VALUES (1)
	INSERT INTO Employees VALUES (1)
	INSERT INTO Employees VALUES (2)
	INSERT INTO Employees VALUES (3)
	INSERT INTO ProjectInfos VALUES ('Face Recognition with AI and Machine Learning')
	INSERT INTO ProjectInfos VALUES ('Data mining')
	INSERT INTO ProjectInfos VALUES ('Code testing')
	INSERT INTO ProjectInfos VALUES ('Deep AI')
	INSERT INTO ContractECs VALUES (1, 1, 'Finishes by the deadline')
	INSERT INTO ContractECs VALUES (1, 2, 'Keeps the informations secret')
	INSERT INTO ContractECs VALUES (4, 2, 'Works hard')
	INSERT INTO Breaks VALUES(10)
	INSERT INTO Breaks VALUES(30)
	INSERT INTO Breaks VALUES(60)
	INSERT INTO Breaks VALUES(50)
	INSERT INTO Breaks VALUES(80)
	INSERT INTO WorkTimes VALUES(2, 1, 8)
	INSERT INTO WorkTimes VALUES(3, 1, 7)
	INSERT INTO WorkTimes VALUES(4, 5, 11)
	INSERT INTO Desks VALUES (1, 61)
	INSERT INTO Desks VALUES (2, 32)
	INSERT INTO Computers VALUES ('Linux', 1, 'Yes')
	INSERT INTO Computers VALUES ('Windows', 2, 'No')
	INSERT INTO Computers VALUES ('Kali', 2, 'Yes')
	INSERT INTO ProjectManagers VALUES (15, 1)
	INSERT INTO Teams VALUES (4980, 1)
GO

EXEC [Restart]

SELECT * FROM CEOs
SELECT * FROM MainDepartments
SELECT * FROM DepartmentDirectors
SELECT * FROM ProjectManagers
SELECT * FROM Teams
SELECT * FROM Employees
SELECT * FROM ProjectInfos
SELECT * FROM ContractECs
SELECT * FROM Breaks
SELECT * FROM WorkTimes
SELECT * FROM Desks
SELECT * FROM Computers