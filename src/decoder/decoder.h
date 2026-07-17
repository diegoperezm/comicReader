#ifndef CR_DECODER_H
#define CR_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#include "error.h"
#include "renderer.h"

CR_Error
CR_DecodeImage(
    const uint8_t *data,
    size_t size,
    CR_Image *image);

void
CR_FreeImage(
    CR_Image *image);

#endif
