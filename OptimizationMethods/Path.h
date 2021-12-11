//
//  Path.h
//  OptimizationMethods
//
//  Created by Алексей Агеев on 11.12.2021.
//

#ifndef Path_h
#define Path_h


struct Path {
    int vertices[5] = { 0 };
    int length = 0;
    
    Path() {
        int generated = 0;
        
        while (generated < 5) {
            int newVertex = rand() % 5;
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
        
        for (int i = 0; i < 5; i++) {
            int const thisVertex = vertices[i];
            int const nextVertex = vertices[(i + 1) % 5];
            length += distances[thisVertex][nextVertex];
        }
    }
};

#endif /* Path_h */
