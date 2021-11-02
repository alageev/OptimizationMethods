//
//  Vector.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 02.11.2021.
//

#ifndef Vector_h
#define Vector_h

#include <cmath>


struct Vector {
    double x;
    double y;
    
    Vector(double x, double y) {
        this->x = x;
        this->y = y;
    }
    
    double norm() {
        return std::sqrt(*this * *this);
    }
    
    Vector operator -() {
        return Vector(-this->x, -this->y);
    }
    
    Vector operator +(Vector rhs) {
        return Vector(this->x + rhs.x, this->y + rhs.y);
    }
    
    double operator *(Vector rhs) {
        return this->x * rhs.x + this->y * rhs.y;
    }
    
    Vector operator *(double c) {
        return Vector(this->x * c, this->y * c);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }
};

#endif /* Vector_h */
