# Tyler Slussar
#CS 161 12pm

from typing import List

def multiply(numbers: List[float]) -> float:
    """
    returns product of numbers without mutating numbers
    :param numbers: the sequence (list or tuple) of float (or int) numbers
    :return: 0 if list is empty, otherwise product of items in list
    """
    # base cases: if there is only one number in the list then return that number and if the list is empty return 0
    if len(numbers) == 1:
        return numbers[0]
    elif len(numbers) == 0:
        return 0
    # makes a new list leaving off the first item
    recursionList = numbers[1:]
   # returns the first number multiplied by the function recursively
    return numbers[0] * multiply(recursionList)

