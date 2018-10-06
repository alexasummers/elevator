#include<iostream>
#include"Elevator.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	bool exit = false; //initializing booleans	

	int amountOfFloors = 10; //How may floors are in the building
	int currentFloor = 1; //The random elevator position floor
	int maxPeople = 20; //The max amount of people that can fit in the elevator
	int leastTime1 = 10; //The least amount of time it would take for the elevator to reach a particular floor within three floors above or below the current floor
	int leastTime2 = 20; //The least amount of time it would take for the elevator to reach a particular floor
	int longestTime1 = 40; //The most amount of time it would take for the elevator to reach a particular floor more than three floors either above or below the current floor
	int longestTime2 = 60; //The most amount of time it would take for the elevator to reach a particular floor
	int averageTime; //The average amount of time it takes for the elevator to reach the demanded floor

	Elevator Elevator(currentFloor, true, amountOfFloors, 0, maxPeople);  //max values for the information asked

	int totalCycles = 0; //How many movements the elevator goes through

	do {
		int destination = (rand() % amountOfFloors); //generates the random request for the elevator to tend to
		while (destination == currentFloor)
			destination = (rand() % amountOfFloors); //Tells the elevator that if the random number generator creates a number equal to the floor it's already on, it will generate a new one

		int amountOfPeople = (rand() % maxPeople); //generates the amount of people riding in the elevator

		int howManyFloors = abs(currentFloor - destination); //tells how many floors the elevator is going up
		bool goingUp; //if true, the elevator is going up. If false, the elevator is going down.

		if (howManyFloors <= 3)
			int averageTime = (rand() % longestTime1 + leastTime1); //If the amount of floors the elevator moves is less than or equal to three, the amount of time will be lower
		if (howManyFloors > 3)
			int averageTime = (rand() % longestTime2 + leastTime2);//If the amount of floors the elevator moves is more than three, the amount of time will be higher
		
		if (currentFloor < destination)
			goingUp = true; //If the current floor is less than the destination, then the elevator will be moving up
		else
			goingUp = false; //If the current floor is greater than the destination, then the elevator will be moving down

		MoveRequest move(currentFloor, maxPeople, destination); //tells the elevator to move

		Elevator.NewRequest(move, goingUp); //Tells the elevator there is a new request

		//outputs all the information
		cout << "Time " << totalCycles << "\t The elevator is going from floor." << currentFloor << " to floor " << destination << endl; //outputting the elevator location and travel information
		cout << "The elevator traveled " << howManyFloors << " floors." << endl;
		cout << "There are " << amountOfPeople << " riding the elevator currently. " << endl;
		cout << "The wait time was " << averageTime << " seconds. "<< endl;
		Elevator.UpdatePos(); //updates the elevator position

		currentFloor = destination;

		totalCycles++;
		if (totalCycles == 100)
			exit = true; //tells the elevator to run 100 times, and then stop
	} while (!exit);

	cout << endl << "DONE" << endl;

	cin.ignore(); //so it doesn't quit automatically at the end of the program
	cin.get();

	return 0;
}
