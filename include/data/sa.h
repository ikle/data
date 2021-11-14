/*
 * Small Allocator
 *
 * Copyright (c) 2008-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_SA_H
#define COLIBRI_DATA_SA_H  1

#include <stddef.h>

struct sa_pool *sa_pool_alloc (unsigned align);
void sa_pool_free (struct sa_pool *o);

void *sa_alloc (struct sa_pool *o, size_t size);

#endif  /* COLIBRI_DATA_SA_H */
