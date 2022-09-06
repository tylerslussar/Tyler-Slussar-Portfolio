# Tyler Slussar
# CS 161 12pm

def indexOfItem(item, items: list):
    """
    recursive version of list index method; returns index of items in list items;
    raises IndexError if not found
    :param item: value to find index of
    :param items: the sequence (list or tuple) of values to return index of item
    :return: index of item in items or raises IndexError if not found
    """
    # takes the list that is passed in and creates a new list without the first item
    recursionList = items[1:]
    # base case: if there is nothing in the list raise error
    if len(items) == 0:
        raise IndexError
    # if the item is the the first thing in the list return 0
    elif item == items[0]:
        return 0
    # this counts the amount of times the function is recursively called, whereas if the item is found it returns 0 and
    # does not increase the count
    else:
        return 1 + indexOfItem(item, recursionList)


