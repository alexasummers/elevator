#include<iostream>
#include"Queue.h"

using namespace std;
/**
* @author  Aiden Cornstubble
* @version 1.5
* @date last edited   10-4-2018
*/

//Elevator Class
class Elevator
{
private:
	//declaration for the three PriorityQueues
	PriorityQueue upQueue;
	PriorityQueue tempQueue;
	PriorityQueue downQueue;
	//the integer variable declaration for the current floor, the highest floor, the current amount of people, and the maximum amount of people
	int currFloor, highestFloor, currPeople, maxPeople;
	//the boolean variable declaration for the current heading of the elevator
	bool goingUp;

public:

	/*
	* The default constructor for the Elevator Class
	*/
	Elevator()
	{
		//sets the current floor to one
		currFloor = 1;
		//sets the current heading to up(true)
		goingUp = true;
		//sets the highest floor to 10
		highestFloor = 10;
		//sets the current amount of people to zero
		currPeople = 0;
		//sets the maximum amount of people to 15
		maxPeople = 15;
	}

	/*
	* The constructor that doesn't take people for the Elevator Class
	* @param cF used to pass in the current floor
	* @param gU used to pass in the current heading
	* @param hF used to pass in the highest floor
	*/
	Elevator(int cF, bool gU, int hF)
	{
		//sets the current floor to cF
		currFloor = cF;
		//sets the current heading to up or down if gU is true or false respectively
		goingUp = gU;
		//sets the highest floor to hF
		highestFloor = hF;
		//sets the current amount of people to zero
		currPeople = 0;
		//sets the maximum amount of people to 15
		maxPeople = 15;
	}

	/*
	* The constructor that takes in all parameters for the Elevator Class
	* @param cF used to pass in the current floor
	* @param gU used to pass in the current heading
	* @param hF used to pass in the highest floor
	* @param cW used to pass in the current amount of people
	* @param mW used to pass in the maximum amount of people
	*/
	Elevator(int cF, bool gU, int hF, int cP, int mP)
	{
		//sets the current floor to cF
		currFloor = cF;
		//sets the current heading to up or down if gU is true or false respectively
		goingUp = gU;
		//sets the highest floor to hF
		highestFloor = hF;
		//sets the current amount of people to cP
		currPeople = cP;
		//sets the maximum amount of people to mP
		maxPeople = mP;
	}

	/* UpdatePos
	* @return void
	* used to update the elevator's position
	*/
	void UpdatePos()
	{
		//if the elevator has reached the highest floor or the bottom floor or has no more pickups on it's current heading this reverses the direction the elevator is traveling
		if (goingUp && currFloor == highestFloor || !goingUp && currFloor == 1 || goingUp && upQueue.IsEmpty() || !goingUp && downQueue.IsEmpty())
		{
			//call to ReverseDirection
			ReverseDirection();
		}
		//if goingUp is equal to true
		if (goingUp)
		{
			//increments the current floor by one
			currFloor++;
			//while the floor number of the MoveRequest at the front of the upQueue is equal to the current floor number
			while (upQueue.Front().Floor() == currFloor)
			{
				//if the current people plus 300 is less than or equal to the maximum people or the pickup variable of the MoveRequest at the front of the upQueue is equal to false
				if (currPeople < maxPeople || !upQueue.Front().Pickup())
				{

					//if the pickup variable of the MoveRequest at the front of the upQueue is equal to true
					if (upQueue.Front().Pickup())
					{
						//adds the people variable of the MoveRequest at the front of the upQueue to the current people(if it is a drop off the people is negative)
						currPeople += upQueue.Front().People();
						//prints the result to the console
						cout << "picked up at " << upQueue.Front().Floor() << " the people added was " << upQueue.Front().People() << " elevator is going up" << endl;
					}
					//if the pickup variable of the MoveRequest at the front of the upQueue is equal to false
					else
					{
						//subtracts the people variable of the MoveRequest at the front of the upQueue to the current people
						currPeople -= upQueue.Front().People();
						//prints the result to the console
						cout << "dropped off at " << upQueue.Front().Floor() << " the people added was " << upQueue.Front().People() << " elevator is going up" << endl;
					}
					//deletes the front of the upQueue
					upQueue.Pop();
				}
				//if the current people is greater than or equal to the maximum people and the pickup variable of the MoveRequest at the front of the upQueue is equal to true
				else
				{
					//prints that it can't pick up at this time to the console
					cout << "Can't pick up, pushed to temporary stack" << endl;
					//pushes the front of the upQueue onto the tempQueue
					tempQueue.Push(upQueue.Front());
					//deletes the front of the upQueue
					upQueue.Pop();
				}
			}

		}
		//if goingUp is equal to false
		else
		{
			//decrements the current floor by one
			currFloor--;
			//while the floor number of the MoveRequest at the front of the downQueue is equal to the current floor number
			while (downQueue.Front().Floor() == currFloor)
			{
				//if the current people plus 300 is less than or equal to the maximum people or the pickup variable of the MoveRequest at the front of the downQueue is equal to false
				if (currPeople < maxPeople || !downQueue.Front().Pickup())
				{

					//if the pickup variable of the MoveRequest at the front of the downQueue is equal to true
					if (downQueue.Front().Pickup())
					{
						//adds the people variable of the MoveRequest at the front of the downQueue to the current people(if it is a drop off the people is negative)
						currPeople += downQueue.Front().People();
						//prints the result to the console
						cout << "picked up at " << downQueue.Front().Floor() << " the people added was " << downQueue.Front().People() << " elevator is going down" << endl;
					}
					//if the pickup variable of the MoveRequest at the front of the downQueue is equal to false
					else
					{
						//subtracts the people variable of the MoveRequest at the front of the downQueue to the current people
						currPeople -= downQueue.Front().People();
						//prints the result to the console
						cout << "dropped off at " << downQueue.Front().Floor() << " the people added was " << downQueue.Front().People() << " elevator is going up" << endl;
					}
					//deletes the front of the downQueue
					downQueue.Pop();
				}
				else
				{
					//prints that it can't pick up at this time to the console
					cout << "Can't pick up, pushed to temporary stack" << endl;
					//pushes the front of the downQueue onto the tempQueue
					tempQueue.DownPush(downQueue.Front());
					//deletes the front of the downQueue
					downQueue.Pop();
				}
			}
		}
	}

