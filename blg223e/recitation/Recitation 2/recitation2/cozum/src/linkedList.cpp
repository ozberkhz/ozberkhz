#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

void LinkedList::changeHead(Node* a){
    this->head = a;
    return;
}

void LinkedList::reorderList(){
    Node* current = head;
    Node* next_pointer = current->next;
    char temp;

    while(true){
        if (current->letter > next_pointer->letter){
            temp = current->letter;
            current->letter = next_pointer->letter;
            next_pointer->letter = temp;
            current = head;
            next_pointer = current->next;
            continue;
        }
        if(next_pointer->next == NULL){
            break;
        }
        current = current->next;
        next_pointer = next_pointer->next;
    }
    return;
};

void LinkedList::removeDublicates(){
    Node* current = head;
    Node* next_pointer = head->next;
    while (next_pointer != NULL){
        if ((current->letter == next_pointer->letter) && (current == head)){
            delete current;
            head = next_pointer;
            current = next_pointer;
            next_pointer = current->next;
        }
        else if (current->letter == next_pointer->letter){
            next_pointer = next_pointer->next;
            delete current->next;
            current->next = next_pointer;
        }
        else{
            current = current->next;
            next_pointer = next_pointer->next;
        }
    }
    return;
};

void LinkedList::reverseList(){
    Node* previous;
    Node* current;
    Node* next_pointer;

    current = head;
    previous = NULL;

    while (current != NULL){
        next_pointer = current->next;
        current->next = previous;
        previous = current;
        current = next_pointer;
    }
    head = previous;
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};

/* 
Student Name: Özberk Hazantekin
Student ID: 150200100
Date: 26.10.2021
*/