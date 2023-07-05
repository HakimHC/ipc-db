#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <sys/socket.h>
# include <sys/un.h>

typedef struct data
{
	char	*op;
	char	*arg1;
	char	*arg2;
}	t_data;

#endif
