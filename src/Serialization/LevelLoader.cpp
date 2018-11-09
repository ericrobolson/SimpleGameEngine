#include "LevelLoader.h"
#include "EntityComponentManager.h"
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "PlayerAssemblage.h"

LevelLoader::LevelLoader()
{
    //ctor
}

LevelLoader::~LevelLoader()
{
    //dtor
}

std::string RemoveSubstring(std::string s, std::string subString){
    if (s.empty()){
        return s;
    }

    size_t start_pos = s.find(subString);
    if (start_pos != std::string::npos){
        s.replace(start_pos, subString.length(), "");

        s = RemoveSubstring(s, subString);
    }

    return s;
}

std::string RemoveWhitespace(std::string s){
    s = RemoveSubstring(s, " ");
    s = RemoveSubstring(s, "\n");
    s = RemoveSubstring(s, "\r");

    return s;
}

void LevelLoader::LoadLevel(std::string levelName, ECS::EntityComponentManager &ecs){
    ecs.Reset();

    std::string fileLocation = "assets/levels/"+ levelName + ".lvl";
    std::ifstream file(fileLocation, std::ios::in);

    if (file.is_open()){
        int objectIndex = 0;
        int componentIndex = 0;
        int maxObjects = ECS::MAXNUMBEROFENTITIES;
        int maxComponents = ECS::MAXNUMBEROFCOMPONENTTABLES;

        std::vector<std::string> objects[maxObjects];

        // Load the objects
        for(std::string line; getline(file, line);){
            if (line.length() > 0){
                // skip comments
                if (line[0] == '#' || line[0] == '{'){
                    continue;
                }
                // Move on to next object
                else if (line[0] == '}'){
                    objectIndex++;
                    componentIndex = 0;
                }
                else{
                    objects[objectIndex].push_back(RemoveWhitespace(line));
                }
            }
        }

        file.close();

        // Create the objects
        for (int i = 0; i < maxObjects; i++){
            if (objects[i].size() > 0){
                if (objects[i][0] == "player"){
                    int x = 100;
                    int y = 0;

                    std::string xStr = objects[i][1];
                    //x = std::stoi(xStr);
                    PlayerAssemblage::BuildPlayer(ecs, x, y);
                }


                std::shared_ptr<int> entityIdPtr = ecs.AddEntity();
                if (entityIdPtr != nullptr){
                    int entityId = *entityIdPtr.get();
                }
            }
        }
    }
}
