#pragma once
enum LoopStyle { Standard, Other };
#include "pch.h"
#include "ActionObject.cpp"

void doNothing() { return; }
int returnSeven() { return 7; }
int returnEight() { return 8; }

bool atlasLoop(LoopStyle style, std::list<ActionObject> listActions, std::list<int> breakpointIndexes);