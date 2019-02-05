/*
 * S-Expressions, destructor
 *
 * Copyright (c) 2019 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <ctype.h>

#include "se-int.h"

static int str_is_simple (const char *s)
{
	for (; *s != '\0'; ++s)
		if (*s == '"' || *s == '\\' || !isgraph (*s))
			return 0;

	return 1;
}

static void show_escaped (const char *s, FILE *to)
{
	if (str_is_simple (s)) {
		fprintf (to, "%s", s);
		return;
	}

	fputc ('"', to);

	for (; *s != '\0'; ++s)
		switch (*s) {
		case '"':
		case '\\':
			fprintf (to, "\\%c", *s);
			break;
		default:
			if (isprint (*s))
				fputc (*s, to);
			else
				fprintf (to, "\\%03o", *s);
		}

	fputc ('"', to);
}

static int se_show_list (struct se *o, FILE *to)
{
	struct se *p;

	for (p = o; !se_is_atom (p); p = se_to_pair (p)->tail) {}

	if (p != NULL)
		return 0;

	fputs ("(", to);

	if (o != NULL)
		for (;;) {
			se_show (se_to_pair (o)->head, to);

			if ((o = se_to_pair (o)->tail) == NULL)
				break;

			fputc (' ', to);
		}

	fputs (")", to);

	return 1;
}

static int se_show_atom (struct se *o, FILE *to)
{
	if (!se_is_atom (o))
		return 0;

	show_escaped (se_atom_name (o), to);
	return 1;
}

void se_show (struct se *o, FILE *to)
{
	if (se_show_list (o, to) || se_show_atom (o, to))
		return;

	fputs ("(", to);

	se_show (se_to_pair (o)->head, to);
	fputs (" . ", to);
	se_show (se_to_pair (o)->tail, to);

	fputs (")", to);
}
