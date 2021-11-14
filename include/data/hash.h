/*
 * Generic Hash
 *
 * Copyright (c) 2010-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DATA_HASH_H
#define DATA_HASH_H  1

#include <stddef.h>

size_t hash (size_t iv, const void *data, size_t size);

#endif  /* DATA_HASH_H */
