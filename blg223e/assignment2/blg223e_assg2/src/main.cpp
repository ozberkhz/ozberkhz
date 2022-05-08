#include <iostream>
#include <fstream>
#include <string.h>
#include <vector> 

#include "highwaymap.h"

int main(int argc, char* argv[]){

    HighwayMap first_map;
    HighwayMap second_map;
    std::string target_city;
    int total_duration;

    //opening the files

    std::ifstream first_file;
    first_file.open(argv[1]);
    std::ifstream second_file;
    second_file.open(argv[2]);

    // creating, pruning and then traversing the maps

    first_map.createmap(first_file);
    first_map.prune(first_map.head);
    std::cout << "FRIEND-1: ";
    first_map.preorder_traverse(first_map.head, true, false);


    second_map.createmap(second_file);
    second_map.prune(second_map.head);
    std::cout << "\nFRIEND-2: ";
    second_map.preorder_traverse(second_map.head, true, false);

    // calculating the meeting point and total duration

    target_city = calculate_meeting_point(first_map, second_map);
    total_duration = calculate_total_duration(target_city, first_map, second_map);

    std::cout << "\n\nMEETING POINT: " << target_city << std::endl;
    std::cout << "TOTAL DURATION COST: " << total_duration << std::endl;

    first_file.close();
    second_file.close();

    return 0;
}

/*
STUDENT NAME: ÖZBERK HAZANTEKİN
STUDENT ID: 150200100
DATE: 27.12.2021
*/