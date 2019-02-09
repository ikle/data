/*
 * Simple Binary Heap with Wait Queue
 *
 * Copyright (c) 2015 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DATA_BH_H
#define DATA_BH_H  1

#include <stddef.h>

struct bh {
	int (*cmp) (void *a, void *b);
	size_t count;	/* points to end of heap */
	size_t tail;	/* points to end of pending objects queue */
	size_t avail;	/* points to end of pool */
	void **pool;
};

/* initialize heap object for a first use; cmp -- predicate, should return
   nonzero if object a has higher priority over object b */
void bh_init (struct bh *bh, int (*cmp) (void *a, void *b));

/* free all internal objects */
void bh_fini (struct bh *bh);

/* returns object with higher priority in head */
void *bh_top (struct bh *bh);

/* queue object to heap, but do not insert it immediately, returns nonzero
   on success */
int bh_add (struct bh *bh, void *x);

/* commit all pending objects into heap */
void bh_commit (struct bh *bh);

/* insert object into heap: queue object to heap and commit all pending
   objects, returns nonzero on success */
int bh_push (struct bh *bh, void *x);

/* commit all pending objects and remove top object from heap */
void *bh_pop (struct bh *bh);

#endif  /* DATA_BH_H */
