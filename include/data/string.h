/*
 * Colibry String Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_STRING_H
#define COLIBRI_DATA_STRING_H  1

#include <capsa/string.h>
#include <data/type.h>

extern const struct data_type string_type;

void *string_copy_fn (const void *from);
struct string;

#endif  /* COLIBRI_DATA_STRING_H */
