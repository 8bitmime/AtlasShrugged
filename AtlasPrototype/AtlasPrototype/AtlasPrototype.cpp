// AtlasPrototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
// new comment

#include "pch.h"
#include "Header1.h"
#include <iterator>

#define VERBOSE_FLAG true
#define MAX_COUNT 50000

bool returnTrue() {
	//std::cout << "you called true!\n";
	return true;
}

bool returnTrue2() {
	return true;
}

bool returnTrue3() {
	return true;
}

bool returnTrue4() {
	return true;
}

bool returnTrue5() {
	return true;
}

bool returnTrue6() {
	return true;
}

bool returnTrue7() {
	return true;
}

bool returnTrue8() {
	return true;
}

bool returnTrue9() {
	return true;
}

bool returnFalse() {
	return false;
}

bool countReturnTrue1() {
	for (int k = 0; k < MAX_COUNT; k++) {
		int arrResults[MAX_COUNT + 10];
		for (int i = 0; i < MAX_COUNT; i++) {
			arrResults[i] = i;
		}
	}
	return true;
}

bool countReturnTrue2() {
	return countReturnTrue1();
}

bool countReturnTrue3() {
	return countReturnTrue1();
}

bool countReturnTrue4() {
	return countReturnTrue1();
}

bool countReturnTrue5() {
	return countReturnTrue1();
}

bool countReturnTrue6() {
	return countReturnTrue1();
}

bool countReturnTrue7() {
	return countReturnTrue1();
}

bool countReturnTrue8() {
	return countReturnTrue1();
}

bool countReturnTrue9() {
	return countReturnTrue1();
}

