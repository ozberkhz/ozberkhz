#include <iostream>
#include <fstream>
#include <string.h>
#include <vector> 

#include "highwaymap.h"

HighwayMap::HighwayMap(){
    head = new Node();
}

void HighwayMap::prune(Node* root){

    preorder_traverse(root, false, true);

    for (int i = 0; i < city_pruning_vector.size() - 1; i++){
        for (int j = i + 1; j < city_pruning_vector.size(); j++){
            // find the duplicate node (the node that has an excess link on the map) in the vector if it exists
            if (city_pruning_vector[i] == city_pruning_vector[j]){

               Node* currentNode = root;
               Node* previousNode = root;

                // if the distance to the node from the left side is longer than the distance from the right side prune the link from the left
                if (calculate_distance(city_pruning_vector[i], head, true) > calculate_distance(city_pruning_vector[i], head, false)){
                    // searching for the node
                    while(currentNode->name != city_pruning_vector[i]){
                        if (currentNode->leftNode != NULL && currentNode->leftNode->mark_as_traversed != true){
                            previousNode = currentNode;
                            currentNode = currentNode->leftNode;
                        }
                        else if (currentNode->rightNode != NULL && currentNode->rightNode->mark_as_traversed != true){
                            previousNode = currentNode;
                            currentNode = currentNode->rightNode;
                        }
                        else{
                            currentNode->mark_as_traversed = true;
                            currentNode = root;
                        }
                    }

                    // find the excess link that points to the duplicate node

                    if (previousNode->leftNode == currentNode){
                        previousNode->leftNode = NULL;
                    }

                    else{
                        previousNode->rightNode = NULL;
                    }

                }

                // if the distance from the right side is longer or equal to the distance from the left side prune the link from the right

                else{
                    // searching for the node
                    while(currentNode->name != city_pruning_vector[i]){
                        if (currentNode->rightNode != NULL && currentNode->rightNode->mark_as_traversed != true){
                            previousNode = currentNode;
                            currentNode = currentNode->rightNode;
                        }
                        else if (currentNode->leftNode != NULL && currentNode->leftNode->mark_as_traversed != true){
                            previousNode = currentNode;
                            currentNode = currentNode->leftNode;
                        }
                        else{
                            currentNode->mark_as_traversed = true;
                            currentNode = root;
                        }
                    }

                    // find the excess link that points to the duplicate node

                    if (previousNode->leftNode == currentNode){
                        previousNode->leftNode = NULL;
                    }

                    else{
                        previousNode->rightNode = NULL;
                    }

                }

                // reset the mark_as_traversed marks

                preorder_traverse(root, false, false);

                // empty the vector since the function is recursive and the vector will be filled again during recursion

                while (!city_pruning_vector.empty()){
                    city_pruning_vector.pop_back();
                }

                // we have to call the function again to traverse the map again, because an excess link 
                // will create false duplicates while traversing. so we remove the excess link and traverse without
                // excess link in order to find other excess links if they exist

                prune(root);
            }   
        }
    }


    return;
}

void HighwayMap::createmap(std::ifstream& file){
    Node* temp;
    std::string parent_node;
    std::string child_node;
    std::string temp_string;
    int duration;

    while(file >> parent_node >> child_node >> duration){

        // first create the head node

        if (head->name == ""){
            head->name = parent_node;
            head->leftNode = new Node();
            head->leftNode->name = child_node;
            head->leftNode->mark_as_traversed = false;
            head->leftDuration = duration;
        }


        else{
            temp = find_node(parent_node, head);

            // if the child node exists, link he parent node to the child node. linking from the left is prioritized 

            if (find_node(child_node, head) != NULL){
                if (temp->leftNode == NULL){
                    temp->leftDuration = duration;
                    temp->leftNode = find_node(child_node, head);
                    temp->leftNode->mark_as_traversed = false;
                }
                else{
                    temp->rightDuration = duration;
                    temp->rightNode = find_node(child_node, head);
                    temp->rightNode->mark_as_traversed = false;
                }
                continue;
            }

            // else create a node and and link it to the parent. linking from the right is prioritized

            if (temp->leftNode == NULL){
                temp->leftDuration = duration; 
                temp->leftNode = new Node();
                temp->leftNode->name = child_node;
                temp->leftNode->mark_as_traversed = false;
            }
            else if (temp->rightNode == NULL){
                temp->rightDuration = duration; 
                temp->rightNode = new Node();
                temp->rightNode->name = child_node;
                temp->rightNode->mark_as_traversed = false;
            }
        }
    }

    return;
}

