/*
Name:
Date:
Description:
Sample Input:
Sample Output:
 */

#include<stdio.h>
#include "types.h"
#include "read.h"
#include "edit.h"

int main(int argc, char *argv[])
{

    if(argc <= 1)
    {
	printf("Error: INVALID ARGUMENTS\nUSAGE:\nTo view please pass like: ./a.out -v mp3filename\nTo edit please pass like: ./a/out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\nTo get help pass like: ./a.out --help\n");
    }
    if(check_operation_type(argv) == e_view)
    {
	ViewInfo viewinfo;
	printf("Your's chioce is perform view the data\n");

	if(read_and_validate_view_content(argv, &viewinfo) == e_success)
	{
	    printf("read and validate is completed\n");

	    if(do_view_content(&viewinfo) == e_success)
	    {
		printf("viewing the mp3 file content is completed\n");
		return e_success;
	    }
	    else
	    {
		printf("viewing the mp3 file content is not completed\n");
	    }
	}
	else
	{
	    printf("read and validate is failed\n");
	}
    }
    else if(check_operation_type(argv) == e_edit)
    {
	EditInfo editinfo;
	printf("Your's chioce is perform edit the data\n");

	if(read_and_validate_edit_content(argv, &editinfo) == e_success)
	{
	    printf("read and validate is completed\n");

	    if(do_edit_content(argv, &editinfo) == e_success)
	    {
		printf("editing the mp3 file content is completed\n");
		return e_success;
	    }
	    else
	    {
		printf("editing the mp3 file content is not completed\n");
	    }
	}
	else
	{
	    printf("read and validate is failed\n");
	}
    }
    else if(check_operation_type(argv) == e_help)
    {
	printf("\n---------------HELP MENU---------------\n\n");
	printf("1. -v -> to view the mp3 file contents\n");
	printf("2. -e -> to edir the mp3 file contents\n");
	printf("\t2.1. -t -> to edit song title\n");
	printf("\t2.2. -a -> to edit artist name\n");
	printf("\t2.3. -A -> to edit album name\n");
	printf("\t2.4. -y -> to edit year\n");
	printf("\t2.5. -m -> to edit content\n");
	printf("\t2.6. -c -> to edit comment\n");
	printf("\n---------------------------------------\n");
    }
    else
    {
	printf("Error: Wrong Option is given\n");
    }

}


