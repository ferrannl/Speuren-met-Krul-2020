#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <iostream>
#include "CurlHandler.h"

class Interpreter {
public:

	void readLine(std::string line);

	//constructor
	Interpreter();

	std::shared_ptr<CurlHandler> curl_handler;

	int currentLine;
	//3.1.1 Values & Types
	std::string digits;
	std::string text;
	std::string label;
	std::string labelReference;
	std::string var;
	std::string varReference;

	//3.1.2 Integer operaties
	std::string add(std::string firstValue, std::string secondValue);
	std::string subtract(std::string firstValue, std::string secondValue);
	std::string multiply(std::string firstValue, std::string secondValue);
	std::string divide(std::string firstValue, std::string secondValue);
	std::string modulo(std::string firstValue, std::string secondValue);
	std::string negate(std::string value);
	std::string absolute(std::string value);
	std::string increment(std::string value);
	std::string decrement(std::string value);

	//3.1.3 String operaties
	std::string duplicate(std::string value);
	std::string reverse(std::string value);
	std::string substring(std::string to, std::string from, std::string value);
	std::string index(std::string index, std::string value);
	std::string concat(std::string firstValue, std::string secondValue);
	std::string length(std::string value);
	std::string rotate(std::string value);
	std::string newline(std::string value);

	bool is_number(std::string s);
	void getLines(std::string value);
	void set_end();


	std::string GetVariable(std::string keyValue);
	void SetVariable(std::string keyValue, std::string value);
	void getNewLines(const char* filename);

	void RunNextLine();
	void RunLines();
	//3.1.4 Tests & Jumps

	//3.1.5 Functies

	//3.1.6 Eindoplossing

	//The stack(list) that holds the retrieved values from the curl website thingy
	std::vector<std::string> stack;
	std::map<std::string, std::string> map;
	std::map<std::string, std::string> labels;

private:
	bool get_end();
	bool _end;
	std::vector<std::string> _commands;
	void checkLabelDefinitions();
	std::vector<std::string> get_lineCommands();
	void set_lineCommands(std::vector<std::string> value);
	std::string get_last();
};