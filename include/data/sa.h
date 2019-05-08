/*
 * Small Allocator
 *
 * Copyright (c) 2008-2010,2019 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DATA_SA_H
#define DATA_SA_H  1

#include <stddef.h>

struct sa_pool {
	struct sa_block *head, *tail;
	size_t end;
	unsigned order;
};

int  sa_pool_init (struct sa_pool *o, int order);
void sa_pool_fini (struct sa_pool *o);

void *sa_alloc (struct sa_pool *o, size_t size);

#endif  /* DATA_SA_H */
