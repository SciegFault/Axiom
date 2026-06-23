#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

char command[100]="";
char version[20]="0.0.1";
char list[100]="-help,\n-version,\n-exit,\n-list\nFor have the documentation type -help [command]\n";
char yes_no[10]="";
void *ptryn=yes_no;
void *ptrcmd=command;

int main() {
    printf("Axiom %s type -help for documentation or -version for the version or -exit for exit\n", version);

    while(1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("|%s|>>> ", cwd);
        }
        else {
            printf(">>> ");
        }
        fgets((char*)ptrcmd, 100, stdin);

        command[strcspn(command, "\n")] = '\0';

        char *cmd_1 = strtok(command, " \t\r\n");

        if (cmd_1 == NULL) {
            continue;
        }

        char *cmd_2 = strtok(NULL, " \t\r\n");

        if (strcmp(cmd_1, "-help") == 0) {
            if (cmd_2 != NULL) {
                if (strcmp(cmd_2, "-version") == 0) {
                    printf("-version is a command for now the exact version of Axiom.\n");
                }
                else if (strcmp(cmd_2, "-exit") == 0) {
                    printf("-exit is a command for quit Axiom.\n");
                }
                else if (strcmp(cmd_2, "-list") == 0) {
                    printf("-list is a command for list all the command of Axiom.\n");
                }
                else if (strcmp(cmd_2, "-goto") == 0) {
                    printf("goto is a command for change the directory of the shell. For use it type goto [path]\n");
                }
                else if (strcmp(cmd_2, "-show_file") == 0) {
                    printf("show_file is a command for see the file into a directory. For use it type show_file or show_file [path]\n");
                }
                else if (strcmp(cmd_2, "-bash_trad") == 0) {
                    printf("bash_trad is a command for traduct the axiom command in bash. For use it type bash_trad -[command]\n");
                }
                else {
                    printf("Argument not found.\n");
                }
            }
            else if (cmd_2 == NULL) {
                printf("Type -version for the version and -help [command] for the description of the command and for exit type -exit\n");
            }
        }

        else if (strcmp(cmd_1, "-version") == 0) {
            printf("%s\n", version);
        }

        else if (strcmp(cmd_1, "-exit") == 0) {
            break;
        }

        else if (strcmp(cmd_1, "-list") == 0) {
            printf("%s", list);
        }

        else if (strcmp(cmd_1, "goto") == 0) {
            if (cmd_2 != NULL) {
                chdir(cmd_2);
            }
            else {
                continue;
            }
        }

        else if (strcmp(cmd_1, "show_file") == 0) {
            if (cmd_2 != NULL) {
                DIR *dossier = opendir(cmd_2);
                struct dirent *element;

                if (dossier != NULL) {
                    while ((element = readdir(dossier)) != NULL) {
                        if (element->d_name[0] != '.') {
                            printf("%s  ", element->d_name);
                        }
                    }
                    printf("\n");
                    closedir(dossier);
                }
                else {
                    perror("Axiom: show_file failed\n");
                }
            }
            else {
                DIR *dossier = opendir(".");
                struct dirent *element;

                if (dossier != NULL) {
                    while ((element = readdir(dossier)) != NULL) {
                        if (element->d_name[0] != '.') {
                            printf("%s  ", element->d_name);
                        }
                    }
                    printf("\n");
                    closedir(dossier);
                }
                else {
                    perror("Axiom: show_file failed\n");
                }
            }
        }

        else if (strcmp(cmd_1,"bash_trad") == 0) {
            if (cmd_2 != NULL) {
                if (strcmp(cmd_2, "-goto") == 0) {
                    printf("Axiom : goto Bash : cd\n");
                }
                else if (strcmp(cmd_2, "-show_file") == 0) {
                    printf("Axiom : show_file Bash : ls\n");
                }
                else {
                    printf("But but this command dont exist in Axiom I can't traduct in Bash ?!\n");
                }
            }
            else {
                printf("Your are strange you want to traduct nothing ?!\n");
            }
        }

        else if (strcmp(cmd_1, "suppr") == 0) {
            if (cmd_2 != NULL) {
                printf("Are you sure ? There is not trash ? [N/y]\n");
                fgets((char*)ptryn, 10, stdin);
                yes_no[strcspn(yes_no, "\n")] = '\0';

                if (strcmp(yes_no, "y") == 0) {
                    if (unlink(cmd_2) == 0) {
                        printf("File delete.\n");
                    }
                    else {
                        perror("Error file not delete.\n");
                    }
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        else {
            printf("Command not found type -list for have the list of the command\n");
        }

    }
    return 0;
}

