USE [ITCompany]
GO

DROP PROC IF EXISTS change_column
GO

CREATE PROCEDURE change_column
@table VARCHAR(25),
@column VARCHAR(20),
@type VARCHAR(20)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' ALTER COLUMN ' + QUOTENAME(@column) + @type

	EXECUTE sp_executesql @statement	
GO

DROP PROC IF EXISTS do_version_1
GO

CREATE PROCEDURE do_version_1
AS
	EXEC change_column 'MainDepartments', 'activity', 'VARCHAR(30)'
GO

do_version_1
GO

DROP PROC IF EXISTS undo_version_1
GO

CREATE PROCEDURE undo_version_1
AS
	EXEC change_column 'MainDepartments', 'activity', 'VARCHAR(25)'
GO

undo_version_1
GO

--done with the first version

DROP PROC IF EXISTS add_column
GO

CREATE PROCEDURE add_column
@table VARCHAR(25),
@column VARCHAR(20),
@type VARCHAR(40)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' ADD ' + @column + @type

	EXECUTE sp_executesql @statement	
GO

DROP PROC IF EXISTS do_version_2
GO

CREATE PROCEDURE do_version_2
AS
	EXEC add_column 'Servers', 'remote_control', ' CHAR(3)'
GO

do_version_2
GO


DROP PROC IF EXISTS remove_column
GO

CREATE PROCEDURE remove_column
@table VARCHAR(25),
@column VARCHAR(20)
AS   
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' DROP COLUMN ' + QUOTENAME(@column)
	EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS undo_version_2
GO

CREATE PROCEDURE undo_version_2
AS
	EXEC remove_column 'Servers', 'remote_control'
GO

undo_version_2
GO

SELECT C.name, D.definition 
FROM sys.columns AS C
JOIN sys.default_constraints AS D
  ON C.column_id = D.parent_column_id
  WHERE C.name LIKE 'touch%'
  ------------------------------------------------------------------------------------------
--done with the second version

DROP PROC IF EXISTS add_default
GO

CREATE PROCEDURE add_default
@table VARCHAR(25),
@column VARCHAR(20),
@constraint VARCHAR(30),
@value INT
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					'ADD CONSTRAINT ' + QUOTENAME(@constraint) + ' DEFAULT ' + CONVERT(VARCHAR(5), @value) + ' FOR ' + QUOTENAME(@column)

	EXECUTE sp_executesql @statement	
GO

DROP PROC IF EXISTS do_version_3
GO

CREATE PROCEDURE do_version_3
AS
	EXEC add_default 'Teams', 'no_of_employees', 'df_number', 5
GO

do_version_3
GO


DROP PROC IF EXISTS remove_default
GO

CREATE PROCEDURE remove_default
@table VARCHAR(25),
@constraint VARCHAR(20)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' DROP CONSTRAINT ' + QUOTENAME(@constraint)

	EXECUTE sp_executesql @statement	
GO

DROP PROC IF EXISTS undo_version_3
GO

CREATE PROCEDURE undo_version_3
AS
	EXEC remove_default 'Teams', 'df_number'
GO

undo_version_3
GO

--done with the third version

DROP PROC IF EXISTS add_primary
GO

CREATE PROCEDURE add_primary
@table VARCHAR(25),
@column VARCHAR(20),
@constraint VARCHAR(30)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' ADD CONSTRAINT ' + QUOTENAME(@constraint) + ' PRIMARY KEY (' + QUOTENAME(@column) + ')'
	EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS do_version_4
GO

CREATE PROCEDURE do_version_4
AS
	EXEC add_primary 'Servers', 'id', 'pk_id'
GO

do_version_4
GO


DROP PROC IF EXISTS remove_primary
GO

CREATE PROCEDURE remove_primary
@table VARCHAR(25),
@constraint VARCHAR(20)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' DROP CONSTRAINT IF EXISTS ' + QUOTENAME(@constraint)

	EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS undo_version_4
GO

CREATE PROCEDURE undo_version_4
AS
	EXEC remove_primary 'Servers', 'pk_id'
GO

undo_version_4
GO
--done with the fourth version

DROP PROC IF EXISTS add_candidate
GO

CREATE PROCEDURE add_candidate
@table VARCHAR(25),
@column VARCHAR(20),
@constraint VARCHAR(20)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' ADD CONSTRAINT ' + QUOTENAME(@constraint) + ' UNIQUE (' + QUOTENAME(@column) + ')'

	EXECUTE sp_executesql @statement	
