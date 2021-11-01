//
//  Functions.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 17.10.2021.
//

#ifndef Functions_h
#define Functions_h

#include "Constants.h"

double function(double x) {
    return x * x - 3 * x + x * log(x);
}

double firstDerivative(double x) {
    return 2 * x - 3 + log(x) + x / x;
}

double secondDerivative(double x) {
    return 2 + 1 / x;
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
        throw std::range_error("derivatives have equal sign on both ends of given interval");
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
        
    } while (std::abs(firstDerivative(intersection)) > epsilon);
    
    return intersection;
}

double newtonMethod(Interval interval, double epsilon) {
    
    double x = interval.random();
    
    while (std::abs(firstDerivative(x)) > epsilon) {
        const double newX = x - firstDerivative(x) / secondDerivative(x);
        x = newX;
    }
    
    if (!interval.contains(x)) {
        throw std::range_error("found x = " + std::to_string(x) + " is not in the interval");
    }
    
    return x;
}


double fraction(double a, double b, double c) {
    return function(a) * (b - c);
}

template<typename T, size_t N>
void sort(T (&array)[N]) {
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j > i; j--) {
            if (array[i] > array[j]) {
                const T temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

double quadraticInterpolationMethod(Interval interval, double epsilon) {
    
    double x[4];
    if (function(initialApproximation) < function(initialApproximation + epsilon)) {
        x[0] = initialApproximation - epsilon;
        x[1] = initialApproximation;
        x[2] = initialApproximation + epsilon;
        x[3] = x[2];
    } else {
        x[0] = initialApproximation;
        x[1] = initialApproximation + epsilon;
        x[2] = initialApproximation + 2 * epsilon;
        x[3] = x[2];
    }
    
    while (abs(x[0] - x[1]) >= epsilon) {
        x[3] = (x[0] + x[1]) / 2 +
        (x[2] - x[0]) * (x[2] - x[1]) * (function(x[1]) - function(x[0]))
        / (fraction(x[0], x[1], x[2]) + fraction(x[1], x[2], x[0]) + fraction(x[2], x[0], x[1]));

        sort(x);
    }
    
    return x[0];
}



#endif /* Functions_h */
