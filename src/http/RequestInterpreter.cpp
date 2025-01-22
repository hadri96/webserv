#include "RequestInterpreter.hpp"
#include "ToString.hpp"
#include "HttpMethodType.hpp"
#include "Logger.hpp"
#include "ResourceDefault.hpp"

#include <string>
#include <stdexcept>
#include <sys/stat.h> // For struct stat and stat()
#include <unistd.h>   // For realpath()
#include <limits.h>   // For PATH_MAX

// =============================================================================
// Constructors and Destructor
// =============================================================================

RequestInterpreter::RequestInterpreter(Server* server)
    : server_(server)
{}

RequestInterpreter::~RequestInterpreter()
{}

// =============================================================================
// Getters
// =============================================================================


// =============================================================================
// Public Methods 
// =============================================================================

HttpResponse   RequestInterpreter::interpret(HttpRequest& request, Config& config)
{
    HttpMethodType      method = request.getMethod();
    HttpResponse        response;

    /*
    if (!config.isMethodAllowed(method, request.getUri()))
        return (HttpResponse(createResourceError(config, 405)));

    if (!config.isSizeAllowed(request.getBodySize(), request.getUri()))
        return (HttpResponse(createResourceError(config, 413)));
    */

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
            throw (RequestInterpreter::BadRequest());
    }
    return (response);
}

// =============================================================================
// Private Methods 
// =============================================================================

HttpResponse    RequestInterpreter::handleGetRequest(Config& config, HttpRequest& request)
{
    (void) request;
    Logger::logger()->log(LOG_DEBUG, "handleGetRequest...");
    return (HttpResponse(createResourceError(config, 404)));
}


HttpResponse    RequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
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

HttpResponse    RequestInterpreter::handleDeleteRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri             uri = request.getRelativeUri();

    // allowed to deleter or not --> ResourceError(403)
    // is dir ? 
    // deleteResource(Uri)

    Logger::logger()->log(LOG_INFO, config.getServerName());
    return (response);
}

// --- Resources ---
Resource	RequestInterpreter::createResourceError(Config& config, int code)
{
    Logger::logger()->log(LOG_DEBUG, "handleResourceError...");
    (void) config;
	//const ErrorPage* errorPage = getErrorPage(code)
	// For now we return only the default status page
	return (ResourceDefault(code));
}

Resource	RequestInterpreter::createResourceFile(Config& config, HttpRequest& request)
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

Resource	RequestInterpreter::createResourceDirectoryList(Config& config, Path path)
{
	(void) path;
    (void) config;
	return (Resource(200, "Directory list..."));
}

Resource        RequestInterpreter::createResourceCgi(Config& config, HttpRequest& request)
{
    (void) request;

    // Check Request Mime type (authorised by config? )
        // return 415 Unsupported Media Type 
        
    // Check Request Body not empty()
        // 400 bad request 

    // Check "inputs" field (map) -> correct types
        // 422 Unprocessable Entity
    
    // Check permissions 
        // 401 Unauthorised or 403 Forbidden
    
    // Check duplicate ? Does the resource already exist? 
        // 409 Conflict

    // check amount of requests? 
        // 429 too many requests
    
    // protect from sql injection
    
    // Run CGI script in new process (fork())

    // create response with CGI script output

    return (createResourceError(config, 404));
}
