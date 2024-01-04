#ifndef EDIT_H
#define EDIT_H

#include "types.h"
#include<string.h>
#include<stdio.h>

typedef struct _EditInfo
{
    FILE *fptr_mp3;
    char *file_name;
    char *edit_option;

    char frame_id[4];

    int title_size;
    char *title_name;

    int albume_name_size;
    char *album_name;

    int artist_name_size;
    char *artist_name;

    int year_size;
    int year;

    int music_size;
    char *music_name;

    int comment_size;
    char *comment;
} EditInfo;


OperationType check_operation_type(char *argv[]);
Status read_and_validate_edit_content(char *argv[], EditInfo *editinfo);
Status do_edit_content(char *argv[], EditInfo *editinfo);
Status open_file_for_edit(EditInfo *editinfo);
Status check_ID3_edit(EditInfo *editinfo);
Status check_version_edit(EditInfo *editinfo);
Status check_the_edit_option(char *argv[], EditInfo *editinfo);
/*Status read_the_content_from_file(ViewInfo *viewinfo);
Status get_sizeof_tag(ViewInfo *viewinfo);
Status get_and_display_data(char *str_frame, char *str_id, char *frame_id, int *tag_size, char *tag_title, FILE *fptr, ViewInfo *viewinfo);
*/
#endif
