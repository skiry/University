USE TeaShop
DROP DATABASE ITCompany
CREATE DATABASE ITCompany
GO
USE [ITCompany]
GO

CREATE TABLE CEOs(
	id INT PRIMARY KEY IDENTITY,
	[name] VARCHAR(20),
	age INT NOT NULL
)

CREATE TABLE MainDepartments(
	id INT PRIMARY KEY IDENTITY,
	activity VARCHAR(50),
	ceo_id INT FOREIGN KEY REFERENCES CEOs
)

CREATE TABLE DepartmentDirectors(
	id INT PRIMARY KEY IDENTITY,
	[name] VARCHAR(20) DEFAULT 'Director',
	main_department_id INT FOREIGN KEY REFERENCES MainDepartments
)

CREATE TABLE ProjectManagers(
	id INT PRIMARY KEY IDENTITY,
	no_of_teams INT DEFAULT 0,
	department_director_id INT FOREIGN KEY REFERENCES DepartmentDirectors
)

CREATE TABLE Teams(
	id INT PRIMARY KEY IDENTITY,
	no_of_employees INT NOT NULL,
	project_manager_id INT FOREIGN KEY REFERENCES ProjectManagers
)

CREATE TABLE Employees(
	id INT PRIMARY KEY IDENTITY,
	team_id INT FOREIGN KEY REFERENCES Teams
)

CREATE TABLE ProjectInfos(
	id INT PRIMARY KEY IDENTITY,
	description_of_project VARCHAR(200)
)

CREATE TABLE ContractECs(
	employee_id INT FOREIGN KEY REFERENCES Employees(id),
	project_info_id INT FOREIGN KEY REFERENCES ProjectInfos(id),
	constraints VARCHAR(200),
	CONSTRAINT pk_Contract PRIMARY KEY(employee_id,project_info_id)
)

CREATE TABLE Breaks(
	id INT PRIMARY KEY IDENTITY,
	minutes_taken INT DEFAULT 0
)

CREATE TABLE WorkTimes(
	employee_id INT FOREIGN KEY REFERENCES Employees(id),
	break_id INT FOREIGN KEY REFERENCES Breaks(id),
	work_time INT DEFAULT 8 NOT NULL,
	CONSTRAINT pk_WT PRIMARY KEY(employee_id,break_id)
)

CREATE TABLE Desks(
	team_id INT FOREIGN KEY REFERENCES Teams(id),
	number_of_pcs INT NOT NULL,
	CONSTRAINT pk_Desk PRIMARY KEY(team_id)
)

CREATE TABLE Computers(
	id INT PRIMARY KEY,
	operating_system VARCHAR(20),
	desk_id INT FOREIGN KEY REFERENCES Desks
)