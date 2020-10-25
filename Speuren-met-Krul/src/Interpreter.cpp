#include "Interpreter.h"

Interpreter::Interpreter() {
	curl_handler = std::make_shared<CurlHandler>();
	stack = std::vector<std::string>();
	callStack = std::vector<std::string>();
	_commands = std::vector<std::string>();
	labels = std::map<std::string, int>();
	variables = std::map<std::string, std::string>();
	currentLine = 0;
	_end = false;
}

// push_back	=		waarde toevoegen aan einde
// back			=		pak waarde aan het einde
// pop_back		=		verwijderd waarde aan het einde

void Interpreter::readLine(std::string line)
{
	if (line.empty()) {
		++currentLine;
		return;
	}
	if (line.find("\\") != std::string::npos) {
		stack.push_back(line.substr(1, line.length() - 1));
	}
	if (line.find("=") != std::string::npos) {
		std::string value = line.substr(1, line.length() - 1);
		variables[value] = stack.back();
		stack.pop_back();
	}
	if (line.find("dup") != std::string::npos) {
		stack.push_back(duplicate(stack.back()));
	}
	if (is_number(line)) {
		int integer = std::stoi(line);
		if (integer < 0) {
			stack.push_back(negate(line));
		}
		else {
			stack.push_back(line);
		}
	}
	if (line.find(":") != std::string::npos) {
		std::string label = line.substr(1, line.length() - 1);
		labels[label] = currentLine;
	}
	if (line.find("$") != std::string::npos) {
		std::string var1 = line.substr(1, line.length() - 1);
		std::string var2 = variables[var1];
		stack.push_back(var2);
	}
	if (line.find("cat") != std::string::npos) {
		std::string var1 = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		stack.push_back(var2 + var1);
	}
	if (line.find("dec") != std::string::npos) {
		std::string var = stack.back();
		stack.pop_back();
		stack.push_back(decrement(var));
	}
	if (line.find(">") != std::string::npos) {
		std::string label = line.substr(1, line.length() - 1);
		stack.push_back(label);
	}
	if (line.find("gne") != std::string::npos) {
		std::string labelValue = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		std::string var1 = stack.back();
		stack.pop_back();
		if (std::stoi(var1) != std::stoi(var2)) {
			currentLine = (labels[labelValue]);
		}
	}
	if (line.find("glt") == 0) {
		std::string labelValue = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		std::string var1 = stack.back();
		stack.pop_back();
		if (std::stoi(var1) < std::stoi(var2)) {
			currentLine = (labels[labelValue]);
		}
	}
	if (line.compare("gle") == 0) {
		std::string labelValue = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		std::string var1 = stack.back();
		stack.pop_back();
		if (std::stoi(var1) <= std::stoi(var2)) {
			currentLine = (labels[labelValue]);
		}
	}
	if (line.find("ggt") == 0) {
		std::string labelValue = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		std::string var1 = stack.back();
		stack.pop_back();
		if (std::stoi(var1) > std::stoi(var2)) {
			currentLine = (labels[labelValue]);
		}
	}
	if (line.find("gge") == 0) {
		std::string labelValue = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		std::string var1 = stack.back();
		stack.pop_back();
		if (std::stoi(var1) >= std::stoi(var2)) {
			currentLine = (labels[labelValue]);
		}
	}
	if (line.find("gto") == 0) {
		Gto();
		return;
	}
	if (line.find("fun") == 0) {
		callStack.push_back(std::to_string(currentLine));
		Gto();
	}
	if (line.find("ret") == 0) {
		currentLine = std::stoi(callStack.back());
		callStack.pop_back();
	}
	currentLine++;
}

std::string Interpreter::add(std::string firstValue, std::string secondValue) {
	int result = (std::stoi(firstValue) + std::stoi(secondValue));
	return std::to_string(result);
}

