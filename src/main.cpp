#include "Webserv.hpp"
#include "Observer.hpp"
#include "Server.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#include <iostream>


int	main(int argc, char** argv)
{
	std::string configPath;

	if (argc == 1)
		configPath = "src/config/minimal.conf";
	else if (argc == 2)
		configPath = argv[1];

	Observer o;
	Config c1;
	Location r1;
	Cgi	cgi1;

	// =============================================================================
	// Option A : Parsed Config File (how it should work in the end)
	// =============================================================================

	try
	{
		Webserv webserv(configPath);
		//webserv.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	// =============================================================================
	// Option B : Configuration Object Sample (only for tests, will be later removed)
	// =============================================================================

	/*
	// General
	c1.setHost("127.0.0.1");
	c1.setPort(8084);
	c1.setServerName("server_1");

	// Client Max Body Size
	c1.setClientMaxBodySize(10);

	// Redirection
	c1.setRedirection(HttpRedirection(301, Uri("/redirection.html")));

	// Error Pages
	c1.addErrorPage(ErrorPage(404, Path("/www/404.html")));
	c1.addErrorPage(ErrorPage(403, Path("/www/403.html")));

	// Locations
	r1.setUri(Uri("/html"));
	r1.setRootPath(Path("/www/html"));
	// r1.setRedirection(HttpRedirection(301, Path("/www/redirection.html")));
	r1.setAutoIndex(true);
	r1.setDefaultFile(Path("index.html"));
	r1.setUploadDirectory(Path("/www/upload"));
	r1.addAllowedMethod(GET);
	r1.addAllowedMethod(POST);
	*/

	// Locations : CGI
	//r1.setIsCgi(true);
	//cgi1.setFileExtension(".php");
	//cgi1.setRootPath(Path("/www/cgi"));
	//cgi1.setScriptPath(Path("/www/cgi/script.sh"));
	//cgi1.setWorkingDirectory(Path("/www/cgi/work"));
	//cgi1.addAllowedMethod(GET);
	//cgi1.addAllowedMethod(POST);
	//r1.setCgi(cgi1);
	//c1.addLocation(r1);

	// =============================================================================
	// Option C : Server Constructors (only for tests, will be later removed)
	// =============================================================================

	/*
	Logger::logger()->logTitle(LOG_INFO, "Servers starting");

	Server s1("127.0.0.1", 8084, &o);
	s1.setConfig(c1);
	s1.start();
	Server s2("127.0.0.1", 8085, &o);
	s2.setConfig(c1);
	s2.start();

	o.addServerToMonitor(&s1);
	o.addServerToMonitor(&s2);
	o.monitorEvents();
	*/

	return (0);
}
