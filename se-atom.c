/*
 * S-Expressions
 *
 * Copyright (c) 2019 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include <data/ht.h>
#include <data/string.h>

#include "se-int.h"

struct se_scope {
	struct ht table;
};

static const struct data_type string_type = {
	.hash	= string_hash,
	.eq	= string_eq,
	.free	= free,
};

struct se_scope *se_scope_alloc (int flags)
{
	struct se_scope *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		goto no_object;

	if (!ht_init (&o->table, &string_type))
		goto no_ht;

	return o;
no_ht:
	free (o);
no_object:
	return NULL;
}

void se_scope_free (struct se_scope *o)
{
	if (o == NULL)
		return;

	ht_fini (&o->table);
}

struct se *se_atom (struct se_scope *scope, const char *name)
{
	char *o;

	if ((o = ht_lookup (&scope->table, (void *) name)) != NULL)
		return name_to_atom (o);

	if ((o = strdup (name)) == NULL)
		goto no_object;

	if (!ht_insert (&scope->table, o, 0))
		goto no_insert;

	return name_to_atom (o);
no_insert:
	free (o);
no_object:
	return NULL;
}

const char *se_atom_name (const struct se *o)
{
	return o == NULL ? "nil" : se_is_atom (o) ? atom_to_name (o) : NULL;
}
