#include<string>
#include<vector>
#include "Levels.hpp"

//This just stores and returns level paths, nothing to crazy
const std::string level0 = "C:/Users/bodie/OneDrive/Documents/Games/Platformer/Levels/TestLevel.txt";
const std::string level1 = "C:/Users/bodie/OneDrive/Documents/Games/Platformer/Levels/Level1.txt";

std::vector<std::string> returnbingus(){
    
    return {level0, level1};

}