/*
 * Simple Binary Heap with Wait Queue
 *
 * Copyright (c) 2015-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_BH_H
#define COLIBRI_DATA_BH_H  1

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
void bh_init (struct bh *o, int (*cmp) (void *a, void *b));

/* free all internal objects, call destructor (if not NULL) for each
   contained object */
void bh_fini (struct bh *o, void (*item_free) (void *o));

/* returns object with higher priority in head */
void *bh_top (struct bh *o);

/* commit all pending objects into heap */
void bh_commit (struct bh *o);

/*
 * 1. Resize the buffer if necessary unless nowait = 1.
 * 2. Queue object into heap if there is enough space.
 * 3. Commit all pending objects into heap unless nowait = 1.
 *
 * Returns nonzero on success
 */
int bh_push (struct bh *o, void *x, int nowait);

/* commit all pending objects and remove top object from heap */
void *bh_pop (struct bh *o);

#endif  /* COLIBRI_DATA_BH_H */
