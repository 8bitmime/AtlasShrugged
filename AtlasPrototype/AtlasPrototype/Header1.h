#pragma once
enum LoopStyle { Standard, Other };
#include "pch.h"
#include "ActionObject.cpp"

void doNothing() { return; }
int returnSeven() { return 7; }
int returnEight() { return 8; }

bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions, std::list<int> breakpointIndexes);
ActionObject getEltAt(int a, std::list<ActionObject> listAO);
int getEltAt(int a, std::list<int> listInt);
std::list<ActionObject> deSugar(ool aoArr[], int sizeOfArray);
std::list<int> deSugarBreakpoints(ool aoArr[], int sizeOfArray);
bool returnTrue();