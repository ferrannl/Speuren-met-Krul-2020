#pragma once
#include <string>
#include <iostream>
#include <string>
#include <curl/curl.h>

class CurlHandler {

public:
	size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp);
	std::string GetTextFile(const char* filename);
private:

};