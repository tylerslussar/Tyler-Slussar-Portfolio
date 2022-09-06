#!/usr/bin/env python3

# ----------------------------------------------------------------------
# Student.py
# Tyler Slussar
# CS 493 12:30pm
# ----------------------------------------------------------------------

from __future__ import annotations
from typing import List, Dict, Tuple
import csv

class Student:

    FIRST = "first"
    LAST = "last"
    IDENTIFIER = "identifier"

    # ------------------------------------------------------------------

    def __init__(self, first: str = "", last: str="", identifier: str = ""):
        """
        :param first: first name for student
        :param last:  last name for student
        :param identifier: identifier for student
        """
        self.first: str = first
        self.last: str = last
        self.identifier: str = identifier

    # ------------------------------------------------------------------

    def __str__(self) -> str:
        """
        :return: string of first name last name and (identifier)
        """
        return f"{self.first} {self.last} ({self.identifier})"

    # ------------------------------------------------------------------

    def dictionary(self):
        """
        :return: dictionary (for writing CSV) mapping CSV header string to the string value
        """
        return { Student.FIRST: self.first, Student.LAST: self.last, Student.IDENTIFIER: self.identifier }


    # ------------------------------------------------------------------

    @staticmethod
    def fromDictionary(d: Dict[str, str]) -> Student:
        """
        create Student from dictionary (for reading from CSV)
        :param d: dictionary
        :return: Student using the info in the dictionary
        """
        first = d[Student.FIRST]
        last = d[Student.LAST]
        identifier = d[Student.IDENTIFIER]
        return Student(first, last, identifier)
    # ------------------------------------------------------------------

    def _tuple(self) -> Tuple[str, str, str]:
        """
        :return: tuple to use in comparison methods
        """
        return self.last, self.first, self.identifier

    # ------------------------------------------------------------------

    # comparison methods to sort by last name, then first name, then identifier

    def __lt__(self, other: Student) -> bool:
        return self._tuple() < other._tuple()

    def __le__(self, other: Student) -> bool:
        return self._tuple() <= other._tuple()

    def __gt__(self, other: Student) -> bool:
        return self._tuple() > other._tuple()

    def __ge__(self, other: Student) -> bool:
        return self._tuple() >= other._tuple()

    def __eq__(self, other: Student):
        return self._tuple() == other._tuple()

    def __ne__(self, other: Student):
        return self._tuple() != other._tuple()

    # ------------------------------------------------------------------

    @staticmethod
    def saveToCSV(students: List[Student], filename: str = "students.csv"):
        """
        save a list of Student objects to CSV file
        :param students: list of StudentDate objects to save
        :param filename: name of file to save to
        :return: None
        """
        with open(filename, 'w', newline='') as csvFile:
            fieldnames = [Student.FIRST, Student.LAST, Student.IDENTIFIER]
            writer = csv.DictWriter(csvFile, fieldnames=fieldnames)
            writer.writeheader()
            for s in sorted(students):
                writer.writerow(s.dictionary())

    # ------------------------------------------------------------------

    @staticmethod
    def readFromCSV(filename: str = "students.csv") -> List[Student]:
        """
        read a list of Student objects from CSV file
        :param filename: name of file to read from
        :return: list of Student objects read from file
        """
        student = []
        with open(filename, newline='') as csvFile:
            reader = csv.DictReader(csvFile)
            for row in reader:
                student.append(Student.fromDictionary(row))
        return student

# ----------------------------------------------------------------------ˆ

def main():
    students = []
    for (first, last, identifier) in [("Dave", "Reed", "42"), ("Joan", "Smith", "50"), ("Jane", "Jones", 55)]:
        d = { Student.FIRST: first, Student.LAST: last, Student.IDENTIFIER: identifier }
        students.append(Student.fromDictionary(d))

    Student.saveToCSV(students)
    students = Student.readFromCSV()
    for s in students:
        print(s)

# ----------------------------------------------------------------------

if __name__ == '__main__':
    main()