Node* HighwayMap::find_node(std::string input, Node* root){
    
    // if we are searching for root return root
    
    if (root != NULL && root->name == input){
        return root;
    }

    while (root != NULL){

        // starting from the root node, function recursively traverses the tree and returns the targeted node

        if (find_node(input, root->leftNode) != NULL && find_node(input, root->leftNode)->name == input){
            return find_node(input, root->leftNode);
        } 

        if (find_node(input, root->rightNode) != NULL && find_node(input, root->rightNode)->name == input){
            return find_node(input, root->rightNode);
        } 

        return NULL;

    }

    return NULL;

}

void HighwayMap::preorder_traverse(Node* root, bool print, bool prune){
    
    if (root != NULL){
        // depending on the parameters we will either print or prune the map while traversing. 
        // if both parameters are false, this function will just traverse the map and turn all mark_as_traversed marks to false. this is important for recursive pruning 

        if (print) {
            std::cout << root->name << " ";
        }
        if (prune) {
            city_pruning_vector.push_back(root->name);
        }
        root->mark_as_traversed = false;
        preorder_traverse(root->leftNode, print, prune);
        preorder_traverse(root->rightNode, print, prune);
    }
        
    return;
}

int HighwayMap::calculate_distance(std::string target, Node* root, bool calculate_from_the_left){

    Node* currentNode = root;
    Node* previousNode = currentNode;
    int distance = 0;

    // reseting the mark_as_traversed bools by calling preorder_traverse()

    preorder_traverse(head, false, false);

    // searching for the target from the left side and calculating the distance

    if (calculate_from_the_left){
        while(currentNode->name != target){
            if (currentNode->leftNode != NULL && currentNode->leftNode->mark_as_traversed != true){
                previousNode = currentNode;
                distance += currentNode->leftDuration;
                currentNode = currentNode->leftNode;
            }
            else if (currentNode->rightNode != NULL && currentNode->rightNode->mark_as_traversed != true){
                previousNode = currentNode;
                distance += currentNode->rightDuration;
                currentNode = currentNode->rightNode;
            }
            else{
                currentNode->mark_as_traversed = true;
                distance = 0;
                currentNode = root;
            }
        }
    }

    // searching for the target from the right side and calculating the distance

    else {
        while(currentNode->name != target){
            if (currentNode->rightNode != NULL && currentNode->rightNode->mark_as_traversed != true){
                previousNode = currentNode;
                distance += currentNode->rightDuration;
                currentNode = currentNode->rightNode;
            }
            else if (currentNode->leftNode != NULL && currentNode->leftNode->mark_as_traversed != true){
                previousNode = currentNode;
                distance += currentNode->leftDuration;
                currentNode = currentNode->leftNode;
            }
            else{
                currentNode->mark_as_traversed = true;
                distance = 0;
                currentNode = root;
            }
        }
    }

    return distance;

}

int calculate_total_duration(std::string target, HighwayMap map1, HighwayMap map2){

    // returns the total distance to a chosen city on the maps

    return map1.calculate_distance(target, map1.head, true) + map2.calculate_distance(target, map2.head, true);

}

std::string calculate_meeting_point(HighwayMap map1, HighwayMap map2){

    std::string meeting_point;
    int duration = 100000;

    // we call these functions because we need to fill the city_pruning_vectors

    map1.preorder_traverse(map1.head, false, true);
    map2.preorder_traverse(map2.head, false, true);

    for (int i = 0; i < map1.city_pruning_vector.size(); i++){
        for (int j = 0; j < map2.city_pruning_vector.size(); j++){
            // find a city that exists on both maps
            if (map1.city_pruning_vector[i] == map2.city_pruning_vector[j]){
                // find the minimal duration and the city that has it
                if (map1.calculate_distance(map1.city_pruning_vector[i], map1.head, true) + map2.calculate_distance(map2.city_pruning_vector[j], map2.head, true) < duration){
                    duration = map1.calculate_distance(map1.city_pruning_vector[i], map1.head, true) + map2.calculate_distance(map2.city_pruning_vector[j], map2.head, true);
                    meeting_point = map1.city_pruning_vector[i];
                }
            }
        }
    }
    return meeting_point;
}

/*
STUDENT NAME: ÖZBERK HAZANTEKİN
STUDENT ID: 150200100
DATE: 27.12.2021
*/