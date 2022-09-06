#!/usr/bin/env python3

# ----------------------------------------------------------------------
# takeAttendance.py
# Dave Reed
# 06/08/2020
# ----------------------------------------------------------------------

import time
from argparse import ArgumentParser

from HourMinuteDate import HourMinuteDate
from AppModel import AppModel
from AttendanceDate import AttendanceDate


# ----------------------------------------------------------------------

def main():
    parser = ArgumentParser(description='take attendance')
    parser.add_argument('-d', '--date', dest='date', default=None, type=str,
                        help='''take directory for the specified date, defaults to current date rounded to nearest hour
                        ''')
    parser.add_argument('-n', '--note', dest='note', default=None,
                        help='''note for the day
                        ''')

    options = parser.parse_args()
    date = options.date
    # if no date specified use, nearest 30 minutes
    if date is None:
        year, month, day, hour, minute = time.localtime()[:5]
        if minute > 30:
            # FIXME: this will not work correctly if after 11:30PM
            hour += 1
        minute = 0
        date = HourMinuteDate(year, month, day, hour, minute)
    else:
        date = HourMinuteDate.fromString(date)

    # if no note provided, ask user to enter
    note = options.note
    if note is None:
        note = input(f"enter note for {date}: ")

    # creates new date
    newDate = AttendanceDate(date, note)
    a = AppModel()
    # loads the data and adds the new date
    a.loadData()
    a.addDate(newDate)
    print("take attendance for", newDate)
    # ask for the status for each student then saves the data
    a.studentsAndDates(newDate)
    a.saveData()


# ----------------------------------------------------------------------

if __name__ == '__main__':
    main()
