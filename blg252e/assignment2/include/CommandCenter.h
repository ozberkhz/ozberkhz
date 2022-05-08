//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//
#include <iostream>
#include "Robot.h"
using namespace std;
class Crew{
	friend class CommandCenter;
	private:
		int maxExplorers;
		int maxMiners;
		int crewManufactureCost;
		float crewMaintenanceCost;
		int explorerCrewSize;
		int minerCrewSize;
		Explorer** ExplorerCrew;
		Miner** MinerCrew;
		
	public:
		Crew(int, int, int, int);
		~Crew();
		Robot* manufactureRobot(string);
		Robot* manufactureRobot();
		void initMovement();
		void updateDurability();
		void operator+=(Robot*);
		void operator-=(string);
		void showInfo() const;
		void setCrewMaintenanceCost(float);
		float getCrewMaintenanceCost() const;
		int getExplorerCrewSize() const;
		int getMinerCrewSize() const;
		Explorer** getExplorers();
		Miner** getMiners();
};

class CommandCenter{
	private:
		const int neededSelenium;
		const float searchArea;
		const int seleniumWorth;
		int turnCount;
		float totalCrewMaintenanceCost;
		float profit;
	public:
		CommandCenter(int, float, int);
		bool isGameEnded();
		void calculateProfit(Crew&);
		void operator++();
		void showInfo() const;

};



