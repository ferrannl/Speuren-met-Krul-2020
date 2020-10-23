#include "Interpreter.h"

Interpreter::Interpreter() {
	stack = std::vector<std::string>();
	map = std::map<std::string, std::string>();
	labels = std::map<std::string, std::string>();
	commands = std::vector<std::string>();
	lineCounter = 0;
}

// push_back	=		waarde toevoegen aan einde
// back			=		pak waarde aan het einde
// pop_back		=		verwijderd waarde aan het einde

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
		labels[label] = lineCounter + 1;
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
	lineCounter++;
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
