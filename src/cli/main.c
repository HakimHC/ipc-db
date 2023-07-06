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

#include <stdlib.h>
#include <stdio.h>

#include "shared.h"
#include "socket.h"
#include "server.h"
#include <string.h>

int op_to_num(const char *op)
{
	char *ops[] = { "GET", "MGET", "SET", "SETNX", "DELETE"};
	int nums[] = { GET, MGET, SET, SETNX, DELETE };

	for (int i = 0; i < NUMOPS; i++) {
		if (!strcmp(op, ops[i]))
			return nums[i];
	}
	return -1;
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

int	main(int argc, char **argv)
{
	if (argc < 3)
		return 1;

	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd < 0)
		return 1;
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (connect(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		return 2;

	int op = op_to_num(argv[1]);
	send(sfd, &op, sizeof(int), 0);
	for (int i = 2; i < argc + 1; i++)
	{
		if (i == 4 && op == GET)
			break;
		char *tmp = argv[i];
		int size = (argv[i] ? strlen(argv[i]) + 1 : 0);
		send(sfd, tmp, size, 0);
	}
	char *ptr = calloc(sizeof(char), BUFFER_SIZE);
	recieve_str(ptr, sfd);
	printf("\"%s\"\n", ptr);
	free(ptr);
	return 0;
}
