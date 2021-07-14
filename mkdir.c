#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
int  main(int argc, char *argv[100])
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
        fprintf(stderr,RED"%s\n"RESET,"mkdir: missing operand");
        return 0;
    }
    if(index >= 1) {
        if(strcmp(arguments[0],"-v") == 0) {
        if(index == 1)
	    {
			printf("mkdir: missing operand\n");
			return 0;
	    }
        for(int i=1; i<index; i++) {
            int error_check = mkdir(arguments[i], 0777);
            if (error_check != 0) {
                fprintf(stderr,RED "%s '%s'%s\n"RESET,RED"mkdir: cannot create directory",arguments[i], ": File exists");
            } 
            else {
                printf("mkdir: created directory '%s'\n", arguments[i]);
            }
           }
        }
        else if(strcmp(arguments[0],"--help")) {
            for(int i=0; i<index; i++) {
                int error_check = mkdir(arguments[i], 0777);
                if (error_check != 0) {
                    fprintf(stderr,RED "%s '%s'%s\n"RESET,RED"mkdir: cannot create directory",arguments[i], RED": File exists"RESET);
                }
            }
        }
        else if(strcmp(arguments[0],"--help") == 0)
        {
            printf("Usage: mkdir [OPTION]... DIRECTORY...\n"
                   "Create the DIRECTORY(ies), if they do not already exist.\n"
                   "\n"
                   "Mandatory arguments to long options are mandatory for short options too.\n"
                   "  -m, --mode=MODE   set file mode (as in chmod), not a=rwx - umask\n"
                   "  -p, --parents     no error if existing, make parent directories as needed\n"
                   "  -v, --verbose     print a message for each created directory\n"
                   "  -Z                   set SELinux security context of each created directory\n"
                   "                         to the default type\n"
                   "      --context[=CTX]  like -Z, or if CTX is specified then set the SELinux\n"
                   "                         or SMACK security context to CTX\n"
                   "      --help     display this help and exit\n"
                   "      --version  output version information and exit\n"
                   "\n"
                   "GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n"
                   "Full documentation at: <https://www.gnu.org/software/coreutils/mkdir>\n"
                   "or available locally via: info '(coreutils) mkdir invocation'\n");
        }
    }
    return 0;
}
