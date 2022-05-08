#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

void Train::create(){
    head = NULL;
}; 

void Train::addMaterial(char material, int weight){
        //FILL THIS FUNCTION ACCORDINGLY
}; 


void Train::deleteFromWagon(char material, int weight){
        //FILL THIS FUNCTION ACCORDINGLY
};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 