/*
 * String Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DATA_STRING_H
#define DATA_STRING_H  1

#include <data/type.h>

int string_eq (const void *o, const void *sample);
size_t string_hash (size_t iv, const void *o);

#endif  /* DATA_STRING_H */
