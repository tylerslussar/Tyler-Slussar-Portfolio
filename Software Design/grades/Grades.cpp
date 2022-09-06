//
//  Grades.cpp
//  Grades
//
// Tyler Slussar
// CS 493 12:30 pm

#include <iomanip>
#include <sstream>
#include <algorithm>

#include "Grades.hpp"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::setw;
using std::left;
using std::right;
using std::setprecision;
using std::fixed;

// --------------------------------------------------------------------------------

std::string trim(const std::string& str, const std::string& whitespace)
{
    // from: http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

// --------------------------------------------------------------------------------
// MARK: - Category

Category::Category(std::string name, double weight, int numToDrop) {
    // constructor 
    _name = name; 
    _weight = weight;
    _numToDrop = numToDrop;
}

double Category::average(){
    // if no assessments return zero for the average
    if (_numberOfAssessments == 0) {
        return 0.0;
    }

    // sort the assessments in descending order
    std::sort(_assessments, _assessments + _numberOfAssessments, std::greater<Assessment>());

    //initializes the variable average
    double average = 0;
    // droppingSpot is the first position that a number will not be used to calculate average
    int droppingSpot = _numberOfAssessments - _numToDrop; 

    // loop that will go through each assessment and if it is in the droppingSpot or above
    // it will set it to be dropped
    for (int i = 0; i < _numberOfAssessments; ++i){
        Assessment x = _assessments[i];
        
        if (i >= droppingSpot) {
            x.setDropped();
        }
        // if not dropped it will calulate the total
        else {
            average = average + x.score();
        }
        
    }
    // computes the actual average 
    average = average / droppingSpot;
    return average;
}

std::istream& operator>>(std::istream& is, Category& c) {
    std::string line;

    is >> c._name;
    // fail if can't read a name (such as we reached end of file when trying to read previous category)
    if (is.fail()) {
        return is;
    }
    is >> c._weight >> c._numToDrop;
    // read \n at end of line
    getline(is, line);

    // reset assessment count
    c._numberOfAssessments = 0;
    // now read first line of assessments
    do {
        getline(is, line);
        // in case no blank line at end of file after last assessment
        if (is.eof()) {
            // clear eof bit so this input operator doesn't fail,
            // but next call to this input operator will fail at beginning of method when trying to read name
            is.clear();
            return is;
        }

        // if blank, this is the end of the assessments for this category
        line = trim(line);
        if (line == "") {
            return is;
        }

        // read the line into an Assessment
        std::istringstream iss(line);
        Assessment a;
        iss >> a;

        // and add assessment to the category
        c.addAssessment(a);
    } while (is);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Category& c) {
    // outputs the category name
    os << c.name();
    Category p;
    // makes a copy to allow computation of average   
    p = c;
    p.average();

    // loop that outputs the assessment and score and a new line
    for (int i = 0; i < c._numberOfAssessments; i++) {
        os << endl << c._assessments[i];
    }
    if (c.hasAssessments() == true) {
        // this will output the average with one decimal place
        os << endl << "Average: " << fixed << setprecision(1) << p.average() << endl << endl;
}
    return os;

}


void Category::addAssessment(const Assessment& a) {
    // every addAssessment will add the assessment to the array and then add 1 to _numberOfAssessments
    _assessments[_numberOfAssessments] = a;
    _numberOfAssessments = _numberOfAssessments + 1;
}

// ----------------------------------------------------------------------------------
// MARK: - Grades

void Grades::addCategory(const Category& c) {
    // see addAssessment 
    _categories[_numberOfCategories] = c;
    _numberOfCategories = _numberOfCategories + 1;
}

double Grades::computeAverage() const {
    double average = 0;
    double sumOfWeights = 0;

    for (int i = 0; i < _numberOfCategories; ++i) {
        
        // if a category has assessments it will take the weight of that category and add it to sumOfWeights
        if (_categories[i].hasAssessments() == true) {
            sumOfWeights = sumOfWeights+  _categories[i].weight();

        }
        double x;
        Category p;
        // p is a single category
        p = _categories[i];
        // to find the average of each category, it will take the category average and * by the weight
        // of the category
        x = p.average() * _categories[i].weight();
        average = average + x;

    }
    // after adding each average, dividing that number by the sum of all the weights will determine course average
    average = average / sumOfWeights;
    return average;
}

std::istream& operator>>(std::istream& is, Grades& g) {
   
    // brings in the line and creates the category and adds it to the grade
    std::string name; double weight; int drop;
    is >> name >> weight >> drop;
    Category c(name, weight, drop);

    g.addCategory(c);

    
    return is;

}

std::ostream& operator<<(std::ostream& os, const Grades& g) {
    // outputs the course average with one decimal place
    os << endl << "Course Average: " << fixed << setprecision(1) <<  g.computeAverage();
    return os;
}

// -------------------------------------------------------------------------------
// MARK: - Assessment

Assessment::Assessment(std::string name, double score, bool dropped) {
    // constuctor
    _name = name;
    _score = score;
    _dropped = dropped;

}

std::istream& operator>>(std::istream& is, Assessment& a) {
    // read line and assigns the assessment name and score   
    is >> a._name >> a._score;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Assessment& a) {
    // output name and score with appropriate justification
    os << left << setw(12) << a._name << right << setw(6) << fixed << setprecision(1) << a._score;
   
    // if the assessment is dropped it will output
    if (a.dropped() == true) {
        os << " (dropped)";
    }
    return os;
}

bool operator==(const Assessment& lhs, const Assessment& rhs) {
    // returns true if the names are equal 
    if (lhs.name() == rhs.name()) {
        return true;
    }
    return false;
}

bool operator!=(const Assessment& lhs, const Assessment& rhs) {
   // returns true if the names are not equal
    if (lhs.name() != rhs.name()) {
        return true;
    }
    return false;
}

bool operator>(const Assessment& lhs, const Assessment& rhs) {
    // compares scores 
    if (lhs.score() > rhs.score()) {
        return true;
    }
    return false;
}