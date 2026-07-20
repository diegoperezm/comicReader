#include <unistd.h>
#include <stdlib.h>
#include "miniz.h"
#include "raylib.h"

int
main(int argc, char *argv[]) 
{
  (void) argc;
  (void) argv;
// char cwd[1024]; if(getcwd(cwd, sizeof(cwd))) printf("cwd = %s\n", cwd);
  InitWindow(600, 600, "Comic Reader");
  SetTargetFPS(30);               

  void* image_data;
  size_t image_size;
  mz_zip_archive zip_archive = {0};
  const char* filename = "data/data.zip";
 
// 1. mz_zip_reader_init_file()
  mz_bool status = mz_zip_reader_init_file(&zip_archive,filename,0);

  if(!status)
  {
    mz_zip_error err = mz_zip_get_last_error(&zip_archive);
    fprintf(stderr,"Failed to open zip file: %s\n",filename);
    fprintf(stderr,"Error code: %d\n", err);
    fprintf(stderr, "%s\n", mz_zip_get_error_string(err));
    return EXIT_FAILURE;
  }

  printf("Archive opened successfully.\n");

// 2. mz_zip_reader_get_num_files()
  mz_uint file_count = mz_zip_reader_get_num_files(&zip_archive);
  printf("Files: %u\n\n", file_count);

  for(mz_uint i=0; i < file_count; i++)
  {
// 3. mz_zip_reader_file_stat()
    mz_zip_archive_file_stat  stat; 
    if(!mz_zip_reader_file_stat(&zip_archive,i,&stat))
    {
    	printf("Cannot read file %u\n",i);
     	continue;
    }
    printf("Index:    %u\n", stat.m_file_index);
    printf("Filename: %s\n",stat.m_filename);
    printf("Compressed: %llu\n",
	   (unsigned long long)stat.m_comp_size);
    printf("Original: %llu bytes\n",
	   (unsigned long long)stat.m_uncomp_size);
    printf("Directory?: %s\n",
	   stat.m_is_directory ? "yes" : "no");
    printf("\n"); 

// 4. mz_zip_reader_extract_to_mem() 
// 4. or mz_zip_reader_extract_to_heap() 
   image_data =  mz_zip_reader_extract_to_heap( 
                &zip_archive,
        		    0,
	              &image_size,
		            0);
  }

  if (image_data == NULL)
  {
    fprintf(stderr, "Extraction failed: %s\n",
            mz_zip_get_error_string(mz_zip_get_last_error(&zip_archive)));
    return EXIT_FAILURE;
  }
   Image image = LoadImageFromMemory(
    ".png",
    image_data,
    (int)image_size
   );

   if (image.data == NULL)
   {
    fprintf(stderr, "Failed to decode image.\n");
    mz_free(image_data);
    return EXIT_FAILURE;
   }

   Texture2D texture = LoadTextureFromImage(image);
   mz_free(image_data);
   UnloadImage(image);

   while (!WindowShouldClose())    
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
          ClearBackground(RAYWHITE);
          DrawTexture(texture,0,0, WHITE);
          DrawText("this IS a texture!", 360, 370, 10, GRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  UnloadTexture(texture);
  CloseWindow();                

// 5. mz_zip_reader_end()
  mz_zip_reader_end(&zip_archive);
  return EXIT_SUCCESS;
}






