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
		for (ActionObject obj : listActions) {
			(*obj.ptrActionFunction)();
		}
	}
	else if (style == Other) {
		//do stuff
	}
	return true;
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
	atlasLoop(Standard, std::list<ActionObject>{myObject2}, std::list<int>{});

	
	//atlasLoop(Standard, )
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
