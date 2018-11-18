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

bool runMe(bool (*function) ()) {
	return (*function)();
}


bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions, std::list<int> breakpointIndexes) {
	if (style == Standard) {
		int actionIndex = 0;
		while ((size_t)actionIndex < listActions.size()) { //cast because size is unsigned

			//get actionobject
			ActionObject ao = getEltAt(actionIndex, listActions);

			//call function until action is done, store return val
			int jmpVal = ao.runFunction();

			if (actionIndex + jmpVal < 0) {
				throw std::runtime_error("Tried to go back before start");
			}
			else {
				actionIndex = actionIndex + jmpVal;
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
	if ((size_t)a >= listAO.size() - 1) {
		throw std::runtime_error("index out of bound");
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
	if ((size_t)a >= listInt.size()-1) {
		throw std::runtime_error("index out of bound");
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
	ActionObject myObject2(pointerToReturnTrue, lpairs, 5);
	myObject2.printValues();
	//atlasLoop(Standard, std::list<ActionObject>{myObject2}, std::list<int>{});
	std::list<int> listInts = { 101, 102, 103, 104, 105, 106 };

	//std::cout << listInts.size() << " " << getEltAt(4, listInts);
	//std::cout << listInts.size() << " " << getEltAt(4, listInts);
	myObject2.runFunction();
	
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
