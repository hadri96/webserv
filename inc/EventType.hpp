#ifndef EVENT_TYPE_HPP
# define EVENT_TYPE_HPP

enum	EventType
{
	CLIENT_NEW_CONNECTION,
	CLIENT_READY_TO_READ,
	CLIENT_READY_TO_WRITE,
	CLIENT_ERROR,
	CLIENT_DISCONNECTED
};

#endif