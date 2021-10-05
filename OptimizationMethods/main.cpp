//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include <cmath>


struct Point {
    double coordinate;
    double value;
    
    Point(double coordinate, double value) {
        this->coordinate = coordinate;
        this->value = value;
    }
};

struct Interval {
    double start;
    double end;
    
    Interval(double start, double end) {
        this->start = start;
        this->end = end;
    }
    
    double middle() {
        return (start + end) / 2;
    }
    
    double length() {
        return (end - start) / 2;
    }
    
    bool contains(double value) {
        return start <= value && value <= end;
    }
    
    double random() {
        srand(time(NULL));
        return double(rand()) / double(RAND_MAX) * length() + start;
    }
};

inline double function(double x) {
    return x * x + 3 * x + std::log(x);
}

inline double firstDerivative(double x) {
    return 2 * x + 3 + 1 / x;
}

inline double secondDerivative(double x) {
    return 2 - 1 / (x * x);
}

Point halvesMethod(Interval, double);
Point goldenRatioMethod(Interval, double);
Point chordesMethod(Interval, double);
Point newtonMethod(Interval, double);

int main(int argc, const char * argv[]) {
    
    // First variant
    const double epsilon = 0.05;
    const Interval interval = Interval(1, 2);
    
    std::cout << halvesMethod(interval, epsilon).value << std::endl;
    std::cout << goldenRatioMethod(interval, epsilon).value << std::endl;
    std::cout << chordesMethod(interval, epsilon).value << std::endl;
    std::cout << newtonMethod(interval, epsilon).value << std::endl;
    
    return 0;
}

Point halvesMethod(Interval interval, double epsilon) {
    
    // Checking condition satisfaction
    if (interval.length() <= 2 * epsilon) {
        return Point(interval.middle(), function(interval.middle()));
    }
    
    const double middle = interval.middle();
    const double leftCoordinate  = middle - epsilon;
    const double rightCoordinate = middle + epsilon;
    
    if (function(leftCoordinate) < function(rightCoordinate)) {
        return halvesMethod(Interval(interval.start, leftCoordinate), epsilon);
    } else {
        return halvesMethod(Interval(rightCoordinate, interval.end), epsilon);
    }
}

Point goldenRatioMethod(Interval interval, double epsilon) {
    if (interval.length() <= 2 * epsilon) {
        return Point(interval.middle(), function(interval.middle()));
    }
    
    const double intervalLength = interval.length();
    const double leftCoordinate  = interval.start + 0.38196601125 * intervalLength;
    const double rightCoordinate = interval.start + 0.61803398875 * intervalLength;
    
    if (function(leftCoordinate) < function(rightCoordinate)) {
        return halvesMethod(Interval(interval.start, rightCoordinate), epsilon);
    } else {
        return halvesMethod(Interval(leftCoordinate, interval.end), epsilon);
    }
}


// If signs of the derivative on both sides are equal, function returns least of the ends
Point chordesMethod(Interval interval, double epsilon) {
    
    if (firstDerivative(interval.start) * firstDerivative(interval.end) >= 0) {
        if (firstDerivative(interval.start) > 0) {
            return Point(interval.start, function(interval.start));
        } else {
            return Point(interval.end, function(interval.end));
        }
    }
        
    const double intersection = interval.start + firstDerivative(interval.start) / (firstDerivative(interval.start) - firstDerivative(interval.end)) * interval.length();
    
    if (std::abs(firstDerivative(intersection)) <= epsilon) {
        return Point(intersection, function(intersection));
    }
    
    if (firstDerivative(intersection) < 0) {
        return chordesMethod(Interval(intersection, interval.end), epsilon);
    } else {
        return chordesMethod(Interval(interval.start, intersection), epsilon);
    }
}

Point newtonMethod(Interval interval, double epsilon) {
    
    // Random is taken just for fun, because the specification didn't stated it should be in the middle of the interval:)
    double x = interval.random();
    
    // Breaks if accuracy condition is satisfied or new x is not inside the interval anymore
    while (std::abs(firstDerivative(x)) > epsilon) {
        const double newX = x - firstDerivative(x) / secondDerivative(x);
        if (interval.contains(newX)) {
            x = newX;
        } else {
            break;
        }
    }
    
    return Point(x, function(x));
}
