#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "Interpreter.h"
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	Interpreter* curl_interpreter = new Interpreter();

	curl_interpreter->getNewLines("start.txt");

	delete curl_interpreter;

	_CrtDumpMemoryLeaks();

	return 0;
}