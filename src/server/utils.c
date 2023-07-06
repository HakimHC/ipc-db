#include <stdio.h>
#include <time.h>
#include <string.h>

#include "server.h"
#include "shared.h"

const char * get_time(void)
{
	time_t t;
	char * res;

	time(&t);
	res = ctime(&t);
	res[strlen(res) - 1] = 0;
	return res;
}

const char *num_to_op(int num)
{
	char *ops[] = { "GET", "MGET", "SET", "SETNX", "DELETE"};
	int nums[] = { GET, MGET, SET, SETNX, DELETE };

	for (int i = 0; i < NUMOPS; i++) {
		if (num == nums[i])
			return ops[i];
	}
	return NULL;
}
