#include "path.h"

#include <string.h>

int get_cwd(char* buff, size_t buff_size)
{
    return getcwd(buff, buff_size) != NULL;
}
void path_append(char* buff, const char* append)
{
    strcat(buff, append);
}