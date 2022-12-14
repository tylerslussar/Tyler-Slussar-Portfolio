DROP DATABASE IF EXISTS projectDB;
CREATE DATABASE projectDB;
USE projectDB;

CREATE TABLE DEPARTMENT(
DName 	varchar(15) NOT NULL,
PRIMARY KEY(DName)
);

INSERT INTO DEPARTMENT VALUES('CS');
INSERT INTO DEPARTMENT VALUES('MATH');

CREATE TABLE STUDENT(
SID		INT(6)		NOT NULL,
Major 	VARCHAR(12) NOT NULL,
PRIMARY KEY(SID),
FOREIGN KEY(Major) REFERENCES DEPARTMENT(DName)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO STUDENT VALUES(123456, 'CS');

CREATE TABLE PROFESSOR(
FID  	INT(6) 		NOT NULL,
Works_for	VARCHAR(15) NOT NULL,
PRIMARY KEY(FID),
FOREIGN KEY(Works_for) REFERENCES DEPARTMENT(DName)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO PROFESSOR VALUES(234567, 'CS');

CREATE TABLE RESEARCH(
Title 	VARCHAR(50) NOT NULL,
PRIMARY KEY(Title)
);

INSERT INTO RESEARCH VALUES('Taste of Water');

CREATE TABLE SYMPOSIUM(
SymID 	INT(6)		NOT NULL,
Chair	INT(6) NOT NULL,
Chair_start_date DATE,
Award_winner VARCHAR(15) NOT NULL,
PRIMARY KEY(SymID),
FOREIGN KEY(Chair) REFERENCES PROFESSOR(FID)
ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(Award_winner) REFERENCES RESEARCH(Title)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO SYMPOSIUM VALUES(345678, 234567, '2021-04-18', 'Taste of Water');

CREATE TABLE MEETING(
Meeting_name VARCHAR(15)	NOT NULL,
SymID 		 INT(6)			NOT NULL,
PRIMARY KEY(Meeting_name, SymID),
FOREIGN KEY(SymID) REFERENCES SYMPOSIUM(SymID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO MEETING VALUES('MEETING 1', 345678);

CREATE TABLE STUDENT_MINOR(
DName 	VARCHAR(15) 	NOT NULL,
SID		INT(6) 		NOT NULL,
PRIMARY KEY(DName, SID),
FOREIGN KEY(DName) REFERENCES DEPARTMENT(DName)
ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(SID) REFERENCES STUDENT(SID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO STUDENT_MINOR VALUES('MATH', 123456);

CREATE TABLE WORKS_ON(
Title 	VARCHAR(15) 	NOT NULL,
SID     INT(6) 		NOT NULL,
PRIMARY KEY(Title, SID),
FOREIGN KEY(Title) REFERENCES RESEARCH(Title)
ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(SID) REFERENCES STUDENT(SID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO WORKS_ON VALUES('Taste of Water', 123456);

CREATE TABLE PHONE(
FID 	INT(6)		NOT NULL,
Phone_number INT(10) NOT NULL,
PRIMARY KEY(FID, Phone_number),
FOREIGN KEY(FID) REFERENCES PROFESSOR(FID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO PHONE VALUES(234567, 614234567);

CREATE TABLE RESEARCH_HAS(
Title	VARCHAR(15)		NOT NULL,
SymID 	INT(6)			NOT NULL,
PRIMARY KEY(Title, SymID),
FOREIGN KEY(Title) REFERENCES RESEARCH(Title)
ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(SymID) REFERENCES SYMPOSIUM(SymID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO RESEARCH_HAS VALUES('Taste of Water', 345678);

CREATE TABLE COMMITTEE(
FID		INT(6)		NOT NULL,
SymID 	INT(6) 		NOT NULL,
PRIMARY KEY(FID, SymID),
FOREIGN KEY(FID) REFERENCES PROFESSOR(FID)
ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(SymID) REFERENCES SYMPOSIUM(SymID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO COMMITTEE VALUES(234567, 345678);

CREATE TABLE SUPERVISE(
Title	VARCHAR(15) 	NOT NULL,
FID		INT (6)		NOT NULL,
PRIMARY KEY(Title, FID),
FOREIGN KEY(Title) REFERENCES RESEARCH(Title)
ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(FID) REFERENCES PROFESSOR(FID)
ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO SUPERVISE VALUES('Taste of Water', 234567);
