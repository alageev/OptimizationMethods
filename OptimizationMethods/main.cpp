//
//  main.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 05.10.2021.
//

#include <iostream>
#include "Constants.h"
#include "Path.h"


int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    Path currentPopulation[populationSize];
    int currentLength = INT_MAX;
    int currentIteration = 0;
    
    while (currentLength > idealLength) {
        
        int probabilityAccumulator[populationSize] = { currentPopulation[0].length };
        for (int i = 1; i < populationSize; i++) {
            probabilityAccumulator[i] = currentPopulation[i].length + currentPopulation[i - 1].length;
        }
        
        //Finding first to participate in crossingover
        int const randomChosenFirst = rand() % probabilityAccumulator[populationSize - 1];
        
        Path first;
        int skipIndex = 0;
        
        for (int i = 0; i < populationSize; i++) {
            if (randomChosenFirst < probabilityAccumulator[i]) {
                first = currentPopulation[i];
                skipIndex = i;
                break;
            }
        }
        
        //Removing first chosen from population
        probabilityAccumulator[0] = currentPopulation[0].length;
        
        //Recalculating probabilities without first
        for (int i = 1; i < populationSize - 1; i++) {
            probabilityAccumulator[i] = currentPopulation[i].length + currentPopulation[i - 1].length;
        }
        
        int const randomChosenSecond = rand() % probabilityAccumulator[populationSize - 2];
        
        Path second;
        
        for (int i = 0; i < populationSize; i++) {
            if (randomChosenSecond < probabilityAccumulator[i]) {
                second = currentPopulation[i];
                break;
            }
        }
        
        Crossingover crossingover = Crossingover(first, second);
        
        Path newPopulation[populationSize + 2];
        
        for (int i = 0; i < populationSize - 1; i++) {
            newPopulation[i] = currentPopulation[i];
        }
        
        newPopulation[populationSize - 1] = first;
        newPopulation[populationSize    ] = crossingover.first;
        newPopulation[populationSize + 1] = crossingover.second;
        
        std::sort(std::begin(newPopulation), std::end(newPopulation), Path::descending);
        
        for (int i = 0; i < populationSize; i++) {
            currentPopulation[i] = newPopulation[i];
        }
        
        currentLength = currentPopulation[0].length;
        currentIteration++;
        std::cout << currentIteration << ": " << currentLength << "\n";
    }
    
    return 0;
}
