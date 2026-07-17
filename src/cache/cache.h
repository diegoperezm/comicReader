#ifndef CR_CACHE_H
#define CR_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "error.h"
#include "renderer.h"

typedef struct CR_Cache CR_Cache;

CR_Error
CR_CacheCreate(
    CR_Cache **cache,
    size_t memory_limit);

void
CR_CacheDestroy(
    CR_Cache *cache);

CR_Error
CR_CacheInsert(
    CR_Cache *cache,
    size_t page,
    const CR_Image *image);

const CR_Image *
CR_CacheFind(
    CR_Cache *cache,
    size_t page);

void
CR_CacheClear(
    CR_Cache *cache);

#endif
