#include "CurlHandler.h"

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

std::string CurlHandler::GetTextFile(std::string filename) {
	std::string result;
	auto deleter = [&](CURL* ptr) {curl_easy_cleanup(ptr); };
	std::unique_ptr<CURL, decltype(deleter)> curl(curl_easy_init(), deleter);
	CURLcode res;
	const std::string baseUrl = "https://www.swiftcoder.nl/cpp1/";
	std::string fullUrl = baseUrl + filename;
	curl_global_init(CURL_GLOBAL_DEFAULT);

	if (curl) {
		curl_easy_setopt(curl.get(), CURLOPT_URL, fullUrl.c_str());
		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, my_write);
		/* Set a pointer to our struct to pass to the callback */
		curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &result);

		/* Switch on full protocol/debug output */
		curl_easy_setopt(curl.get(), CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl.get());

		if (CURLE_OK != res) {
			/* we failed */
			std::cerr << "curl told us " << res << '\n';
		}
	}
	curl_global_cleanup();

	return result;
}