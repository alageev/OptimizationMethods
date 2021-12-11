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
const double distances[5][5] = {
    {0, 4, 5, 3, 5},
    {4, 0, 7, 6, 8},
    {5, 7, 0, 7, 9},
    {3, 6, 7, 0, 9},
    {8, 8, 9, 9, 0}
}

#endif /* Constants_h */
