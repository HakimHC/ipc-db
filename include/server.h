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

#ifndef __SERVER_H__
# define __SERVER_H__

# define FNV_OFFSET 	2166136261
# define FNV_PRIME 	16777619

# define MAX_HT_SIZE	100

typedef struct s_hashtable
{
	char	*key;
	char	*value;
}	t_hashtable;

/* Hashing algorithm (FNV-1a) */
int	hash_fnv1a(const char *str);

#endif
