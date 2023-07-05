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
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		return ((*status = BIND), BIND);
	if (listen(sfd, BACKLOG) == -1)
		return ((*status = LISTEN), LISTEN);
	*status = SUCCESS;
	return sfd;
}

static enum error_code read_strings(int fd)
{
	int r;
	size_t size;

	void *it[] = { &op, buf_key, buf_value };

	for (int i = 0; i < 3; i ++)
	{
		size = (!i ? sizeof(int) : BUFFER_SIZE);
		r = recv(fd, it[i], size, 0);
		printf("%d\n", r);
		if (r < 0)
			return RECV;
	}
	printf("%s\n", buf_key);
	printf("%s\n", buf_value);
	return SUCCESS;
}

enum error_code recieve_data(void)
{
	int status;

	int sfd = mksocket_server(&status);
	if (sfd < 0)
		return sfd;
	printf("socket return success\n");
	for (;;)
	{
		int cfd = accept(sfd, NULL, NULL);
		if (cfd < 0)
			return ACCEPT;
		read_strings(cfd);
	}
	return SUCCESS;
}
