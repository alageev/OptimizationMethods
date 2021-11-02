//
//  Functions.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 17.10.2021.
//

#ifndef Functions_h
#define Functions_h

#include "Vector.h"


double function(Vector vector) {
    return vector.x * vector.x - vector.x * vector.y + vector.y * vector.y - 2 * vector.x + vector.y;
}

double xDerivative(Vector vector) {
    return 2 * vector.x - vector.y - 2;
}

double yDerivative(Vector vector) {
    return -vector.x + 2 * vector.y + 1;
}

Vector gradF(Vector vector) {
    return Vector(xDerivative(vector), yDerivative(vector));
}

Vector gradientDescent(Vector vector) {
    Vector minVector = vector;
    Vector antigradient = -gradF(minVector);
    
    while (antigradient.norm() >= epsilon) {
        Vector newVector = minVector + antigradient * step;
        minVector = newVector;
        antigradient = -gradF(newVector);
    }
    
    return minVector;
}

// vector vector vector vector
#endif /* Functions_h */
