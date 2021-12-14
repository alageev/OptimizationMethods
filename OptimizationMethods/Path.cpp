//
//  Path.cpp
//  OptimizationMethods
//
//  Created by Алексей Агеев on 11.12.2021.
//

#include "Path.h"
#include <cstdlib>
#include <iostream>

Path::Path() {
    int generated = 0;
    
    while (generated < numberOfCities) {
        int newVertex = rand() % numberOfCities;
        bool alreadyInArray = false;
        
        for (int i = 0; i < generated; i++) {
            if (vertices[i] == newVertex) {
                alreadyInArray = true;
                break;
            }
        }
        
        if (!alreadyInArray) {
            vertices[generated] = newVertex;
            generated++;
        }
    }
    
    for (int i = 0; i < numberOfCities; i++) {
        int const thisVertex = vertices[i];
        int const nextVertex = vertices[(i + 1) % numberOfCities];
        length += distances[thisVertex][nextVertex];
    }
}

Path::Path(int* newPath) {
    
    bool mutationOccured = false;
    
    if (rand() % 101 < 100 * mutationProbability) {
        mutationOccured = true;
    }
    
    for (int i = 0; i < numberOfCities; i++) {
        vertices[i] = newPath[i];
    }
    
    if (mutationOccured) {
        int first = rand() % numberOfCities;
        int second = rand() % numberOfCities;
        std::swap(vertices[first], vertices[second]);
    }
    
    for (int i = 0; i < numberOfCities; i++) {
        int const thisVertex = vertices[i];
        int const nextVertex = vertices[(i + 1) % numberOfCities];
        length += distances[thisVertex][nextVertex];
    }
}

std::ostream& operator <<(std::ostream& os, const Path& path) {
    os << path.vertices[0];
    
    for (int i = 1; i < numberOfCities; i++) {
        os << "-" << path.vertices[i];
    }
    
    os << ":" << path.length;
    return os;
}

bool Path::descending(Path lhs, Path rhs) {
    return lhs.length < rhs.length;
}

Crossingover::Crossingover(Path lhs, Path rhs) {
    int newPath[5] = { 0 };
    bool nextParentLhs = bool(rand() % 2);
    int verticesAdded = 0;
    
    int previousIndex = rand() % numberOfCities;
    int previousVertex = nextParentLhs ? lhs.vertices[previousIndex] : rhs.vertices[previousIndex];
    nextParentLhs = !nextParentLhs;
    
    while (verticesAdded < numberOfCities) {
        int index = 0;
        Path currentPath = nextParentLhs ? lhs : rhs;
        
        while (currentPath.vertices[index] != previousVertex) {
            index = (index + 1) % numberOfCities;
        }
        
        index = (index + 1) % numberOfCities;
        bool vertexWasInserted = false;
        
        while (!vertexWasInserted) {
            bool isPresent = false;
            for (int i = 0; i < verticesAdded; i++) {
                if (newPath[i] == currentPath.vertices[index]) {
                    isPresent = true;
                    break;
                }
            }
            if (isPresent) {
                index = (index + 1) % numberOfCities;
            } else {
                newPath[verticesAdded] = currentPath.vertices[index];
                verticesAdded++;
                vertexWasInserted = true;
                previousVertex = currentPath.vertices[index];
                previousIndex = index;
                nextParentLhs = !nextParentLhs;
            }
        }
    }
    
    this->first = Path(newPath);
    
    int secondPath[numberOfCities] = { 0 };
    
    for (int i = 0; i < numberOfCities; i++) {
        secondPath[i] = newPath[numberOfCities - 1 - i];
    }
    this->second = Path(secondPath);
    
//    return Crossingover(first, second);
}

//CrossingoverResult::CrossingoverResult(Path first, Path second) {
//    this->first = first;
//    this->second = second;
//}
