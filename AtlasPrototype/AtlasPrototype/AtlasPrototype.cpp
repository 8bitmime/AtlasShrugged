// AtlasPrototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
// new comment

#include "pch.h"
#include "Header1.h"
#include <iterator>

//enum LoopStyle { Standard, Other };

bool returnTrue() {
	//std::cout << "you called true!\n";
	return true;
}

bool returnTrue2() {
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
	//std::cout << "Called fot for the " << globFOT << " time, returning " << value << "\n";
	return value;
}

bool runMe(bool (*function) ()) {
	return (*function)();
}

bool atlasLoop(std::list<ActionObject> listActions, std::list<int> breakpointIndexesIn) {
	return atlasLoop(Standard, listActions, breakpointIndexesIn);
}

bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions) {
	std::list<int> breakpointIndexesIn;
	breakpointIndexesIn = std::list<int>{};
	return atlasLoop(style, listActions, breakpointIndexesIn);
}

bool atlasLoop(std::list<ActionObject> listActions) {
	return atlasLoop(Standard, listActions);
}



bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions, std::list<int> breakpointIndexesIn) {
	//std::cout << "atlas looping\n";
	std::list<int> breakpointIndexes = breakpointIndexesIn;
	if (style == Standard) {
		int actionIndex = 0;
		while ((size_t)actionIndex < listActions.size()) { //cast because size is unsigned
			while (breakpointIndexes.size() > 0 && actionIndex >= getEltAt(1, breakpointIndexes)) {
				breakpointIndexes.pop_front();
			}
			//get actionobject
			ActionObject ao = getEltAt(actionIndex, listActions);

			//call function until action is done, store return val
			std::cout << "Calling function with index " << actionIndex << "\n";
			int jmpVal = ao.runFunction();

			//check for breakpoints
			if (breakpointIndexes.size() > 0 &&								// no point in checking if no breakpoints
				jmpVal > 0 &&												//If the index is jumping backwards
				actionIndex > breakpointIndexes.front() &&					//and the index used to be above the first breakpoint
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
				//std::cout << "index is now " << actionIndex << "\n";
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


//std::list<ActionObject> createAOList 

void printArr(int *arr) {
	//std::cout << arr[0];
}

std::list<ActionObject> deSugar(objOrList aoArr[], int sizeOfArray) {
	std::list<ActionObject> listOfAO;
	listOfAO = std::list<ActionObject>{};
	//std::cout << sizeOfArray << "\n";
	for (int i = 0; i < sizeOfArray; i++) {
		std::cout << "size is: " << aoArr[i].list.getList().size() << "\n";
		if (aoArr[i].list.getList().size() <1) {
			std::cout << "sugaring object\n";
			listOfAO.emplace_back(aoArr[i].ao.ptrActionFunction, aoArr[i].ao.resultList, aoArr[i].ao.minSuccess);
			//std::cout << "Sugared for " << i << "th time\n";
		}
		else {
			std::cout << "sugaring list:\n";
			for (ActionObject aoi : aoArr[i].list.getList()) {
				std::cout << "\t object in list\n";
				listOfAO.emplace_back(aoi.ptrActionFunction, aoi.resultList, aoi.minSuccess);
			}
		}
	}
	//std::cout << listOfAO.size();
	return listOfAO;
}

int main()
{
	std::cout << "Hello World!\n";
	doNothing();
	ActionObject myObject1;
	bool(*pointerToReturnTrue)();
	pointerToReturnTrue = &returnTrue;
	bool(*pointerToReturnTrue2)();
	pointerToReturnTrue2 = &returnTrue2;
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
	//atlasLoop(Standard, std::list<ActionObject>{myObject2, myObject4, myObject3, myObject5}, std::list<int>{});

	objOrList arrToDesugar[] = { objOrList(pointerToReturnTrue), objOrList(pointerToFailThirds), objOrList(pointerToReturnTrue2) };
	ActionObject tempList[] = { ActionObject(pointerToFailThirds), ActionObject(pointerToReturnTrue2) };
	loActionObject temploAO = loActionObject(tempList, 2);
	objOrList arrToDesugar2[] = { objOrList(pointerToReturnTrue), objOrList(temploAO)};
	std::list<ActionObject> results = deSugar(arrToDesugar, 3);
	//std::cout << results.size() << "\n";
	atlasLoop(results);
	

	objOrList arrToDesugar3[] = { objOrList(pointerToReturnTrue), objOrList(pointerToFailThirds, pointerToReturnTrue2) };
	atlasLoop(deSugar(arrToDesugar3, 2));


}


// loopme({myaction, myAction2}, {myaction3}, {myaction5, myac5tion7}}
/*
ListOfActions templist1 = {myaction, myaction2}
ListOfActions templist2 = {myaction3};
ListOfActions templist3 = {myaction5, myaction7}
listOfactions templist4 = {templist1, templist2, templist3}
loopme(templist4);

*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
