CREATE DATABASE shutdown;
USE shutdown;
CREATE TABLE nurses (
    nurse_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL
);

INSERT INTO nurses (name) VALUES
('Nurse 1'),
('Nurse 2'),
('Nurse 3'),
('Nurse 4');
CREATE TABLE patients (
    patient_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL,
    room_no INT NOT NULL,
    bed_no INT NOT NULL,
    nurse_id INT,
    FOREIGN KEY (nurse_id) REFERENCES nurses(nurse_id)
);
INSERT INTO patients (name, room_no, bed_no, nurse_id) VALUES
('Ashu', 1, 1, 1),
('Hargun', 1, 2, 1),
('Disha', 1, 3, 2),
('Jai', 1, 4, 2),
('Ashish', 2, 1, 3),
('Vivek', 2, 2, 3),
('Varda', 2, 3, 4),
('Jayanti', 2, 4, 4);

