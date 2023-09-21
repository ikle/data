/*
 * Capsa String Vector Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_STRING_VEC_H
#define CAPSA_STRING_VEC_H  1

#include <capsa/string.h>
#include <capsa/vec.h>

VEC_DECLARE_TYPED (string, char *, const char *)
VEC_DECLARE_COPY (string)

#endif  /* CAPSA_STRING_VEC_H */
