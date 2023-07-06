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

# define MAX_HT_SIZE	2048

extern struct s_hashtable** 	hashtable;

extern char*			buf_key;
extern char*			buf_value;
extern int			op;

typedef struct s_hashtable
{
	char	*key;
	char	*value;
	struct s_hashtable *next;
}	t_hashtable;

/* Hashing algorithm (FNV-1a) */
int	hash_fnv1a(const char *str);

/* Hashtable utilities */
const char* get(const char* value);
int	set(const char *key, const char *value);

/* Initializer */
void	init(void);

/* Utilities */
const char * get_time(void);
const char *num_to_op(int num);

#endif
