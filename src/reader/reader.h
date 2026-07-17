#ifndef CR_READER_H
#define CR_READER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "archive.h"
#include "cache.h"
#include "decoder.h"
#include "error.h"
#include "renderer.h"

typedef struct CR_Reader CR_Reader;

CR_Error
CR_ReaderCreate(
    CR_Reader **reader);

void
CR_ReaderDestroy(
    CR_Reader *reader);

CR_Error
CR_ReaderOpen(
    CR_Reader *reader,
    const char *filename);

void
CR_ReaderClose(
    CR_Reader *reader);

size_t
CR_ReaderPageCount(
    const CR_Reader *reader);

size_t
CR_ReaderCurrentPage(
    const CR_Reader *reader);

CR_Error
CR_ReaderGoToPage(
    CR_Reader *reader,
    size_t page);

CR_Error
CR_ReaderNextPage(
    CR_Reader *reader);

CR_Error
CR_ReaderPreviousPage(
    CR_Reader *reader);

CR_Error
CR_ReaderRender(
    CR_Reader *reader,
    CR_Renderer *renderer);

#endif
