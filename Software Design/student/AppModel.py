#!/usr/bin/env python3

# ----------------------------------------------------------------------
# AppModel.py
# Tyler Slussar
# CS 493 12:30pm
# ----------------------------------------------------------------------

from typing import List, Tuple, Optional
from Student import Student
from AttendanceDate import AttendanceDate
from StudentDate import StudentDate

class AppModel:

    # ------------------------------------------------------------------

    def __init__(self):
        """
        class for providing convenient access to the data
        """
        # map each student's ID to the Student with that ID
        self._students: [str, Student] = {}
        # map each isoString date to the AttendanceDate for that date
        self._attendanceDates: [str, AttendanceDate] = {}
        # map tuple of studentID and isoString for the date to the StudentDate
        self._studentDates: [(str, str), StudentDate] = {}
        # map studentID to the StudentDates for that student
        self._datesForStudent: [str, StudentDate] = {}

    # ------------------------------------------------------------------

    def loadData(self):
        """
        load all the data from CSV files
        :return: None
        """
        # for each of the dictionaries, the specific class will load in the data and place them in
        # instance variable for this class
        self._attendanceDates = {}
        dates = AttendanceDate.readFromCSV()
        for d in dates:
            self._attendanceDates[d.date.isoString()] = d

        self._students = {}
        students = Student.readFromCSV()
        for s in students:
            self._students[s.identifier] = s

        self._studentDates = {}
        self._datesForStudent = {}
        for s in students:
            self._datesForStudent[s.identifier] = []
        studentDates = StudentDate.readFromCSV()
        for sd in studentDates:
            self._studentDates[(sd.studentID, sd.date)] = sd
            # datesForStudents holds the student ID and then the StudentDates in a list, that is why append is needed
            self._datesForStudent[sd.studentID].append(sd)


    # ------------------------------------------------------------------

    def saveData(self):
        """
        save all the data to CSV files
        :return: None
        """
        # takes the values and makes them a list and then saves to CSV
        students = list(self._students.values())
        Student.saveToCSV(students)

        dates = list(self._attendanceDates.values())
        AttendanceDate.saveToCSV(dates)

        studentDates = list(self._studentDates.values())
        StudentDate.saveToCSV(studentDates)




    # ------------------------------------------------------------------

    def addDate(self, attendanceDate: AttendanceDate, statusValue: str = "Absent") -> bool:
        """
        add the specified date and assign the specified statusValue to each student for that date
        :param attendanceDate: date to add
        :param statusValue: status value to assign to each student for that date
        :return: True if date added, False if date already exists
        """
        dates = list(self._attendanceDates.keys())
        # goes through each date and if the date is already there, it returns false
        for d in dates:
            if d == attendanceDate.date.isoString():
                return False

        # adding the new date into the instance variable dictionary
        self._attendanceDates[attendanceDate.date.isoString()] = attendanceDate
        students = list(self._students.keys())
        # creates a new student date per each student
        for s in students:
            sd = StudentDate(s, attendanceDate.date, statusValue)
            self._studentDates[(sd.studentID, sd.date.isoString())] = sd

    # ------------------------------------------------------------------

    def setStatus(self, attendanceDate: AttendanceDate, student: Student, statusValue: str):
        """
        for the specified date and student, sets the status for that student and date to statusValue
        :param attendanceDate: the AttendanceDate to set the status for
        :param student: the Student to set the status for
        :param statusValue: the status value for that student and date
        :return: None
        """
        # sets the status
        date = attendanceDate.date
        studentID = student.identifier
        currentStudentDate = self._studentDates[(studentID, date)]
        currentStudentDate.setStatus(statusValue)

    # ------------------------------------------------------------------

    def studentsAndDates(self, attendanceDate, defaultStatusForMissing: str = "Absent") -> List[Tuple[Student, StudentDate]]:
        """
        :param attendanceDate: date to get statuses for each student
        :param defaultStatusForMissing: default status to use for any student that does not have a status for that date
        :return: list of tuples; each tuple is a student and the StudentDate for that student and the specified date;
        the list is sorted by Student (last name, then first name, then identifier)
        """
        date = attendanceDate.date.isoString()
        studentsID = list(self._students.keys())
        returnList =[]

        # this will go through each student and allow you to put in their status
        for s in studentsID:

            student = self._students[s]
            sd = self._studentDates[(s, date)]
            sd.setStatus(defaultStatusForMissing)
            returnList = [student, sd]

            val = input(f"enter status for {student} [Present]: ")
            if val == "A":
                sd.setStatus("Absent")
            # this sets it as present if you just hit return
            elif val == "":
                sd.setStatus("Present")
            elif val == "L":
                sd.setStatus("Late")
            else:
                sd.setStatus(val)
        return returnList
# ----------------------------------------------------------------------
