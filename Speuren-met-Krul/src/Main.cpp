#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "Interpreter.h"

int main(int argc, char* argv[])
{
	auto curl_interpreter = std::make_unique<Interpreter>();
	//const char startUrl[] = "start.txt";
	const char startUrl[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt";

	curl_interpreter->getNewLines(startUrl);
	//std::string readBuffer = curl_interpreter->curl_handler->GetTextFile(startUrl);
	//std::stringstream stream(readBuffer);
	//curl_interpreter->getLines(readBuffer);
	//while (stream.good()) {
	//	std::string line;
	//	std::getline(stream, line, '\n');
	//	std::cout << line << std::endl;
	//	curl_interpreter->readLine(line);
	//}
	return 0;
}