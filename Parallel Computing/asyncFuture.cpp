//
//  asyncFuture.cpp
//  CS 381 9:30AM
//  Lab 2
//
//  Created by Tyler Slussar on 3/27/23.
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <future>
#include <thread>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::string;

using std::chrono::high_resolution_clock;

using std::thread;

/// struct for storing the subarray with the maximum sum
struct Result {
    int start; // starting index in subarray
    int end; // ending index in subarray
    int sum; // sum from start to (end - 1) in the array
};

const int MAX_THREADS = 32;

Result globalResults[MAX_THREADS];

/// output operator for Result
/// - Parameters:
///   - os: stream to output to
///   - r: Result to output
std::ostream& operator<<(std::ostream &os, const Result r) {
    os << "[ " << r.start << " : " << r.end << " ] " << r.sum;
    return os;
}

/// reads array of numbers from file and returns the starting address of dynamically allocated array; callee must deallocate the array
/// - Parameters:
///   - filename: name of file to read
///   - n: number of values in the array (passed by reference so value is overwritten)
short* readArray(std::string filename, unsigned int &n) {
    std::ifstream ifs;
    ifs.open(filename.c_str());
    // read first number which indicates how many values
    ifs >> n;

    // allocate array of that size
    auto array = new short[n];

    // read numbers from file
    for (auto i=0; i<n; ++i){
        ifs >> array[i];
    }
    ifs.close();
    return array;
}

Result helperSum(short array[], int startRange, int endRange, int end){
    
    Result r = {.start = 0, .end = 0, .sum = array[startRange]};
     // for the ranges passed in
     // the sequential sum is calculated for that specific range only
        for (auto i=startRange; i<endRange; ++i) {
            // for every possible ending point for that starting point
            // use <= end so last value is size of array and then for k loop stops 1 before that
            for (auto j=i+1; j<=end; ++j) {
                // compute sum between i and j
                int sum = 0;
                
                for (auto k=i; k<j; ++k) {
                    sum += array[k];
                }
                // if this sum is better
                if (sum > r.sum) {
                    r = { .start = i, .end = j, .sum = sum };
                }
            }
        }
    
        return r;

}

/// compute maximum sum for the subarray
/// - Parameters:
///   - array: array of values as unique pointer dynamically allocated array of short
///   - start: starting index
///   - end: ending index (check from start to (end - 1) so that end can be the size of the array
Result maxSum(short array[], int start, int end, int numThreads) {
   
    // assume best result is just the first value
    Result r = {.start = start, .end = start + 1, .sum = array[start]};
    // comparison result
    Result r1;
    
    // evenly distributing values per thread
    int range = end / numThreads;
    // handles any numbers where numThreads does not divide end
    int remainder = end % numThreads;
    
    std::future<Result> *f = new std::future<Result>[numThreads];
    
    // each thread will launch with a different startingRange and a different endingRange
    for (int i = 0; i < numThreads; i++){
        int startRange = i * range;
        int endRange = (i *  range) + range;
        // for the final thread
        // add the range and the remainder
        if (i == numThreads - 1){
            // f[i] = std::async(std::launch::async, helperSum, array, startRange, end, end);
            endRange = endRange + remainder;
        }
        f[i] = std::async(std::launch::async, helperSum, array, startRange, endRange, end);
    }
    
    
    // waits for threads to finish and compares them to find the max sum
    for (int i = 0; i < numThreads; i++){
        r1 = f[i].get();
        if (r1.sum > r.sum){
            r = r1;
        }
    }
    
    // deallocates the thread array
    delete [] f;
    return r;
}


int main(int argc, const char * argv[]) {
    string filename;
    int numThreads;

    if (argc == 2 && string(argv[1]) == "--usage") {
        cout << "thread [filename]" << endl;
        return 0;
    }

    if (argc < 2) {
//        cout << "enter filename: ";
//        cin >> filename;
        filename = "/Users/tyslu/Library/CloudStorage/OneDrive-Personal/Documents/School Documents/Senior Year!/Parallel Computing/Number Generator/2430.txt";
    }
    else {
        filename = string(argv[1]);
    }

    if (argc == 3) {
        numThreads = atoi(argv[2]);
    }
    else {
        numThreads = 16;
    }

    unsigned int n;
    auto array = readArray(filename, n);

    // time the run and output results
    auto start = high_resolution_clock::now();
    auto result = maxSum(array, 0, n, numThreads);
    auto stop = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    // output timing and result
    cout << "time: " << duration << " (" << (duration / 1.0E6) << " seconds)" << endl;
    cout << result << endl;

    delete [] array;

    return 0;
}
