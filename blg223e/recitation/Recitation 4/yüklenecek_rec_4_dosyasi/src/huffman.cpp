#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

int Huffman::findindex(Token *arr,string elem){
	// YOU HAVE TO COMPLETE THIS PART
	// THIS FUNCTION RETURNS THE INDEX OF STRING ON TOKEN ARRAY, IF STRING IS NOT IN TOKEN ARRAY, RETURNS -1

    for (int i = 0; i < token_count; i++){
        if (arr[i].symbol == elem){
            return i;
        }
    }
    return -1; 
}

void Huffman::find_frequencies()
{

    string empty;

    // THE LOOP BELOW RESETS THE ARRAY TO CALCULATE THE FREQUENCIES AGAIN

    for (int i = 0; i < token_count; i++){
        token_array[i].symbol = empty;
        token_array[i].code = empty;
        token_array[i].count = 0;
    }

    token_count = 0;

    //int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);
        // YOU HAVE TO COMPLETE THIS PART

        // FIND THE SYMBOLS IN THE STRING AND EVALUATE HOW MANY TIMES THEY REPEAT

        bool not_in_token_array = true;

        for (int i = 0; i <= token_count; i++){
            if (token_array[i].symbol == s){
                token_array[i].count += 1;
                not_in_token_array = false;
            }
        }
        if (not_in_token_array){
            token_array[token_count].symbol = s;
            token_array[token_count].count = 1;
            token_count++;
        }

    }

    /*for (int i = 0; i < token_count; i++){                                                                // DEBUG CODE
        cout << "There are " << token_array[i].count << " instances of " << token_array[i].symbol << endl;  // DEBUG CODE
    }*/                                                                                                     // DEBUG CODE

    file_obj.close();

    return;
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
	// YOU HAVE TO COMPLETE THIS PART

    Node* tempNode;
    tempNode = head;

    // IF THE QUEUE IS EMPTY, CREATE IT

    if (head == NULL) {
        head = newnode;
        //cout << newnode->token.symbol << " has been pushed into the priority queue 1" << endl; // DEBUG CODE
        return;
    }

    else{

    // IF THE COUNT OF NEWNODE IS SMALLER THAN THE HEAD NODE, MAKE NEWNODE THE NEW HEAD NODE
        
        if (newnode->token.count < head->token.count){
            head = newnode;
            head->next = tempNode;
            //cout << newnode->token.symbol << " has been pushed into the priority queue 2" << endl; // DEBUG CODE
            return;
        }

    // ELSE, FIND A NODE WHOSE COUNT IS GREATER THAN NEWNODE AND PUT THE NEWNODE BEFORE IT

        else{
            while (tempNode->next != NULL && newnode->token.count > tempNode->next->token.count){
                tempNode = tempNode->next;
            }
            newnode->next = tempNode->next;
            tempNode->next = newnode;
            //cout << newnode->token.symbol << " has been pushed into the priority queue 3" << endl; // DEBUG CODE
        }

    }

}

Node* PriorityQueue::pop()
{
    // YOU HAVE TO COMPLETE THIS PART

    // REMOVES THE TOP OF THE QUEUE AND RETURNS IT

    Node* temp = head;
    head = head->next;
    return temp;

}

void Huffman::get_priority_queue()
{
    // YOU HAVE TO COMPLETE THIS PART  

    // COPY EVERY ELEMENT FROM THE TOKEN ARRAY AND PUSH THEM INTO THE PRIORITY QUEUE, THEREFORE GETTING THE PRIORITY QUEUE

    Node* temp;

    for (int i = 0; i < token_count; i++){
        temp = new Node();
        temp->token = token_array[i];
        //cout << "token_array[i].symbol is " << token_array[i].symbol << endl; // DEBUG CODE
        priority_queue.push(temp);
    }

    /*temp = priority_queue.head;                                           // DEBUG CODE
                                                                            // DEBUG CODE
    for (int i = 0; i < token_count; i++){                                  // DEBUG CODE
        cout << temp->token.symbol << " " << temp->token.count << endl;     // DEBUG CODE
        temp = temp->next;                                                  // DEBUG CODE
    }                                                                       // DEBUG CODE
    */         
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    // CREATES A PARENT NODE IN ORDER TO MERGE TWO NODES AND APPENDS IT TO THE ROOT OF THE TREE

    Node* temp = new Node();
    temp->left = node1;
    temp->right = node2;
    temp->token.count = node1->token.count + node2->token.count;
    temp->token.symbol = node1->token.symbol + node2->token.symbol;
    root = temp;
    return root;

}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    Node* firstNode;
    Node* secondNode;
    // YOU HAVE TO COMPLETE THIS PART 

    // MERGES TWO NODES AND PUSHES THEM BACK INTO THE PRIORITY QUEUE
    while(priority_queue.head->next != NULL){
        firstNode = priority_queue.pop();
        secondNode = priority_queue.pop();
        priority_queue.push(huffman_binary_tree.merge(firstNode, secondNode));
    }
    
}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    // YOU HAVE TO COMPLETE THIS PART
    // A RECURSIVE FUNCTION APPENDS CODEPART STRING 1 OR 0 ACCORDING TO THE HUFFMAN BINARY TREE

    if(traversal != NULL){
        get_codes(traversal->left, codepart + "0");
        get_codes(traversal->right, codepart + "1");
        traversal->token.code = codepart;
        for (int i = 0; i < token_count; i++){
            if (traversal->token.symbol == token_array[i].symbol){
                token_array[i].code = codepart; // MODIFIES THE TOKEN ARRAY ACCORDING TO THE HUFFMAN BINARY TREE
            }
        }   
        //cout << traversal->token.symbol << " has been given the code " << traversal->token.code << endl; //DEBUG CODE
    }

}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}

/*
Student Name: Özberk Hazantekin
Student ID: 150200100
Date:
*/