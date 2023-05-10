//
//  floydthread.cpp
//  Tyler Slussar
//  CS381 9:30AM
//
//  Created by David Reed on 2/4/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::istream;
using std::ifstream;
using std::thread;
using namespace std::chrono;

const int SIZE = 3000;
unsigned short path[SIZE][SIZE];
unsigned short parent[SIZE][SIZE];
unsigned short movie[SIZE][SIZE];

const short MY_INFINITY = 32767;
const int NUM_THREADS = 16;
//--------------------------------------------------------------------

void readFile(string filename, unsigned short &numActors, unsigned short &numMovies, string *&actorNames, string *&movieNames)
{
    ifstream ifs;
    // temp string for getline
    string temp;
    int i, j;
    unsigned short actor1Num, actor2Num, movieNum, n;

    ifs.open(filename.c_str());

    // read actors
    ifs >> numActors;
    cout << "num actors: " << numActors << endl;
    getline(ifs, temp);
    actorNames = new string[numActors];
    for (i=0; i<numActors; ++i) {
        getline(ifs, actorNames[i]);
    }

    // read movies
    ifs >> numMovies;
    getline(ifs, temp);
    cout << "num movies: " << numMovies << endl;
    movieNames = new string[numMovies];
    for (i=0; i<numMovies; ++i) {
        getline(ifs, movieNames[i]);
    }

    // initialize path, parent, and movie matrix
    for (i=0; i<numActors; ++i) {
        for (j=0; j<numActors; ++j) {
            if (i != j) {
                path[i][j] = MY_INFINITY;
            }
            else {
                // no path/parent/movie from vertex i to vertex j
                path[i][j] = 0;
            }
            parent[i][j] = MY_INFINITY;
            movie[i][j] = MY_INFINITY;
        }
    }

    // read edges from file
    while (ifs >> actor1Num) {
        ifs >> n;
        // if (actor1Num % 100 == 0) cout << actor1Num << " " << endl;
        for (i=0; i<n; ++i) {
            ifs >> actor2Num >> movieNum;
            // path from a1 to a2
            path[actor1Num][actor2Num] = 1;
            // path from a2 to a1
            path[actor2Num][actor1Num] = 1;
            // parent of a2 is a1
            parent[actor1Num][actor2Num] = actor1Num;
            // parent of a1 is a2
            parent[actor2Num][actor1Num] = actor2Num;
            // set movie connecting a1 and a2
            movie[actor1Num][actor2Num] = movieNum;
            movie[actor2Num][actor1Num] = movieNum;
        }
    }
    ifs.close();
    cout << "finished reading file" << endl;
}

//--------------------------------------------------------------------
void floydThreads(short k, short start, short end, unsigned short numActors){
   
    short i, j;
    unsigned short valik, val;
    
    // seperating the i loop work
    // each thread is doing a section of work
    for (i=start; i<end; ++i) {
        valik = path[i][k];
        for (j=0; j<numActors; ++j) {
            val = valik + path[k][j];
            // if find shorter path
            if (val < path[i][j]) {
                // update path length and parent
                path[i][j] = val;
                // since new path goes from i to k to j, the new parent for [i][j] should be
                // what the parent of [k][j] is since that is the parent on the path from k to j
                parent[i][j] = parent[k][j];
            }
        }
    }
}

void floyd(unsigned short numActors)
{
    
    // file 2005.txt time:
    // 7.2567 seconds
    
    std::thread t[NUM_THREADS];
    short start, end;
    short perThread = numActors / NUM_THREADS;
    
    // for each k, cannot run k loop in parallel as
    // it will lead to race conditions
    for (short k=0; k < numActors; k++) {
        // each thread is given different i loop ranges
        for (short j=0; j < NUM_THREADS; j++){
            // last thread handles from the start until the end of numActors
            // this will handle any cases where NUM_THREAD does not divide numActors
            if (j == (NUM_THREADS-1)){
                start = j * perThread;
                end = numActors;
            }
            else {
                start = j * perThread;
                end = j * perThread + perThread;
           }
            // creates the threads with their i loop ranges
            t[j] = thread(floydThreads, k, start, end, numActors);
        }
        
        // this waits for the threads to finish
        // therefore we can wait for this k iteration to complete
        for(int i=0; i < NUM_THREADS; i++){
            t[i].join();
        }
    }
}

//--------------------------------------------------------------------

