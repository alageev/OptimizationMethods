//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include <cmath>


const double phi = 1.61803398875;

struct Interval {
    double start;
    double end;
    
    Interval(double start, double end) {
        if (start <= end) {
            this->start = start;
            this->end = end;
        } else {
            this->start = end;
            this->end = start;
        }
    }
    
    double middle() {
        return (start + end) / 2;
    }
    
    double length() {
        return (end - start);
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

double halvesMethod(Interval, double);
double goldenRatioMethod(Interval, double);
double chordesMethod(Interval, double);
double newtonMethod(Interval, double);

int main(int argc, const char * argv[]) {
    
    // First variant
    const double epsilon = 0.05;
    const Interval interval = Interval(1, 2);
    
    const double halvesResult = halvesMethod(interval, epsilon);
    std::cout << "halves method:       f(x) = " << function(halvesResult)      << ", x = " << halvesResult      << std::endl;
    
    const double goldenRatioResult = goldenRatioMethod(interval, epsilon);
    std::cout << "golden ratio method: f(x) = " << function(goldenRatioResult) << ", x = " << goldenRatioResult << std::endl;
    
    try {
        const double chordesResult = chordesMethod(interval, epsilon);
        std::cout << "chordes method:      f(x) = " << function(chordesResult)     << ", x = " << chordesResult     << std::endl;
    } catch(const std::exception) {
        std::cout << "chordes method cannot be used on this function on this interval"<< std::endl;
    }
    
    const double newtonResult = newtonMethod(interval, epsilon);
    std::cout << "newton method:       f(x) = " << function(newtonResult)      << ", x = " << newtonResult      << std::endl;
    
    return 0;
}

double halvesMethod(Interval interval, double epsilon) {
    if (interval.length() <= 2 * epsilon) {
        return interval.middle();
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

double goldenRatioMethod(Interval interval, double epsilon) {
    
    double leftCoordinate  = interval.start + (2 - phi) * interval.length();
    double rightCoordinate = interval.start + (phi - 1) * interval.length();
    
    do {
        if (function(leftCoordinate) < function(rightCoordinate)) {
            interval.end = rightCoordinate;
            rightCoordinate = leftCoordinate;
            leftCoordinate = interval.start + (2 - phi) * interval.length();
        } else {
            interval.start = leftCoordinate;
            leftCoordinate = rightCoordinate;
            rightCoordinate = interval.start + (phi - 1) * interval.length();
        }
    } while (interval.length() > 2 * epsilon);
    
    return interval.middle();
}


double chordesMethod(Interval interval, double epsilon) {
    
    if (firstDerivative(interval.start) * firstDerivative(interval.end) >= 0) {
        throw std::range_error("invalid interval");
    }
    
    double intersection;
    
    do {
        double difference = firstDerivative(interval.start) - firstDerivative(interval.end);
        double ratio = firstDerivative(interval.start) / difference;
        intersection = interval.start + ratio * interval.length();
        
        if (firstDerivative(intersection) < 0) {
            interval.start = intersection;
        } else {
            interval.end = intersection;
        }
        
    } while (std::abs(firstDerivative(intersection)) <= epsilon);
    
    return intersection;
}

double newtonMethod(Interval interval, double epsilon) {
    
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
    
    return x;
}
