#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "Interpreter.h"
#include <crtdbg.h>
#include <exception>


int main(int argc, char* argv[])
{
	try {
		Interpreter* curl_interpreter = new Interpreter();

		curl_interpreter->getNewLines("start.txt");

		delete curl_interpreter;
	}
	catch (const std::exception& ex) {
		std::cerr << argv[0] << ": " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << argv[0] << ": unknown error\n";
		return EXIT_FAILURE;
	}
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}