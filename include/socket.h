#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <sys/socket.h>
# include <sys/un.h>

typedef struct data
{
	int	op;
	char	*arg1;
	char	*arg2;
}	t_data;

# define BACKLOG 5

enum error_code recieve_data(void);

#endif
