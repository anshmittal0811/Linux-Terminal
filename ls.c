#include<stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include <string.h>
#include <unistd.h>
#define RED "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"
static int comparator(const void* str1, const void* str2) {
    char *str_1 = *(char**)str1;
    char *str_2 = *(char**)str2;
    char a[1000],b[1000];
    strcpy(a,str_1);
    strcpy(b,str_2);
    for (int i = 0; a[i]!='\0'; i++) {
        if(a[i] >= 'A' && a[i] <= 'Z') {
            a[i] = a[i] + 32;
        }
    }
    for (int i = 0; b[i]!='\0'; i++) {
        if(b[i] >= 'A' && b[i] <= 'Z') {
            b[i] = b[i] + 32;
        }
    }
    if(strcmp(a,b) >= 0)
    {
        return 1;
    }
    else return 0;

}
int main(int argc, char *argv[])
{
    DIR *directory;
    struct dirent *dir;
    char arguments[1000][1000];
    char *arg = strtok(argv[1]," \n");
    int argidx = 0;
    while (arg != NULL)
    {
        strcpy(arguments[argidx++],arg);
        arg = strtok(NULL," \n");
    }
    if(argidx == 0)
    {
        char path_store[1000];
        getcwd(path_store,1000);
        directory = opendir(path_store);
        char *name[10000];
        int index = 0;
        int len = 0;
        if (directory)
        {
            while ((dir = readdir(directory)) != NULL)
            {
                len++;
                name[index++] =  dir->d_name;
            }
            qsort(name, len, sizeof(const char*), comparator);
            for(int i=0; i<len; i++)
            {
                if(*name[i] != 46)
                {
                    printf(YELLOW "%s\n" RESET, name[i]);
                }
            }
            closedir(directory);
        }
    }
    else {
        if (strcmp(arguments[0], "-a") == 0) {
            if (argidx >= 2) {
                for(int i=1; i<argidx; i++) {
                    
                    char path[100];
                    char path_store[1000];
                    char *name[10000];
                    getcwd(path_store, 1000);
                    strcpy(path, path_store);
                    strcat(path, "/");
                    strcat(path, arguments[1]);
                    directory = opendir(path);
                    int index = 0;
                    int len = 0;
                    if (directory) {
                    	 printf("%s:\n",arguments[i]);
                        while ((dir = readdir(directory)) != NULL) {
                            len++;
                            name[index++] = dir->d_name;
                        }
                        qsort(name, len, sizeof(const char *), comparator);
                        for (int j = 0; j < len; j++) {
                            printf(YELLOW "%s\n" RESET, name[j]);
                        }
                        closedir(directory);
                    }
                    else
                    {
                        fprintf(stderr,RED"%s '%s': No such file or directory"RESET,"ls: cannot access",arguments[i]);
                    }
                    printf("\n");
                }
            } else {
                char path_store[1000];
                getcwd(path_store,1000);
                directory = opendir(path_store);
                char *name[10000];
                int index = 0;
                int len = 0;
                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {
                        len++;
                        name[index++] =  dir->d_name;
                    }
                    qsort(name, len, sizeof(const char*), comparator);
                    for(int i=0; i< len; i++)
                    {
                        printf(YELLOW "%s\n" RESET, name[i]);
                    }
                    closedir(directory);
                }
            }
        } else if (strcmp(arguments[0], "-B") == 0) {
            if (argidx >= 2) {
                for(int i=1; i<argidx; i++)
                {
                    char path[100];
                    char path_store[1000];
                    getcwd(path_store,1000);
                    strcpy(path, path_store);
                    strcat(path,"/");
                    strcat(path, arguments[1]);
                    directory = opendir(path);
                    int flag = 0;
                    char *name[10000];
                    int index = 0;
                    int len = 0;
                    if (directory) {
                    	 printf("%s:\n",arguments[i]);
                        while ((dir = readdir(directory)) != NULL) {
                            name[index++] =  dir->d_name;
                            len++;

                        }
                        qsort(name, len, sizeof(const char*), comparator);
                        for(int k=0; k<len; k++)
                        {
                            for (int j = 0; j < strlen(name[k]); j++) {
                                if (*(name[k] + j) == 126) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if (!flag) {
                                printf(YELLOW "%s\n" RESET, name[i]);
                            }
                        }
                        closedir(directory);
                    }
                    else
                    {
                        fprintf(stderr,RED"%s '%s': No such file or directory"RESET,"ls: cannot access",arguments[i]);
                    }
                    printf("\n");
                }
            }
            else {
                char path_store[1000];
                getcwd(path_store,1000);
                directory = opendir(path_store);
                int flag = 0;
                char *name[10000];
                int index = 0;
                int len = 0;
                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {
                        name[index++] =  dir->d_name;
                        len++;
                    }
                    qsort(name, len, sizeof(const char*), comparator);
                    for(int i=0; i<len; i++)
                    {
                        for (int j = 0; j < strlen(name[i]); j++) {
                            if (*(name[i] + j) == 126) {
                                flag = 1;
                                break;
                            }
                        }
                        if (!flag) {
                            printf(YELLOW "%s\n" RESET, name[i]);
                        }
                    }
                    closedir(directory);
                }
            }
        }
        else
        {
            for(int i=0; i<argidx; i++) {
                
                char path[100];
                char path_store[1000];
                getcwd(path_store,1000);
                strcpy(path, path_store);
                strcat(path,"/");
                strcat(path, arguments[i]);
                directory = opendir(path);
                char *name[10000];
                int index = 0;
                int len = 0;
                if (directory) {
                    printf("%s:\n",arguments[i]);
                    while ((dir = readdir(directory)) != NULL) {
                        name[index++] = dir->d_name;
                        len++;
                    }
                    qsort(name, len, sizeof(const char *), comparator);
                    for (int j = 0; j < len; j++) {
                        printf(YELLOW "%s\n" RESET, name[j]);
                    }
                    closedir(directory);
                } else
                {
                    fprintf(stderr,RED"%s '%s': No such file or directory"RESET,"ls: cannot access",arguments[i]);
                }
                printf("\n");
            }
        }
    }
    return(0);
}
