//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------/

#include <iostream>
using namespace std;
#include "Robot.h"


/*
****************
BEGIN: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/

// INITIALIZE STATIC VARIABLES

int Robot::unqID = 1; 

// CONSTRUCTOR

Robot::Robot(string type, float speed, int durability, int manufactureCost, float maintenanceCost): RobotType(type), manufactureCost(manufactureCost){
    this->RobotName = static_cast<string>((type == "explorer" ? "exp" : "mnr")) + static_cast<string>("-") + to_string(unqID);
    this->speed = speed;
    this->durability = durability;
    this->maintenanceCost = maintenanceCost;
    canMove = true;
    unqID++;
}

// ASSIGN NON-CONST VARIABLES AND RETURN THE OBJECT

Robot& Robot::operator=(const Robot& r2){
    this->speed = speed;
    this->durability = durability;
    this->maintenanceCost = maintenanceCost;
    return *this;
}

// PRINT ATTRIBUTES

void Robot::showInfo() const{
    cout << "Name: " << RobotName << endl;    
    cout << "Type: " << RobotType << endl;
    cout << "Speed: " << speed << endl;
    cout << "Durability: " << durability << endl;
    cout << "ManufactureCost: " << manufactureCost << endl;
    cout << "MaintenanceCost: " << maintenanceCost << endl;
    cout << "CanMove: " << (canMove ? "1" : "0") << endl;
}

// GETTERS

string Robot::getRobotType() const{
    return RobotType;
}

string Robot::getName() const{
    return RobotName;
}

bool Robot::getCanMove() const {
    return canMove;
}

float Robot::getMaintenanceCost() const {
    return maintenanceCost;
}

// SETTERS

void Robot::setCanMove(bool setMove){
    canMove = setMove;
}

/*
****************
END: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/


/*
****************
BEGIN: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

// INITIALIZE STATIC VARIABLES

float Explorer::totalExploredArea = 0;
int Explorer::totalNumberOfSeleniumArea = 0;

// CONSTRUCTOR

Explorer::Explorer(string type, float speed, int durability): Robot(type, speed, durability, 3000, 450/speed){

}

// IF CANMOVE IS TRUE, RETURN TRUE AND SET CANMOVE TO FALSE, ELSE RETURN FALSE

bool Explorer::move(){
    if (getCanMove()){
        setCanMove(false);
        return true;
    }
    return false;
}

// IF RANDOM NUMBER IS ABOVE 40 THEN DETECT SELENIUM, ELSE DONT

void Explorer::explore(){
    int probability = rand() % 101;
    totalExploredArea += 1500;
    exploredArea = 1500;

    if (probability >= 40){
        totalNumberOfSeleniumArea += 1;
        detectedSelenium = true;
        return;
    }
    else{
        detectedSelenium = false;
        return;
    }
}

// FIRST USE THE INHERITED ASSIGNMENT OPERATOR FUNCTION, AND THEN ALSO COPY ATTRIBUTES UNIQUE TO THE EXPLORER CLASS

Robot& Explorer::operator=(Explorer& explorer2){
    *this = explorer2;
    this->exploredArea = explorer2.exploredArea;
    this->detectedSelenium = explorer2.detectedSelenium;
    return *this;
}

// PRINT ROBOT ATTRIBUTES FIRST, AND THEN UNIQUE EXPLORER ATTRIBUTES

void Explorer::showInfo() const{
    Robot::showInfo();
    cout << "explored area: " << exploredArea << endl;
}

/*
****************
END: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: MINER CLASS FUNCTION DECLARATIONS 
****************
*/

// INITIALIZE STATIC VARIABLES

int Miner::totalGatheredSelenium = 0;

// CONSTRUCTOR

Miner::Miner(string type, float speed, int durability): Robot(type, speed, durability, 5000, 750/speed){
    gatheredSelenium = 0;
}

// MINE SELENIUM AND ADD THE MINED SELENIUM TO TOTAL GATHERED SELENIUM

void Miner::mine(){
    float minedSelenium = (rand() % 91) + 10;
    minedSelenium *= 5;
    totalGatheredSelenium += minedSelenium;
    gatheredSelenium = minedSelenium;
    Explorer::totalNumberOfSeleniumArea -= 1;
    return;
}

// IF CANMOVE IS TRUE FOR MINER AND THERE IS SOMETHING TO MINE, MINER CAN MOVE

bool Miner::move(){
    if (getCanMove() && Explorer::totalNumberOfSeleniumArea != 0){
        return true;
    }
    return false;
}

// FIRST USE THE INHERITED ASSIGNMENT OPERATOR FUNCTION, AND THEN ALSO COPY ATTRIBUTES UNIQUE TO THE MINER CLASS

Miner& Miner::operator=(Miner& miner2){
    *this = miner2;
    this->gatheredSelenium = miner2.gatheredSelenium;
    return *this;
}

// PRINT ROBOT ATTRIBUTES FIRST, AND THEN UNIQUE EXPLORER ATTRIBUTES

void Miner::showInfo() const{
    Robot::showInfo();
    cout << "# of gathered selenium: " << gatheredSelenium << endl;
}

/*
****************
END: MINER CLASS FUNCTION DECLARATIONS 
****************
*/

