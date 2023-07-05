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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "shared.h"

void	init(void)
{
	buf_key = (char *) calloc(sizeof(char), BUFFER_SIZE);
	buf_value = (char *) calloc(sizeof(char), BUFFER_SIZE);

	if (!buf_key || !buf_value) { perror("malloc"); exit(errno); }
}
