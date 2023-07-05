#ifndef __SHARED_H__
# define __SHARED_H__

enum op_tokens
{
	GET,
	MGET,
	SET,
	SETNX,
	DELETE
};

enum error_code
{
	SUCCESS = -10,
	NOMEM,
	REMOVE,
	SOCKET,
	BIND,
	LISTEN,
	ACCEPT,
	CONNECT,
	SEND,
	RECV
};

# define SOCK_PATH "/tmp/dbsock"
# define BUFFER_SIZE 512

#endif
