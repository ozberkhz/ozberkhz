//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//
#include <iostream>
#ifndef _H
#define _H
using namespace std;
class Robot {
	friend class Crew;
	private:
		static int unqID;
		string RobotName;
		const string RobotType;
		float speed; 
		int durability; 
		const int manufactureCost; 
		bool canMove;
		float maintenanceCost;
	public:
		Robot(string, float, int, int, float);
		Robot& operator=(const Robot&);
		string getRobotType() const;
		string getName() const;
		bool getCanMove() const;
		float getMaintenanceCost() const;
		void setCanMove(bool);
		void showInfo() const;
}; 

class Explorer: public Robot{
	friend class Miner;
	friend class CommandCenter;
	private:
		static float totalExploredArea;
		static int totalNumberOfSeleniumArea;
		float exploredArea;
		bool detectedSelenium;
		
		
	public:
		Explorer(string, float, int);
		bool move();
		void explore();
		Robot& operator=(Explorer&);
		void showInfo() const;
};

class Miner: public Robot{
	friend class CommandCenter;
	private:
		static int totalGatheredSelenium;
		int gatheredSelenium;
		
	public:
		Miner(string, float, int);
		void mine();
		bool move();
		Miner& operator=(Miner&);
		void showInfo() const;
};



#endif