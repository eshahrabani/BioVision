#pragma once
#include "Logger.h"

Logger::Logger(LoggerLevel loggerLevel = LoggerLevel::NORMAL) {
	this->loggerLevel = loggerLevel;
}

void Logger::write(string s, LoggerLevel loggerLevel) {
	this->write(LoggerMessage(s, loggerLevel));
}

void Logger::write(LoggerMessage message) {
	// Check if message is appropriate for the logger level.
	if (message.loggerLevel <= this->loggerLevel) {
		cout << message.message << endl;
	}
}

void Logger::writeNormal(string s) {
	this->write(LoggerMessage(s, LoggerLevel::NORMAL));
}

void Logger::writeVerbose(string s) {
	this->write(LoggerMessage(s, LoggerLevel::VERBOSE));
}

LoggerMessage::LoggerMessage(string s, LoggerLevel loggerLevel) {
	message = s;
	this->loggerLevel = loggerLevel;
}
