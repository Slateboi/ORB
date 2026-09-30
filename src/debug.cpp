#include <iostream>
#include <vector>
#include "orb/debug.hpp"


namespace orb{
    void printAllCorners(std::vector<std::vector<Corner>>& cornersList){

        int level = 0;

        for(std::vector<Corner>& corners : cornersList){

            std::cout << "--------" << level << "--------" << std::endl;
            
            for(Corner& corner : corners){  
                std::cout << "x: " << corner.x << " y: " << corner.y << " originalx: " << corner.originalx << " originaly: " << corner.originaly << std::endl;

            }

            level++;
        }
        
    }
}