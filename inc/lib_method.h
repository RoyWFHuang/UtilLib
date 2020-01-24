#ifndef __lib_method_H__
#define __lib_method_H__

#include <unistd.h>
#include <sys/types.h>
#include "macro.h"

typedef unsigned char u_char;

int is_regular_file(const char *path_pchar);
int is_regular_folder(const char *path_pchar);
int is_regular_link(const char *path_pchar);
char *hex_to_str(u_char *input_pchar, int input_len_int);
char *md5_hash(char *input_pchar, int len_int);

time_t get_file_last_access(const char *path);
time_t get_file_last_modification(const char *path);
time_t get_file_last_status_change(const char *path);



int create_link(const char *dist_cpchar, const char *src_cpchar);

typedef struct _tLastNameData
{
// intput
    char *input_path_pchar;
// output
    char *prefix_path_pchar;
    char *last_name_pchar;
}tLastNameData;

typedef struct _tFixupFolderPath
{
    char *path_pchar;
    char *ret_pchar;
}tFixupFolderPath;

#define free_ptr_tFixupFolderPath(ptr) do{\
    free_to_NULL(ptr->path_pchar);\
    free_to_NULL(ptr->ret_pchar);\
}while(0)

#define free_tFixupFolderPath(non_ptr) do{\
    free_to_NULL(non_ptr.path_pchar);\
    free_to_NULL(non_ptr.ret_pchar);\
}while(0)

int fixup_folder_path(
    tFixupFolderPath* input_pstruct);

#define free_ptr_tLastNameData(ptr) do{\
    free_to_NULL(ptr->input_path_pchar);\
    free_to_NULL(ptr->prefix_path_pchar);\
    free_to_NULL(ptr->last_name_pchar);\
}while(0)

#define free_tLastNameData(non_ptr) do{\
    free_to_NULL(non_ptr.input_path_pchar);\
    free_to_NULL(non_ptr.prefix_path_pchar);\
    free_to_NULL(non_ptr.last_name_pchar);\
}while(0)

int get_last_folder_name(
    tLastNameData *inputdata_pstruct);

char *add_str_to_prefix(const char *prefix_str_pchar, const char *path_pchar);

int recursive_remove_directory(const char *path);

#define autofree_type_ptr \
    __attribute__((cleanup(auto_free_type_ptr)))

__attribute__((always_inline))
inline void auto_free_type_ptr(void *ptr){free_to_NULL(*(void **) ptr);}

#endif
