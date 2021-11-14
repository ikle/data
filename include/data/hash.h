/*
 * Generic Hash
 *
 * Copyright (c) 2010-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_HASH_H
#define COLIBRI_DATA_HASH_H  1

#include <stddef.h>

size_t hash (size_t iv, const void *data, size_t size);

#endif  /* COLIBRI_DATA_HASH_H */
