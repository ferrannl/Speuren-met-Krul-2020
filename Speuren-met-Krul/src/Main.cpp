#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "CurlHandler.h"

int main(int argc, char* argv[])
{
	const char starurl[] = "https://www.swiftcoder.nl/cpp1/start.txt";

	CurlHandler curl_handler = CurlHandler();

	std::string readBuffer = curl_handler.GetTextFile(starurl);

	std::stringstream stream(readBuffer);

	while (stream.good()) {
		std::string line;
		std::getline(stream, line, '\n');
		std::cout << line << std::endl;
	}

	return 0;
}