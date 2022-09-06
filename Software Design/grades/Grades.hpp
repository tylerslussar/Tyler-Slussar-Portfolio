//
//  Grades.hpp
//  Grades
//
//  Created by David M. Reed on 6/16/20.
//  Copyright © 2020 David Reed. All rights reserved.
//

#ifndef Grades_hpp
#define Grades_hpp

#include <iostream>
#include <string>
#include <algorithm>

/// returns new string with leading and trailing characters specifed by whitespace parameter removed
/// @param str characters to be removed from beginning and end of str
/// @return new string with leading and trailing characters specifed by whitespace parameter removed
std::string trim(const std::string& str, const std::string& whitespace = " \t");

// --------------------------------------------------------------------------------
// MARK: - Assessment

class Assessment {
    friend class Category;
    friend std::istream& operator>>(std::istream&, Assessment&);
    friend std::ostream& operator<<(std::ostream&, const Assessment&);

public:
    // default constructor so can declare without providing parameters
    Assessment(std::string name = "", double score = 0.0, bool dropped = false);

    std::string name() const { return _name; }
    double score() const { return _score; }
    bool dropped() const { return _dropped; }

    void setDropped(bool value = true) { _dropped = value; }

private:
    // initialization with declaration is supported in later C++11 and later
    std::string _name = "";
    double _score = 0.0;
    bool _dropped = false;
};

// input and output operators - see assignment for formats
std::istream& operator>>(std::istream& is, Assessment& a);
std::ostream& operator<<(std::ostream& os, const Assessment& a);


// necessary comparision operators

// returns true if the two Assessments have the same name, false otherwise
bool operator==(const Assessment& lhs, const Assessment& rhs);

// returns true if the two Assessments do not have the same name, false otherwise
bool operator!=(const Assessment& lhs, const Assessment& rhs);

// returns true if the lhs assessment's score is > than the rhs assessment's score
bool operator>(const Assessment& lhs, const Assessment& rhs);

// --------------------------------------------------------------------------------
// MARK: - Category

class Category {
    friend std::istream& operator>>(std::istream&, Category&);
    friend std::ostream& operator<<(std::ostream&, const Category&);

public:
    // default constructor
    Category(std::string name = "", double weight = 0.0, int numToDrop = 0);

    std::string name() const { return _name; }
    double weight() const { return _weight; }
    bool hasAssessments() const { return _numberOfAssessments > 0; }

    /// add assessment to this category
    /// @param a assessment to add
    void addAssessment(const Assessment& a);

    /// computes average of the assessments for the category
    /// @post the assessments are sorted in descending order by score
    double average();

private:
    std::string _name;
    double _weight;
    int _numToDrop;
    Assessment _assessments[20];
    int _numberOfAssessments = 0;
};

// input and output operators - see assignment for formats
std::istream& operator>>(std::istream& is, Category& c);
std::ostream& operator<<(std::ostream& os, const Category& c);

// --------------------------------------------------------------------------------
// MARK: - Grades

class Grades {
    friend std::istream& operator>>(std::istream&, Grades&);
    friend std::ostream& operator<<(std::ostream&, const Grades&);

public:
    /// add specified category to the assignment
    /// @param c category to add
    void addCategory(const Category& c);

    /// computer average for the course based on all categories and assessments
    /// see description on assignment for how to caluclate
    double computeAverage() const;

private:
    int _numberOfCategories = 0;
    Category _categories[10];
};

// input and output operators - see assignment for formats
std::istream& operator>>(std::istream& is, Grades& g);
std::ostream& operator<<(std::ostream& os, const Grades& g);

#endif /* Grades_hpp */
