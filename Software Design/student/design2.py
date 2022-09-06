# Tyler Slussar
# CS 493 12:30

class Student:

    def __init__(self, firstName, lastName, indentifier):
        """
        this class is establishing one single student
        :param firstName: first name of the student
        :param lastName: last name of the student
        :param indentifier: ID of the student
        """
        pass




class Attendance:

    def __init__(self, dateAndTime, note):
        """
        this class is establishing one specific date
        :param dateAndTime: date and time of an attendance being taken
        :param note: note for that date
        """
        pass



class Status:

    def __init__(self, date, student, status):
        """
        this class will take the date and student and will establish their status
        :param date: the date that which the status is being noted
        :param student: the student that is referred to
        :param status: the status of the student
        """
        pass


class Records:
    """
    this class will contain much of the other classes and will write a file
    with the appropriate information
    """
    def __init__(self, dictOfAttendance: dict):
        """

        :param dictOfAttendance: this is a dictionary which each date having keys that are both
        the students and their status
        """
        pass

    def addDate(self, date):
        """
        this will add an attendance to the dict
        :param date: date to add attendance
        :return: none
        """
        pass

    def readFiles(self, studentFile, dateFile, recordFile):
        """
         this method will read from each of the csv files
        :param studentFile: the file with all the students listed
        :param dateFile: the file with the listed dates
        :param recordFile: the file with the students' status
        :return: none
        """
        pass

    def writeFile(self):
        """
        this class will have the inputs and write data onto a file
        :return: none
        """
        pass

    def addValue(self, date, student, status):
        """
        this method will add dates to the dictionary for records such that
        each date will have each student and their status for that day
        :param date: which date to refer to in dict
        :param student: student to add
        :param status: status of student
        :return: none
        """
        pass
