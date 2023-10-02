/*
 * Capsa Tree
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <capsa/tree.h>

struct s_node {
	struct avl node;
	const char *key;
	size_t index;
};

static struct s_node *s_node_alloc (const char *key)
{
	struct s_node *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	o->key = key;
	return o;
}

static void s_node_free (struct s_node *o)
{
	free (o);
}

static int s_node_order (const char *key, const struct s_node *o)
{
	return strcmp (key, o->key);
}

TREE_DECLARE (s_node)

static void s_node_show (struct s_node *o, void *cookie)
{
	printf ("%zu = %s\n", o->index, o->key);
}

TREE_DECLARE_WALK (s_node, show)

static const char *list[] = {
	"test string #1",
	"Lorem ipsum dolor sit amet",
	"consectetur adipiscing elit",
	"sed do eiusmod tempor incididunt",
	"ut labore et dolore magna aliqua",
	"test string #2",
	NULL
};

int main (int argc, char *argv[])
{
	struct s_node_tree t;
	struct s_node *e;
	size_t i;

	s_node_tree_init (&t);

	for (i = 0; list[i] != NULL; ++i)
		if ((e = s_node_tree_insert (&t, list[i])) == NULL) {
			perror ("E: tree insert");
			s_node_tree_fini (&t);
			return 1;
		}
		else
			e->index = i;

	if ((e = s_node_tree_lookup (&t, list[3])) == NULL) {
			fprintf (stderr, "E: tree lookup failed\n");
			s_node_tree_fini (&t);
			return 1;
	}
	else
		s_node_show (e, NULL);

	if ((e = s_node_tree_remove (&t, list[3])) == NULL) {
			fprintf (stderr, "E: tree remove failed\n");
			s_node_tree_fini (&t);
			return 1;
	}
	else
		s_node_free (e);

	s_node_tree_show (&t, NULL);
	s_node_tree_fini (&t);
	return 0;
}
