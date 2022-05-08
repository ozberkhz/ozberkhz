#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "linkedList.h"

using namespace std; 


int main(int argc, char* argv[]) {
	system("clear");

    FILE* filep = fopen(argv[1], "r");
    char c;

    LinkedList newLinkedList;
    Node* last = new Node();
    newLinkedList.changeHead(last);
    Node* temp;
    c = fgetc(filep);
    last->letter = c;

    while(true){
        c = fgetc(filep);
        if (feof(filep)){
            break;
        }
        if (c != '\n'){      
            temp = new Node();
            last->next = temp;
            last = temp;
            last->letter = c;
        }  
    }
    fclose(filep);

    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();


    return EXIT_SUCCESS;
}

/* 
Student Name: Özberk Hazantekin
Student ID: 150200100
Date: 26.10.2021
*/
