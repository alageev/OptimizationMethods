//
//  Path.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 11.12.2021.
//

#ifndef Path_h
#define Path_h
#include "Constants.h"
#include <iostream>

struct CrossingoverResult;

struct Path {
    int vertices[numberOfCities] = { 0 };
    int length = 0;

    Path();
    Path(int*);
    
    CrossingoverResult operator+(Path rhs);
    friend std::ostream& operator <<(std::ostream&, const Path&);
    static bool descending(Path, Path);
};

struct Crossingover {
    Path first;
    Path second;
    
    Crossingover(Path, Path);
};


#endif /* Path_h */
