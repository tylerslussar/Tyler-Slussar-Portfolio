#!/usr/bin/env python3

# ----------------------------------------------------------------------
# AttendanceDate.py
# Dave Reed
# 06/08/2020
# ----------------------------------------------------------------------

from __future__ import annotations
from typing import List, Dict
import csv

from HourMinuteDate import HourMinuteDate

class AttendanceDate:

    # constants for CSV file headers
    DATE = "date"
    NOTE = "note"

    # ------------------------------------------------------------------

    def __init__(self, date: HourMinuteDate, note: str = ""):
        """
        store a date and a note with information such as what was done that day
        :param date: HourMinuteDate specifying the date
        :param note: info for the date
        """
        self.date = date
        self.note = note

    # ------------------------------------------------------------------

    # comparision operators to sort by the date

    def __lt__(self, other: AttendanceDate) -> bool:
        return self.date < other.date

    def __le__(self, other: AttendanceDate) -> bool:
        return self.date <= other.date

    def __gt__(self, other: AttendanceDate) -> bool:
        return self.date > other.date

    def __ge__(self, other: AttendanceDate) -> bool:
        return self.date >= other.date

    def __eq__(self, other: AttendanceDate) -> bool:
        return self.date == other.date

    def __ne__(self, other: AttendanceDate) -> bool:
        return self.date != other.date

    # ------------------------------------------------------------------

    def __str__(self) -> str:
        """
        :return: string showing the date and note with format: {date} : {note}
        """
        return f"{self.date} : {self.note}"

    # ------------------------------------------------------------------

    def dictionary(self) -> Dict[str, str]:
        """
        :return: dictionary (for writing CSV) mapping CSV header string to the string value
        """
        return { AttendanceDate.DATE: self.date.isoString(), AttendanceDate.NOTE: self.note }

    # ------------------------------------------------------------------

    @staticmethod
    def fromDictionary(d: Dict[str, str]):
        """
        create AttendanceDate from dictionary (for reading from CSV)
        :param d: dictionary
        :return: AttendanceDate using the info in the dictionary
        """
        date = HourMinuteDate.fromIsoString(d[AttendanceDate.DATE])
        note = d[AttendanceDate.NOTE]
        return AttendanceDate(date, note)

    # ------------------------------------------------------------------

    @staticmethod
    def saveToCSV(dates: List[AttendanceDate], filename: str = "dates.csv"):
        """
        save a list of AttendanceDate objects to CSV file
        :param dates: list of StudentDate objects to save
        :param filename: name of file to save to
        :return: None
        """
        with open(filename, 'w', newline='') as csvFile:
            fieldnames = [AttendanceDate.DATE, AttendanceDate.NOTE]
            writer = csv.DictWriter(csvFile, fieldnames=fieldnames)
            writer.writeheader()
            for d in sorted(dates):
                writer.writerow(d.dictionary())

    # ------------------------------------------------------------------

    @staticmethod
    def readFromCSV(filename: str = "dates.csv") -> List[AttendanceDate]:
        """
        read a list of AttendanceDate objects from CSV file
        :param filename: name of file to read from
        :return: list of AttendanceDate objects read from file
        """
        dates = []
        with open(filename, newline='') as csvFile:
            reader = csv.DictReader(csvFile)
            for row in reader:
                dates.append(AttendanceDate.fromDictionary(row))
        return dates

# ----------------------------------------------------------------------

def main():
    dates = []
    for (d, n) in (("6/7/2020 9:00", "note for June 7"), ("6/8/2020 9:00", "note for June 8")):
        date = HourMinuteDate.fromString(d)
        ad = AttendanceDate(date, n)
        dates.append(ad)
    AttendanceDate.saveToCSV(dates)
    dates = AttendanceDate.readFromCSV()
    for d in dates:
        print(d)


# ----------------------------------------------------------------------

if __name__ == '__main__':
    main()
