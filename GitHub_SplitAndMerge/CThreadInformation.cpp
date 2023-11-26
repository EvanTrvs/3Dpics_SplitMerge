#pragma once 

#include "CThreadInformation.h"


unsigned int CThreadInformation::TDICurrentThreadCount = 0;
unsigned int CThreadInformation::TDIThreadLimit = 1; //initialisation de base
std::mutex CThreadInformation::TDIThreadCountMutex;

void CThreadInformation::TDIIncrementCurrentThreadCount() {
	if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
		TDIThreadCountMutex.lock();
		TDICurrentThreadCount++;
		TDIThreadCountMutex.unlock();
	}
}

unsigned int CThreadInformation::TDIGetCurrentThreadCount() {
	return TDICurrentThreadCount;
}

void CThreadInformation::TDISetThreadLimit(unsigned int uiNumber) {
	TDIThreadLimit = uiNumber;
}

unsigned int CThreadInformation::TDIGetThreadLimit() {
	return TDIThreadLimit;
}