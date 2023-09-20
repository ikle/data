/*
 * Colibry Atom Type
 *
 * Copyright (c) 2017-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_ATOM_H
#define COLIBRI_DATA_ATOM_H  1

#include <data/type.h>
#include <data/unit.h>

/*
 * An atom is a pointer. It can be used, for example, to store constant
 * strings, where two identical strings with different pointers cannot
 * exist.
 */

UNIT_DECLARE_TYPED (atom, const void *, const void *, 1)

extern const struct data_type atom_type;

#endif  /* COLIBRI_DATA_ATOM_H */
