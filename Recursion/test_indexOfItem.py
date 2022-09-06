# Tyler Slussar
# CS 161 12pm

import unittest
from indexOfItem import *

class indexOfItemTest(unittest.TestCase):

    def testIndexOfItem(self):
        self.assertEqual(indexOfItem(3, [1,2,3,4]), 2)
        self.assertEqual(indexOfItem(2, [2,35,2,4,5,6]), 0)
        self.assertEqual(indexOfItem(35, [1,3,5,6,35,3,5,3,6,35]), 4)
        with self.assertRaises(IndexError):
            indexOfItem(5, [1,2,3,4])