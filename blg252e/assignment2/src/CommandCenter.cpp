//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------//
#include "CommandCenter.h"
#include "Robot.h"
#include <iostream>
using namespace std;
/*
****************
BEGIN: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

// CONSTRUCTOR, IF PARAMETERS ARE OUT OF BOUNDS CHOOSE DEFAULT 2

Crew::Crew(int maxExplorers, int maxMiners, int explorerCrewSize, int minerCrewSize){

    // DETERMINING MAX EXPLORER AND MINERS

    if (maxExplorers <= 5 && maxExplorers >= 1){
        this->maxExplorers = maxExplorers;
    } else {
        this->maxExplorers = 2;
    }
    if (maxMiners <= 5 && maxMiners >= 1){
        this->maxMiners = maxMiners;
    } else {
        this->maxMiners = 2;
    }

    // DETERMINING EXPLORER AND MINER CREW SIZES

    if (explorerCrewSize <= maxExplorers && explorerCrewSize >= 0){
        this->explorerCrewSize = explorerCrewSize;
    } else {
        this->explorerCrewSize = 2;
    }
    if (minerCrewSize <= maxMiners && minerCrewSize >= 0){
        this->minerCrewSize = minerCrewSize;
    } else {
        this->minerCrewSize = 2;
    }

    this->ExplorerCrew = new Explorer*[this->maxExplorers];
    this->MinerCrew = new Miner*[this->maxMiners]; 
    this->crewManufactureCost = 0;
    this->crewMaintenanceCost = 0;

    for (int i = 0; i < this->explorerCrewSize; i++){
        ExplorerCrew[i] = static_cast<Explorer *>(manufactureRobot("explorer"));
        crewManufactureCost += 3000;
    }

    for (int i = 0; i < this->minerCrewSize; i++){
        MinerCrew[i] = static_cast<Miner *>(manufactureRobot("miner"));
        crewManufactureCost += 5000;
    }

}

// CREATE A ROBOT AND RETURN A POINTER TO IT

Robot* Crew::manufactureRobot(string type){
    int durability = (rand() % 5) + 1;
    float speed = (rand()/(float)RAND_MAX);

    if (type == "explorer" || type == "exp") {
        Robot* newExplorer = new Explorer("explorer",  speed + 1.5, durability);
        return newExplorer;
    }
    else if (type == "miner" || type == "mnr") {
        Robot* newMiner = new Miner("miner", speed * 0.5 + 1.0 , durability);
        return newMiner;
    }
    else{
        return NULL;
    }
}

// CREATE A ROBOT AND RETURN A POINTER TO IT, BUT TAKE USER INPUT

Robot* Crew::manufactureRobot(){
    int durability = (rand() % 5) + 1;
    float speed = (rand()/(float)RAND_MAX);
    string type;
    cout << "Type:";
    cin >> type;

    if (type == "explorer" || type == "exp") {
        Robot* newExplorer = new Explorer("explorer", speed + 1.5 , durability);
        newExplorer->setCanMove(false);
        return newExplorer;
    }
    else if (type == "miner" || type == "mnr") {
        Robot* newMiner = new Miner("miner", speed * 0.5 + 1.0 , durability);
        newMiner->setCanMove(false);
        return newMiner;
    }
    else{
        return NULL;
    }
}

// ITERATE THROUGH ALL ROBOTS AND SET THEM READY TO MOVE

void Crew::initMovement(){
    for (int i = 0; i < explorerCrewSize; i++){
        ExplorerCrew[i]->setCanMove(true);
    }
    for (int i = 0; i < minerCrewSize; i++){
        MinerCrew[i]->setCanMove(true);
    }
}

// DECREMENT ALL DURABILITIES BY ONE AND REMOVE ROBOTS IF THEY ARE NOT THE ONLY ROBOT IN THE CREW OF THEIR OWN TYPE

void Crew::updateDurability(){

    cout << "Explorer durability is being updated" << endl;

    if (explorerCrewSize != 1){
        for (int i = 0; i < explorerCrewSize; i++){
            ExplorerCrew[i]->durability -= 1;
        }
        for (int i = 0; i < explorerCrewSize; i++){
            if (ExplorerCrew[i]->durability == 0){
                delete ExplorerCrew[i];
                for (int j = i + 1; j < explorerCrewSize; j++){
                    ExplorerCrew[i] = ExplorerCrew[j];
                }
                explorerCrewSize--;
            }
        }
    }
    else {
        if (ExplorerCrew[0]->durability != 0){
            ExplorerCrew[0]->durability -= 1;
        }
    }

    cout << "Miner durability is being updated" << endl;

    if (minerCrewSize != 1){
        for (int i = 0; i < minerCrewSize; i++){
            MinerCrew[i]->durability -= 1;
        }
        for (int i = 0; i < minerCrewSize; i++){
            if (MinerCrew[i]->durability == 0){
                delete MinerCrew[i];
                for (int j = i + 1; j < minerCrewSize; j++){
                    MinerCrew[i] = MinerCrew[j];
                }
                minerCrewSize--;
            }
        }
    }
    else {
        if (MinerCrew[0]->durability != 0){
            MinerCrew[0]->durability -= 1;
        }
    }
}

// ADD ROBOTS TO THE CREW, UPDATE MANUFACTURE COSTS ACCORDINGLY

void Crew::operator+=(Robot* robot){
    if (robot->getRobotType() == "explorer" && explorerCrewSize != maxExplorers) {
        ExplorerCrew[explorerCrewSize] = static_cast<Explorer *>(robot);
        explorerCrewSize++;
        crewManufactureCost += 3000;
    }
    else if(robot->getRobotType() == "explorer" && explorerCrewSize == maxExplorers){
        cout << "This robot cannot be added, check maximum size of the crew" << endl;
        delete robot;
    }

    if (robot->getRobotType() == "miner" && minerCrewSize != maxMiners){
        MinerCrew[minerCrewSize] = static_cast<Miner *>(robot);
        minerCrewSize++;
        crewManufactureCost += 5000;
    }
    else if(robot->getRobotType() == "miner" && minerCrewSize == maxMiners){
        cout << "This robot cannot be added, check maximum size of the crew" << endl;
        delete robot;
    }

    return;
}

// REMOVE ROBOTS FROM THE CREW AND RESORT THE POINTER ARRAYS

void Crew::operator-=(string name){
    cout << name << ": Goodbye" << endl;
    if (explorerCrewSize != 1){
        for (int i = 0; i < explorerCrewSize; i++){
            if (ExplorerCrew[i]->getName() == name){
                delete ExplorerCrew[i];
                for (int j = i; j < explorerCrewSize - 1; j++){
                    ExplorerCrew[j] = ExplorerCrew[j + 1];
                }
                explorerCrewSize--;
                return;
            }
        }
    }
    if (minerCrewSize != 1){    
        for (int i = 0; i < minerCrewSize; i++){
            if (MinerCrew[i]->getName() == name){
                delete MinerCrew[i];
                for (int j = i; j < minerCrewSize - 1; j++){
                    MinerCrew[j] = MinerCrew[j + 1];
                }
                minerCrewSize--;
                return;
            }
        }
    }
    return;
}

// SHOW INFORMATION ABOUT THE CREW

void Crew::showInfo() const{
    cout << "explorerCrew Size:" << explorerCrewSize << endl;
    cout << "minerCrew Size:" << minerCrewSize << endl;

    for (int i = 0; i < explorerCrewSize; i++){
        ExplorerCrew[i]->showInfo();
    }
    for (int i = 0; i < minerCrewSize; i++){
        MinerCrew[i]->showInfo();
    }
    cout << "Total manufacture cost: " << crewManufactureCost << endl;
    cout << "Total maintenance cost: " << crewMaintenanceCost << endl;
}

// DESTRUCTOR

Crew::~Crew(){
    for (int i = 0; i < explorerCrewSize; i++){
            delete ExplorerCrew[i];
    }
    for (int i = 0; i < minerCrewSize; i++){
            delete MinerCrew[i];
    }
    delete[] ExplorerCrew;
    delete[] MinerCrew;
}


// GETTERS

float Crew::getCrewMaintenanceCost() const{
    return crewMaintenanceCost;
}

int Crew::getExplorerCrewSize() const{
    return explorerCrewSize;
}

int Crew::getMinerCrewSize() const{
    return minerCrewSize;
}

Explorer** Crew::getExplorers(){
    return ExplorerCrew;
}

Miner** Crew::getMiners() {
    return MinerCrew;
}

// SETTERS

void Crew::setCrewMaintenanceCost(float cost){
    crewMaintenanceCost = cost;
}

/*
****************
END: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/

// CONSTRUCTOR

CommandCenter::CommandCenter(int neededSelenium, float searchArea, int seleniumWorth): neededSelenium(neededSelenium), searchArea(searchArea), seleniumWorth(seleniumWorth){
    turnCount = 1;
}

// CHECK IF ALL AREAS HAVE BEEN EXPLORED, IF YES ASSESS WHETHER THE GAME HAS BEEN WON

bool CommandCenter::isGameEnded(){
    if (searchArea == Explorer::totalExploredArea){
        cout << "Area has been fully explored." << endl;
        cout << "Aim: " << neededSelenium << " selenium." << endl;
        cout << "Collected " << Miner::totalGatheredSelenium << endl;
        if (profit > 0 && Miner::totalGatheredSelenium >= neededSelenium){
            cout << "Congrats!" << endl;
            return true;
        }
        else{
            cout << "Mission Failed!" << endl;
        }
        return true;
    }
    return false;
}

// CALCULATE PROFIT, SELF EXPLANATORY

void CommandCenter::calculateProfit(Crew& crew){
    float seleniumRevenue = Miner::totalGatheredSelenium * seleniumWorth;
    float expenses = crew.crewManufactureCost + crew.crewMaintenanceCost;
    profit = seleniumRevenue - expenses;
    cout << "Profit:" << profit << endl;
    cout << "Expenses:" << expenses << endl;
    cout << "Selenium Revenue:" << seleniumRevenue << endl;
}

// INCREMENT TURN COUNT

void CommandCenter::operator++(){
    ++turnCount;
}

// SHOW INFORMATION

void CommandCenter::showInfo() const{
    cout << "Current turn: " << turnCount << endl;
    cout << "Aim: " << neededSelenium << " selenium." << endl;
    cout << "Collected: " << Miner::totalGatheredSelenium << endl;
    cout << "Total Search Area: " << searchArea << endl;
    cout << "Explored Area: " << Explorer::totalExploredArea << endl;
    cout << "Currently, there are " << Explorer::totalNumberOfSeleniumArea << " area/s that include selenium" << endl;
    if (Explorer::totalNumberOfSeleniumArea > 0){
        cout << "Mine these areas if miners have not finished their turn! If you cannot cope with mining, you can always add new miners!" << endl;
    }
}

/*
****************
END: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/