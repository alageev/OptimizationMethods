//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include "Constants.h"
#include "Functions.h"


int main(int argc, const char * argv[]) {
    
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        const Vector gradientResult = gradientDescent(initialVector);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto methodTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        
        std::cout << "gradient descent method: " << function(gradientResult) << " at " << gradientResult;
        std::cout << ", t = " << methodTime << std::endl;
    }
    
    return 0;
}
