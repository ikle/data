/*
 * Colibry Atom Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_ATOM_H
#define COLIBRI_DATA_ATOM_H  1

#include <data/type.h>

/*
 * An atom is a constant string, where two identical strings with different
 * pointers cannot exist. 
 */

void  *atom_copy (const void *from);
void   atom_free (void *o);
int    atom_eq   (const void *o, const void *sample);
size_t atom_hash (size_t iv, const void *o);

const struct data_type atom_type;

#endif  /* COLIBRI_DATA_ATOM_H */
