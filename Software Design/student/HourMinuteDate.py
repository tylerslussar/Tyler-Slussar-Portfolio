#!/usr/bin/env python3

# ----------------------------------------------------------------------
# HourMinuteDate.py
# Dave Reed
# 06/06/2020
# ----------------------------------------------------------------------

from __future__ import annotations
from typing import Tuple

class HourMinuteDate:

    # ------------------------------------------------------------------

    def __init__(self, year: int, month: int, day: int, hour: int = 0, minute: int = 0):
        """
        class for representing a date including the month, day, year, hour, and minute
        :param year: year for the date
        :param month: month for the date
        :param day: day of month for the date
        :param hour: hour for the date
        :param minute: minute for the date
        """
        self.year = year
        self.month = month
        self.day = day
        self.hour = hour
        self.minute = minute

    # ------------------------------------------------------------------

    def __str__(self) -> str:
        """
        :return: US form of date mm/dd/yy HH:MM
        """
        return f"{self.month:02}/{self.day:02}/{self.year} {self.hour:02}:{self.minute:02}"

    def isoString(self) -> str:
        """
        :return: ISO date form YYYY-mm-dd HH:MM"
        """
        return f"{self.year}-{self.month:02}-{self.day:02} {self.hour:02}:{self.minute:02}"

    # ------------------------------------------------------------------

    @staticmethod
    def fromString(s: str) -> HourMinuteDate:
        """
        create HourMinuteDate from US form of date (inverse of __str__)
        :param s: string representing the date
        :return: HourMinuteDate for the string
        """
        try:
            date, time = s.split()
            date = date.split("/")
            time = time.split(":")
            m, d, y = [int(x) for x in date]
            hour, minute = [int(x) for x in time]
            return HourMinuteDate(y, m, d, hour, minute)
        except:
            raise ValueError(f"invalid date format: {s}")

    @staticmethod
    def fromIsoString(s: str) -> HourMinuteDate:
        """
        create HourMinuteDate from ISO form of date (inverse of isoString method)
        :param s: string representing the date
        :return: HourMinuteDate for the string
        """
        try:
            date, time = s.split()
            date = date.split("-")
            time = time.split(":")
            y, m, d = [int(x) for x in date]
            hour, minute = [int(x) for x in time]
            return HourMinuteDate(y, m, d, hour, minute)
        except:
            raise ValueError(f"invalid ISO date format: {s}")

    # ------------------------------------------------------------------

    def _tuple(self) -> Tuple[int, int, int, int, int]:
        """
        :return: tuple representation for use in comparison methods
        """
        return self.year, self.month, self.day, self.hour, self.minute

    # ------------------------------------------------------------------

    # comparison methods to compare two dates

    def __lt__(self, other: HourMinuteDate) -> bool:
        return self._tuple() < other._tuple()

    def __le__(self, other: HourMinuteDate) -> bool:
        return self._tuple() <= other._tuple()

    def __gt__(self, other: HourMinuteDate) -> bool:
        return self._tuple() > other._tuple()

    def __ge__(self, other: HourMinuteDate) -> bool:
        return self._tuple() >= other._tuple()

    def __eq__(self, other: HourMinuteDate) -> bool:
        return self._tuple() == other._tuple()

    def __ne__(self, other: HourMinuteDate) -> bool:
        return self._tuple() != other._tuple()

    # ------------------------------------------------------------------

# ----------------------------------------------------------------------

def main():
    d = HourMinuteDate(2020, 6, 7)
    print(d)
    print(d.isoString())
    d = HourMinuteDate.fromIsoString("2020-06-08 08:05")
    print(d)
    d = HourMinuteDate.fromString("6/8/2020 08:05")
    print(d.isoString())

# ----------------------------------------------------------------------

if __name__ == '__main__':
    main()
