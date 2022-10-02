/*
 * Colobri Atom Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <data/atom.h>

const struct data_type atom_type = {
	.copy	= (copy_fn *) atom_copy,
	.free	= (free_fn *) atom_free,
	.eq	= (eq_fn   *) atom_eq,
	.hash	= (hash_fn *) atom_hash,
};
