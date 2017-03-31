#pragma once
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

enum LoggerLevel {
	NORMAL = 0,
	VERBOSE = 1
};

class LoggerMessage : string {
public:
	LoggerMessage(string, LoggerLevel);
	LoggerLevel loggerLevel;
	string message;
};

class Logger {
public:
	LoggerLevel loggerLevel;

	Logger(LoggerLevel);
	void write(string, LoggerLevel);
	void write(LoggerMessage);
	void writeNormal(string);
	void writeVerbose(string);
};