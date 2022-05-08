#ifndef _HEADER
#define _HEADER

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector> 

class Node {
    public:
        int rightDuration;
        int leftDuration;
        std::string name;
        Node* rightNode;
        Node* leftNode;
        bool mark_as_traversed;
};

class HighwayMap {
    public:
        Node* head;
        HighwayMap();
        void createmap(std::ifstream&);
        void prune(Node*);
        Node* find_node(std::string, Node*);
        void preorder_traverse(Node*, bool, bool);
        std::vector<std::string> city_pruning_vector;
        int calculate_distance(std::string, Node*, bool);        
};

int calculate_total_duration(std::string, HighwayMap, HighwayMap);
std::string calculate_meeting_point(HighwayMap, HighwayMap);


#endif

/*
STUDENT NAME: ÖZBERK HAZANTEKİN
STUDENT ID: 150200100
DATE: 27.12.2021
*/