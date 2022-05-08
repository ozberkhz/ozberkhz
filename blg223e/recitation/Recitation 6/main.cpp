#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

string file_path;

bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();


int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;


}


void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "D: List 5 products with the highest revenue for each day" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
            terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
// *********************Fill this method 

    ifstream filep;
    filep.open(file_path,ios::in);

    multimap<string, double> productMap;
    multimap<string, double> totalSum;
    multimap<double, string, greater <double> > totalSumSymmetric; // greater double sorts the prices in a decreasing order

    string productname;
    double price;
    int amount;
    string day;

    filep >> productname >> productname >> productname >> productname; // skipping the first line of the text file as it contains no data

    while (filep >> productname >> price >> amount >> day) {
        productMap.insert(pair<string,double>(productname, price * amount)); // copying the products to a multimap with their full revenue
    }

    for (auto itr = productMap.begin(); itr != productMap.end(); itr++){ // summing the total revenues for all products and adding them to another multimap
        if (totalSum.find(itr->first) != totalSum.end()){          // if product exists in the totalSum map, update the total revenue of the product
            totalSum.find(itr->first)->second += itr->second;
        }
        else{                                                      // else, insert the product into the totalSum map
            totalSum.insert(pair<string, double>(itr->first, itr->second));
        }
    }

    for (auto itr = totalSum.begin(); itr != totalSum.end(); itr++){
        totalSumSymmetric.insert(pair<double,string>(itr->second, itr->first)); // changing the values and keys of our multimap by using another multimap
    }

    cout << "5 products with the highest revenue for total are:" << endl;

    int five_loops = 5;
    auto itr = totalSumSymmetric.begin();

    while (five_loops) { //when five_loops equals 0 the while loop will stop, so we will only get the first five products as the output
        cout << itr->second << " " << fixed << setprecision(2) << itr->first << endl;
        itr++;
        five_loops--;
    }

    filep.close();

    return;
}



void listDay()
{
// *********************Fill this method 

    ifstream filep;
    filep.open(file_path,ios::in);

    string productname;
    double price;
    int amount;
    string day;

    multimap<string, multimap<string,double>> revenueMap;
    multimap<string, double> revenueByProduct;
    
    multimap<string, multimap<double,string, greater<double>>> revenueMapSymmetric;
    multimap<double, string, greater<double> > revenueByProductSymmetric;

    filep >> productname >> productname >> productname >> productname; // skipping the first line of the text file as it contains no data

    while (filep >> productname >> price >> amount >> day) {
        if (revenueMap.find(day) != revenueMap.end() && revenueMap.find(day)->second.find(productname) != revenueMap.find(day)->second.end()){
            revenueMap.find(day)->second.find(productname)->second += price * amount;   // if the day and the product exist, update the total revenue
        }
        else if (revenueMap.find(day) != revenueMap.end()){
            revenueMap.find(day)->second.insert(make_pair(productname, price * amount)); // if only the day exists, than insert the product and its revenue into the inner multimap that the day holds
        }
        else{
            revenueByProduct.insert(make_pair(productname, price * amount)); // if neither the day nor its product and its revenue exist in the outer multimap, insert them into the multimap
            revenueMap.insert(make_pair(day, revenueByProduct));
            revenueByProduct.erase(productname);
        }
    }

    for (auto itr = revenueMap.begin(); itr != revenueMap.end(); itr++){    // copy the revenueMap into another map in order to sort it by day and revenue
        for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
            if (revenueMapSymmetric.find(itr->first) != revenueMapSymmetric.end()){ // if day exists insert the product and revenue into the inner multimap
                revenueMapSymmetric.find(itr->first)->second.insert(make_pair(itr2->second, itr2->first));
            }
            else{                                                                   // else insert both the day and the inner multimap
                revenueByProductSymmetric.insert(make_pair(itr2->second, itr2->first));
                revenueMapSymmetric.insert(make_pair(itr->first, revenueByProductSymmetric));
                revenueByProductSymmetric.erase(itr2->second);
            }
        }
    }

    int five_loops = 5;
    int seven_loops = 7;
    multimap<double,string>::iterator itr;

    while (seven_loops){
        switch (seven_loops){ // switch the day
            case 7:
            itr = revenueMapSymmetric.find("Monday")->second.begin();
            cout << "5 products with the highest revenue for Monday are:" << endl;
            break;
            case 6:
            itr = revenueMapSymmetric.find("Sunday")->second.begin();
            cout << "5 products with the highest revenue for Sunday are:" << endl;
            break;
            case 5:
            itr = revenueMapSymmetric.find("Tuesday")->second.begin();
            cout << "5 products with the highest revenue for Tuesday are:" << endl;
            break;
            case 4:
            itr = revenueMapSymmetric.find("Wednesday")->second.begin();
            cout << "5 products with the highest revenue for Wednesday are:" << endl;
            break;
            case 3:
            itr = revenueMapSymmetric.find("Thursday")->second.begin();
            cout << "5 products with the highest revenue for Thursday are:" << endl;
            break;
            case 2:
            itr = revenueMapSymmetric.find("Friday")->second.begin();
            cout << "5 products with the highest revenue for Friday are:" << endl;
            break;
            case 1:
            itr = revenueMapSymmetric.find("Saturday")->second.begin();
            cout << "5 products with the highest revenue for Saturday are:" << endl;
            break;
        }
        while (five_loops) {
            cout << itr->second << " " << fixed << setprecision(2) << itr->first << endl;
            itr++;
            five_loops--;
        }
        five_loops = 5;
        seven_loops--;
    }

    filep.close();

    return;

}

/*
STUDENT NAME: ÖZBERK HAZANTEKİN
STUDENT ID: 150200100
DATE: 11.01.2022
*/