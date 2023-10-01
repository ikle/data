/*
 * Capsa Tree
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_TREE_H
#define CAPSA_TREE_H  1

#include <capsa/avl.h>
#include <capsa/types.h>

#define TREE_DECLARE(name)						\
									\
struct name##_tree {							\
	struct avl *root;						\
};									\
									\
static inline struct avl *name##_node_alloc (const void *key)		\
{									\
	struct name *o;							\
									\
	return (o = name##_alloc (key)) == NULL ? NULL : &o->node;	\
}									\
									\
static inline void name##_node_free (struct avl *node)			\
{									\
	name##_free (container_of (node, struct name, node));		\
}									\
									\
static inline								\
int name##_node_cmp (const void *key, const struct avl *node)		\
{									\
	struct name *n = container_of (node, struct name, node);	\
									\
	return name##_order (key, n);					\
}									\
									\
static inline void name##_tree_init (struct name##_tree *o)		\
{									\
	o->root = NULL;							\
}									\
									\
static inline void name##_tree_fini (struct name##_tree *o)		\
{									\
	avl_free (o->root, name##_node_free);				\
}									\
									\
static inline struct name *						\
name##_tree_insert (struct name##_tree *o, const void *key)		\
{									\
	struct avl *n = avl_search (&o->root, key, name##_node_cmp,	\
				    name##_node_alloc);			\
									\
	return n == NULL ? NULL : container_of (n, struct name, node);	\
}									\
									\
static inline struct name *						\
name##_tree_remove (struct name##_tree *o, const void *key)		\
{									\
	struct avl *n = avl_remove (&o->root, key, name##_node_cmp);	\
									\
	return n == NULL ? NULL : container_of (n, struct name, node);	\
}									\
									\
static inline struct name *						\
name##_tree_lookup (struct name##_tree *o, const void *key)		\
{									\
	struct avl *n = avl_find (&o->root, key, name##_node_cmp);	\
									\
	return n == NULL ? NULL : container_of (n, struct name, node);	\
}									\

#endif  /* CAPSA_TREE_H */