bool countReturnTrue10() {
	return countReturnTrue1();
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
	if (VERBOSE_FLAG) { std::cout << "atlas looping\n"; }
	std::list<int> breakpointIndexes = breakpointIndexesIn;
	if (style == Standard) {
		int actionIndex = 0;
		while ((size_t)actionIndex < listActions.size()) { //cast because size is unsigned
			while (breakpointIndexes.size() > 1 && actionIndex >= getEltAt(1, breakpointIndexes)) {
				breakpointIndexes.pop_front();
			}
			//get actionobject
			ActionObject ao = getEltAt(actionIndex, listActions);

			//call function until action is done, store return val
			if (VERBOSE_FLAG) { std::cout << "Calling function with index " << actionIndex << "\n"; }
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

//For sugared inputs
bool atlasLoop(objOrList aoArr[], int sizeOfArray) {
	std::list<ActionObject> desugaredActions = deSugar(aoArr, sizeOfArray);
	std::list<int> desugaredBreakpoints = deSugarBreakpoints(aoArr, sizeOfArray);
	return atlasLoop(desugaredActions, desugaredBreakpoints);
}

//Because we should have used an array
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

//Because we should have used an array
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

//Takes in an array of arrays  or actionobjects, and determines the indexes of the breakpoints in the 1d list
std::list<int> deSugarBreakpoints(objOrList aoArr[], int sizeOfArray) {
	std::list<int> retBreakpoints = std::list<int>{};
	int prevBreak = 0;
	retBreakpoints.push_back(0);
	//This loops says "for each arr/object in the array aoArr, add it's length to the previous breakpoint to find the new breakpoint
	for (int i = 0; i < sizeOfArray; i++) {
		int lengthOfThisBit = 0;
		if (aoArr[i].list.aObjectList.size() < 1) {
			lengthOfThisBit = 1;
		}
		else {
			lengthOfThisBit = aoArr[i].list.aObjectList.size();
		}
		prevBreak = prevBreak + lengthOfThisBit;
		retBreakpoints.push_back(prevBreak);
	}
	return retBreakpoints;

}

//Takes an array of arrays or actionobjects, and compresses them into a 1d list
std::list<ActionObject> deSugar(objOrList aoArr[], int sizeOfArray) {
	std::list<ActionObject> listOfAO;
	listOfAO = std::list<ActionObject>{};
	if (VERBOSE_FLAG) { std::cout << sizeOfArray << "\n"; }
	for (int i = 0; i < sizeOfArray; i++) { //For each array or object in aoArr:
		if (VERBOSE_FLAG) { std::cout << "size is: " << aoArr[i].list.getList().size() << "\n"; }
		if (aoArr[i].list.getList().size() <1) {
			listOfAO.emplace_back(aoArr[i].ao.ptrActionFunction, aoArr[i].ao.resultList, aoArr[i].ao.minSuccess);
			if (VERBOSE_FLAG) { std::cout << "Sugaring OBJECT for " << i << "th time\n"; }
		}
		else {
			if (VERBOSE_FLAG) { std::cout << "Sugaring LIST for the " << i << "th time:\n"; }
			for (ActionObject aoi : aoArr[i].list.getList()) {
				if (VERBOSE_FLAG) { std::cout << "\t object in list\n"; }
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
	//myObject2.printValues();
	//atlasLoop(Standard, std::list<ActionObject>{myObject2}, std::list<int>{});
	std::list<int> listInts = { 101, 102, 103, 104, 105, 106 };

	/*
	//Declare the pointers to functions
	bool(*pointerToFunctionA)(); pointerToFunctionA = &FunctionA;
	bool(*pointerToFunctionB)(); pointerToFunctionB = &FunctionB;

	//Create pairs of failure-nums and jump-backs
	PairInt pair1(2, 2);
	PairInt pair2(4, 5);

	//Create the list of pairs
	std::list<PairInt> lpairs1 = { pair1, pair2 };
	std::list<PairInt> lpairs2 = {};

	//Create ActionObjects with a pointer to a function, a list of pairs, and a minimum number of successes
	ActionObject myObjectA(pointerToFunctionA, lpairs1, 3);
	ActionObject myObjectB(pointerToFunctionB, lpairs2, 2);

	//Create the list of ActionObjects
	std::list<ActionObject> lActionObjects = { myObjectA, myObjectB };

	//Call atlas loop with style Standard, the list of action objects, and an empty list of breakpoints
	atlasLoop(Standard, lActionObjects, std::list<int>{});
	 */
	/*
	 //Declare the pointers to functions
	bool(*pointerToFunctionA)(); pointerToFunctionA = &FunctionA;
	...

	//Create the list of objOrList s
	objOrList arrayOfObjOrList[] = {
		objOrList(pointerToFunctionA),
		objOrList(pointerToFunctionB, pointerToFunctionC),
		objOrList(pointerToFunctionD, pointerToFunctionE, pointerToFunctionF),
		objOrList(pointerToFunctionG, pointerToFunctionH),
		objOrList(pointerToFunctionI),
		objOrList(pointerToFunctionJ) };

	//Call looping function with size of list
	atlasLoop(arrayOfObjOrList, 6);
	*/

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
	
	bool(*pointerToReturnTrue3)();
	pointerToReturnTrue3 = &returnTrue3;
	bool(*pointerToReturnTrue4)();
	pointerToReturnTrue4 = &returnTrue4;
	bool(*pointerToReturnTrue5)();
	pointerToReturnTrue5 = &returnTrue5;
	bool(*pointerToReturnTrue6)();
	pointerToReturnTrue6 = &returnTrue6;
	bool(*pointerToReturnTrue7)();
	pointerToReturnTrue7 = &returnTrue7;
	bool(*pointerToReturnTrue8)();
	pointerToReturnTrue8 = &returnTrue8;
	bool(*pointerToReturnTrue9)();
	pointerToReturnTrue9 = &returnTrue9;



	objOrList arrToDesugar3[] = { 
		objOrList(pointerToReturnTrue), 
		objOrList(pointerToFailThirds, pointerToReturnTrue2), 
		objOrList(pointerToReturnTrue3, pointerToReturnTrue4, pointerToReturnTrue5), 
		objOrList(pointerToReturnTrue6, pointerToReturnTrue7), 
		objOrList(pointerToReturnTrue8), 
		objOrList(pointerToReturnTrue9) };
	atlasLoop(arrToDesugar3, 6);

	bool(*pointerToCountReturnTrue1)();
	pointerToCountReturnTrue1 = &countReturnTrue1;
	bool(*pointerToCountReturnTrue2)();
	pointerToCountReturnTrue2 = &countReturnTrue2;
	bool(*pointerToCountReturnTrue3)();
	pointerToCountReturnTrue3 = &countReturnTrue3;
	bool(*pointerToCountReturnTrue4)();
	pointerToCountReturnTrue4 = &countReturnTrue4;
	bool(*pointerToCountReturnTrue5)();
	pointerToCountReturnTrue5 = &countReturnTrue5;
	bool(*pointerToCountReturnTrue6)();
	pointerToCountReturnTrue6 = &countReturnTrue6;
	bool(*pointerToCountReturnTrue7)();
	pointerToCountReturnTrue7 = &countReturnTrue7;
	bool(*pointerToCountReturnTrue8)();
	pointerToCountReturnTrue8 = &countReturnTrue8;
	bool(*pointerToCountReturnTrue9)();
	pointerToCountReturnTrue9 = &countReturnTrue9;
	bool(*pointerToCountReturnTrue10)();
	pointerToCountReturnTrue10 = &countReturnTrue10;

	ActionObject objCntReturn1(countReturnTrue1);
	ActionObject objCntReturn2(countReturnTrue2);
	ActionObject objCntReturn3(countReturnTrue3);
	ActionObject objCntReturn4(countReturnTrue4);
	ActionObject objCntReturn5(countReturnTrue5);
	ActionObject objCntReturn6(countReturnTrue6);
	ActionObject objCntReturn7(countReturnTrue7);
	ActionObject objCntReturn8(countReturnTrue8);
	ActionObject objCntReturn9(countReturnTrue9);
	ActionObject objCntReturn10(countReturnTrue10);

	/*
	float durations[10];
	for (int i = 0; i < 10; i++) {
		const clock_t begin_time = clock();
		//atlasLoop(std::list<ActionObject>{objCntReturn1, objCntReturn2, objCntReturn3, objCntReturn4, objCntReturn5, objCntReturn6, objCntReturn7, objCntReturn8, objCntReturn9, objCntReturn10});
		for (int k = 0; k < 10; k++) {
			countReturnTrue1();
		}
		const clock_t end_time = clock();
		float duration = float(end_time - begin_time) / CLOCKS_PER_SEC;
		durations[i] = duration;
	}
	std::cout << "done";
	for (int i = 0; i < 10; i++) {
		std::cout << durations[i] << ", ";
	}
	float total = 0;
	for (int i = 0; i < 10; i++) {
		total += durations[i];
	}
	std::cout << "\n Avg: " << (total / 10);
	*/
}


// loopme({myaction, myAction2}, {myaction3}, {myaction5, {myaction6, myaction7}}}
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
