USE [ITCompany]

INSERT INTO CEOs VALUES ('Ionut Corneliu', 20)
--no, primary key is identity
INSERT INTO CEOs VALUES (1, 'Ionut Corneliu', 20)
INSERT INTO CEOs VALUES ('Alex Manea', 29)
INSERT INTO CEOs VALUES ('Ionut Gingu', 34)
SELECT * FROM CEOs


INSERT INTO MainDepartments VALUES ('All activities', 16)
INSERT INTO MainDepartments VALUES ('PE Section', 19)
SELECT * FROM MainDepartments

INSERT INTO DepartmentDirectors(main_department_id) VALUES (1)
--no, because 19 is not a valid id from main departments
INSERT INTO DepartmentDirectors(main_department_id) VALUES (19)
INSERT INTO DepartmentDirectors VALUES ('Andreea Schiriac', 2)
INSERT INTO DepartmentDirectors VALUES ('Cristi Gabriel', 2)
SELECT * FROM DepartmentDirectors

UPDATE DepartmentDirectors 
SET [name] = 'Andreea Sista'
WHERE [name] LIKE 'S_h%'
SELECT * FROM DepartmentDirectors

UPDATE DepartmentDirectors 
SET [name] = 'Andreea Sista'
WHERE (main_department_id BETWEEN 2 AND 5)
SELECT * FROM DepartmentDirectors

INSERT INTO ProjectManagers VALUES (15, 2)
INSERT INTO ProjectManagers VALUES (7, 3)
INSERT INTO ProjectManagers VALUES (3, 4)
SELECT * FROM ProjectManagers

INSERT INTO Teams VALUES (132, 2)
INSERT INTO Teams VALUES (64, 3)
INSERT INTO Teams VALUES (100, 4)
SELECT * FROM Teams


INSERT INTO Employees VALUES (1)
INSERT INTO Employees VALUES (1)
INSERT INTO Employees VALUES (2)
INSERT INTO Employees VALUES (3)
SELECT * FROM Employees

INSERT INTO ProjectInfos VALUES ('Face Recognition with AI and Machine Learning')
INSERT INTO ProjectInfos VALUES ('Data mining')
INSERT INTO ProjectInfos VALUES ('Code testing')
INSERT INTO ProjectInfos VALUES ('Deep AI')
SELECT * FROM ProjectInfos

INSERT INTO ContractECs VALUES (1, 1, 'Finishes by the deadline')
INSERT INTO ContractECs VALUES (1, 2, 'Keeps the informations secret')
INSERT INTO ContractECs VALUES (4, 2, 'Works hard')
INSERT INTO ContractECs VALUES (7, 3, 'Detects bugs')
SELECT * FROM ContractECs

UPDATE ContractECs
SET constraints = 'Does not make the informations public'
WHERE constraints LIKE '%secret%'
SELECT * FROM ContractECs

INSERT INTO Breaks VALUES(10)
INSERT INTO Breaks VALUES(30)
INSERT INTO Breaks VALUES(60)
INSERT INTO Breaks VALUES(50)
INSERT INTO Breaks VALUES(80)
SELECT * FROM Breaks

UPDATE Breaks
SET minutes_taken = 45
WHERE minutes_taken >= 60
SELECT @@SPID AS 'ID', SYSTEM_USER AS 'Login Name', USER AS 'User Name' 
UPDATE Breaks
SET minutes_taken = 45
WHERE minutes_taken IS NULL OR minutes_taken IN (40,60,80)
SELECT * FROM Breaks

DELETE FROM Breaks
WHERE minutes_taken >=40 AND minutes_taken <50
SELECT * FROM Breaks

INSERT INTO WorkTimes VALUES(2, 1, 8)
--no break id = 3
INSERT INTO WorkTimes VALUES(3, 3, 10)
INSERT INTO WorkTimes VALUES(6, 2, 12)
INSERT INTO WorkTimes VALUES(3, 1, 7)
INSERT INTO WorkTimes VALUES(4, 5, 11)
INSERT INTO WorkTimes VALUES(5, 5, 4)
INSERT INTO WorkTimes VALUES(7, 2, 5)
SELECT * FROM WorkTimes

DELETE FROM WorkTimes
WHERE break_id IN (3,4,5) OR break_id BETWEEN 8 AND 10
SELECT * FROM WorkTimes

INSERT INTO Desks VALUES (1, 61)
INSERT INTO Desks VALUES (2, 32)
SELECT * FROM Desks

INSERT INTO Computers VALUES (1, 'Linux', 1)
INSERT INTO Computers VALUES (2, 'Windows', 2)
INSERT INTO Computers VALUES (3, 'Kali', 2)
SELECT * FROM Computers

DELETE FROM Computers
WHERE operating_system LIKE '%K__%' OR operating_system = 'Ubuntu'
SELECT * FROM Computers

--the CEOs that are younger than 25 or their first name is 'Ionut' ordered by age descendently
SELECT * 
FROM CEOs
WHERE age <=25 OR [name] LIKE '%Ionut%'
ORDER BY age DESC

