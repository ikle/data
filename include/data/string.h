/*
 * Colibry String Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_STRING_H
#define COLIBRI_DATA_STRING_H  1

#include <data/type.h>

void  *string_copy (const void *from);
void   string_free (void *o);
int    string_eq   (const void *o, const void *sample);
size_t string_hash (size_t iv, const void *o);

const struct data_type string_type;

struct string;

#endif  /* COLIBRI_DATA_STRING_H */
