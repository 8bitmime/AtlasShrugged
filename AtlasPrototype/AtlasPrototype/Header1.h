#pragma once
enum LoopStyle { Standard, Other };
#include "pch.h"
void doNothing() { return; }
int returnSeven() { return 7; }
int returnEight() { return 8; }

bool atlasLoop(LoopStyle style, std::list<bool(*)()> listOfActions, std::list<std::list<int>> listOfJumpBacks, std::list<std::list<int>> listOfFailuresReq, std::list<int> breakpointIndexes);