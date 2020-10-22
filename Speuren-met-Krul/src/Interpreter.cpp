#include "Interpreter.h"

Interpreter::Interpreter() {
	stack = std::vector<std::string>();
	map = std::map<std::string, std::string>();
}

void Interpreter::readLine(std::string line)
{
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
		stack.push_back(line);
	}
	if ()
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

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
