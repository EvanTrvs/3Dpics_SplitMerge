#ifndef CThreadInformation_h
#define CThreadInformation_h

#include <mutex>

/* This class is required for thread management */

class CThreadInformation {
private:
	static unsigned int TDICurrentThreadCount;
	static unsigned int TDIThreadLimit;

	static std::mutex TDIThreadCountMutex;

public:
	/************************************************************************************************************************************************
	***** TDIIncrementCurrentThreadCount : Writting Accessor																					*****
	*************************************************************************************************************************************************
	***** Input : None																															*****
	***** Precondition : Nothing                                                                                                                *****
	***** Output : None																															*****
	***** Effects : Incrementation of the variable TDICurrentThreadCount                                                                        *****
	************************************************************************************************************************************************/
	static void TDIIncrementCurrentThreadCount();

	/************************************************************************************************************************************************
	***** TDIGetCurrentThreadCount : Reading Accessor																							*****
	*************************************************************************************************************************************************
	***** Input : None																															*****
	***** Precondition : Nothing                                                                                                                *****
	***** Output : TDICurrentThreadCount : unsigned int																							*****
	***** Effects : Return variable TDICurrentThreadCount																						*****
	************************************************************************************************************************************************/
	static unsigned int TDIGetCurrentThreadCount();

	/************************************************************************************************************************************************
	***** TDIGetThreadLimit : Reading Accessor																									*****
	*************************************************************************************************************************************************
	***** Input : None																															*****
	***** Precondition : Nothing                                                                                                                *****
	***** Output : TDIThreadLimit : unsigned int																								*****
	***** Effects : Return variable TDIThreadLimit																								*****
	************************************************************************************************************************************************/
	static unsigned int TDIGetThreadLimit();

};

#endif
