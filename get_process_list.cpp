#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

const char * const LS_PROCESS_FILES = "ls -l  /proc/ | awk '{print $9}' | grep \"[0-9]$\"";
const int32_t TMP_SIZE = 64;


int32_t get_process_list(std::vector<std::string> & process_list)
{
    process_list.clear();
    
    FILE *fd = popen(LS_PROCESS_FILES, "re");
    if (fd == NULL)
    {
        printf("popen failedI\n");
        return -1;
    }

    char tmp[TMP_SIZE] = { 0 };
    while (fgets(tmp, sizeof(tmp), fd) != NULL)
    {
        int32_t len = static_cast<int32_t>(strnlen(tmp, 1024));
        if (len > TMP_SIZE)
        {
            continue;
        }
        if (tmp[len -1] == '\n')
        {
            tmp[len-1] = '\0';
        }
        process_list.push_back(tmp);
    }

    return static_cast<int32_t>(process_list.size());
}

int main(int argc, const char *argv[])
{
    std::vector<std::string> process_list;
    int32_t size = 0;
    size = get_process_list(process_list);

    for(int i = 0; i < size; ++i)
    {
        printf ("num %d, %s\n", i + 1, process_list[i].c_str()); 
    }

    return 0;
}
