#ifndef THREAD_EXCEPTION_H
#define THREAD_EXCEPTION_H

#include <exception>
#include <string>

class ThreadException : public std::exception
{
	public:
		ThreadException(std::string info);
		// ~ThreadException() throw() {};
		virtual const char* what() const throw();
	private:
		std::string exceptionInfo;
};

#endif
