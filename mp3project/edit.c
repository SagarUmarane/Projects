/*
Name:
Date:
Description:
Sample Input:
Sample Output:
*/
#include<stdio.h>
#include "types.h"
#include "edit.h"
Status read_and_validate_edit_content(char *argv[], EditInfo *editinfo)
{
    editinfo->file_name = argv[4];

    if(strcmp(strstr(argv[4], "."), ".mp3") == 0)
    {
	printf("file having .mp3 extension\n");
	return e_success;
    }
    else
    {
	return e_failure;
    }
}


Status do_edit_content(char *argv[], EditInfo *editinfo)
{
    if(open_file_for_edit(editinfo) == e_success)
    {
	printf("file open successfully\n");
    }
    else
    {
	printf("file open is failed\n");
    }

    if(check_ID3_edit(editinfo) == e_success)
    {
	printf("file having ID3\n");
    }
    else
    {
	printf("file not have ID3\n");
	return e_failure;
    }

    if(check_version_edit(editinfo) == e_success)
    {
	printf("file having correct version\n");
    }
    else
    {
	printf("file not having correct version\n");
	return e_failure;
    }

    fseek(editinfo->fptr_mp3, 10, SEEK_SET);
    if(check_the_edit_option(argv, editinfo) == e_success)
    {
	printf("content edited successfully\n");
    }
    else
    {
	printf("failed to edit the content\n");
       return e_failure;
    }    

    return e_success;

}

Status open_file_for_edit(EditInfo *editinfo)
{
    editinfo->fptr_mp3 = fopen(editinfo->file_name, "r+");

    if(editinfo->fptr_mp3==NULL)
    {
	printf("Error: Unable to open the file\n");
	return e_failure;
    }
    return e_success;
}

Status check_ID3_edit(EditInfo *editinfo)
{
    char string[4];
    fread(string, 3, 1, editinfo->fptr_mp3);
    string[4]='\0';
    printf("%s\n",string);
    if(strcmp(string, "ID3")==0)
    {
	return e_success;
    }
    else
    {
	return e_failure;
    }
}

Status check_version_edit(EditInfo *editinfo)
{
   int num=0;
   char ch;
   
   for(int i=0; i<2; i++)
   {
      fread(&ch, 1, 1, editinfo->fptr_mp3);
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

Status check_the_edit_option(char *argv[], EditInfo *editinfo)
{
    char *new_option = argv[2];
    char *new_title = argv[3];
    char *option[] = {"-t", "-a", "-A", "-y", "-m", "-c"};
    char *frame_id[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
    int i=0;
//    int size=0;
    while(i<6)
    {
	char tag[4];
	fread(tag, 4, 1, editinfo->fptr_mp3);
//	printf("%s\n",tag);
//	printf("%s\n",option[i]);
        int size=0;
	char ch;
	for(int j=0;j<sizeof(int);j++)
	{
	    fread(&ch, 1, 1, editinfo->fptr_mp3);
	    size = (size << 8) | ch;
	}
//	printf("%d\n",size);
	fseek(editinfo->fptr_mp3, 3L, SEEK_CUR);

	if(strcmp(option[i], new_option) == 0)
	{
	  if(strcmp(tag, frame_id[i])==0)
	  {
	     fprintf(editinfo->fptr_mp3, "%s", new_title);
	     return e_success;
	  }
	}
	fseek(editinfo->fptr_mp3, size-1, SEEK_CUR);
	i++;
    }
    return e_failure;
}    


