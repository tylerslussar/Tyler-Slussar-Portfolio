#!/usr/bin/env python3

# ----------------------------------------------------------------------
# StudentDate.py
# Tyler Slussar
# CS 493 12:30pm
# ----------------------------------------------------------------------

from __future__ import annotations
from typing import List, Dict
import csv

from HourMinuteDate import HourMinuteDate

class StudentDate:

    # constants for CSV file headers
    DATE = "date"
    STUDENT_ID = "studentID"
    STATUS = "status"

    # ------------------------------------------------------------------

    def __init__(self, studentID: str, date: HourMinuteDate, status: str = "Absent"):
        """
        status for a student for a given date
        :param studentID: the student it is for
        :param date: the date it is for
        :param status: the attendance status for the student for the date
        """
        self.studentID = studentID
        self.date = date
        self._status = status

    # ------------------------------------------------------------------

    def status(self) -> str:
        """
        :return: the attendance status
        """
        return self._status

    # ------------------------------------------------------------------

    def setStatus(self, status: str):
        """
        set the status for the student for the date
        :param status: status to use
        :return: None
        """
        self._status = status

    # ------------------------------------------------------------------

    # comparison operators so sort by date and then student ID

    def __lt__(self, other: StudentDate) -> bool:
        return (self.date, self.studentID) < (other.date, other.studentID)

    def __le__(self, other: StudentDate) -> bool:
        return (self.date, self.studentID) <= (other.date, other.studentID)

    def __gt__(self, other: StudentDate) -> bool:
        return (self.date, self.studentID) > (other.date, other.studentID)

    def __ge__(self, other: StudentDate) -> bool:
        return (self.date, self.studentID) >= (other.date, other.studentID)

    def __eq__(self, other: StudentDate) -> bool:
        return (self.date, self.studentID) == (other.date, other.studentID)

    def __ne__(self, other: StudentDate) -> bool:
        return (self.date, self.studentID) != (other.date, other.studentID)

    # ------------------------------------------------------------------

    def __str__(self) -> str:
        """
        :return: string showing the date, studentID and status
        """
        return f"{self.date} : {self.studentID} : {self.status()}"

    # ------------------------------------------------------------------

    def dictionary(self) -> Dict[str, str]:
        """
        :return: dictionary (for writing CSV) mapping CSV header string to the string value
        """
        return { StudentDate.STUDENT_ID: self.studentID, StudentDate.DATE: self.date, StudentDate.STATUS: self._status }
    # ------------------------------------------------------------------

    @staticmethod
    def fromDictionary(d: Dict[str, str]) -> StudentDate:
        """
        create StudentDate from dictionary (for reading from CSV)
        :param d: dictionary
        :return: StudentDate using the info in the dictionary
        """
        date = d[StudentDate.DATE]
        studentId = d[StudentDate.STUDENT_ID]
        status = d[StudentDate.STATUS]
        return StudentDate(studentId, date, status)

    # ------------------------------------------------------------------

    @staticmethod
    def saveToCSV(studentDates: List[StudentDate], filename: str = "studentDates.csv"):
        """
        save a list of StudentDate objects to CSV file
        :param studentDates: list of StudentDate objects to save
        :param filename: name of file to save to
        :return: None
        """
        with open(filename, 'w', newline= "") as csvFile:
            fieldnames = [StudentDate.STUDENT_ID, StudentDate.DATE, StudentDate.STATUS]
            writer = csv.DictWriter(csvFile, fieldnames=fieldnames)
            writer.writeheader()
            for s in studentDates:
                writer.writerow(s.dictionary())

    # ------------------------------------------------------------------

    @staticmethod
    def readFromCSV(filename: str = "studentDates.csv") -> List[StudentDate]:
        """
        read a list of StudentDate objects from CSV file
        :param filename: name of file to read from
        :return: list of StudentDate objects read from file
        """
        studentDates = []
        with open(filename, newline='') as csvFile:
            reader = csv.DictReader(csvFile)
            for row in reader:
                studentDates.append(StudentDate.fromDictionary(row))
            return studentDates

    # ------------------------------------------------------------------


# ----------------------------------------------------------------------

def main():
    dates = []
    for (d, sid, status) in (("6/7/2020 9:00", "123", "Late"), ("6/8/2020 9:00", "123", "Present"), ("6/7/2020 9:00", "456", "Present"), ("6/8/2020 9:00", "456", "Absent")):
        date = HourMinuteDate.fromString(d)
        sd = StudentDate(sid, date, status)
        dates.append(sd)
    StudentDate.saveToCSV(dates)
    dates = StudentDate.readFromCSV()
    for d in dates:
        print(d)

# ----------------------------------------------------------------------

if __name__ == '__main__':
    main()
