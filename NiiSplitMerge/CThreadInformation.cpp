#pragma once 

#include "CThreadInformation.h"

//Variables Initialization 
unsigned int CThreadInformation::TDICurrentThreadCount = 0;
unsigned int CThreadInformation::TDIThreadLimit = 1; //Default Initialization (1 = all subdivs of the first fragment) => Do not modify with anything other than 1
std::mutex CThreadInformation::TDIThreadCountMutex;

/************************************************************************************************************************************************
***** TDIIncrementCurrentThreadCount : Writting Accessor																					*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Incrementation of the variable TDICurrentThreadCount                                                                        *****
************************************************************************************************************************************************/
void CThreadInformation::TDIIncrementCurrentThreadCount() {

	//Lock with mutex
	TDIThreadCountMutex.lock();

	//Verification of Thread Limit
	if (CThreadInformation::TDIGetCurrentThreadCount() <= CThreadInformation::TDIGetThreadLimit()) {
		TDICurrentThreadCount++;
	}

	//Unlock mutex
	TDIThreadCountMutex.unlock();
}

/************************************************************************************************************************************************
***** TDIGetCurrentThreadCount : Reading Accessor																							*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : TDICurrentThreadCount : unsigned int																							*****
***** Effects : Return variable TDICurrentThreadCount																						*****
************************************************************************************************************************************************/
unsigned int CThreadInformation::TDIGetCurrentThreadCount() {

	return TDICurrentThreadCount;
}

/************************************************************************************************************************************************
***** TDIGetThreadLimit : Reading Accessor																									*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : TDIThreadLimit : unsigned int																								*****
***** Effects : Return variable TDIThreadLimit																								*****
************************************************************************************************************************************************/
unsigned int CThreadInformation::TDIGetThreadLimit() {

	return TDIThreadLimit;
}