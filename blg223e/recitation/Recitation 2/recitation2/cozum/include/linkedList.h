#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    public:
        char letter;
        Node* next;
};


class LinkedList{

    Node* head;

    public:

        void changeHead(Node*);
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif

/* 
Student Name: Özberk Hazantekin
Student ID: 150200100
Date: 26.10.2021
*/