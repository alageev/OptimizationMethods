//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include <cmath>
#include "Functions.h"


int main(int argc, const char * argv[]) {
    const double halvesResult = halvesMethod(interval, epsilon);
    std::cout << "halves method:       f(x) = " << function(halvesResult)      << ", x = " << halvesResult      << std::endl;
    
    const double goldenRatioResult = goldenRatioMethod(interval, epsilon);
    std::cout << "golden ratio method: f(x) = " << function(goldenRatioResult) << ", x = " << goldenRatioResult << std::endl;
    
    try {
        const double chordesResult = chordesMethod(interval, epsilon);
        std::cout << "chordes method:      f(x) = " << function(chordesResult)     << ", x = " << chordesResult     << std::endl;
    } catch(const std::exception &exception) {
        std::cout << "chordes method: " << exception.what() << std::endl;
    }
    
    try {
        const double newtonResult = newtonMethod(interval, epsilon);
        std::cout << "newton method:       f(x) = " << function(newtonResult)      << ", x = " << newtonResult      << std::endl;
    } catch(const std::exception &exception) {
        std::cout << "newton method: " << exception.what() << std::endl;
    }
    
    return 0;
}
