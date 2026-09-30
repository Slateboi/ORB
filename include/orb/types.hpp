#pragma once

namespace orb{
    struct Corner{
        int x;
        int y;
        int score;

        int originalx;
        int originaly;
        
        int level; 

        float angle = 0.0f;
    };
}