	/* NewRequest
	* @return void
	* used to add MoveRequests to the respective queues
	* @param move passes in the MoveRequest to be stored in a queue
	* @param up gives the current heading of the elevator
	*/
	void NewRequest(MoveRequest move, bool up)
	{
		//if the up parameter is equal to the goingUp variable
		if (up == goingUp)
		{
			//if goingUp is equal to true
			if (goingUp)
			{
				//if the current floor is less than or equal to the floor variable of move
				if (currFloor <= move.Floor())
				{
					//pushes the move variable unto the upQueue
					upQueue.Push(move);
				}
				//if the current floor is greater than the floor variable of move
				else
				{
					//pushes the move variable unto the tempQueue
					tempQueue.Push(move);
				}
			}
			//if goingUp is equal to false
			else
			{
				//if the current floor is greater than or equal to the floor variable of move
				if (currFloor >= move.Floor())
				{
					//pushes the move variable unto the downQueue
					downQueue.DownPush(move);
				}
				//if the current floor is less than the floor variable of move
				else
				{
					//pushes the move variable unto the tempQueue
					tempQueue.DownPush(move);
				}
			}
		}
		//if the up parameter is not equal to the goingUp variable
		else
		{
			//if goingUp is equal to true
			if (goingUp)
			{
				//pushes the move variable unto the downQueue
				downQueue.DownPush(move);
			}
			//if goingUp is equal to false
			else
			{
				//pushes the move variable unto the upQueue
				upQueue.Push(move);
			}
		}
	}

	/* ReverseDirection
	* @return void
	* used to change the elevator's direction
	*/
	void ReverseDirection()
	{
		//if goingUp is equal to true
		if (goingUp)
		{
			//sets goingUp to false
			goingUp = false;
			//clears the upQueue
			upQueue.Clear();
			//while the tempQueue IsEmpty equals false
			while (!tempQueue.IsEmpty())
			{
				//pushes the front of the tempQueue onto the front of the upQueue
				upQueue.Push(tempQueue.Front());
				//deletes the front of the tempQueue
				tempQueue.Pop();
			}
		}
		//if goingUp is equal to false
		else
		{
			//sets goingUp to true
			goingUp = true;
			//clears the downQueue
			downQueue.Clear();
			//while the tempQueue IsEmpty equals false
			while (!tempQueue.IsEmpty())
			{
				//pushes the front of the tempQueue onto the front of the downQueue
				downQueue.Push(tempQueue.Front());
				//deletes the front of the tempQueue
				tempQueue.Pop();
			}
		}
	}
};