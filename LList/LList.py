# Tyler Slussar
# CS161 12 pm

from ListNode import ListNode

class LList:

    # ------------------------------------------------------------------

    def __init__(self, seq = None):

        self.head = None
        self.tail = None
        self.size = 0

        for i in seq:
            self.append(i)

    # ------------------------------------------------------------------

    def __iter__(self):
        node = self.head
        # prefer using is vs == when checking None
        while node is not None:
            yield node.item
            node = node.link

    # ------------------------------------------------------------------

    def append(self, value) -> None:
        """
        add values to the end of the list
        :param value: value to add to a list
        :return: None
        """

        newNode = ListNode(value)
        # comparing to None is the about the only time you should is - almost always want ==
        # if self.head is None:
        # if there is nothing in the list both head and tail is the node
        if self.size == 0:
            self.head = newNode
            self.tail = newNode
        # if there is something in the list, the previous tail's link is the new node
        # and then the new node itself is the tail
        else:
            self.tail.link = newNode
            self.tail = newNode
        self.size += 1

    # ------------------------------------------------------------------

    def insert(self, pos: int, value) -> None:
        """
        inserts value at the index pos
        :param pos: the index where the new value should go
        :param value: the value to insert
        :return: None
        """
        # if there is nothing in the list append
        if self.size == 0:
            self.append(value)
        # if they are inserting at the end, append
        elif pos == self.size:
            self.append(value)
        # adding any where else
        else:
            newNode = ListNode(value)
            # if inserting at spot zero
            if pos == 0:
                newNode.link = self.head
                self.head = newNode
            else:
            # find the prevNode and connect the newNode and prevNode and then make the link the newNode
                prevNode = self._find(min(self.size - 1, pos - 1))
                newNode.link = prevNode.link
                prevNode.link = newNode
            self.size += 1

    # ------------------------------------------------------------------

    def remove(self, value) -> None:
        """
        removes the first copy of value from the list, raises ValueError if value not in the list
        :param value: the value to remove
        :return: None
        """

        node = self.head
        prevNode = None
        # checks nodes as long as is it not None and the value has not been found
        while node is not None and value != node.item:
            prevNode = node
            node = node.link
        # raise a value error if node is none
        if node is None:
            raise ValueError(f"LList.remove(x): {value} not in list")
        else:
            # removing first item in list
            if prevNode is None:
                self.head = self.head.link
            # removing last item, if node.link is none then make prevNode the tail and make that link None
            elif node.link is None:
                self.tail = prevNode
                self.tail.link = None
            # removing any where else, make the prevNode like = the nodes link "skipping" over a node entirely
            else:
                prevNode.link = node.link
            self.size -= 1

    # ------------------------------------------------------------------

    def __len__(self):

        '''post: returns number of items in the list'''

        return self.size

    # ------------------------------------------------------------

    def _find(self, position):

        '''private method that returns node that is at location position
        in the list (0 is first item, size-1 is last item)
        pre: 0 <= position < self.size
        post: returns the ListNode at the specified position in the
        list'''

        assert 0 <= position < self.size

        node = self.head
        # move forward until we reach the specified node
        for i in range(position):
            node = node.link
        return node

    # ------------------------------------------------------------

    def __getitem__(self, position):

        '''return data item at location position
        pre: 0 <= position < size
        post: returns data item at the specified position'''

        node = self._find(position)
        return node.item

    # ------------------------------------------------------------

    def __setitem__(self, position, value):

        '''set data item at location position to value
        pre: 0 <= position < self.size
        post: sets the data item at the specified position to value'''

        node = self._find(position)
        node.item = value

    # ------------------------------------------------------------

    def __delitem__(self, position):

        '''delete item at location position from the list
        pre: 0 <= position < self.size
        post: the item at the specified position is removed from
        the list'''

        assert 0 <= position < self.size

        self._delete(position)

    # ------------------------------------------------------------

    def _delete(self, position):

        # private method to delete item at location position from the list
        # pre: 0 <= position < self.size
        # post: the item at the specified position is removed from the list
        # and the item is returned (for use with pop)

        if position == 0:
            # save item from the initial node
            item = self.head.item

            # change self.head to point "over" the deleted node
            self.head = self.head.link

            if self.size == 1:
                self.tail = None
        # of the position is the last item in the list
        elif position == self.size - 1:
            # item is the tail's item
            item = self.tail.item
            # find second to last node
            secondToLastNode = self._find(self.size - 2)
            # make the tail the second to last node and then make that link to None
            self.tail = secondToLastNode
            self.tail.link = None

        else:
            # find the node immediately before the one to delete
            prev_node = self._find(position - 1)

            # save the item from node to delete
            item = prev_node.link.item

            # change predecessor to point "over" the deleted node
            prev_node.link = prev_node.link.link

        self.size -= 1
        return item

    # ------------------------------------------------------------

    def pop(self, i=None):

        '''returns and removes at position i from list; the default is to
        return and remove the last item

        pre: self.size > 0 and ((i is None or (0 <= i < self.size))

        post: if i is None, the last item in the list is removed
        and returned; otherwise the item at position i is removed
        and returned'''

        assert self.size > 0 and (i is None or (0 <= i < self.size))

        # default is to delete last item
        # i could be zero so need to compare to None
        if i is None:
            i = self.size - 1

        return self._delete(i)
    # ---------------------------------------------------------------

    def __copy__(self):

        '''post: returns a new LList object that is a shallow copy of self'''

        # a is a new copy of the same LList
        a = LList()
        node = self.head
        while node is not None:
            a.append(node.item)
            node = node.link
        return a

    # ------------------------------------------------------------

    def index(self, value, start = 0):
        """

        :param value: value that position you want to find
        :param start: where to start in list, default to position 0
        :return: position of value
        """
        # find the starting node
        node = self._find(start)
        prevNode = None
        # checks each node and lets us "walk" through the LList
        while node is not None and value != node.item:
            # counter to identify position
            start = start + 1
            # prevNode is now the node and the node is now the next node
            prevNode = node
            node = node.link

            # if the node is None is raises a ValueError
            if node is None:
                raise ValueError(f"LList.index(value, start): {value} not in list")

            # if the node's item equals the first value we're looking for then return the counter assigned start
            elif node.item == value:
                return start

    # ------------------------------------------------------------

    def extend(self, seq):
        """

        :param seq: list to extend the LList
        :return: None
        """
        # for each value in l append onto the LList
        # append takes care of the tail and the size of the LList already
        n = len(seq)
        count = 0
        for x in seq:
            self.append(x)
            count += 1
            


