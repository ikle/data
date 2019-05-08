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

struct sa_pool *sa_pool_alloc (int order);
void sa_pool_free (struct sa_pool *o);

void *sa_alloc (struct sa_pool *o, size_t size);

#endif  /* DATA_SA_H */
