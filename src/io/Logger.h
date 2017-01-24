#pragma once
#include <string>
#include <iostream>

using namespace std;

enum class LoggerLevel {
	NORMAL = 0,
	DEBUG = 1,
	VERBOSE = 2
};

class Logger {
public:
	Logger(LoggerLevel);
	void write(string, LoggerLevel);
	void write(LoggerMessage);
	void writeNormal(string);
	void writeDebug(string);
	void writeVerbose(string);
	LoggerLevel loggerLevel;
}; 

class LoggerMessage : string {
public:
	LoggerMessage(string, LoggerLevel);
	LoggerLevel loggerLevel;
	string message;
};