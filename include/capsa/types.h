/*
 * Capsa Core Types
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_TYPES_H
#define CAPSA_TYPES_H  1

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * container_of (ptr, type, member) -- cast a member of a structure out to
 * the containing structure, where:
 *
 *  ptr    -- the pointer to the member;
 *  type   -- the type of the container struct this is embedded in;
 *  member -- the name of the member within the struct.
 */
#define container_of(ptr, type, member)  \
 	((type *) ((void *) (ptr) - offsetof (type, member)))

#endif  /* CAPSA_TYPES_H */
