#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "CurlHandler.h"
#include "Interpreter.h"

int main(int argc, char* argv[])
{
	const char baseUrl[] = "https://www.swiftcoder.nl/cpp1";
	const char startUrl[] = "/start.txt";

	auto curl_handler = std::make_unique<CurlHandler>();
	auto curl_interpreter = std::make_unique<Interpreter>();

	std::string readBuffer = curl_handler->GetTextFile("https://www.swiftcoder.nl/cpp1/start.txt");
	std::stringstream stream(readBuffer);
	while (stream.good()) {
		std::string line;
		std::getline(stream, line, '\n');
		std::cout << line << std::endl;
		curl_interpreter->readLine(line);
	}
	return 0;
}