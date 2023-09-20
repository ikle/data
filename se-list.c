/*
 * S-Expressions: List
 *
 * Copyright (c) 2019-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdarg.h>

#include "se-int.h"

static struct se **se_list_add (struct se **tail, struct se *o)
{
	struct se *p;

	if ((p = se_pair (o, NULL)) == NULL)
		return NULL;

	*tail = p;
	return &se_to_pair (p)->tail;
}

struct se *se_list (struct se *arg, ...)
{
	va_list ap;
	struct se *o = arg, *head = NULL, **tail = &head;

	if (o == NULL || (tail = se_list_add (tail, o)) == NULL)
		return NULL;

	va_start (ap, arg);

	while ((o = va_arg (ap, struct se *)) != NULL)
		if ((tail = se_list_add (tail, o)) == NULL)
			goto no_add;

	va_end (ap);
	return head;
no_add:
	va_end (ap);
	se_free (head);
	return NULL;
}
