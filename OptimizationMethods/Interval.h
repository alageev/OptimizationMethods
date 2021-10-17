//
//  Interval.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 17.10.2021.
//

#ifndef Interval_h
#define Interval_h

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
        return (start <= value) && (value <= end);
    }
    
    double random() {
        srand(time(NULL));
        return double(rand()) / double(RAND_MAX) * length() + start;
    }
};

#endif /* Interval_h */
