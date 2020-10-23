#include "CurlHandler.h"

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

std::string CurlHandler::GetTextFile(const char* filename) {
	std::string result;
	CURL* curl;
	CURLcode res;
	const char baseUrl[] = "https://www.swiftcoder.nl/cpp1/";
	char* fullUrl = new char[std::strlen(baseUrl) + std::strlen(filename) + 1];
	std::strcpy(fullUrl, baseUrl);
	std::strcat(fullUrl, filename);
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, fullUrl);
		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		/* Set a pointer to our struct to pass to the callback */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

		/* Switch on full protocol/debug output */
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		if (CURLE_OK != res) {
			/* we failed */
			std::cerr << "curl told us " << res << '\n';
		}
	}
	curl_global_cleanup();

	return result;
}