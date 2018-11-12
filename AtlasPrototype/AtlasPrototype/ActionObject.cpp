#include "pch.h"

class PairInt
{
	public:
		int failNum;
		int resultJump;
	PairInt() {
		//default constructor
	}
	PairInt(int fail, int result) {
		failNum = fail;
		resultJump = result;
	}
	void printValues() {
		std::cout << "I have failNum " << failNum << " and resultJump " << resultJump << ". ";
	}
	void printLessVerbose() {
		std::cout << "failNum " << failNum << " and resultJump " << resultJump <<", \n";
	}

};

class ActionObject
{
	public:
		bool(*ptrActionFunction)();
		std::list<PairInt> resultList;
		int minSuccess;

	ActionObject() {
		//Default constructor
		ptrActionFunction = (NULL);
		resultList = std::list<PairInt>{};
		minSuccess = 1;

	}

	ActionObject(bool(*givenPointer)(), std::list<PairInt> list, int ms) {
		ptrActionFunction = givenPointer;
		resultList = list;
		minSuccess = ms;
	}
	void printEachPair() {
		for (PairInt p : resultList) {
			p.printLessVerbose();
		}
	}

	void printValues() {
		std::cout << "I have pointer " << ptrActionFunction << ", \n";
		printEachPair();
		std::cout << "and minSuccess " << minSuccess << ".\n";

	}
};