/* This file is part of IPC-db. */

/* IPC-db is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* IPC-db is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with IPC-db.  If not, see <https://www.gnu.org/licenses/>. */

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "server.h"
#include "shared.h"
#include "socket.h"

static int mksocket_server(int *status)
{
	int sfd;
	struct sockaddr_un addr;

	if (remove(SOCK_PATH) == -1 && errno != ENOENT)
		return REMOVE;
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd < 0)
		*status = SOCKET;
	printf("[%s]: Socket created.\n", get_time());
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		return ((*status = BIND), BIND);
	printf("[%s]: Socket binded to %s.\n", get_time(), SOCK_PATH);
	if (listen(sfd, BACKLOG) == -1)
		return ((*status = LISTEN), LISTEN);
	printf("[%s]: Socket marked as passive (listening).\n", get_time());
	*status = SUCCESS;
	return sfd;
}

int	recieve_str(char *ptr, int fd)
{
	char 	tmp = 1;
	int 	r;

	while (tmp && ptr)
	{
		r = recv(fd, &tmp, 1, MSG_WAITALL);
		if (r < 0)
			return RECV;
		if (!r)
			break;
		*ptr = tmp;
		++ptr;
	}
	return SUCCESS;
}

static t_data* read_strings(int fd, int *status)
{
	int r;
	int len = 2;

	init();
	char *it[] = { buf_key, buf_value };
	
	r = recv(fd, &op, sizeof(int), 0);
	if (r < 0)
		return ((*status = RECV), NULL);
	for (int i = 0; i < len; i++)
	{
		if (i && op == GET)
			break;
		if (recieve_str(it[i], fd) != SUCCESS)
			return ((*status = RECV), NULL);
	}
	t_data* res = (t_data *) malloc(sizeof(t_data));
	if (!res)
	{
		*status = NOMEM;
		return NULL;
	}
	res->op = op;
	res->arg1 = strdup(buf_key);
	if (op == GET)
		res->arg2 = NULL;
	else
	 	res->arg2 = strdup(buf_value);
	printf("[%s]: Operation: %s | Key: %s | Value: %s\n", get_time(), num_to_op(res->op), res->arg1, res->arg2);
	*status = SUCCESS;
	return res;
}

static const char * operate(t_data *data)
{
	const char *tmp;

	switch (data->op)
	{
		case GET:
			tmp = get(data->arg1);
			return (tmp ? tmp : "(nil)");
		case SET:
			if (set(data->arg1, data->arg2) != EXIT_SUCCESS)
				return strerror(errno);
			return "OK";
		default:
			return NULL;
	}
}

enum error_code recieve_data(void)
{
	int status;

	int sfd = mksocket_server(&status);
	if (sfd < 0)
		return sfd;
	for (;;)
	{
		int cfd = accept(sfd, NULL, NULL);
		if (cfd < 0)
			return ACCEPT;
		printf("[%s]: Accepted incoming connection.\n", get_time());
		t_data *data = read_strings(cfd, &status);
		if (status != SUCCESS)
			return status;
		const char *res = operate(data);
		printf("[%s]: Operation result: %s\n", get_time(), res);
		send(cfd, res, strlen(res) + 1, 0);
		free(data);
		close(cfd);
	}
	return SUCCESS;
}
