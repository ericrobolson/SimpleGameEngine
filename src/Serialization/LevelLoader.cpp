#include "LevelLoader.h"
#include "EntityComponentManager.h"
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "PlayerAssemblage.h"
#include "SolidObjectAssemblage.h"

LevelLoader::LevelLoader()
{
    //ctor
}

LevelLoader::~LevelLoader()
{
    //dtor
}

int ParseIntegers(std::string s){
    int num = 0;

    if (s.empty()){
        return num;
    }

    const int minusChar = 45; // ascii char code for -
    const int zeroCharValue = 48; // ascii char code for 0
    const int nineCharValue = zeroCharValue + 9; // ascii char code for 9

    std::string str;

    for (int i = 0; i < s.size(); i++){
        int c = (int)s[i];

        if (c >=  zeroCharValue && c <= nineCharValue){
            int numberToAdd = c - minusChar;

            str.push_back(s[i]);
        }
    }

    num = std::stoi(str);

    if ((int)s[0] == minusChar){
        num = (-1) * num;
    }

    return num;
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

void CreatePlayer(std::vector<std::string> collection, ECS::EntityComponentManager &ecs){
    int x = 0;
    int y = 0;

    // parse through variable settings
    for (int j = 0; j < collection.size(); j++){
        std::string str = collection[j];

        if (str.find("x=") != std::string::npos){
            x = ParseIntegers(str);
        } else if (str.find("y=") != std::string::npos){
            y = ParseIntegers(str);
        }
    }

    PlayerAssemblage::BuildPlayer(ecs, x, y);
}


void CreateSolidObject(std::vector<std::string> collection, ECS::EntityComponentManager &ecs){
    int x = 0;
    int y = 0;
    int h = 1;
    int w = 1;

    // parse through variable settings
    for (int j = 0; j < collection.size(); j++){
        std::string str = collection[j];

        if (str.find("x=") != std::string::npos){
            x = ParseIntegers(str);
        } else if (str.find("y=") != std::string::npos){
            y = ParseIntegers(str);
        } else if (str.find("h=") != std::string::npos){
            h = ParseIntegers(str);
        } else if (str.find("w=") != std::string::npos){
            w = ParseIntegers(str);
        }
    }

    SolidObjectAssemblage::Build(ecs, x, y, h, w);
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
                    CreatePlayer(objects[i], ecs);
                } else if( objects[i][0] == "solidObject"){
                    CreateSolidObject(objects[i], ecs);
                }
            }
        }
    }
}
