#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void history_getter(char *path)
{
    FILE *history;
    char *pathway = (char *)malloc(500*sizeof(char));
    strcpy(pathway,path);
    strcat(pathway,"/history.txt");
    history = fopen(pathway,"r");
    char buffer[1000];
    while(fgets(buffer,1000,history))
    {
        printf("%s",buffer);
    }
    free(pathway);
    fclose(history);
}
void history_setter(char *path, char *string)
{
    FILE *history;
    char *pathway = (char *)malloc(500*sizeof(char));
    strcpy(pathway,path);
    strcat(pathway,"/history.txt");
    history = fopen(pathway,"a+");
    char words[1000];
    strcpy(words,string);
    char *argu = strtok(words," \n");
    while(argu != NULL)
    {
        fprintf(history,"%s ",argu);
        argu = strtok(NULL," \n");
    }
    fprintf(history,"%s", "\n");
    free(pathway);
    fclose(history);
}
void history_clean(char *path)
{
	FILE *history;
    char *pathway = (char *)malloc(500*sizeof(char));
    strcpy(pathway,path);
    strcat(pathway,"/history.txt");
    remove(pathway);
    free(pathway);
}
int main()
{

    char path_store[1000];
    getcwd(path_store,1000);
    printf(BLUE "=====================================================================\n" RESET);
    while (1) {
        printf(CYAN "RUDIMENTARY SHELL ~$ " RESET);
        char str[100];
        fgets(str, 100, stdin);
        history_setter(path_store,str);
        char list[1000][1000];
        char *arguments = strtok(str," \n");
        int index = 0;
        int len = 0;
        while(arguments != NULL)
        {
            len++;
            strcpy(list[index++],arguments);
            arguments = strtok(NULL," \n");
        }
        if (strcmp(list[0], "exit") == 0) {
            break;
        }
        else if (strcmp(list[0], "cd") == 0) {
            if (strcmp(list[1], "..") == 0) {
                chdir("..");
            }
            else
            {
                if(chdir(list[1]) == -1)
                {
                    printf("cd: ");
                    printf("%s",list[1]);
                    printf(": ");
                    printf("No such file or directory\n");
                }
                else
                {
                    chdir(list[1]);
                }
            }
        }
        else if(strcmp(list[0],"history") == 0)
        {
            if(len == 1) {
                history_getter(path_store);
            }
            else if(strcmp(list[1],"-c") == 0)
            {
            	history_clean(path_store);
            }
            else
            {
                printf("history: history [-c] [-d offset] [n] or history -anrw [filename] or history -ps arg [arg...]\n"
                       "    Display or manipulate the history list.\n"
                       "    \n"
                       "    Display the history list with line numbers, prefixing each modified\n"
                       "    entry with a `*'.  An argument of N lists only the last N entries.\n"
                       "    \n"
                       "    Options:\n"
                       "      -c\tclear the history list by deleting all of the entries\n"
                       "      -d offset\tdelete the history entry at position OFFSET. Negative\n"
                       "    \t\toffsets count back from the end of the history list\n"
                       "    \n"
                       "      -a\tappend history lines from this session to the history file\n"
                       "      -n\tread all history lines not already read from the history file\n"
                       "    \t\tand append them to the history list\n"
                       "      -r\tread the history file and append the contents to the history\n"
                       "    \t\tlist\n"
                       "      -w\twrite the current history to the history file\n"
                       "    \n"
                       "      -p\tperform history expansion on each ARG and display the result\n"
                       "    \t\twithout storing it in the history list\n"
                       "      -s\tappend the ARGs to the history list as a single entry\n"
                       "    \n"
                       "    If FILENAME is given, it is used as the history file.  Otherwise,\n"
                       "    if HISTFILE has a value, that is used, else ~/.bash_history.\n"
                       "    \n"
                       "    If the HISTTIMEFORMAT variable is set and not null, its value is used\n"
                       "    as a format string for strftime(3) to print the time stamp associated\n"
                       "    with each displayed history entry.  No time stamps are printed otherwise.\n"
                       "    \n"
                       "    Exit Status:\n"
                       "    Returns success unless an invalid option is given or an error occurs.\n");
            }
        }
        else if(strcmp(list[0],"pwd") == 0)
        {
            char current_store[1000];
            getcwd(current_store,1000);
            printf("%s\n",current_store);
        }
        else if(strcmp(list[0],"echo") == 0)
        {
            if(strcmp(list[1],"-n") == 0)
            {
                int idx = 2;
                while(idx < len)
                {
                    printf("%s ",list[idx]);
                    idx++;
                }
            }
            else if(strcmp(list[1],"-e") == 0)
            {
                int idx = 2;
                while (idx < len)
                {
                    for(int i=0; i<strlen(list[idx]);i++)
                    {
                        if(list[idx][i] - 92 == 0 && list[idx][i+1] - 'n' == 0 && list[2][0] == '"')
                        {
                            printf("\n");
                            i++;
                            continue;
                        }
                        if(list[idx][i] == '"')
                        {}
                        else
                        {
                            if(list[idx][i] - 92 != 0){printf("%c",list[idx][i]);}
                        }
                    }
                    printf("\n");
                    idx++;
                }
            }
            else
            {
                int idx = 1;
                while(idx < len)
                {
                    for(int i=0; i<strlen(list[idx]); i++)
                    {
                        if(list[idx][i] != 34){
                            printf("%c",list[idx][i]);}
                    }
                    idx++;
                }
                printf("\n");
            }
        }
        else if(strcmp(list[0],"date") == 0)
        {
            pid_t pid;
            pid = fork();
            if(pid == 0)
            {
                if(len == 1)
                {
                    strcat(path_store,"/dateo");
                    execl(path_store,"dateo",NULL);
                }
                else if(len == 2)
                {
                    strcat(path_store,"/dateo");
                    execl(path_store,"dateo",list[1],NULL);
                }
            }
            else if(pid < 0)
            {
                fprintf(stderr, RED "Fork failed!\n" RESET);
                exit(-1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if(strcmp(list[0],"rm") == 0)
        {
            pid_t pid;
            pid = fork();
            char file_string[10000];
            strcpy(file_string," ");
            if(pid == 0)
            {
                for(int i=1; i<len; i++)
                {
                    if(i == 1)
                    {
                        strcpy(file_string,list[i]);
                    }
                    else
                    {
                        strcat(file_string,list[i]);
                    }
                    if(i != len-1) {
                        strcat(file_string, " ");
                    }
                    else
                    {
                        strcat(file_string,"\n");
                    }
                }
                printf("%s",file_string);
                strcat(path_store,"/rmo");

                execl(path_store, "rmo", file_string, NULL);
            }
            else if(pid < 0)
            {
                fprintf(stderr, RED "Fork failed!\n" RESET);
                exit(-1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if(strcmp(list[0],"cat") == 0)
        {
            pid_t pid;
            pid = fork();
            char file_string[10000];
            strcpy(file_string," ");
            if(pid == 0)
            {
                for(int i=1; i<len; i++)
                {
                    if(i == 1)
                    {
                        strcpy(file_string,list[i]);
                    }
                    else
                    {
                        strcat(file_string,list[i]);
                    }
                    if(i != len-1) {
                        strcat(file_string, " ");
                    }
                    else
                    {
                        strcat(file_string,"\n");
                    }
                }
                strcat(path_store,"/cato");
                execl(path_store, "cato", file_string, NULL);
            }
            else if(pid < 0)
            {
                fprintf(stderr, RED "Fork failed!\n" RESET);
                exit(-1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if(strcmp(list[0],"ls") == 0)
        {
            pid_t pid;
            pid = fork();

            if(pid == 0)
            {
                char file_string[10000];
                strcpy(file_string," ");
                for(int i=1; i<len; i++)
                {
                    if(i == 1)
                    {
                        strcpy(file_string,list[i]);
                    }
                    else
                    {
                        strcat(file_string,list[i]);
                    }
                    if(i != len-1) {
                        strcat(file_string, " ");
                    }
                    else
                    {
                        strcat(file_string,"\n");
                    }
                }
                strcat(path_store,"/lso");
                execl(path_store, "lso", file_string, NULL);

            }
            else if(pid < 0)
            {
                fprintf(stderr, RED "Fork failed!\n" RESET);
                exit(-1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if(strcmp(list[0],"mkdir") == 0)
        {
            pid_t pid;
            pid = fork();
            char file_string[10000];
            strcpy(file_string," ");
            if(pid == 0)
            {
                for(int i=1; i<len; i++)
                {
                    if(i == 1)
                    {
                        strcpy(file_string,list[i]);
                    }
                    else
                    {
                        strcat(file_string,list[i]);
                    }
                    if(i != len-1) {
                        strcat(file_string, " ");
                    }
                    else
                    {
                        strcat(file_string,"\n");
                    }
                }
                strcat(path_store,"/mkdiro");
                execl(path_store, "mkdiro", file_string, NULL);

            }
            else if(pid < 0)
            {
                fprintf(stderr, RED "Fork failed!\n" RESET);
                exit(-1);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            fprintf(stderr,RED"%s%s\n"RESET,list[0],": command not found");
        }
    }

    printf(BLUE "=====================================================================\n" RESET);
    return 0;
}
