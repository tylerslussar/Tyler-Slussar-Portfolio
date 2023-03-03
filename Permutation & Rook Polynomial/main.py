# Tyler Slussar
# Combinatorics Final Project
# Rook Polynomial

# importing graphics.py by John Zelle
# importing  a button class using graphics.py, adapted
# with additions useful for this program

import math
from graphics import *
from button import *
import itertools


def possibleSubsets(forbiddenPos, n):
    """
    determines all the possible subsets needed to determine the rook polynomial
    :param forbiddenPos: the forbidden positions on the rook board
    :param n: rook board size
    :return: all possible subsets of the forbidden positions up to the board size
    """

    subsets = []
    buttonLables = []

    # grabs the button values for each button
    for i in range(len(forbiddenPos)):
        buttonLables.append(forbiddenPos[i].buttonValue())

    # we cannot place more non-attacking rooks on the board than the board size itself
    for i in range(len(buttonLables) + 1):
        if i > n:
            break
        # built into python that will live subsets of passed in size
        subsets.append(list(itertools.combinations(buttonLables, i)))

    return subsets

def checkAttack(subset, n):
    """
    checks to see if the rooks in the subset are in attacking position
    :param subset: a single subset
    :param n: rook board size
    :return: 0 if rooks are in attacking position, 1 if rooks are in non-attacking position
    """
    subsetTwos = []

    # for the subset, find subsets with 2 values of the subset, so it can compare to values at a time
    subsetTwos.append(list(itertools.combinations(subset, 2)))
    # 6, 15, 8
    # [(6,15), (6,8), (15,8)]
    for i in subsetTwos:
        for subsets in i:
            # integer division determines same row, mod determines same column
            if (subsets[0] // n == subsets[1] // n) or (subsets[0] % n == subsets[1] % n):
            # attacking is true
                return 0
    # attacking is false
    return 1





def RookPolynomial(length, n, subsets):
    """
    uses checkAttack() to calculate the sum, which is a coefficient
    :param length: length of forbidden position
    :param n: rook board size
    :param subsets: all the possible subsets of the forbidden positions
    :return: coefficients of the rook polynomial
    """
    coef = []

    # only 1 way to place 0 rooks on the board
    if len(subsets) >= 1:
        coef.append(1)

    # number of ways to place 1 rook on the board is equal to the count of forbidden positions
    if len(subsets) >= 2:
        coef.append(length)

    # determine coefficient of the rest
    for i in range(2, len(subsets)):
        subsetRange = subsets[i]
        sum = 0
        for subset in subsetRange:
            value = checkAttack(subset, n)
            sum += value

        coef.append(sum)

    return coef

def permutations(coef, n):
    """

    :param coef: the coefficients of the rook polynomial
    :param n: rook board size
    :return: the calculated permutations based on forbidden positions
    """
    total = math.factorial(n)
    # needed to change +,- in equation
    change = -1
    for i in range(1, len(coef)):
        # calculation for permutations
        if n >= 1:
            total = total + (change * coef[i] * math.factorial(n-1))
            change = change * -1
            n = n-1
    return total


def findExponent(number):
    """

    :param number: exponent value
    :return: the unicode value for the superscript
    """

    dict ={2: "\u00b2", 3: "\u00b3", 4: "\u2074", 5: "\u2075", 6: "\u2076",
           7: "\u2077", 8: "\u2078", 9: "\u2079"}

    exponent = dict.get(number)
    return exponent



def polynomialLabel(coef):
    """

    :param coef: coefficients of the rook polynomial
    :return: string of the polynomial
    """

    polynomial = ""
    if len(coef) >= 1:
        polynomial = polynomial + f'1'
    if len(coef) >= 2:
        if coef[1] == 1:
            polynomial = polynomial + f' + x'
        else:
            polynomial = polynomial + f' + {coef[1]}x'


    for i in range(2, len(coef)):

        exponent = findExponent(i)

        if coef[i] == 0:
            break
        else:

            if coef[i] == 1:
                polynomial = polynomial + f' + x{exponent}'
            else:
                polynomial = polynomial + f' + {coef[i]}x{exponent}'

    return polynomial

def blankRookBoard(size, win):
    """

    :param size: size of the board
    :param win: window to draw in
    :return: the board buttons and the size of the baord
    """

    boardButtons = []
    # these are used to pop from the list and used as the letters to label columns and rows
    columns = ["R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
    rows = ["I", "H", "G", "F", "E", "D", "C", "B", "A"]

    # n assigned based on size
    # i is increasing to give the buttons an increasing value
    if size == "5x5":
        n = 5
        y = 100
        i = 0
        for column in range(5):
            x = 300
            for row in range(5):
                button = Button(win, Point(x,y), 100, 100, "", i)
                boardButtons.append(button)
                button.activate()
                x += 100
                i += 1

            y += 100

        cPosition = 700
        for column in range(5):
            letter = columns.pop()
            message = Text(Point(cPosition, 25), letter)
            message.setSize(25)
            message.draw(win)
            cPosition -= 100

        rPosition = 100
        for row in range(5):
            letter = rows.pop()
            message = Text(Point(200, rPosition), letter)
            message.setSize(25)
            message.draw(win)
            rPosition += 100



    elif size == "6x6":
        n = 6
        y = 100
        i = 0
        for column in range(6):
            x = 200
            for row in range(6):
                button = Button(win, Point(x,y), 100, 100, "", i)
                boardButtons.append(button)
                button.activate()
                x += 100
                i += 1

            y += 100

        cPosition = 700
        for column in range(6):
            letter = columns.pop()
            message = Text(Point(cPosition, 25), letter)
            message.setSize(25)
            message.draw(win)
            cPosition -= 100

        rPosition = 100
        for row in range(6):
            letter = rows.pop()
            message = Text(Point(100, rPosition), letter)
            message.setSize(25)
            message.draw(win)
            rPosition += 100



    elif size == "7x7":
        n = 7
        y = 100
        i = 0
        for column in range(7):
            x = 200
            for row in range(7):
                button = Button(win, Point(x,y), 80, 80, "", i)
                boardButtons.append(button)
                button.activate()
                x += 80
                i += 1

            y += 80

        cPosition = 680
        for column in range(7):
            letter = columns.pop()
            message = Text(Point(cPosition, 25), letter)
            message.setSize(25)
            message.draw(win)
            cPosition -= 80

        rPosition = 100
        for row in range(7):
            letter = rows.pop()
            message = Text(Point(100, rPosition), letter)
            message.setSize(25)
            message.draw(win)
            rPosition += 80


    elif size == "8x8":
        n = 8
        y = 100
        i = 0
        for column in range(8):
            x = 200
            for row in range(8):
                button = Button(win, Point(x,y), 75, 75, "", i)
                boardButtons.append(button)
                button.activate()
                x += 75
                i += 1

            y += 75

        cPosition = 725
        for column in range(8):
            letter = columns.pop()
            message = Text(Point(cPosition, 25), letter)
            message.setSize(25)
            message.draw(win)
            cPosition -= 75

        rPosition = 100
        for row in range(8):
            letter = rows.pop()
            message = Text(Point(100, rPosition), letter)
            message.setSize(25)
            message.draw(win)
            rPosition += 75


    else:
        n = 9
        y = 75
        i = 1
        for column in range(9):
            x = 100
            for row in range(9):
                button = Button(win, Point(x, y), 75, 75, "", i)
                boardButtons.append(button)
                button.activate()
                x += 75
                i += 1

            y += 75

        cPosition = 700
        for column in range(9):
            letter = columns.pop()
            message = Text(Point(cPosition, 25), letter)
            message.setSize(25)
            message.draw(win)
            cPosition -= 75

        rPosition = 75
        for row in range(9):
            letter = rows.pop()
            message = Text(Point(50, rPosition), letter)
            message.setSize(25)
            message.draw(win)
            rPosition += 75

    return boardButtons, n





def main():

    win = GraphWin("Rook Board", 1000, 800)
    forbiddenButtons = []

    selectionScreen = Text(Point(500,200), "Select Rook Board Size")
    selectionScreen.setSize(32)
    selectionScreen.draw(win)

    five = Button(win, Point(200,450),150, 300, "5x5")
    six = Button(win, Point(350,450), 150, 300, "6x6")
    seven = Button(win, Point(500, 450), 150, 300, "7x7")
    eight = Button(win, Point(650,450), 150, 300, "8x8")
    nine = Button(win, Point(800,450), 150, 300, "9x9")

    buttons = [five, six, seven, eight, nine]
    for b in buttons:
        b.activate()

    boardSize = None
    click = win.getMouse()
    while click:
        for b in buttons:
            if b.clicked(click):
                boardSize = b
                click = False
                break
        if click:
            click = win.getMouse()

    selectionScreen.undraw()
    for b in buttons:
        b.deactivate()
        b.undraw()

    size = boardSize.getLabel()
    boardButtons, n = blankRookBoard(size, win)

    quitButton = Button(win, Point(900,100), 125, 125, "Quit" )
    quitButton.activate()

    polyText = Text(Point(500,750), "")
    polyText.draw(win)
    polyText.setSize(20)
    permText = Text(Point(875, 650), "")
    permText.draw(win)
    permText.setSize(20)

    # loops through on the mouse click to select/deselect squares
    # calculate rook polynomial and permutations after each click
    click = win.getMouse()
    while click:

        for b in boardButtons:
            if b.clickedColor(click):
                if b not in forbiddenButtons and b.getColor() == 1:
                    forbiddenButtons.append(b)
                    subsets = possibleSubsets(forbiddenButtons, n)
                    coef = RookPolynomial(len(forbiddenButtons), n, subsets)
                    poly = polynomialLabel(coef)
                    polyText.setText(f'Rook Polynomial: {poly}')
                    perm = permutations(coef, n)
                    permText.setText(f'Permutations: {perm}')


                else:
                    forbiddenButtons.remove(b)
                    subsets = possibleSubsets(forbiddenButtons, n)
                    coef = RookPolynomial(len(forbiddenButtons), n, subsets)
                    poly = polynomialLabel(coef)
                    polyText.setText(f'Rook Polynomial: {poly}')
                    perm = permutations(coef, n)
                    permText.setText(f'Permutations: {perm}')

        # end program with quit button
        if quitButton.clicked(click):
            win.close()
            break

        click = win.getMouse()


if __name__ == '__main__':
    main()




