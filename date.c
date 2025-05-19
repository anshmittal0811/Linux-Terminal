#include <stdio.h>
#include <string.h>
#include <time.h>
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int main(int argc, char *argv[100]) {
    time_t rawtime;
    struct tm *info;
    char buffer[100];
    time(&rawtime);
    info = localtime(&rawtime);
    if(argc == 1) {
        strftime(buffer, 100, "%A %d %B %Y %I:%M:%S %p IST", info);
        printf("%s\n", buffer);
    }
    else
    {
        if(strcmp(argv[1],"-I") == 0)
        {
            strftime(buffer, 100, "%Y-%m-%d", info);
            printf("%s\n", buffer);
        }
        else if(strcmp(argv[1],"-R") == 0)
        {
            strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S +0530", info);
            printf("%s\n", buffer);
        }
        else
     	{
     	     fprintf(stderr,RED "%s'%s'\n" RESET,"date: invalid option -- ",argv[1]);
	     return 0;
    	}
    }
    return (0);
}
