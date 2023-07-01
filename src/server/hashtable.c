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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "server.h"

const char* get(const char* key)
{
	int	idx;
	struct s_hashtable *tmp;

	idx = hash_fnv1a(key);
	tmp = hashtable[idx];
	if (!tmp)
		return (char *)NULL;
	while (tmp && strcmp(tmp->key, key))
		tmp = tmp->next;
	if (!tmp)
		return (char *)NULL;
	return tmp->value;
}

static struct s_hashtable *create_elem(const char *key, const char *value)
{
	struct s_hashtable *res = malloc(sizeof(struct s_hashtable));
	if (!res)
		return (NULL);
	res->key = (char *)key;
	res->value = (char *)value;
	res->next = NULL;
	return res;
}

int	set(const char *key, const char *value)
{
	int	idx;
	struct s_hashtable *tmp;

	idx = hash_fnv1a(key);
	if (!hashtable[idx])
	{
		hashtable[idx] = create_elem(key, value);
		if (errno == ENOMEM)
		{
			perror("malloc");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	tmp = hashtable[idx];
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_elem(key, value);
	if (!tmp->next && errno == ENOMEM)
		return perror("malloc"), EXIT_FAILURE;
	return EXIT_SUCCESS;
}
