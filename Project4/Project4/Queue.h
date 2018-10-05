#include<iostream>
#include"MoveRequest.h"
using namespace std;


const int MAX_FLOORS = 100;


class PriorityQueue {
private:
	MoveRequest requests[MAX_FLOORS];
	int m_itemCount;
	void ShiftRight(int index);
	void ShiftLeft(int index);

public:
	PriorityQueue();
	void Push(MoveRequest move);
	void DownPush(MoveRequest move);
	void Pop();
	MoveRequest Front();
	int Size();
	bool IsEmpty();
	void Clear();
};


PriorityQueue::PriorityQueue() {
	MoveRequest requests[MAX_FLOORS];
	m_itemCount = 0;
}


void PriorityQueue::Push(MoveRequest move) {

	if (PriorityQueue::Size() == MAX_FLOORS) {
		throw runtime_error("Sorry, the queue is full!");
	}
	if (IsEmpty()) {
		requests[0] = move;
		m_itemCount++;
		return;
	}
	else {
		for (int i = 0; i < m_itemCount; i++) {
			if (move.Floor() == requests[i].Floor()) { // if same floor, prioritize dropoff over pickup
				int j = 0;
				while (!(requests[j].Pickup())) {
					j++;
				}
				ShiftRight(j);
				requests[j] = move;
				m_itemCount++;
				return;
			}

			if (move.Floor() < requests[i].Floor()) {
				ShiftRight(i);
				requests[i] = move;
				m_itemCount++;
				return;
			}
		}
		//reached end of loop, meaning our new request has the lowest priority
		requests[m_itemCount] = move;
		m_itemCount++;
		return;
	}
}


void PriorityQueue::DownPush(MoveRequest move) {
	if (PriorityQueue::Size() == MAX_FLOORS) {
		throw runtime_error("Sorry, the queue is full!");
	}
	if (IsEmpty()) {
		requests[0] = move;
		m_itemCount++;
		return;
	}
	else {
		for (int i = 0; i < m_itemCount; i++) {
			if (move.Floor() == requests[i].Floor()) { // if equal floors, prioritize a dropoff request before a pickup request
				int j = 0;
				while (!(requests[j].Pickup())) {
					j++;
				}
				ShiftRight(j);
				requests[j] = move;
				m_itemCount++;
				return;
			}
			if (move.Floor() > requests[i].Floor()) {
				ShiftRight(i);
				requests[i] = move;
				m_itemCount++;
				return;
			}
		}
		// reached end of loop, so our new request has a lower priority than everything else
		requests[m_itemCount] = move;
		m_itemCount++;
		return;
	}
}


void PriorityQueue::Pop() {
	ShiftLeft(0);
	m_itemCount--;
	return;
}


MoveRequest PriorityQueue::Front() {
	return requests[0];
}


int PriorityQueue::Size() {
	return m_itemCount;
}


bool PriorityQueue::IsEmpty() {
	if (m_itemCount == 0) {
		return true;
	}
	else {
		return false;
	}
}


void PriorityQueue::ShiftRight(int index) {
	for (int i = m_itemCount; i > index; i--) {
		requests[i] = requests[i - 1];
	}
	return;
}


void PriorityQueue::ShiftLeft(int index) {
	for (int i = 0; i < m_itemCount; i++) {
		requests[i] = requests[i + 1];
	}
	return;
}


void PriorityQueue::Clear() {
	m_itemCount = 0; // lazy clear
}


