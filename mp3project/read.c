/*
Name:
Date:
Description:
Sample Input:
Sample Output:
*/

#include<stdio.h>
#include "types.h"
#include<stdlib.h>
#include "read.h"


OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1], "-v") == 0)
    {
	return e_view;
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
	return e_edit;
    }
    else if(strcmp(argv[1], "--help")==0)
    {
	return e_help;
    }
    else
    {
	return e_unsupported;
    }
}

Status read_and_validate_view_content(char *argv[], ViewInfo *viewinfo)
{
    viewinfo->file_name = argv[2];

    if(strcmp(strstr(argv[2], "."), ".mp3") == 0)
    {
//	printf("file having .mp3 extension\n");
	return e_success;
    }
    else
    {
//	printf("file not having .mp3 extension\n");
	return e_failure;
    }

}
Status do_view_content(ViewInfo *viewinfo)
{
    open_file(viewinfo);
    check_ID3(viewinfo);
    check_version(viewinfo);
 /*   if(open_file(viewinfo)==e_success)
    {
	printf("file opened successfuliy\n");
    }
    else
    {
	printf("file failed to open\n");
	return e_failure;
    }

    if(check_ID3(viewinfo) == e_success)
    {
	printf("file having ID3\n");
    }
    else
    {
	printf("file not have ID3\n");
	return e_failure;
    }

    if(check_version(viewinfo) == e_success)
    {
	printf("file having correct version\n");
    }
    else
    {
	printf("file not having correct version\n");
	return e_failure;
    }*/

    fseek(viewinfo->fptr_mp3, 10, SEEK_SET);

    if(read_the_content_from_file(viewinfo) == e_success)
    {
	printf("content in the file is printed successfully\n");
    }
    else
    {
	printf("content in the file is failed to print\n");
	return e_failure;
    }
    return e_success;

}

Status open_file(ViewInfo *viewinfo)
{
    viewinfo->fptr_mp3 = fopen(viewinfo->file_name, "r");

    if(viewinfo->fptr_mp3==NULL)
    {
	printf("Error: Unable to open the file\n");
	return e_failure;
    }
    return e_success;
}

Status check_ID3(ViewInfo *viewinfo)
{
    char string[4];
    fread(string, 3, 1, viewinfo->fptr_mp3);
    string[4]='\0';
   // printf("%s\n",string);
    if(strcmp(string, "ID3")==0)
    {
	return e_success;
    }
    else
    {
	return e_failure;
    }
}

Status check_version(ViewInfo *viewinfo)
{
   int num=0;
   char ch;
   
   for(int i=0; i<2; i++)
   {
      fread(&ch, 1, 1, viewinfo->fptr_mp3);
      num = (num << 8) | ch;
   }

   if(num == 768)
   {
       return e_success;
   }
   else
   {
       return e_failure;
   }
}


Status read_the_content_from_file(ViewInfo *viewinfo)
{
    Status ret;

    printf("\n------------------------------------------------------\n");
    printf("\n----------------SELECTED VIEW DETAILS---------------\n\n");
    ret = get_and_display_data("Title: ", "TIT2", viewinfo->frame_id, &viewinfo->title_size, viewinfo->title_name, viewinfo->fptr_mp3, viewinfo);
    if(ret == e_failure)
    {
	printf("Error: title frame id content cannot be displayed.\n");
	return e_failure;
    }
    ret = get_and_display_data("Artist: ", "TPE1", viewinfo->frame_id, &viewinfo->artist_name_size, viewinfo->artist_name, viewinfo->fptr_mp3, viewinfo);
    if(ret == e_failure)
    {
	printf("Error: title frame id content cannot be displayed.\n");
	return e_failure;
    }
    ret = get_and_display_data("Album: ", "TALB", viewinfo->frame_id, &viewinfo->albume_name_size, viewinfo->album_name, viewinfo->fptr_mp3, viewinfo);
    if(ret == e_failure)
    {
	printf("Error: title frame id content cannot be displayed.\n");
	return e_failure;
    }
    ret = get_and_display_data("Year: ", "TYER", viewinfo->frame_id, &viewinfo->year_size, viewinfo->title_name, viewinfo->fptr_mp3, viewinfo);
    if(ret == e_failure)
    {
	printf("Error: title frame id content cannot be displayed.\n");
	return e_failure;
    }
    ret = get_and_display_data("Content: ", "TCON", viewinfo->frame_id, &viewinfo->music_size, viewinfo->music_name, viewinfo->fptr_mp3, viewinfo);
    if(ret == e_failure)
    {
	printf("Error: title frame id content cannot be displayed.\n");
	return e_failure;
    }
    ret = get_and_display_data("Comment: ", "COMM", viewinfo->frame_id, &viewinfo->comment_size, viewinfo->comment, viewinfo->fptr_mp3, viewinfo);
    if(ret == e_failure)
    {
	printf("Error: title frame id content cannot be displayed.\n");
	return e_failure;
    }
    printf("\n------------DETAILS DISPLAYED SUCCESSFULLY--------------\n");
    printf("\n--------------------------------------------------------\n\n");
    return e_success;
}    
Status get_sizeof_tag(ViewInfo *viewinfo)
{
    int size=0;
    char str;
    for(int i=0; i<sizeof(int); i++)
    {
	fread(&str, 1, 1, viewinfo->fptr_mp3);
	size = (size << 8) | str;
    }
    return size;
}

Status get_and_display_data(char *str_frame, char *str_id, char *frame_id, int *tag_size, char *tag_title, FILE *fptr, ViewInfo *viewinfo)
{
    fread(frame_id, 4, 1, fptr);
  //  printf("%s\n",frame_id);

    *tag_size = get_sizeof_tag(viewinfo);
  //  printf("%d\n",*tag_size);

    if((strncmp(frame_id, str_id, 4))==0)
    {
	fseek(fptr, 3L, SEEK_CUR);
	tag_title = (char *)malloc(((*tag_size) * sizeof(char)));
	fread(tag_title, *tag_size-1, 1, fptr);
	printf("%-10s%s.\n", str_frame, tag_title);
	return e_success;
    }
    return e_failure;
}
