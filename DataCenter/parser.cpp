#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "parser.h"
#include "Objects\worldData.h"

Parser::Parser() {

}

Parser::~Parser() {
    
}

WorldData* Parser::ParseFile(char* filename) {
    WorldData* data = new WorldData();
    if(filename[0] == '\0') {
        std::cout << "No file provided." << std::endl;
        return data;
    }

    std::ifstream file(std::string("DataCenter\\DataFiles\\Inputs\\") + filename + ".txt");
    if (!file.is_open()) {
        std::cout << "Could not open file!" << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        line.erase(line.find_last_not_of(" \t\n\r") + 1);

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if(cmd == "TEXTURES_ON") {
            ss >> data->TEXTURES_ON;
        } else if(cmd == "RANDOM_SEED") {
            ss >> data->RANDOM_SEED;
        } else if(cmd == "PERLIN_HILL_SCALE") {
            ss >> data->PERLIN_HILL_SCALE;
        } else if(cmd == "FRACTAL_OCTAVES") {
            ss >> data->FRACTAL_OCTAVES;
        } else if(cmd == "FRACTAL_LACUNARITY") {
            ss >> data->FRACTAL_LACUNARITY;
        } else if(cmd == "FRACTAL_GAIN") {
            ss >> data->FRACTAL_GAIN;
        } else if(cmd == "ISO_VALUE") {
            ss >> data->ISO_VALUE;
        } else if(cmd == "ALT_COLOR_R") {
            ss >> data->ALT_COLOR_R;
        } else if(cmd == "ALT_COLOR_G") {
            ss >> data->ALT_COLOR_G;
        } else if(cmd == "ALT_COLOR_B") {
            ss >> data->ALT_COLOR_B;
        } else if(cmd == "MESH_ROTATION") {
            ss >> data->MESH_ROTATION;
        } else if(cmd == "MESH_Y_TRANSLATION") {
            ss >> data->MESH_Y_TRANSLATION;
        } else if(cmd == "MESH_Z_TRANSLATION") {
            ss >> data->MESH_Z_TRANSLATION;
        } else if(cmd == "VIEW_DISTANCE") {
            ss >> data->VIEW_DISTANCE;
        } else if(cmd == "WORLD_WINDOW_SIZE") {
            ss >> data->WORLD_WINDOW_SIZE;
        } else if(cmd == "Ka") {
            ss >> data->Ka;
        } else if(cmd == "Kd") {
            ss >> data->Kd;
        } else if(cmd == "Ks") {
            ss >> data->Ks;
        } else if(cmd == "Kgls") {
            ss >> data->Kgls;
        } else if(cmd == "SAND_LEVEL") {
            ss >> data->SAND_LEVEL;
        } else if(cmd == "GRASS_LEVEL") {
            ss >> data->GRASS_LEVEL;
        } else if(cmd == "ROCK_LEVEL") {
            ss >> data->ROCK_LEVEL;
        }
    }

    file.close();
    return data;
}