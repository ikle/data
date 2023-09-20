/*
 * Capsa Atom Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_ATOM_H
#define CAPSA_ATOM_H  1

#include <capsa/unit.h>

/*
 * An atom is a pointer. It can be used, for example, to store constant
 * strings, where two identical strings with different pointers cannot
 * exist.
 */

UNIT_DECLARE_TYPED (atom, const void *, const void *, 0)

#endif  /* CAPSA_ATOM_H */
