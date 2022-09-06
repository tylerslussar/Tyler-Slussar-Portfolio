# Tyler Slussar
# CS 161 12pm

import unittest
from multiply import *

class multiplyTest(unittest.TestCase):

    def testMultiply(self):
        self.assertEqual(multiply([5,4,3,2]), 120)
        self.assertEqual(multiply([4,8,13]), 416)
        self.assertEqual(multiply([3]), 3)
        self.assertEqual(multiply([]), 0)