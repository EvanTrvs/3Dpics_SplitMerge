#ifndef CThreadInformation_h
#define CThreadInformation_h

#include <mutex>

class CThreadInformation {
private:
	static unsigned int TDICurrentThreadCount;
	static unsigned int TDIThreadLimit;

	static std::mutex TDIThreadCountMutex;

public:
	static void TDIIncrementCurrentThreadCount();
	static unsigned int TDIGetCurrentThreadCount();
	static void TDISetThreadLimit(unsigned int uiNumber);
	static unsigned int TDIGetThreadLimit();
};

#endif
