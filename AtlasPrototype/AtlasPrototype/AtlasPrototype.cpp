// AtlasPrototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
// new comment

#include "pch.h"
#include "Header1.h"

//enum LoopStyle { Standard, Other };

bool returnTrue() {
	return true;
}

bool returnFalse() {
	return false;
}

bool runMe(bool (*function) ()) {
	return (*function)();
}
bool atlasLoop(LoopStyle style, std::list<bool (*)()> listOfActions, std::list<std::list<int>> listOfJumpBacks, std::list<std::list<int>> listOfFailuresReq, std::list<int> breakpointIndexes) {
	return true;
}

int main()
{
	std::cout << "Hello World!\n";
	doNothing();
	std::list<bool(*)()> listActions = {int returnTrue(), int returnTrue() };
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
