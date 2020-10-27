#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>  
#include <sstream>
#include <iostream>
#include "CurlHandler.h"

class Interpreter {
public:
	Interpreter();

	void Gto();
	bool is_number(std::string s);
	void getLines(std::string value);
	void set_end();
	void getNewLines(std::string filename);
	void RunNext();
	void RunLines();
	void readLine(std::string line);

	std::unique_ptr<CurlHandler> curl_handler;

	int totalCounter;
	int currentLine;

	std::string digits;
	std::string text;
	std::string label;
	std::string labelReference;
	std::string var;
	std::string varReference;

	std::string add(std::string firstValue, std::string secondValue);
	std::string subtract(std::string firstValue, std::string secondValue);
	std::string multiply(std::string firstValue, std::string secondValue);
	std::string divide(std::string firstValue, std::string secondValue);
	std::string modulo(std::string firstValue, std::string secondValue);
	std::string negate(std::string value);
	std::string absolute(std::string value);
	std::string increment(std::string value);
	std::string decrement(std::string value);
	std::string duplicate(std::string value);

	std::vector<std::string> stack;

	std::vector<int> callStack;

	std::map<std::string, std::string> variables;

	std::map<std::string, int> labels;

private:
	bool _end;

	std::vector<std::string> _commands;

	void checkLabelDefinitions();

	void addLabelDefinition(std::string value);

	void set_lineCommands(std::vector<std::string> value);

	std::vector<std::string> get_lineCommands();

	std::string ROT13(std::string source);
};