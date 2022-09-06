# Tyler Slussar
#CS 161 12pm

def countOfItem(item, items: list):
    """
    recursive version of list count method; returns numbers of occurrences of item
    in the sequence items
    :param item: the value to count
    :param items: the sequence (list or tuple) in which to count item
    :return: number of occurrences of item in the sequence of items
    """
    # creates new list leaving off the first item
    recursionList = items[1:]
    # if there is nothing in the list then return 0
    if len(items) == 0:
        return 0
    # if the new list that is passed through recursively has the item then it would be in position 0 which then would be counted as 1
    # if position 0 does not have the value it calls the function again without adding to the count
    # this pattern of new list and checking the 0 position continues until it reaches the base case, that there are no items in the list
    elif item == items[0]:
        return 1 + countOfItem(item, recursionList)
    else:
        return 0 + countOfItem(item, recursionList)

