#include "Interpreter.h"

Interpreter::Interpreter() {
	curl_handler = std::make_shared<CurlHandler>();
	stack = std::vector<std::string>();
	map = std::map<std::string, std::string>();
	labels = std::map<std::string, std::string>();
	_commands = std::vector<std::string>();
	currentLine = 0;
	_end = false;
}

// push_back	=		waarde toevoegen aan einde
// back			=		pak waarde aan het einde
// pop_back		=		verwijderd waarde aan het einde

void Interpreter::readLine(std::string line)
{
	if (line.empty()) {
		return;
	}
	if (line.find("\\") != std::string::npos) {
		stack.push_back(line.substr(1, line.length()));
	}
	if (line.find("=") != std::string::npos) {
		std::string value = line.substr(1, line.length());
		map[value] = stack.back();
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
		std::string label = line.substr(1, line.length());
		labels[label] = currentLine + 1;
	}
	if (line.find("$") != std::string::npos) {
		std::string var1 = line.substr(1, line.length());
		std::string var2 = map[var1];
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
		std::string label = line.substr(1, line.length());
		std::string var = labels[label];
		stack.push_back(var);
	}
	if (line.find("gne") != std::string::npos) {
		std::string labelWaarde = stack.back();
		stack.pop_back();
		std::string var2 = stack.back();
		stack.pop_back();
		std::string var1 = stack.back();
		stack.pop_back();
		if (std::stoi(var1) != std::stoi(var2)) {

		}
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

bool Interpreter::is_number(std::string s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void Interpreter::getLines(std::string value) {
	std::stringstream stream(value);
	std::string line;
	while (stream.good()) {
		std::getline(stream, line, '\n');
		if (!line.empty()) {
			_commands.push_back(line);
		}
	}
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

bool Interpreter::get_end()
{
	return _end;
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

				/*

				:label Label definition.
				Beschouw de tekst na de dubbele punt tot het einde van
				de regel als een label-naam, en onthoud die,
				samen met de volgende regelpositie, zodat je later naar die regel kunt springen

				*/
			}
		}
	}
}

void Interpreter::RunNextLine() {
	std::string value = _commands[currentLine];
	++currentLine;
	readLine(value);
}

std::vector<std::string> Interpreter::get_lineCommands() {
	return _commands;
}

void Interpreter::RunLines() {
	checkLabelDefinitions();
	while (get_lineCommands().size() > currentLine) {
		RunNextLine();
	}
	std::string result = get_last();
	std::cout << result << std::endl;
	if (!get_end()) {
		//
	}
	else {
		std::cout << "Einde" << std::endl;
	}
}

void Interpreter::set_lineCommands(std::vector<std::string> value) {
	_commands = value;
}

std::string Interpreter::get_last() {
	return "";
}

std::string Interpreter::GetVariable(std::string keyValue) {
	return "";
}

void Interpreter::SetVariable(std::string keyValue, std::string value) {

}

