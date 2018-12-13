#pragma once
enum LoopStyle { Standard, Other };
#include "pch.h"
#include "ActionObject.cpp"

ActionObject getEltAt(int a, std::list<ActionObject> listAO);
int getEltAt(int a, std::list<int> listInt);
std::list<ActionObject> deSugar(ool aoArr[], int sizeOfArray);
std::list<int> deSugarBreakpoints(ool aoArr[], int sizeOfArray);

bool atlasLoop(std::list<ActionObject> listActions, std::list<int> breakpointIndexesIn);
bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions);
bool atlasLoop(std::list<ActionObject> listActions);
bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions, std::list<int> breakpointIndexesIn);
bool atlasLoop(ool aoArr[], int sizeOfArray);