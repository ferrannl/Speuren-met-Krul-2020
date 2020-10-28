#pragma once
#include <string>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <stdlib.h>

class CurlHandler {

public:
	std::string GetTextFile(std::string filename);
private:

};