#include <stdio.h>
#include <stdlib.h>
#include "miniz.h"

int 
main(int argc, char* argv[])
{

/*
void* mz_zip_extract_archive_file_to_heap(
    const char* pZip_filename,
    const char* pArchive_name,
    size_t*     pSize 
*/

 const char* zip_filename = "../data/data.zip";  
 const char* file_to_extract = "red.png";
 const char* pCom = "";
 size_t uncompressed_size = 0;
 mz_uint zip_flags = 0; 
 mz_zip_error pError = MZ_ZIP_NO_ERROR;
 
 printf("Extracting '%s' from '%s' ...\n", 
	 file_to_extract,
	 zip_filename);

 void* pData = mz_zip_extract_archive_file_to_heap_v2(
		 zip_filename,
		 file_to_extract,
		 pCom,
		 &uncompressed_size,
		 zip_flags, 
		 &pError);

 if(!pData) {
   printf("%s\n", mz_zip_get_error_string(pError));
   return EXIT_FAILURE;
 }

 printf("%zu\n", uncompressed_size);

 const unsigned char* bytes = pData;

 if(uncompressed_size >= 4) {
   printf("First 4 bytes in hex: %02X  %02X %02X %02X \n",
	 bytes[0],bytes[1],bytes[2],bytes[3]);	 
 }

 for (size_t i=0; i < uncompressed_size; i++) {
   if(i%16==0)
     printf("%02zX",(size_t)i);

   printf("%02X", bytes[i]);

   if((i+1)%16 == 0)
    printf("\n");
 }
 if (uncompressed_size % 16 != 0) {
    printf("\n");
 }

 const unsigned char *end = bytes + uncompressed_size;

 for (; bytes < end; bytes++) 
   printf("%02X", *bytes);
 

 mz_free(pData);
 
 return EXIT_SUCCESS;
}


/*
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
*/
