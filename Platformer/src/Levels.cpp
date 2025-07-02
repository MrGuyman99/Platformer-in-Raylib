#include<string>
#include<vector>
#include "Levels.hpp"

//This just stores and returns level paths, nothing too crazy
const std::string level0 = "Levels/TestLevel.txt";
const std::string level1 = "Levels/Level1.txt";

std::vector<std::string> returnbingus(){
    
    return {level0, level1};

}