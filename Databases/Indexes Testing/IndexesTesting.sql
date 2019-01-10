CREATE DATABASE IndexesTesting
GO

USE IndexesTesting
GO

CREATE TABLE Kid(
	ID INT PRIMARY KEY IDENTITY,
	ToyID INT UNIQUE,
	[Name] VARCHAR(100)  
)

CREATE TABLE Kindergarten(
	ID INT PRIMARY KEY IDENTITY,
	NumberOfGroups INT
)

CREATE TABLE Catalogue(
	ID INT PRIMARY KEY IDENTITY,
	KidID INT FOREIGN KEY REFERENCES Kid(ID),
	KinderID INT FOREIGN KEY REFERENCES Kindergarten(ID)
)

DELETE FROM Catalogue
DELETE FROM Kid
DELETE FROM Kindergarten

INSERT INTO Kid VALUES (3, 'Ionut')
INSERT INTO Kid VALUES (5, 'Andrei')
INSERT INTO Kid VALUES (9, 'Vicky')
INSERT INTO Kid VALUES (1, 'Andreea')
INSERT INTO Kindergarten VALUES (4)
INSERT INTO Kindergarten VALUES (20)
INSERT INTO Kindergarten VALUES (15)
INSERT INTO Kindergarten VALUES (13)
INSERT INTO Catalogue VALUES (1, 1)
INSERT INTO Catalogue VALUES (2, 1)
INSERT INTO Catalogue VALUES (3, 2)
INSERT INTO Catalogue VALUES (4, 1)

----------------------
--Clustered Index Scan
----------------------
SELECT * 
FROM Kid
WHERE [Name] LIKE '%y'

----------------------
--Clustered Index Seek
----------------------
SELECT K.NumberOfGroups
FROM Kindergarten K
WHERE K.id > 3

SELECT ToyID
FROM Kid
WHERE Id < 20

-------------------------
--NonClustered Index Scan
-------------------------
SELECT *
FROM Kid
ORDER BY ToyID

-------------------------
--NonClustered Index Seek
-------------------------
SELECT ToyID
FROM Kid
WHERE ToyID BETWEEN 5 AND 15

------------
--Key Lookup
------------
SELECT Name
FROM Kid
WHERE ToyID = 3
ORDER BY ToyID

---------------------------
--Create NonClustered Index
---------------------------
SELECT *
FROM Kindergarten K
WHERE K.NumberOfGroups = 10

IF EXISTS ( SELECT name 
			FROM sys.indexes
			WHERE name = N'NCL_idx_Kinder_NG'
			)
	DROP INDEX NCL_idx_Kinder_NG ON Kindergarten
GO

CREATE NONCLUSTERED INDEX NCL_idx_Kinder_NG ON Kindergarten(NumberOfGroups)
GO

SELECT *
FROM Kindergarten K
WHERE K.NumberOfGroups = 10

GO
-----------------------------------
--View that joins at least 2 tables
-----------------------------------
DROP VIEW IF EXISTS EvenMaxl
GO

CREATE VIEW EvenMax
AS
	SELECT C.ID, MAX(Kg.NumberOfGroups) AS MaxEvenNo
	FROM Kid
	INNER JOIN Catalogue C ON C.KidID = Kid.ID
	INNER JOIN Kindergarten Kg ON C.KinderID = Kg.ID
	WHERE NumberOfGroups % 2 = 0
	GROUP BY C.ID
GO

SELECT *
FROM EvenMax