std::string Interpreter::subtract(std::string firstValue, std::string secondValue) {
	int result = (std::stoi(firstValue) - std::stoi(firstValue));
	return std::to_string(result);
}

std::string Interpreter::multiply(std::string firstValue, std::string secondValue) {
	int result = (std::stoi(firstValue) * std::stoi(firstValue));
	return std::to_string(result);
}

std::string Interpreter::divide(std::string firstValue, std::string secondValue) {
	int result = (std::stoi(firstValue) / std::stoi(firstValue));
	return std::to_string(result);
}

std::string Interpreter::modulo(std::string firstValue, std::string secondValue) {
	int result = (std::stoi(firstValue) % std::stoi(firstValue));
	return std::to_string(result);
}

std::string Interpreter::negate(std::string value) {
	int result = -1 * (std::stoi(value));
	return std::to_string(result);
}

std::string Interpreter::absolute(std::string value) {
	int result = abs((std::stoi(value)));
	return std::to_string(result);
}

std::string Interpreter::increment(std::string value) {
	int result = std::stoi(value) + 1;
	return std::to_string(result);
}

std::string Interpreter::decrement(std::string value) {
	int result = std::stoi(value) - 1;
	return std::to_string(result);
}

std::string Interpreter::duplicate(std::string value) {
	return value;
}

void Interpreter::Gto() {
	std::string labelValue = stack.back();
	stack.pop_back();
	currentLine = (labels[labelValue]);
}

bool Interpreter::is_number(std::string s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void Interpreter::getNewLines(const char* filename) {
	_commands = {};
	std::string readBuffer = curl_handler->GetTextFile(filename);
	std::stringstream stream(readBuffer);
	while (stream.good()) {
		std::string line;
		std::getline(stream, line, '\n');
		std::cout << line << std::endl;
		_commands.push_back(line);
	}
	set_lineCommands(_commands);
	RunLines();
}

void Interpreter::set_end() {
	_end = true;
}

void Interpreter::checkLabelDefinitions() {
	while (currentLine < _commands.size()) {
		std::string line = _commands[currentLine];
		++currentLine;
		if (!line.empty()) {
			if (line.find(":") != std::string::npos) {
				addLabelDefinition(line);
				/*
				:label Label definition.
				Beschouw de tekst na de dubbele punt tot het einde van
				de regel als een label-naam, en onthoud die,
				samen met de volgende regelpositie, zodat je later naar die regel kunt springen
				*/
			}
		}
	}
	currentLine = 0;
}

void Interpreter::addLabelDefinition(std::string value) {
	std::string label = value.substr(1, value.length() - 1);
	if (labels.count(label) == 0) {
		labels.insert(std::pair<std::string, int>(label, currentLine));
	}
}

void Interpreter::RunNext() {
	std::string value = _commands[currentLine];
	//++currentLine;
	readLine(value);
}

void Interpreter::RunLines() {
	checkLabelDefinitions();
	while (_commands.size() > currentLine) {
		RunNext();
	}
	std::string lastLine = stack.back();
	std::cout << lastLine << std::endl;
	if (_end == false) {
		stack.clear();
		labels.clear();
		callStack.clear();
		_commands.clear();
		variables.clear();
		currentLine = 0;
		getNewLines(lastLine.c_str());
	}
	else {
		std::cout << "Bob Polis, glashelder." << std::endl;
	}
}

void Interpreter::getLines(const char* filename) {
	std::string readBuffer = curl_handler->GetTextFile(filename);
	std::stringstream stream(readBuffer);
	std::string line;
	while (stream.good()) {
		std::string line;
		std::getline(stream, line, '\n');
		std::cout << line << std::endl;
		readLine(line);
		if (!line.empty()) {
			_commands.push_back(line);
		}
	}
}

std::vector<std::string> Interpreter::get_lineCommands() {
	return _commands;
}
void Interpreter::set_lineCommands(std::vector<std::string> value) {
	_commands = value;
}
