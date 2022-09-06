# Tyler Slussar
# CS161 12 pm


import sys
import unittest

sys.path.insert(0, '..')
from LList import *

class LListTest(unittest.TestCase):

    # ---------------------------------------------

    def checkList(self, mine: LList, expected: list):
        actual = list(mine)
        self.assertEqual(actual, expected)

        if len(expected) > 0:
            self.assertEqual(mine.tail.item, expected[-1])

    # --------------------------------------------------

    def testAppend(self):
        testList = LList()
        expected = []
        for i in range(0,12,3):
            expected.append(i)
            testList.append(i)

        self.checkList(testList, expected)

    # -------------------------------------------------

    def testInsert(self):
        testList = LList()
        expected = []
        for i in range(0, 12, 3):
            expected.append(i)
            testList.append(i)

        testList.insert(0,4)
        expected.insert(0,4)
        testList.insert(len(testList), 8)
        expected.insert(len(expected), 8)
        testList.insert(3, 16)
        expected.insert(3, 16)

        self.checkList(testList, expected)

    # ------------------------------------------------------

    def testPop(self):
        testList = LList()
        expected = []
        for i in range(0, 13, 3):
            expected.append(i)
            testList.append(i)

        testList.pop()
        expected.pop()
        testList.pop(0)
        expected.pop(0)

        self.checkList(testList, expected)

    def testRemove(self):
        testList = LList()
        expected = []
        for i in range(0, 13, 3):
            expected.append(i)
            testList.append(i)

        testList.remove(0)
        expected.remove(0)
        testList.remove(12)
        expected.remove(12)
        testList.remove(6)
        expected.remove(6)

        self.checkList(testList, expected)

    # ------------------------------------------------------

    def testIndex(self):
        testList = LList()
        for i in range(0, 13, 3):
            testList.append(i)

        test1 = testList.index(6)
        self.assertEqual(test1, 2)

        self.assertRaises(ValueError, testList.index, 37)

        testList.append(3)
        test3 = testList.index(3, 2)
        self.assertEqual(test3, 5)

        test4 = testList.index(3)
        self.assertEqual(test4, 1)

    # ------------------------------------------------------
    def testExtend(self):
        testList = LList()
        expected = []
        extender = [15, 18, 21]
        for i in range(0, 13, 3):
            testList.append(i)
            expected.append(i)

        for i in extender:
            expected.append(i)

        testList.extend(extender)

        self.checkList(testList, expected)
