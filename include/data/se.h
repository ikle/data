/*
 * S-Expressions
 *
 * Copyright (c) 2019 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DATA_SE_H
#define DATA_SE_H  1

#include <data/type.h>

struct se_scope *se_scope_alloc (int flags);
void se_scope_free (struct se_scope *o);

struct se *se_atom (struct se_scope *scope, const char *atom);
const char *se_atom_name (const struct se *o);

struct se *se_pair (struct se *head, struct se *tail);
struct se *se_list (struct se *arg, ...);
void se_free (struct se *o);

#include <stdio.h>

void se_show (struct se *o, FILE *to);

#endif  /* DATA_SE_H */
