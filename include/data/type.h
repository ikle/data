/*
 * Data Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_TYPE_H
#define COLIBRI_DATA_TYPE_H  1

#include <stddef.h>

struct data_type {
	void (*free) (void *o);
	int (*eq) (const void *o, const void *sample);
	size_t (*hash) (size_t iv, const void *o);
};

#endif  /* COLIBRI_DATA_TYPE_H */
