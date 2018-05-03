PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "WatchList" (
	`Title`	TEXT,
	`Presenter`	TEXT,
	`Minutes`	INTEGER,
	`Seconds`	INTEGER,
	`Likes`	INTEGER,
	`Link`	TEXT
);
INSERT INTO WatchList VALUES('Easy Programming','Ionut F',65,20,1,'www.mySite.ro');
INSERT INTO WatchList VALUES('Easy C++','Johnny',3,22,1500,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
CREATE TABLE IF NOT EXISTS "Repository" (
	`Title`	TEXT,
	`Presenter`	TEXT,
	`Minutes`	INTEGER,
	`Seconds`	INTEGER,
	`Likes`	INTEGER,
	`Link`	TEXT
);
INSERT INTO Repository VALUES('Easy C++','Johnny',3,22,1500,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy C--','Johny',5,59,10,'www.google.com');
INSERT INTO Repository VALUES('Easy C','Johnnie',1,4,150,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy Python','John',3,22,15,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy Java','Ionut',1,4,500,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy Info','Ionutz',5,59,100,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy OOP','Ion',3,22,1000,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy Everything','Mc John',1,4,1900,'http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf');
INSERT INTO Repository VALUES('Easy Programming','Ionut F',65,20,0,'www.mySite.ro');
COMMIT;
