#include<iostream>
#include"Elevator.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	bool exit = false; //initializing booleans	

	int amountOfFloors = 10; //How may floors are in the building
	int currentFloor = 1; //The random elevator position floor
	int maxPeople = 20;

	Elevator Elevator(currentFloor, true, amountOfFloors, 0, maxPeople);  //max values for the information asked

	int totalCycles = 0;

	do {
		int destination = (rand() % amountOfFloors); //generates the random request for the elevator to tend to
		int howManyFloors = abs(currentFloor - destination); //tells how many floors the elevator is going up
		bool goingUp;
		
		if (currentFloor < destination)
			goingUp = true;
		else
			goingUp = false;

		MoveRequest move(currentFloor, maxPeople, destination); //tells the elevator to move

		Elevator.NewRequest(move, goingUp);

		cout << "Time " << totalCycles << "\t The elevator is going from floor " << currentFloor << " to floor " << destination << endl; //outputting the elevator location and travel information

		Elevator.UpdatePos(); //updates the elevator position

		currentFloor = destination;

		totalCycles++;
		if (totalCycles == 100)
			exit = true;
	} while (!exit);

	cout << endl << "DONE" << endl;

	// Don't quit automatically
	cin.ignore();
	cin.get();

	return 0;
}