GO

DROP PROC IF EXISTS do_version_5
GO

CREATE PROCEDURE do_version_5
AS
	EXEC add_candidate 'CEOs', 'name', 'unq_nm'
GO

do_version_5
GO


DROP PROC IF EXISTS remove_candidate
GO

CREATE PROCEDURE remove_candidate
@table VARCHAR(25),
@constraint VARCHAR(20)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) +
					' DROP CONSTRAINT ' + QUOTENAME(@constraint)

	EXECUTE sp_executesql @statement	
GO

DROP PROC IF EXISTS undo_version_5
GO

CREATE PROCEDURE undo_version_5
AS
	EXEC remove_candidate 'CEOs', 'unq_nm'
GO

undo_version_5
GO

--done with the fifth version

DROP PROCEDURE IF EXISTS add_foreign
GO

CREATE PROCEDURE add_foreign
@table VARCHAR(25),
@column VARCHAR(25),
@constraint VARCHAR(30),
@fktable VARCHAR(25),
@fkcolumn VARCHAR(25)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + 
						' ADD CONSTRAINT ' + QUOTENAME(@constraint) + ' FOREIGN KEY (' + QUOTENAME(@column) +
						') REFERENCES ' + QUOTENAME(@fktable) + '(' + QUOTENAME(@fkcolumn) + ')'

	EXECUTE sp_executesql @statement
GO

DROP PROCEDURE IF EXISTS do_version_6
GO

CREATE PROCEDURE do_version_6
AS
	EXECUTE add_foreign 'Servers', 'computer_id', 'fk_computers', 'Computers', 'id'
GO

do_version_6
GO

DROP PROCEDURE IF EXISTS remove_foreign
GO

CREATE PROCEDURE remove_foreign
@table VARCHAR(25),
@constraint VARCHAR(30)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + 
						' DROP CONSTRAINT IF EXISTS ' + QUOTENAME(@constraint)
	EXECUTE sp_executesql @statement
GO

DROP PROCEDURE IF EXISTS undo_version_6
GO

CREATE PROCEDURE undo_version_6
AS
	EXECUTE remove_foreign 'Servers', 'fk_computers'
GO

undo_version_6
GO

--done with the sixth version

DROP PROC IF EXISTS add_table
GO

CREATE PROCEDURE add_table
AS
	CREATE TABLE [Servers](
	id INT NOT NULL,
	max_connections SMALLINT,
	computer_id INT
	)
GO

DROP PROC IF EXISTS remove_table
GO

CREATE PROCEDURE remove_table
@table VARCHAR(20)
AS
	DECLARE @statement NVARCHAR(4000)
	SELECT @statement = 'DROP TABLE ' + QUOTENAME(@table)
	EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS do_version_7
GO

CREATE PROCEDURE do_version_7
AS
	EXEC remove_table 'Servers'
GO

do_version_7
GO


DROP PROC IF EXISTS undo_version_7
GO

CREATE PROCEDURE undo_version_7
AS
	EXEC add_table
GO

undo_version_7
GO

CREATE TABLE CurrentVersion(
	version_id INT CHECK(version_id BETWEEN 0 AND 7)
	)

GO

DROP PROCEDURE IF EXISTS getToVersion
GO

CREATE PROCEDURE getToVersion
@version_id INT
AS
	IF @version_id < 0 OR @version_id > 7
		BEGIN
			PRINT('Unknown version id')
			RETURN 
		END

	DECLARE @current_version INT
	SELECT TOP 1 @current_version = CV.version_id
	FROM CurrentVersion CV

	IF @current_version = @version_id
		BEGIN
			PRINT('Already at desired version')
			RETURN 
		END

	DECLARE @statement NVARCHAR(4000)
	WHILE @version_id > @current_version
		BEGIN
			SET @current_version = @current_version + 1
			SELECT @statement = 'do_version_' + CONVERT(VARCHAR(10),@current_version)
			EXECUTE sp_executesql @statement
		END

	WHILE @version_id < @current_version
		BEGIN
			SELECT @statement = 'undo_version_' + CONVERT(VARCHAR(10),@current_version)
			EXECUTE sp_executesql @statement
			SET @current_version = @current_version - 1
		END

	UPDATE CurrentVersion
	SET version_id = @version_id
GO

getToVersion 0
DELETE FROM CurrentVersion
INSERT INTO CurrentVersion VALUES (0)
SELECT * FROM CurrentVersion