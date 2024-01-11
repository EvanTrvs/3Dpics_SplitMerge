#include "CException.h"


/**********************************************************************************************
 ***** Default class constructor                                                          *****
 **********************************************************************************************
 ***** Input : None                                                                       *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : Create an CException Object with default value 0                   *****
 **********************************************************************************************/
CException::CException() {
	iEXCvalue = 0;
	pcEXCMessage = nullptr;
}

/**********************************************************************************************
 ***** Class constructor                                                                  *****
 **********************************************************************************************
 ***** Input : unsigned int                                                               *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : Create an CException Object with inputed value                     *****
 **********************************************************************************************/
CException::CException( int value) {
	iEXCvalue = value;
	pcEXCMessage = nullptr;
}

/**********************************************************************************************
 ***** Class constructor                                                                  *****
 **********************************************************************************************
 ***** Input : unsigned int ,char * message                                               *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : Create an CException Object with inputed value                     *****
 **********************************************************************************************/
CException::CException(int iValue, const char * pcMessage)
{
	iEXCvalue = iValue;
	pcEXCMessage = new char[strlen(pcMessage) + 1];
	strcpy_s(pcEXCMessage, strlen(pcMessage) + 1, pcMessage);
}

/**********************************************************************************************
 ***** Class copie constructor                                                            *****
 **********************************************************************************************
 ***** Input : CException EXCparam			                                              *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : Create an CException Object with copied value from inputed one     *****
 **********************************************************************************************/
CException::CException(const CException & EXCparam)
{
	iEXCvalue = EXCparam.iEXCvalue;
	pcEXCMessage = new char[strlen(EXCparam.pcEXCMessage) + 1];
	strcpy_s(pcEXCMessage, strlen(EXCparam.pcEXCMessage) + 1, EXCparam.pcEXCMessage);
}

/************************************************************************
*****Destructor | ~CException()                                     *****
*****Input : None                                                   *****
*****Precondition : None                                            *****
*****Output : None                                                  *****
*****Postconditions : Attribut of this are deleted                  *****
************************************************************************/
CException::~CException()
{
	if (pcEXCMessage) {
		delete[] pcEXCMessage;
	}
}

/**********************************************************************************************
 ***** CException operator=                                                               *****
 **********************************************************************************************
 ***** Input : CException EXCparam			                                              *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : return copie CException										      *****
 **********************************************************************************************/
CException & CException::operator=(const CException & EXCparam)
{
	if (this != &EXCparam)
	{
		iEXCvalue = EXCparam.iEXCvalue;

		delete[] pcEXCMessage;
		if (EXCparam.pcEXCMessage)
		{
			pcEXCMessage = new char[strlen(EXCparam.pcEXCMessage) + 1];
			strcpy_s(pcEXCMessage, strlen(EXCparam.pcEXCMessage) + 1, EXCparam.pcEXCMessage);
		}
		else {
			pcEXCMessage = nullptr;
		}
	}
	return *this;
}

/**********************************************************************************************
 ***** CException operator<<	                                                          *****
 **********************************************************************************************
 ***** Input : ostream os, CException EXCparam			                                  *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : print CExeption values in stream								      *****
 **********************************************************************************************/
std::ostream& operator<<(std::ostream& os, const CException& EXCparam)
{
	os << "ERROR CODE : " << EXCparam.iEXCvalue;

	if (EXCparam.pcEXCMessage) {
		os << " " << EXCparam.pcEXCMessage;
	}

	return os;
}