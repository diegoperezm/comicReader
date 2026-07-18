#include <stdlib.h>
#include "miniz.h"


int
main(int argc, char *argv[]) 
{
  (void) argc;
  (void) argv;

  mz_zip_archive zip_archive = {0};
  const char* filename = "../data/data.zip";

// 1. mz_zip_reader_init_file()
  mz_bool status = mz_zip_reader_init_file(&zip_archive,filename,0);

  if(!status)
  {
    fprintf(stderr, "Failed to open zip file: %s\n", filename);
    return EXIT_FAILURE;
  }

  printf("Archive opened successfully.\n");

// 2. mz_zip_reader_get_num_files()

  mz_uint file_count = mz_zip_reader_get_num_files(&zip_archive);
  printf("Files: %u\n\n", file_count);

  void* data;
  size_t size;

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
    data =   mz_zip_reader_extract_to_heap(
		    &zip_archive,
		    stat.m_file_index,
	            &size,
		    0
		    );
  }


  

// 4. mz_zip_reader_extract_to_mem() 
// 4. mz_zip_reader_extract_to_heap() 



// 5. mz_zip_reader_end()
  mz_zip_reader_end(&zip_archive);

  return EXIT_SUCCESS;
}
