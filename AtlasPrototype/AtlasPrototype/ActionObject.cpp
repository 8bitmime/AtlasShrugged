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
		int numFailures;
		int numSuccess;

	ActionObject() {
		//Default constructor
		ptrActionFunction = (NULL);
		resultList = std::list<PairInt>{};
		minSuccess = 1;
		numFailures = 0;
		numSuccess = 0;

	}

	ActionObject(bool(*givenPointer)(), std::list<PairInt> list, int ms) {
		ptrActionFunction = givenPointer;
		resultList = list;
		minSuccess = ms;
		numFailures = 0;
		numSuccess = 0;
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

	void printSansPairs() {
		std::cout << "I have pointer " << ptrActionFunction << ", minSuccess " << minSuccess << ", numFailures " << numFailures << ", and numSuccess " << numSuccess;

	}
	
	int runFunction() {
		int tempNumSuccess = 0;
		int tempNumFailures = 0;
		//std::cout << "succ: " << tempNumSuccess << ", fail: " << tempNumFailures;
		bool doneRunning = false;
		int returnInt = 0;
		while (!doneRunning) {

			//Run the fuction, and document the result
			bool resultFunction = (*ptrActionFunction)();
			resultFunction ? tempNumSuccess++ : tempNumFailures++;


			//If this call of runFunction has hit the min num of success, return the success value of -1
			if (tempNumSuccess >= minSuccess) {
				doneRunning = true;
				returnInt = -1;
				//std::cout << "Success: Finished with jumpback " << returnInt << "\n";
			}

			//If this call of runfunction has hit the first num in the list of pairs of failures, return the jumpback that that pair gives
			if (resultList.size() > 0 && tempNumFailures == resultList.front().failNum) {
				doneRunning = true;
				PairInt thisPair = resultList.front();
				resultList.pop_front();
				returnInt = thisPair.resultJump;
				//std::cout << "Failed: Finished with jumpback " << returnInt << "\n";

			}
		}
		// numFailures += tempNumFailures;
		//numSuccess += tempNumSuccess;

		return returnInt;
	}
};