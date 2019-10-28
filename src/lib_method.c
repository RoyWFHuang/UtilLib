#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/md5.h>

#include "errorno.h"
#include "lib_method.h"
#include "macro.h"

int is_regular_file(const char *path_pchar)
{
    struct stat path_stat_struct;
    if( -1 == stat(path_pchar, &path_stat_struct) )
        return 0;
    else
        return S_ISREG(path_stat_struct.st_mode);
}

int is_regular_folder(const char *path_pchar)
{
    struct stat path_stat_struct;
    if( -1 == stat(path_pchar, &path_stat_struct) )
        return 0;
    else
        return S_ISDIR(path_stat_struct.st_mode);
}

int is_regular_link(const char *path_pchar)
{
    struct stat path_stat_struct;

    if( -1 == stat(path_pchar, &path_stat_struct) )
        return 0;
    else
        return S_ISLNK(path_stat_struct.st_mode);
}

char *hex_to_str(u_char *input_pchar, int input_len_int)
{
    char *hex_pchar = malloc(2*sizeof(char[input_len_int+1]));
    memset(hex_pchar, 0,2*sizeof(char[input_len_int+1]));
    int count_int;
    char tmp_achar[8];

    for(count_int = 0; count_int < input_len_int; count_int++)
    {
        sprintf(tmp_achar, "%02x", input_pchar[count_int]);
        memcpy(hex_pchar+2*count_int, tmp_achar,2);
    }

    return hex_pchar;
}

char* md5_hash(char *input_pchar, int len_int)
{
    MD5_CTX ctx_struct;
    u_char outmd_uchar[16];


    memset(outmd_uchar, 0, sizeof(u_char[16]));
    MD5_Init(&ctx_struct);
    MD5_Update(&ctx_struct, input_pchar, len_int);
    MD5_Final(outmd_uchar, &ctx_struct);
    char *ret_pchar = hex_to_str(outmd_uchar, 16);

    return ret_pchar;
}

time_t get_file_last_access(const char *path)
{
    struct stat st;

    if (stat(path, &st) != -1) {
        return st.st_atime;
    } else {
       return -1;
    }
}

time_t get_file_last_modification(const char *path)
{
    struct stat st;

    if (stat(path, &st) != -1) {
        return st.st_mtime;
    } else {
       return -1;
    }
}

time_t get_file_last_status_change(const char *path)
{
    struct stat st;

    if (stat(path, &st) != -1) {
        return st.st_ctime;
    } else {
       return -1;
    }
}

int create_link(const char *dist_cpchar, const char *src_cpchar)
{
    if( 0 != symlink(dist_cpchar, src_cpchar) )
    {
        return -1;
    }
    else
    {
        return 1;
    }

}
/*
int my_mkdir(char *path_pchar)
{
    DIR *pDir;
    pDir = opendir(path_pchar);
    if (NULL == pDir)
    {
        mode_t process_mask = umask(0);
        if (-1 == mkdir(path_pchar, 0777))
        {
            csglog_err("mkdir %s fail\n", path_pchar);
            return -1;
        }
        umask(process_mask);
    }
    else
    {
        closedir(pDir);
    }
    return ERROR_CODE_SUCCESS;
}
*/


/**
  * Hint : Return address "can't be free"
  * Hint :  data_pstruct is no be free in this func
  *
  * fixup folder path, including add start "/" and end "/"
  *
  * @param input_pstruct type : tFixupFolderPath*
  *     input data :
  *         char *path_pchar : be fixed the path
  *		return data :
  *         char *ret_pchar : fixed path
  * @return int
  * 		ERROR_CODE_SUCCESS
  */
int fixup_folder_path(tFixupFolderPath* input_pstruct)
{
    autofree_type_ptr char *input_pchar = NULL;
    autofree_type_ptr char *prefix_pchar = NULL;
    autofree_type_ptr char *last_pchar = NULL;
    //strcpyALL(input_pchar, input_pstruct->path_pchar);
    check_null_input(input_pstruct);

    if('/' != input_pstruct->path_pchar[0])
    {
        strcpyALL(input_pchar, "/", input_pstruct->path_pchar);
    }
    else
    {
        strcpyALL(input_pchar, input_pstruct->path_pchar);
    }


    strcpyALL(prefix_pchar, dirname(input_pchar), "/");
    free_to_NULL(input_pchar);

    strcpyALL(input_pchar, input_pstruct->path_pchar);

    strcpyALL(last_pchar, basename(input_pchar), "/");
    strcpyALL(input_pstruct->ret_pchar, prefix_pchar, last_pchar);

    return ERROR_CODE_SUCCESS;
}


int get_last_folder_name(tLastNameData *inputdata_pstruct)
{
    if(NULL == inputdata_pstruct)
        return ERROR_CODE_NULL_POINT_EXCEPTION;
    char *input_pchar = NULL;
    strcpyALL(input_pchar, inputdata_pstruct->input_path_pchar);
    char *prefix_pchar = dirname(input_pchar);
    if(strcmp("/", prefix_pchar))
        strcpyALL(inputdata_pstruct->prefix_path_pchar, prefix_pchar, "/");
    else
        strcpyALL(inputdata_pstruct->prefix_path_pchar, prefix_pchar);
    free_to_NULL(input_pchar);
    strcpyALL(input_pchar, inputdata_pstruct->input_path_pchar);
    char *last_pchar = basename(input_pchar);
    strcpyALL(inputdata_pstruct->last_name_pchar, last_pchar);
    free_to_NULL(input_pchar);
    return ERROR_CODE_SUCCESS;
}


char *add_str_to_prefix(const char *prefix_str_pchar, const char *path_pchar)
{
    tLastNameData lnd_struct;
    strcpyALL(lnd_struct.input_path_pchar, (char *)path_pchar);
    get_last_folder_name(&lnd_struct);
    char *ret_str_pchar = NULL;
    strcpyALL(ret_str_pchar, lnd_struct.prefix_path_pchar,
        (char *)prefix_str_pchar, lnd_struct.last_name_pchar);
    free_tLastNameData(lnd_struct);
    return ret_str_pchar;
}

