#include "HttpRequest.hpp"
#include "ToString.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequest::HttpRequest() : 
    rawRequest_(),
    //"GET /cgi-bin/hello.php?name=newFileMickey&content=donaldDucknotdonaldTrump HTTP/1.1\r\n Host: http://127.0.0.1:7777/\r\n Connection: close\r\n\r\n"),
    requestLine_(HttpRequestLine()),
    header_(HttpHeader()),
    body_("")
{
    inputs_.insert(std::make_pair("name", "newFileMickey")); // REVISIT : ?
    inputs_.insert(std::make_pair("content", "donaldDuck not donaldTrump")); // REVISIT : ?
}

HttpRequest::~HttpRequest() {}

void    HttpRequest::appendRequest(std::string input)
{
    if (rawRequest_.empty())
        rawRequest_ = input;
    else 
        rawRequest_.append(input, 0, input.length());
}

// =============================================================================
// Getters
// =============================================================================

const std::string& HttpRequest::getRawRequest() const 
{
    return (rawRequest_);
}

// ·············································································
// Request Line
// ·············································································

const HttpRequestLine& HttpRequest::getRequestLine() const 
{
    return (requestLine_);
}

// --- Method ---

HttpMethodType    HttpRequest::getMethod() const
{
    return (requestLine_.getMethod());
}

void    HttpRequest::setMethod(HttpMethodType httpMethod)
{
    requestLine_.setMethod(httpMethod);
}


// --- Uri ---

const Uri& HttpRequest::getUri() const
{
    return (requestLine_.getUri());
}

void	HttpRequest::setUri(Uri uri)
{
    requestLine_.setUri(uri);
}

// --- Http Version ---

const std::string&  HttpRequest::getHttpVersion(void) const
{
    return(requestLine_.getHttpVersion());
}

void    HttpRequest::setHttpVersion(const std::string& httpVersion)
{
    requestLine_.setHttpVersion(httpVersion);
}

// ·············································································
// Header
// ·············································································

const HttpHeader& HttpRequest::getHttpHeader() const 
{
    return (header_);
}

// ·············································································
// Body
// ·············································································

const std::string& HttpRequest::getBody() const 
{
    return (body_);
}

int HttpRequest::getBodySize() const 
{
    return (body_.length() * sizeof(char));
}

std::string HttpRequest::getInput(std::string key)
{
    return (inputs_[key]);
}

// ··· "Deep" Getters and utils ···

/*HttpMimeType    HttpRequest::getMimeType() const
{
    return (header_.getMimeType());
}*/

// =============================================================================
// Public Methods 
// =============================================================================

std::string   HttpRequest::generatePrintString()
{
    std::stringstream ss;

    ss << "Client Request (RawRequest): " << rawRequest_ << std::endl;
	
    ss << "Dummy RequestLine: \n\n" 
	          << httpMethodToString(requestLine_.getMethod()) << " ; "
	          << requestLine_.getUri() << " ; "
	          << requestLine_.getHttpVersion() << std::endl;

    ss << "\nDummy Header:\n\n"
	          << "host_: " << header_.getHost() << "\n"
	          << "userAgent_: " << header_.getUserAgent() << "\n"
	          << "contentLength_: " << toString(header_.getContentLength()) << "\n"
	          //<< "contentType_: " << header_.getMimeType() << "\n"
	          << "connectionType_: " << header_.getConnectionTypeString() << "\n"
	          //<< "accept_: " << header_.getAccept() << "\n"
	          << "acceptEncoding_: " << header_.getAcceptEncoding() << "\n"
	          << "acceptLanguage_: " << header_.getAcceptLanguage() << std::endl;

    return (ss.str());
}
