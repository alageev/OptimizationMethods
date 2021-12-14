//
//  Constants.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 17.10.2021.
//

#ifndef Constants_h
#define Constants_h


const double mutationProbability = 0.01;
const int populationSize = 4;
const int numberOfCities = 5;
const int idealLength = 31;
const double distances[numberOfCities][numberOfCities] = {
    {0, 4, 5, 3, 8}, // 0
    {4, 0, 7, 6, 8}, // 1
    {5, 7, 0, 7, 9}, // 2
    {3, 6, 7, 0, 9}, // 3
    {8, 8, 9, 9, 0}  // 4
//   0  1  2  3  4
};

#endif /* Constants_h */
