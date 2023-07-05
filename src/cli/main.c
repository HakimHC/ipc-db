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

#include "shared.h"
#include "socket.h"
#include "server.h"
#include <string.h>
#include <sys/un.h>

int	main(void)
{
	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd < 0)
		return 1;
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (connect(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		return 2;
	int a = 5;
	send(sfd, &a, sizeof(int), 0);
	send(sfd, "hola", strlen("hola"), 0);
	send(sfd, "quetal", strlen("quetal"), 0);

	return 0;
}
