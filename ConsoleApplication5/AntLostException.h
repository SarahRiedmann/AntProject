#pragma once

#include <exception>
#include <string>

class AntLostException : public std::exception
{
public:
	AntLostException(std::string);
	~AntLostException();
	std::string getMessage();

private:
	std::string message;
};

