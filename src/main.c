#include <stdlib.h>
#include "app/app.h"

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    CR_App *app = NULL;

    CR_AppConfig config =
    {
        .title         = "Comic Reader",
        .window_width  = 1600,
        .window_height = 900,
        .fullscreen    = false,
        .resizable     = true,
        .vsync         = true
    };

    if (CR_AppCreate(&app, &config) != CR_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    CR_Error result = CR_AppRun(app);

    CR_AppDestroy(app);

    return (result == CR_SUCCESS)
        ? EXIT_SUCCESS
        : EXIT_FAILURE;
}
