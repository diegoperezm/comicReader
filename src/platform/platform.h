#ifndef COMIC_READER_PLATFORM_H
#define COMIC_READER_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Filesystem
////////////////////////////////////////////////////////////////////////////////

bool
CR_FileExists(
    const char *path);


bool
CR_DirectoryExists(
    const char *path);


CR_Error
CR_FileReadAll(
    const char *path,
    uint8_t **data,
    size_t *size);


CR_Error
CR_FileWriteAll(
    const char *path,
    const uint8_t *data,
    size_t size);


////////////////////////////////////////////////////////////////////////////////
// Directory
////////////////////////////////////////////////////////////////////////////////

typedef struct CR_DirectoryIterator CR_DirectoryIterator;


CR_Error
CR_DirectoryOpen(
    CR_DirectoryIterator **iterator,
    const char *path);


bool
CR_DirectoryNext(
    CR_DirectoryIterator *iterator,
    char *filename,
    size_t filename_size);


void
CR_DirectoryClose(
    CR_DirectoryIterator *iterator);


////////////////////////////////////////////////////////////////////////////////
// Path Utilities
////////////////////////////////////////////////////////////////////////////////

CR_Error
CR_PathJoin(
    char *output,
    size_t output_size,
    const char *left,
    const char *right);


const char *
CR_PathFilename(
    const char *path);


const char *
CR_PathExtension(
    const char *path);


bool
CR_PathHasExtension(
    const char *path,
    const char *extension);


////////////////////////////////////////////////////////////////////////////////
// Logging
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    CR_LOG_TRACE = 0,
    CR_LOG_DEBUG,
    CR_LOG_INFO,
    CR_LOG_WARNING,
    CR_LOG_ERROR,
    CR_LOG_FATAL

} CR_LogLevel;


void
CR_Log(
    CR_LogLevel level,
    const char *format,
    ...);


#define CR_LOG_TRACE(...) \
    CR_Log(CR_LOG_TRACE, __VA_ARGS__)

#define CR_LOG_DEBUG(...) \
    CR_Log(CR_LOG_DEBUG, __VA_ARGS__)

#define CR_LOG_INFO(...) \
    CR_Log(CR_LOG_INFO, __VA_ARGS__)

#define CR_LOG_WARNING(...) \
    CR_Log(CR_LOG_WARNING, __VA_ARGS__)

#define CR_LOG_ERROR(...) \
    CR_Log(CR_LOG_ERROR, __VA_ARGS__)

#define CR_LOG_FATAL(...) \
    CR_Log(CR_LOG_FATAL, __VA_ARGS__)


////////////////////////////////////////////////////////////////////////////////
// Time
////////////////////////////////////////////////////////////////////////////////

uint64_t
CR_TimeMilliseconds(void);


double
CR_TimeSeconds(void);


////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////

const char *
CR_PlatformName(void);


#ifdef __cplusplus
}
#endif

#endif
