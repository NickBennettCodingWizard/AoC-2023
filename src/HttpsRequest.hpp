#pragma once

#include <curl/curl.h>
#include <optional>
#include <string>

class HttpsRequest
{
  public:
    HttpsRequest();
    ~HttpsRequest();

    HttpsRequest(const HttpsRequest&) = delete;
    HttpsRequest& operator=(const HttpsRequest&) = delete;

    void setUrl(const std::string& url);
    void setUrl(const char* url);

    void setContentType(const std::string& type);
    void setContentType(const char* type);

    std::optional<std::string> operator()() const;

  private:
    CURL* mCurl = nullptr;
    std::string mReadBuffer;
};
