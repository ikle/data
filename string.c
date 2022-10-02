/*
 * Colobri String Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <data/string.h>

const struct data_type string_type = {
	.copy	= (copy_fn *) string_copy,
	.free	= (free_fn *) string_free,
	.eq	= (eq_fn   *) string_eq,
	.hash	= (hash_fn *) string_hash,
};
