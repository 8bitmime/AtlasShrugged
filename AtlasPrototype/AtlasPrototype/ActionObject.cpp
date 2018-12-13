#include "pch.h"

class PairInt
{
	public:
		int failNum;
		int resultJump;
	PairInt() {
		
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
		//Default constructor, never used
		ptrActionFunction = (NULL);
		resultList = std::list<PairInt>{};
		minSuccess = 1;
		numFailures = 0;
		numSuccess = 0;

	}
	//Normal high-detail constructor
	ActionObject(bool(*givenPointer)(), std::list<PairInt> list, int ms) {
		ptrActionFunction = givenPointer;
		resultList = list;
		minSuccess = ms;
		numFailures = 0;
		numSuccess = 0;
	}
	//Normal low-detail constructor
	ActionObject(bool(*givenPointer)()) {
		ptrActionFunction = givenPointer;
		resultList = std::list<PairInt>{};
		for(int i = 0; i < 15; i++) {
			resultList.emplace_back(1, 20);
		}
		minSuccess = 1;
		numFailures = 0;
		numSuccess = 0;
	}

	//For debugging
	void printEachPair() {
		for (PairInt p : resultList) {
			p.printLessVerbose();
		}
	}

	//For debugging
	void printValues() {
		std::cout << "I have pointer " << ptrActionFunction << ", \n";
		printEachPair();
		std::cout << "and minSuccess " << minSuccess << ".\n";

	}

	//For debugging
	void printSansPairs() {
		std::cout << "I have pointer " << ptrActionFunction << ", minSuccess " << minSuccess << ", numFailures " << numFailures << ", and numSuccess " << numSuccess;

	}
	
	int runFunction() {
		//std::cout << "running function\n";
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

class loActionObject {

	public:
		std::list<ActionObject> aObjectList;
		
	loActionObject(std::list<ActionObject> list) {
		aObjectList = list;
	}

	loActionObject() {
		aObjectList = std::list<ActionObject>{};
	}
	
	loActionObject(ActionObject aoArr[], int size) {
		aObjectList = std::list<ActionObject>{};
		for (int i = 0; i < size; i++) {
			aObjectList.emplace_back(aoArr[i].ptrActionFunction, aoArr[i].resultList, aoArr[i].minSuccess);
		}
	}

	std::list<ActionObject> getList() {
		return aObjectList;
	}

};

class ool {
	public:
		loActionObject list;
		ActionObject ao;

		ool(loActionObject inList) {
			list = inList;
			ao = NULL;
		}


		ool(ActionObject inao) {
			list = loActionObject();
			ao = inao;
		}

		ool(int size, ActionObject arr[]) {
			list = loActionObject();
			ao = NULL;
			for (int i = 0; i < size; i++) {
				list.aObjectList.emplace_back(arr[i].ptrActionFunction, arr[i].resultList, arr[i].minSuccess);
			}
		}


		//Cannot pass in an ool into a ool constructor, workaround to work for up to 20 values in list
		ool(ActionObject ao1, ActionObject ao2) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5});
			ao = NULL;
		}
		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6});
			ao = NULL;
		}
		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7});
			ao = NULL;
		}
		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8});
			ao = NULL;
		}
		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14, ActionObject ao15) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14, ao15});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14, ActionObject ao15, ActionObject ao16) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14, ao15, ao16});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14, ActionObject ao15, ActionObject ao16, ActionObject ao17) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14, ao15, ao16, ao17});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14, ActionObject ao15, ActionObject ao16, ActionObject ao17, ActionObject ao18) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14, ao15, ao16, ao17, ao18});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14, ActionObject ao15, ActionObject ao16, ActionObject ao17, ActionObject ao18, ActionObject ao19) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14, ao15, ao16, ao17, ao18, ao19});
			ao = NULL;
		}

		ool(ActionObject ao1, ActionObject ao2, ActionObject ao3, ActionObject ao4, ActionObject ao5, ActionObject ao6, ActionObject ao7, ActionObject ao8, ActionObject ao9, ActionObject ao10, ActionObject ao11, ActionObject ao12, ActionObject ao13, ActionObject ao14, ActionObject ao15, ActionObject ao16, ActionObject ao17, ActionObject ao18, ActionObject ao19, ActionObject ao20) {
			list = loActionObject(std::list<ActionObject>{ao1, ao2, ao3, ao4, ao5, ao6, ao7, ao8, ao9, ao10, ao11, ao12, ao13, ao14, ao15, ao16, ao17, ao18, ao19, ao20});
			ao = NULL;
		}

};



