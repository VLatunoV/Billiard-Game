#pragma once
#include <exception>
#include <sstream>

template <typename Exception, typename... Args>
[[noreturn]] inline void raise(Args&&... args) {
	std::ostringstream msg;
	(msg << ... << args);
	throw Exception(msg.str().c_str());
}

struct BaseException: public std::exception {
	using std::exception::exception;
};

struct InitializationException: public BaseException {
	using BaseException::BaseException;
};
