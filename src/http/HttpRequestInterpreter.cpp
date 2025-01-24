#include "HttpRequestInterpreter.hpp"
#include "ToString.hpp"
#include "HttpMethodType.hpp"
#include "Logger.hpp"
#include "ResourceDefault.hpp"
#include "Cgi.hpp"

#include <string>
#include <stdexcept>
#include <sys/stat.h> // For struct stat and stat()
#include <unistd.h>   // For realpath()
#include <limits.h>   // For PATH_MAX

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequestInterpreter::HttpRequestInterpreter(Server* server)
    : server_(server)
{}

HttpRequestInterpreter::~HttpRequestInterpreter()
{}

// =============================================================================
// Getters
// =============================================================================


// =============================================================================
// Public Methods 
// =============================================================================

HttpResponse   HttpRequestInterpreter::interpret(HttpRequest& request, Config& config)
{
    HttpMethodType      method = request.getMethod();
    HttpResponse        response;


    if (!config.isMethodAllowed(method, request.getUri()))
        return (HttpResponse(createResourceError(config, 405)));

    if (!config.isSizeAllowed(request.getBodySize(), request.getUri()))
        return (HttpResponse(createResourceError(config, 413)));

    if (isCgiRequest(config, request))
        return (HttpResponse(createResourceCgi(config, request)));

    switch (method)
    {
        case GET:
            Logger::logger()->log(LOG_INFO, "CLient sent a GET request");
            response = handleGetRequest(config, request);
            break;
        case POST:
            Logger::logger()->log(LOG_INFO, "CLient sent a POST request");
            // get request content length header (if too big --> 403)
            response = handlePostRequest(config, request);
            break;
        case DELETE:
            Logger::logger()->log(LOG_INFO, "CLient sent a DELETE request");
            response = handleDeleteRequest(config, request);
            break;
        case UNDEFINED:
            throw (HttpRequestInterpreter::BadRequest());
    }
    return (response);
}

// =============================================================================
// Private Methods 
// =============================================================================

// ·············································································
// Method Handlers
// ·············································································

HttpResponse    HttpRequestInterpreter::handleGetRequest(Config& config, HttpRequest& request)
{
    (void) request;
    Logger::logger()->log(LOG_DEBUG, "handleGetRequest...");
    return (HttpResponse(createResourceError(config, 404)));
}


HttpResponse    HttpRequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri     uri = request.getRelativeUri();

    // formulaire POST prenom, nom  --> page php --> salut Mickey Mouse
    // upload de fichier

    Logger::logger()->log(LOG_INFO, config.getServerName());
    // check if resource exists
    // check if resource is allowed
    // get request content length header (check not too big --> 403)
    return (response);
}

HttpResponse    HttpRequestInterpreter::handleDeleteRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri             uri = request.getRelativeUri();

    // allowed to deleter or not --> ResourceError(403)
    // is dir ? 
    // deleteResource(Uri)

    Logger::logger()->log(LOG_INFO, config.getServerName());
    return (response);
}

// ·············································································
// Resource Makers
// ·············································································

# include <iostream>

Resource	HttpRequestInterpreter::createResourceError(Config& config, int code)
{
    Logger::logger()->log(LOG_DEBUG, "handleResourceError...");
	const ConfigErrorPage*  customErrorPage = config.getConfigErrorPage(code);

	if (!customErrorPage)
	{
		 Logger::logger()->log(LOG_DEBUG, "No custom error page found, creating a default one...");
		return (ResourceDefault(code));
	}

	Logger::logger()->log(LOG_DEBUG, "Custom error page URI : " + customErrorPage->getUri());

	const Path* customErrorPagePath = config.getPath(customErrorPage->getUri());

	if (!customErrorPagePath)
	{
		Logger::logger()->log(LOG_DEBUG, "No custom error root path found");
		return (ResourceDefault(code));
	}

	Logger::logger()->log(LOG_DEBUG, std::string("Custom error page root path : ") + customErrorPagePath);
	
	return (ResourceDefault(code));
}

Resource	HttpRequestInterpreter::createResourceFile(Config& config, HttpRequest& request)
{
	Uri     uri = request.getRelativeUri();
	 (void) config;
	// check if uri exists 
	// check if directory or file 
        // if directory get index file
    // check if directory listing is on
    // build File object
    // check permissions
	// check if redirection
	// if redirection  return  resourceRedirection

	return (Resource(200, "File..."));
}

Resource	HttpRequestInterpreter::createResourceDirectoryList(Config& config, Path path)
{
	(void) path;
    (void) config;
	return (Resource(200, "Directory list..."));
}

Resource        HttpRequestInterpreter::createResourceCgi(Config& config, HttpRequest& request)
{
    (void) request;

    // if (config.isTypeAllowed(request.getMimeType(), request.getUri()))
    //     return (createResourceError(config, 415));

    if (request.getMethod() == POST && request.getBody().empty())
        return (createResourceError(config, 400));

    // Check "inputs" field (map) -> correct types
        // 422 Unprocessable Entity
    
    // Check permissions 
        // 401 Unauthorised or 403 Forbidden
    
    // Check duplicate ? Does the resource already exist? 
        // 409 Conflict

    // check amount of requests? 
        // 429 too many requests
    
    // protect from sql injection

        
    Cgi     cgi(config, request);

    cgi.runCgi();

    // create response with CGI script output

    return (createResourceError(config, 404));
}

// ·············································································
// Utils
// ·············································································

bool    HttpRequestInterpreter::isCgiRequest(Config& config, HttpRequest& request)
{
    Logger::logger()->log(LOG_DEBUG, "request uri : " + request.getUri());
    const Path*                 pathPtr = config.getPath(request.getUri());
    if (pathPtr == NULL)
    {   
        Logger::logger()->log(LOG_DEBUG, "path from config is NULL, it's not a CGI request"); 
        return (false);
    }
    
    Path                        realPath = *pathPtr;
    std::vector<std::string>    pathComponents = realPath.getComponents();

    Logger::logger()->log(LOG_DEBUG, "real path = " + realPath);
    for (size_t i = 0; i < pathComponents.size(); i++)
    {
        Logger::logger()->log(LOG_DEBUG, "path component: " + pathComponents[i]);
        if (pathComponents[i].find("cgi-bin") != std::string::npos || 
                pathComponents[i].find(config.getCgiDir()) != std::string::npos ||
                pathComponents[i].find(".php") != std::string::npos || 
                pathComponents[i].find(".py") != std::string::npos || 
                pathComponents[i].find(".cgi") != std::string::npos)
        {
            Logger::logger()->log(LOG_DEBUG, "It's a CGI request all right");
            return (true);
        }
    }
    Logger::logger()->log(LOG_DEBUG, "It's not a CGI request");
    return (false); 
}
