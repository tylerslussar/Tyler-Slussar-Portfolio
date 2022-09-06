//
//  main.cpp
//  Grades
//
// Tyler Slussar
// CS 493 12:30 pm

#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

using std::ifstream;
using std::string;

#include "Grades.hpp"

int main(int argc, const char* argv[]) {
    string filename;

    if (argc == 1) {
        //        cout << "enter filename: " << flush;
        //        cin >> filename;
                // you may replace this with the path to a file on your computer
        filename = "/Users/sluss/OneDrive/Documents/School Documents/Programs/CS 493/Lab 1";
    }
    else {
        // I will always provide a command line argument when testing
        filename = string(argv[1]);
    }

    // assigning variables
    ifstream infile(filename);
    Grades g;
    Assessment a;
    Category c;
   
    // this will read the first or the only category and output it
    infile >> c;
    cout << c;

    // this loop will continue to run as long as the category as assessments
    while (c.hasAssessments() == true) {
       
        infile >> c;
        
        // if a category does not have assigment it will not output the category name
        if (c.hasAssessments() == false) {
            break;
        }
        cout << c;
    }
    
    // output overall grade
    cout << g;
   
   



    return 0;
}