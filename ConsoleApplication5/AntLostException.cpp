#include "stdafx.h"
#include "AntLostException.h"

AntLostException::AntLostException(std::string _message) : message(_message)
{
}

AntLostException::~AntLostException()
{
}

std::string AntLostException::getMessage()
{
	return message;
}
