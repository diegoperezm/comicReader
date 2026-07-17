#ifndef CR_RENDERER_H
#define CR_RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../common/error.h"

typedef struct CR_Renderer CR_Renderer;

typedef struct
{
    int width;
    int height;

    unsigned char *pixels;

} CR_Image;

typedef struct
{
    float zoom;

    float offset_x;
    float offset_y;

    float rotation;

} CR_View;

CR_Error CR_RendererCreate(CR_Renderer **renderer);

void CR_RendererDestroy(
    CR_Renderer *renderer);

CR_Error CR_RendererUploadImage(
    CR_Renderer *renderer,
    const CR_Image *image);

void CR_RendererDraw(
    CR_Renderer *renderer,
    const CR_View *view);

void CR_RendererResize(
    CR_Renderer *renderer,
    int width,
    int height);

#endif
