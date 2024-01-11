#pragma once 

#include "CThreadInformation.h"


unsigned int CThreadInformation::TDICurrentThreadCount = 0;
unsigned int CThreadInformation::TDIThreadLimit = 1; //initialisation de base (1 = toutes sous div du premier fragment) => Ne pas modifier par autre chose que 1
std::mutex CThreadInformation::TDIThreadCountMutex;

void CThreadInformation::TDIIncrementCurrentThreadCount() {

	TDIThreadCountMutex.lock();

	if (CThreadInformation::TDIGetCurrentThreadCount() <= CThreadInformation::TDIGetThreadLimit()) {
		TDICurrentThreadCount++;
	}

	TDIThreadCountMutex.unlock();

}

unsigned int CThreadInformation::TDIGetCurrentThreadCount() {
	return TDICurrentThreadCount;
}

unsigned int CThreadInformation::TDIGetThreadLimit() {
	return TDIThreadLimit;
}