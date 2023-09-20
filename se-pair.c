/*
 * S-Expressions: Pair
 *
 * Copyright (c) 2019-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "se-int.h"

struct se *se_pair (struct se *head, struct se *tail)
{
	struct se_pair *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->head = head;
	o->tail = tail;
	return pair_to_se (o);
}

void se_free (struct se *o)
{
	if (o == NULL)
		return;

	if (!se_is_atom (o)) {
		se_free (se_to_pair (o)->head);
		se_free (se_to_pair (o)->tail);
		free (o);
	}
}
