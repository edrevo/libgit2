/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#include "debugalloc.h"
#include <include/jemalloc/jemalloc.h>

void *je_malloc_wrapper(size_t size, const char *file, int line)
{
    return _rjem_malloc(size);
}

void *je_realloc_wrapper(void *ptr, size_t size, const char *file, int line)
{
    return _rjem_realloc(ptr, size);
}

int git_debugalloc_init_allocator(git_allocator *allocator)
{
	// Setup jemalloc
	allocator->gmalloc = je_malloc_wrapper;
	allocator->grealloc = je_realloc_wrapper;
	allocator->gfree = _rjem_free;
	return 0;
}
