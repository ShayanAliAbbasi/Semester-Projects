CREATE DATABASE PortalDB;

USE PortalDB;

CREATE TABLE Departments
(
	dep_name VARCHAR(50) NOT NULL PRIMARY KEY,
	hod_name VARCHAR(50) NOT NULL,
	publications INT,
	total_subjects INT
);

CREATE TABLE Semesters
(
	sem_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	sem_num INT NOT NULL CHECK (sem_num > 0 AND sem_num < 9),
	sem_session VARCHAR(20) NOT NULL,
	[start_date] DATE,
	num_courses INT
);	

CREATE TABLE Classes
(
	class_id INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
	class_name VARCHAR(50) NOT NULL,
	dep_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Departments(dep_name),
	section CHAR NOT NULL
);

CREATE TABLE Courses
(
	course_id INT NOT NULL IDENTITY(1,1),
	course_name VARCHAR(50) NOT NULL PRIMARY KEY,
	dep_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Departments(dep_name),
	sem_id INT FOREIGN KEY REFERENCES Semesters(sem_id),
	credit_hours INT NOT NULL
);

CREATE TABLE Students
(
	roll_no VARCHAR(20) NOT NULL PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	father_name VARCHAR(50) NOT NULL,
	cgpa FLOAT NOT NULL,
	[session] VARCHAR(10) NOT NULL,
	section CHAR NOT NULL,
	has_image BIT NOT NULL,
	gender CHAR,
	sem_id INT NOT NULL FOREIGN KEY REFERENCES Semesters(sem_id),
	dep_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Departments(dep_name),
);

CREATE TABLE Student_Login_Details
(
	login_id INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	[password] VARCHAR(100) NOT NULL
);

CREATE TABLE Student_Contact_Details
(
	cont_id INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	email_address VARCHAR(100) NOT NULL,
	postal_address VARCHAR(100),
	phone_num1 BIGINT,
	phone_num2 BIGINT
);

CREATE TABLE Student_Attendence_Details
(
	att_id INT NOT NULL PRIMARY KEY IDENTITY(1, 1),
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	course_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Courses(course_name),
	sem_id INT NOT NULL FOREIGN KEY REFERENCES Semesters(sem_id),
	present BIT NOT NULL,
	[date] DATE NOT NULL
);

CREATE TABLE Student_Academic_Details
(
	acd_id INT NOT NULL PRIMARY KEY IDENTITY(1, 1),
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	course_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Courses(course_name),
	sem_id INT NOT NULL FOREIGN KEY REFERENCES Semesters(sem_id),
	grade VARCHAR(2) NOT NULL 
);

CREATE TABLE Student_Financial_Details
(
	fin_id INT NOT NULL PRIMARY KEY IDENTITY(1, 1),
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	sem_id INT NOT NULL FOREIGN KEY REFERENCES Semesters(sem_id),
	total_fee INT NOT NULL,
	paid_fee INT NOT NULL,
	scholorship INT
);

CREATE TABLE Student_Library_Details
(
	lib_id INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	book_name VARCHAR(50) NOT NULL,
	issue_date DATETIME NOT NULL,
	due_date DATETIME NOT NULL,
	returned BIT NOT NULL
);

CREATE TABLE Student_Transfered_Courses
(
	trans_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	course_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Courses(course_name),
	grade varchar(2) NOT NULL,
	trans_from VARCHAR(50)
);

CREATE TABLE Student_Enrollment_Details 
(
	enroll_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	roll_no VARCHAR(20) NOT NULL FOREIGN KEY REFERENCES Students(roll_no),
	sem_id INT NOT NULL FOREIGN KEY REFERENCES Semesters(sem_id),
	course_name VARCHAR(50) FOREIGN KEY REFERENCES Courses(course_name)
);

CREATE TABLE Teachers
(
	teacher_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	salary INT,
	dep_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Departments(dep_name)
);

CREATE TABLE Teacher_Courses 
(
	teach_course_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	teacher_id INT NOT NULL FOREIGN KEY REFERENCES Teachers(teacher_id),
	course_name VARCHAR(50) NOT NULL FOREIGN KEY REFERENCES Courses(course_name)
);

CREATE TABLE Teacher_Classes
(
	teach_class_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	teacher_id INT NOT NULL FOREIGN KEY REFERENCES Teachers(teacher_id),
	class_id INT NOT NULL FOREIGN KEY REFERENCES Classes(class_id)
);

CREATE TABLE Student_Fine_Details
(
	fine_id INT NOT NULL IDENTITY(1, 1) PRIMARY KEY,
	roll_no VARCHAR(20) FOREIGN KEY REFERENCES Students(roll_no),
	amount INT NOT NULL,
	reason VARCHAR(250),
	teacher_id INT FOREIGN KEY REFERENCES Teachers(teacher_id),
	paid BIT NOT NULL
);
