#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "Interpreter.h"

int main(int argc, char* argv[])
{
	auto curl_interpreter = std::make_unique<Interpreter>();
	//const char startUrl[] = "start.txt";
	//const char startUrl[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt";
	//const char startUrl[] = "4812-9-6727.txt";
	const char startUrl[] = "AasHgsho.txt";
	curl_interpreter->getNewLines(startUrl);
	return 0;
}