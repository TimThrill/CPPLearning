#include "ThreadException.h"

ThreadException::ThreadException(std::string info) : exceptionInfo(info) {}

const char* ThreadException::what() const throw()
{
	return exceptionInfo.c_str();
}
