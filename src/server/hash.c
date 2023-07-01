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

#include <stdint.h>

#include "server.h"

int	hash_fnv1a(const char *str)
{
	uint32_t hash = FNV_OFFSET;
	const uint8_t *s = (uint8_t *) str;

	while (*s)
	{
		hash ^= *s;
		hash *= FNV_PRIME;
		++s;
	}
	return hash % MAX_HT_SIZE;
}
