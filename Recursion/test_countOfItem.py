# Tyler Slussar
# CS 161 12pm

import unittest
from countOfItem import *

class countOfItemTest(unittest.TestCase):

    def testCountOfItem(self):
        self.assertEqual(countOfItem(3,[4,5,3,4,]), 1)
        self.assertEqual(countOfItem(22, [25,32,56,22,56,43,33,22,56,22]), 3)
        self.assertEqual(countOfItem(2,[1,3,5]), 0)
