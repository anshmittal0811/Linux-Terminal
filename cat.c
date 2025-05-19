#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[100000])
{
    FILE *fptr;
    char line[100];
    char arguments[1000][1000];
    char *arg = strtok(argv[1]," \n");
    int index = 0;
    while (arg != NULL)
    {
        strcpy(arguments[index++],arg);
        arg = strtok(NULL," \n");
    }
    if(index > 0) {
        if(strcmp(arguments[0],"-n") == 0)
        {
            int counter = 1;
            for (int i = 1; i < index; i++) {
                fptr = fopen(strtok(arguments[i],"\""), "r");
                while (fgets(line, sizeof(line), fptr)) {
                    printf("   %d  ",counter);
                    printf("%s", line);
                    counter++;
                }
            }
        }
        else if(strcmp(arguments[0],"-E") == 0)
        {
            for (int i = 1; i < index; i++) {
                fptr = fopen(strtok(arguments[i],"\""), "r");
                while (fgets(line, sizeof(line), fptr)) {
                    for(int i=0; i<100; i++)
                    {
                        if(line[i] == 0)
                        {
                            line[i-1] = 36;
                            break;
                        }
                    }
                    printf("%s\n", line);
                }
            }
        }
        else
        {
            for (int i = 0; i < index; i++) {
                fptr = fopen(strtok(arguments[i],"\""), "r");
                while (fgets(line, sizeof(line), fptr)) {
                    printf("%s", line);
                }
            }
        }
    }
}
