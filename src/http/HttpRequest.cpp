#include "HttpRequest.hpp"

HttpRequest::HttpRequest() : 
    requestLine_(RequestLine()),
    header_(Header()),
    body_("")
    {}

HttpRequest::~HttpRequest() {}

void    HttpRequest::appendRequest(std::string input)
{
    if (rawRequest.empty())
        rawRequest = input;
    else 
        rawRequest.append(input, 0, input.length());
}

std::string     HttpRequest::getRawRequest()
{
    return (this->rawRequest);
}
