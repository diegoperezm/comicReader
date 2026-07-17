#ifndef COMIC_READER_ARCHIVE_H
#define COMIC_READER_ARCHIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "error.h"

////////////////////////////////////////////////////////////////////////////////
//
// Types
//
////////////////////////////////////////////////////////////////////////////////

typedef struct CR_Archive CR_Archive;

typedef enum
{
    CR_ARCHIVE_UNKNOWN = 0,
    CR_ARCHIVE_DIRECTORY,
    CR_ARCHIVE_CBZ
} CR_ArchiveType;

typedef struct
{
    uint32_t index;
    char name[256];
    uint64_t compressed_size;
    uint64_t uncompressed_size;
    bool directory;
} CR_ArchiveEntry;

////////////////////////////////////////////////////////////////////////////////
//
// Archive Lifetime
//
////////////////////////////////////////////////////////////////////////////////

CR_Error
CR_ArchiveOpen(
    CR_Archive **archive,
    const char *path);


void
CR_ArchiveClose(
    CR_Archive *archive);

////////////////////////////////////////////////////////////////////////////////
//
// Information
//
////////////////////////////////////////////////////////////////////////////////

CR_ArchiveType
CR_ArchiveGetType(
    const CR_Archive *archive);


const char *
CR_ArchiveGetPath(
    const CR_Archive *archive);


uint32_t
CR_ArchiveGetEntryCount(
    const CR_Archive *archive);

////////////////////////////////////////////////////////////////////////////////
//
// Entries
//
////////////////////////////////////////////////////////////////////////////////

CR_Error
CR_ArchiveGetEntry(
    const CR_Archive *archive,
    uint32_t index,
    CR_ArchiveEntry *entry);


CR_Error
CR_ArchiveFindEntry(
    const CR_Archive *archive,
    const char *name,
    CR_ArchiveEntry *entry);

////////////////////////////////////////////////////////////////////////////////
//
// Reading
//
////////////////////////////////////////////////////////////////////////////////

CR_Error
CR_ArchiveReadEntry(
    const CR_Archive *archive,
    uint32_t index,
    uint8_t **data,
    size_t *size);


CR_Error
CR_ArchiveReadEntryByName(
    const CR_Archive *archive,
    const char *name,
    uint8_t **data,
    size_t *size);

////////////////////////////////////////////////////////////////////////////////
//
// Utility
//
////////////////////////////////////////////////////////////////////////////////

bool
CR_ArchiveIsOpen(
    const CR_Archive *archive);


bool
CR_ArchiveIsDirectory(
    const CR_Archive *archive);

#ifdef __cplusplus
}
#endif

#endif