SELECT * 
FROM CEOs
WHERE age <=25 
UNION
SELECT * 
FROM CEOs
WHERE [name] LIKE '%Ionut%'
ORDER BY age DESC

--the projectInfos that have their id an odd number an contain 'AI' in their name and another area
SELECT * 
FROM ProjectInfos
WHERE id % 2 = 1 AND description_of_project IN 
	(SELECT P.description_of_project
	FROM ProjectInfos P
	WHERE P.description_of_project LIKE '%AI%___%') --___ stand for 'and' because we need another area

SELECT * 
FROM ProjectInfos
WHERE id % 2 = 1
INTERSECT
SELECT * 
FROM ProjectInfos
WHERE description_of_project LIKE '%AI%___%'

--the employees and their constraints that have their project id different than their own id EXCEPT the ones that do not divide exaclty
SELECT CE.employee_id AS Employee, CE.constraints AS [Constraint]
FROM ContractECs CE
WHERE CE.employee_id <> CE.project_info_id AND CE.employee_id NOT IN 
	(SELECT CEE.employee_id
	FROM ContractECs CEE
	WHERE CEE.employee_id % CEE.project_info_id = 1)

SELECT employee_id AS Employee, constraints AS [Constraint]
FROM ContractECs
WHERE employee_id <> project_info_id 
EXCEPT
SELECT employee_id AS Employee, constraints AS [Constraint]
FROM ContractECs
WHERE employee_id % project_info_id = 1


SELECT * FROM Teams,Desks,Computers
--all different operating systems running on each computer of all teams
SELECT DISTINCT C.operating_system
FROM Computers C
INNER JOIN Desks D ON D.team_id = C.desk_id
INNER JOIN Teams T ON T.id = D.team_id

--first 2 teams ordered by their number of employees together with their workspaces
SELECT TOP 2 *
FROM Teams C
LEFT OUTER JOIN Desks D ON D.team_id = C.id	
ORDER BY C.no_of_employees

--first 50% of the contracts toghether with corresponding project informations sorted descendently by their project id
SELECT TOP 50 PERCENT *
FROM ContractECs CE
RIGHT JOIN ProjectInfos P ON CE.project_info_id = P.id
ORDER BY P.id DESC

SELECT * FROM Employees
SELECT * FROM ContractECs
SELECT * FROM ProjectInfos

--all employees that had a break or not and all projects associated to a employee;
SELECT DISTINCT *
FROM Employees E
FULL JOIN ContractECs CE ON CE.employee_id = E.id
FULL JOIN ProjectInfos P ON CE.project_info_id = P.id
FULL JOIN WorkTimes W ON W.employee_id = E.id
FULL JOIN Breaks B ON B.id = W.break_id

--the employees' id increased by 5 and their constraint if they belong to a team that has id between 10 and 99 or is 2 or 4
SELECT (C.employee_id + 5) AS Employee, C.constraints
FROM ContractECs C
WHERE C.employee_id IN
	(SELECT E.id
	FROM Employees E
	WHERE E.team_id IN 
		(SELECT T.id
		FROM Teams T
		WHERE (T.no_of_employees >=10 AND T.no_of_employees <100) OR (T.project_manager_id % 2 = 0 OR T.project_manager_id < 5)))

--the name of department directors that have their main activity Production Engineering
SELECT D.name--, MD.activity
FROM DepartmentDirectors D--, MainDepartments MD
WHERE D.main_department_id IN -----------question here
	(SELECT M.id
	FROM MainDepartments M
	WHERE M.activity LIKE '%PE%')


--the ids, number of employees divided by 2 and their project if their workspace have at least 50 computers, but not 60, 70 or 80
SELECT T.id, (T.no_of_employees/2) AS Employees, T.project_manager_id AS Project
FROM Teams T
WHERE EXISTS 
	(SELECT *
	FROM Desks D
	WHERE (D.number_of_pcs > 50 AND D.number_of_pcs NOT IN (60,70,80)) AND T.id = D.team_id)

	SELECT * FROM MainDepartments
	SELECT * FROM CEOs

--the name of the CEOs that have some department associated and their age five years ago if their activity is not about software nor gaming
SELECT C.name, C.age - 5 as Age
FROM CEOs C
WHERE EXISTS
	(SELECT *
	FROM MainDepartments M
	WHERE M.ceo_id = C.id AND (M.activity NOT LIKE '%Software%' OR M.activity NOT LIKE 'Gaming'))

--the constraints of employees that have their project id different than their own id EXCEPT the ones that do not divide exaclty
SELECT A.[Constraint]
FROM 
	(SELECT CE.employee_id AS Employee, CE.constraints AS [Constraint]
	FROM ContractECs CE
	WHERE CE.employee_id <> CE.project_info_id AND CE.employee_id NOT IN 
		(SELECT CEE.employee_id
		FROM ContractECs CEE
		WHERE CEE.employee_id % CEE.project_info_id = 1)) A

