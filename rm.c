#include <stdio.h>
#include <string.h>
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
int  main(int argc, char *argv[100000])
{
    char arguments[1000][1000];
    char *arg = strtok(argv[1]," \n");
    int index = 0;
    while (arg != NULL)
    {
        strcpy(arguments[index++],arg);
        arg = strtok(NULL," \n");
    }
    if(index == 0)
    {
        fprintf(stderr,RED"%s\n"RESET,"rm: missing operand");
        return 0;
    }
    if(strcmp(arguments[0],"-v") == 0) {
        if(index == 1)
        {
            fprintf(stderr,RED"%s\n"RESET,"rm: missing operand");
            return 0;
        }
        for (int i = 1; i < index; i++) {
            int error_check = remove(arguments[i]);
            if (error_check != 0) {
                fprintf(stderr,RED"%s"RESET,"rm: cannot remove ");
                fprintf(stderr,RED"'%s' %s\n"RESET, arguments[i], " : No such file or directory");
            }
            else {
                printf("removed '%s'\n", arguments[i]);
            }
        }
    }
    else if(strcmp(arguments[0],"-i") == 0) {
        if(index == 1)
        {
            fprintf(stderr,RED"%s\n"RESET,"rm: missing operand");
            return 0;
        }
        for (int i = 1; i < index; i++) {
            char access;
            printf("rm: remove regular file '%s'? ",arguments[i]);
            scanf("%c",&access);
            if(access == 89 || access == 121) {
                int error_check = remove(arguments[i]);
                if (error_check != 0) {
                    fprintf(stderr,RED"%s"RESET,"rm: cannot remove ");
                	fprintf(stderr,RED"'%s' %s\n"RESET, arguments[i], " : No such file or directory");
                }
            }
        }
    }
    else
    {
        for(int i=0; i<index; i++)
        {
            int error_check = remove(arguments[i]);
            if (error_check != 0) {
                fprintf(stderr,RED"%s"RESET,"rm: cannot remove ");
                fprintf(stderr,RED"'%s' %s\n"RESET, arguments[i], " : No such file or directory");
            }
        }
    }
    return 0;
}
