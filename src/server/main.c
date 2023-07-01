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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "server.h"

struct	s_hashtable** hashtable;

int	main(void)
{
	hashtable = calloc(sizeof(struct s_hashtable*), MAX_HT_SIZE);
	if (!hashtable && errno == ENOMEM)
		return perror("malloc"), EXIT_FAILURE;
	set("hola", "que tal");
	printf("%s\n", get("hola"));
	return 0;
}
