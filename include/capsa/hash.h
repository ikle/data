/*
 * Capsa Generic Hash
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_HASH_H
#define CAPSA_HASH_H  1

#include <stddef.h>

size_t hash (size_t iv, const void *data, size_t size);

#endif  /* CAPSA_HASH_H */
