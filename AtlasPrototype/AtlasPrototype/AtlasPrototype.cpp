// AtlasPrototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
// new comment

#include "pch.h"
#include "Header1.h"

//enum LoopStyle { Standard, Other };

bool returnTrue() {
	std::cout << "you called true!\n";
	return true;
}

bool returnFalse() {
	return false;
}

int globFOT = 0;
bool failOnThirds() {
	globFOT++;
	bool value = false;
	if (globFOT % 3 == 0 && globFOT < 16) {
		value = false;
	}
	else {
		value = true;
	}
	std::cout << "Called fot for the " << globFOT << " time, returning " << value << "\n";
	return value;
}

bool runMe(bool (*function) ()) {
	return (*function)();
}




bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions, std::list<int> breakpointIndexesIn) {
	std::list<int> breakpointIndexes = breakpointIndexesIn;
	if (style == Standard) {
		int actionIndex = 0;
		while ((size_t)actionIndex < listActions.size()-1) { //cast because size is unsigned
			while (breakpointIndexes.size() > 0 && actionIndex >= getEltAt(1, breakpointIndexes)) {
				breakpointIndexes.pop_front();
			}
			//get actionobject
			ActionObject ao = getEltAt(actionIndex, listActions);

			//call function until action is done, store return val
			//std::cout << "Calling function with index " << actionIndex << "\n";
			int jmpVal = ao.runFunction();

			//check for breakpoints
			if (breakpointIndexes.size() > 0) {								// no point in checking if no breakpoints
				if (actionIndex > breakpointIndexes.front()) {				//If the index used to be above the first breakpoint
					if (actionIndex - jmpVal < breakpointIndexes.front()) { //And now the index is below the first breakpoint
						actionIndex = breakpointIndexes.front();			//Instead set the index equal to the first breakpoint
					}
				}
			}
			if (breakpointIndexes.size() > 0 &&								// no point in checking if no breakpoints
				actionIndex > breakpointIndexes.front() &&					//If the index used to be above the first breakpoint
				actionIndex - jmpVal < breakpointIndexes.front()) {			//And now the index is below the first breakpoint
				actionIndex = breakpointIndexes.front();					//Instead set the index equal to the first breakpoint
			}
			else if (actionIndex-jmpVal < 0) {								//Otherwise, if trying to go back before 0, 
				std::cout << "tried to go back before start";
				//throw std::runtime_error("Tried to go back before start");
				actionIndex = 0;											//don't.

			}
			else {																//Otherwise, increment/decrement actionindex
				actionIndex = actionIndex - jmpVal;
			}
		}
	}
	else if (style == Other) {
		//do stuff
	}
	return true;
}

ActionObject getEltAt(int a, std::list<ActionObject> listAO) {
	std::list<ActionObject> tempList = listAO;
	if ((size_t)a >= listAO.size()) {
		std::cout << "index out of bound1";
		throw std::runtime_error("index out of bound1");
	}
	else {
		for (int i = 0; i < a; i++) {
			tempList.pop_front();
		}
	}
	return tempList.front();
}

int getEltAt(int a, std::list<int> listInt) {
	std::list<int> tempList = listInt;
	if ((size_t)a >= listInt.size()) {
		std::cout << "index out of bound2";
		throw std::runtime_error("index out of bound2");
	}
	else {
		for (int i = 0; i < a; i++) {
			tempList.pop_front();
		}
	}
	return tempList.front();
}

int main()
{
	std::cout << "Hello World!\n";
	doNothing();
	ActionObject myObject1;
	bool(*pointerToReturnTrue)();
	pointerToReturnTrue = &returnTrue;
	PairInt pair1(2, 2);
	PairInt pair2(4, 5);
	std::list<PairInt> lpairs = { pair1, pair2 };
	ActionObject myObject2(pointerToReturnTrue, lpairs, 1);
	myObject2.printValues();
	//atlasLoop(Standard, std::list<ActionObject>{myObject2}, std::list<int>{});
	std::list<int> listInts = { 101, 102, 103, 104, 105, 106 };

	//std::cout << listInts.size() << " " << getEltAt(4, listInts);
	//std::cout << listInts.size() << " " << getEltAt(4, listInts);
	myObject2.runFunction();
	
	bool(*pointerToFailThirds)();
	pointerToFailThirds = &failOnThirds;
	PairInt pair11(1, 1);
	PairInt pair21(2, 1);
	PairInt pair22(2, 2);
	std::list<PairInt> lpairs2 = { pair11, pair21, pair22 };
	ActionObject myObject3(pointerToFailThirds, lpairs2, 3);

	ActionObject myObject4 = myObject2;
	ActionObject myObject5 = myObject2;
	//std::cout << "startets\n";
	atlasLoop(Standard, std::list<ActionObject>{myObject2, myObject4, myObject3, myObject5}, std::list<int>{});

	
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
