//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include "Functions.h"


int main(int argc, const char * argv[]) {
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        const double halvesResult = halvesMethod(interval, epsilon);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto methodTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        
        std::cout << "halves method: " << function(halvesResult) << " at " << halvesResult;
        std::cout << ", t = " << methodTime << std::endl;
    }
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        const double goldenRatioResult = goldenRatioMethod(interval, epsilon);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto methodTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        
        std::cout << "golden ratio method: " << function(goldenRatioResult) << " at " << goldenRatioResult;
        std::cout << ", t = " << methodTime << std::endl;
    }
    try {
        auto startTime = std::chrono::high_resolution_clock::now();
        const double chordesResult = chordesMethod(interval, epsilon);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto methodTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        
        std::cout << "chordes method: " << function(chordesResult) << " at " << chordesResult;
        std::cout << ", t = " << methodTime << std::endl;
    } catch(const std::exception &exception) {
        std::cout << "chordes method: " << exception.what() << std::endl;
    }
    
    try {
        auto startTime = std::chrono::high_resolution_clock::now();
        const double newtonResult = newtonMethod(interval, epsilon);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto methodTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        
        std::cout << "newton method: " << function(newtonResult) << " at " << newtonResult;
        std::cout << ", t = " << methodTime << std::endl;
    } catch(const std::exception &exception) {
        std::cout << "newton method: " << exception.what() << std::endl;
    }
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        const double interpolationResult = quadraticInterpolationMethod(interval, epsilon);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto methodTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        
        std::cout << "interpolation method: " << function(interpolationResult) << " at " << interpolationResult;
        std::cout << ", t = " << methodTime << std::endl;
    }
    
    return 0;
}
