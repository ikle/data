/*
 * Colobri String Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <data/string.h>
#include <string.h>

void *string_copy_fn (const void *from)
{
	return strdup (from);
}

const struct data_type string_type = {
	.copy	= string_copy_fn,
	.free	= (free_fn *) string_free,
	.eq	= (eq_fn   *) string_eq,
	.hash	= (hash_fn *) string_hash,
};