--the team id and the employees that have id between 2 and 5
SELECT A.team_id, A.id --DISTINCT BY team.id
FROM 
	(SELECT * 
	FROM Employees E
	WHERE E.id BETWEEN 2 AND 5) A

--all employees that have team id greater than all other employees' team id with their id less than 8
SELECT * 
FROM Employees E
WHERE E.team_id>ALL
	(SELECT EM.team_id
	FROM Employees EM
	WHERE EM.id < 8)

SELECT * 
FROM Employees E
WHERE E.team_id>
	(SELECT MAX(EM.team_id)
	FROM Employees EM
	WHERE EM.id < 8)

--print the work time of the employees that have their id less than any of the breaks' id with minutes greater than 20
SELECT W.work_time
FROM WorkTimes W
WHERE W.break_id<ANY
	(SELECT B.id
	FROM Breaks B
	WHERE B.minutes_taken > 20)

SELECT W.work_time
FROM WorkTimes W
WHERE W.break_id<
	(SELECT MAX(B.id)
	FROM Breaks B
	WHERE B.minutes_taken > 20)

--the name of department directors that have all units under their command
SELECT D.name
FROM DepartmentDirectors D
WHERE D.main_department_id = ANY
	(SELECT M.id
	FROM MainDepartments M
	WHERE M.activity LIKE '%All%')

SELECT D.name
FROM DepartmentDirectors D
WHERE D.main_department_id IN
	(SELECT M.id
	FROM MainDepartments M
	WHERE M.activity LIKE '%All%')

--the number of teams of the project managers that do not have their director with 'a' in their name
SELECT PM.no_of_teams
FROM ProjectManagers PM
WHERE PM.department_director_id NOT IN
	(SELECT DD.id
	FROM DepartmentDirectors DD
	WHERE DD.name LIKE '%a%')

SELECT PM.no_of_teams
FROM ProjectManagers PM
WHERE PM.department_director_id <> ALL
	(SELECT DD.id
	FROM DepartmentDirectors DD
	WHERE DD.name LIKE '%a%')

--the team ids with their corresponding number of employees
SELECT E.team_id, COUNT(DISTINCT E.id) AS 'Number Of Employees In Team'
FROM Employees E
GROUP BY E.team_id

--the operating systems and the average number of computers of each type of OS that have at least 50 as average
SELECT C.operating_system, AVG(D.number_of_pcs) AS 'Average Computers'
FROM Computers C
INNER JOIN Desks D ON D.team_id = C.id
GROUP BY C.operating_system
HAVING AVG(D.number_of_pcs) > 50

--the employees' ids and their project description if they belong to even team ids
SELECT C.employee_id, P.description_of_project
FROM ContractECs C 
LEFT JOIN ProjectInfos P ON C.project_info_id = P.id
GROUP BY C.employee_id, P.description_of_project
HAVING
	C.employee_id IN
		(SELECT E.id
		FROM Employees E
		WHERE E.team_id % 2 = 0)

--the employees' id and their total break time if the employee id is greater than any of the employees id that belong to team 1
SELECT W.employee_id, SUM(B.minutes_taken) AS 'Total break time'
FROM WorkTimes W
FULL JOIN Breaks B ON B.id = W.break_id
GROUP BY W.employee_id
HAVING W.employee_id > ANY 
	(SELECT E.id
	FROM Employees E
	WHERE E.team_id = 1)

SELECT * from CEOs
SELECT * from MainDepartments
SELECT * from DepartmentDirectors
SELECT * from ProjectManagers
SELECT * from Teams
SELECT * from Employees
SELECT * from WorkTimes
SELECT * from Breaks


--BONUS
--For every CEO aged between 20 and 50 years and with their name starting with “A” or “I” print its name
--and the total time of real work done by all their employees. This means, all worked hours from which we subtract their breaks.
SELECT C.name, (SUM(W.work_time)*60 - SUM(B.minutes_taken))/60 AS RealWork
			--RealWork -- multiply worked hours with 60 to get minutes, subtract break minutes, divide to 60 to get real work hours
FROM CEOs C
INNER JOIN MainDepartments MD ON C.id = MD.ceo_id
INNER JOIN DepartmentDirectors DD ON DD.main_department_id = MD.id
INNER JOIN ProjectManagers PM ON PM.department_director_id = DD.id
INNER JOIN Teams AS T ON T.project_manager_id = PM.id
INNER JOIN Employees E ON E.team_id = T.id
INNER JOIN WorkTimes W ON W.employee_id = E.id
INNER JOIN Breaks B ON B.id = W.break_id
--inner join on all this tables to get to the breaks table
GROUP BY C.name
HAVING EXISTS
	(SELECT *
	FROM CEOs CE
	WHERE CE.age BETWEEN 20 AND 50 AND CE.name IN
		(SELECT A.name
		FROM 
			(SELECT *
			FROM CEOs
			WHERE CEOs.name LIKE '%A' OR CEOs.name LIKE '%I') A))