void printPaths(unsigned short numActors, string *actorNames, string *movieNames, istream &is) {
    // repeatedly allow user to check paths between actors
    do {
        unsigned short actor1Index, actor2Index;
        string actor1Name, actor2Name;

        cout << "\nenter first actor/actress: ";
        getline(is, actor1Name);
        // stop if empty name
        if (actor1Name == "")
            break;

        cout << "enter second actor/actress: ";
        getline(is, actor2Name);

        // try to find actor names
        actor1Index = 0;
        while (actor1Index < numActors && actorNames[actor1Index] != actor1Name) {
            actor1Index++;
        }
        actor2Index = 0;
        while (actor2Index < numActors && actorNames[actor2Index] != actor2Name) {
            actor2Index++;
        }

        // if didn't find names, output message and get new names
        if (actor1Index == numActors || actor2Index == numActors) {
            if (actor1Index == numActors) {
                cout << "could not find: " << actor1Name << endl;
            }
            if (actor2Index == numActors) {
                cout << "could not find: " << actor2Name << endl;
            }
        }
        else {
            cout << endl;
            // check if path
            if (parent[actor2Index][actor1Index] == MY_INFINITY) {
                cout << "no path from " << actor1Name << " to " << actor2Name << endl;
            }
            else {
                while (actor1Index != actor2Index) {
                    unsigned short current = actor1Index;
                    actor1Index = parent[actor2Index][actor1Index];
                    cout << actorNames[current] << " is in " << movieNames[movie[current][actor1Index]]
                    << " with " << actorNames[actor1Index] << endl;

                }
            }
        }
    } while (true);
}

//--------------------------------------------------------------------

void printMatrices(unsigned short numActors) {
    int i, j;

    cout << "path" << endl;
    // cout << "\\begin{bmatrix}" << endl;
    for (i=0; i<numActors; ++i) {
        for (j=0; j<numActors; ++j) {
            cout << path[i][j] << " ";
            if (j != numActors - 1) {
                // cout << "& ";
            }
            else {
                // cout << "\\\\";
                cout << endl;
            }
        }
    }
    // cout << "\\end{bmatrix}" << endl;
    cout << "parent" << endl;
    // cout << "\\begin{bmatrix}" << endl;
    for (i=0; i<numActors; ++i) {
        for (j=0; j<numActors; ++j) {
            cout << parent[i][j] <<  " ";
            if (j != numActors - 1) {
                //cout << "& ";
            }
            else {
                // cout << "\\\\";
                cout << endl;
            }
        }
    }
    // cout << "\\end{bmatrix}" << endl;
}

//--------------------------------------------------------------------

int main(int argc, char *argv[])
{
    string filename;
    ifstream ifs;

    // arrays for actor names and movie titles
    string *actorNames;
    string *movieNames;


    // number of actors and movies
    unsigned short numActors, numMovies;

    if (argc >= 2) {
        filename = string(argv[1]);
    }
    else {
        filename = "/Users/tyslu/Library/CloudStorage/OneDrive-Personal/Documents/School Documents/Senior Year!/Parallel Computing/Lab 3/2005.txt";
    }

    // read data file
    readFile(filename, numActors, numMovies, actorNames, movieNames);

    // time and run floyd algorithm
    auto start = high_resolution_clock::now();
    floyd(numActors);
    auto stop = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    cout << "time: " << duration << " (" << (duration / 1.0E6) << " seconds)" << endl;

    // DO NOT CALL THIS IN THE VERSION YOU SUBMIT!!!
    // but you may uncomment it while debugging
    //printMatrices(numActors);

    // find longest path
    unsigned short max = 0;
    unsigned short maxi = 0, maxj = 0;
    for (auto i=0; i<numActors; ++i) {
        for (auto j=0; j<numActors; ++j) {
            if (path[i][j] > max && path[i][j] < MY_INFINITY) {
                max = path[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }
    cout << "max path: " << max << endl;
    cout << maxi << " " << actorNames[maxi] << endl;
    cout << maxj << " " << actorNames[maxj] << endl;

    // print paths
    // if at least 3 command line arguments, get actor names from 3rd command line argument
    if (argc >= 3) {
        ifstream inputStream;
        inputStream.open(argv[2]);
        printPaths(numActors, actorNames, movieNames, inputStream);
        inputStream.close();
    }
    else {
        printPaths(numActors, actorNames, movieNames, cin);
    }

    // deallocate memory
    delete [] actorNames;
    delete [] movieNames;

    return 0;
}

//--------------------------------------------------------------------
