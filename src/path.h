#ifndef _PATH_H
#define _PATH_H

#include <unistd.h>

/*
 * Returns 1 on success. 0 otherwise.
*/
int get_cwd(char* buff, size_t buff_size);
void path_append(char* buff, const char* append);

#endif