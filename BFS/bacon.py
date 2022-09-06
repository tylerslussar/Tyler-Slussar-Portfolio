#!/usr/bin/env python3

# ----------------------------------------------------------------------
# bacon.py
# Tyler Slussar
# 10/31/2021
# ----------------------------------------------------------------------

import sys
#import timeit
# ----------------------------------------------------------------------

def addEdges(g, filmActors, film):
    # completely connect actors with this film as edge
    for a1 in filmActors:
        # create actor vertex if doesn't exist
        if a1 not in g:
            g[a1] = {}
        for a2 in filmActors:
            # if not same actor make edge between two actors for this film
            if a1 != a2:
                g[a1][a2] = film

    # ----------------------------------------------------------------------

def readFilmFile(filename):

    """read file of format:
        film
        actor
        actor

        film
        actor
        actor
        actor

        film
        actor
        actor

        and create the graph data structure connecting actors that are in the
        same file by an edge"""

    f = open(filename, 'r')

    # represent graph using a dictionary
    g = {}

    # first line is movie
    line = f.readline()
    filmActors = []

    # while not end of file
    while line != '':
        # remove end of line character
        film = line[:-1]

        # read first actor in film
        line = f.readline()

        # blank line between last actor and next film
        while line not in ('\n', ''):
            # remove end of line character
            actor = line.rstrip()
            filmActors.append(actor)

            # read next actor
            line = f.readline()

        addEdges(g, filmActors, film)
        filmActors = []

        # read next movie
        line = f.readline()
    f.close()

    # return the graph
    return g

# -----------------------------------------------------------------------------------------------------------------------

def BFS(graph, start, end):

    # visited actors
    seenActors = []
    # queue
    queue = [[start]]
    # while queue is not empty
    while queue:
        path = queue.pop(0)
        last = path[-1]
        # actor has not been seen
        if last not in seenActors:
            # check neighbors
            for neighbor in graph[last]:
                newPath = path + [neighbor]
                queue.append(newPath)
                # return if the actor is found
                if last == end:
                    return path
            seenActors.append(last)
    # actor is not found in the graph
    return None

# -----------------------------------------------------

def main():
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = input("enter filename: ")

    #start = timeit.default_timer()

    # reads the file and assigns the dictionary to graph
    graph = readFilmFile(filename)

    #stop = timeit.default_timer()
    #print(stop - start)

    actor = input("enter actor: ")
    actors = graph.keys()
    # checks to see if actors are in the graph
    # if not user must enter another actor
    if actor not in actors:
        actor = input("enter actor: ")

    #start = timeit.default_timer()

    # uses the breadth first search with the actor, the graph,
    # and the actor we are trying to find
    result = BFS(graph, actor, "Kevin Bacon")

    #stop = timeit.default_timer()
    #print(stop - start)

    # if the user enters Kevin Bacon
    if len(result) == 1:
        print("You entered Kevin Bacon and Kevin Bacon is Kevin Bacon")

    # for loop that prints out the actors and their movies
    else:
        for i in range(len(result)):
            actor0 = result[0]
            actor1 = result[1]
            print(f"{result[0]} was in '{graph[actor0][actor1]}' with {result[1]}")
            if result[1] == "Kevin Bacon":
                break
            result = result[1:]






# ----------------------------------------------------------------------

if __name__ == '__main__':
    main()
