/*
 * Capsa Generic Hash
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/hash.h>

/* Jenkins One-at-a-time hash */
size_t hash (size_t iv, const void *data, size_t size)
{
	const unsigned char *p;
	size_t i;

	for (p = data, i = 0; i < size; ++i) {
		iv += p[i];
		iv += (iv << 10);
		iv ^= (iv >> 6);
	}

	iv += (iv << 3);
	iv ^= (iv >> 11);
	iv += (iv << 15);

	return iv;
}
