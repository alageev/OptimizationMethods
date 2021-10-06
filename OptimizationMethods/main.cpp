//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include <cmath>

const double phi = 1.61803398875;

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
    return x * x - 3 * x + x * log(x);
}

inline double firstDerivative(double x) {
    return 2 * x - 3 + log(x) + x / x;
}

inline double secondDerivative(double x) {
    return 2 + 1 / x;
}

Point halvesMethod(Interval, double);
Point goldenRatioMethod(Interval, double);
Point chordesMethod(Interval, double);
Point newtonMethod(Interval, double);

int main(int argc, const char * argv[]) {
    
    // First variant
    const double epsilon = 0.05;
    const Interval interval = Interval(1, 2);
    
    const Point halvesResult = halvesMethod(interval, epsilon);
    const Point goldenRatioResult = goldenRatioMethod(interval, epsilon);
    const Point chordesResult = chordesMethod(interval, epsilon);
    const Point newtonResult = newtonMethod(interval, epsilon);
    
    std::cout << "halves method:       f(x) = " << halvesResult.value      << ", x = " << halvesResult.coordinate      << std::endl;
    std::cout << "golden ratio method: f(x) = " << goldenRatioResult.value << ", x = " << goldenRatioResult.coordinate << std::endl;
    std::cout << "chordes method:      f(x) = " << chordesResult.value     << ", x = " << chordesResult.coordinate     << std::endl;
    std::cout << "newton method:       f(x) = " << newtonResult.value      << ", x = " << newtonResult.coordinate      << std::endl;
    
    return 0;
}

Point halvesMethod(Interval interval, double epsilon) {
    // Checking condition satisfaction
    if (interval.length() <= 2 * epsilon) {
        return Point(interval.middle(), function(interval.middle()));
    }
    
    const double middle = interval.middle();
    const double leftCoordinate  = middle - epsilon / 2;
    const double rightCoordinate = middle + epsilon / 2;
    
    if (function(leftCoordinate) < function(rightCoordinate)) {
        return halvesMethod(Interval(interval.start, leftCoordinate), epsilon);
    } else {
        return halvesMethod(Interval(rightCoordinate, interval.end), epsilon);
    }
}

Point goldenRatioMethod(Interval interval, double epsilon) {
    
    double leftCoordinate  = interval.start + (2 - phi) * interval.length();
    double rightCoordinate = interval.start + (phi - 1) * interval.length();
    
    while (interval.length() > 2 * epsilon) {
        if (function(leftCoordinate) < function(rightCoordinate)) {
            interval.end = rightCoordinate;
            rightCoordinate = leftCoordinate;
            leftCoordinate = interval.start + (2 - phi) * interval.length();
        } else {
            interval.start = leftCoordinate;
            leftCoordinate = rightCoordinate;
            rightCoordinate = interval.start + (phi - 1) * interval.length();
        }
    }
    
    return Point(interval.middle(), function(interval.middle()));
}


// If signs of the derivative on both sides are equal, function returns least of the ends
Point chordesMethod(Interval interval, double epsilon) {
    
    if (firstDerivative(interval.start) * firstDerivative(interval.end) > 0) {
        if (firstDerivative(interval.start) > 0) {
            return Point(interval.start, function(interval.start));
        } else {
            return Point(interval.end, function(interval.end));
        }
    }
    
    if (firstDerivative(interval.start) * firstDerivative(interval.end) == 0) {
        const double x = firstDerivative(interval.start) < firstDerivative(interval.end) ? interval.start : interval.end;
        return Point(x, function(x));
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
