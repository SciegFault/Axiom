#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>

char command[100]="";
char version[20]="0.0.2";
char list[150]="-help,\n-version,\n-exit,\n-list,\ngoto,\nshow_file,\nsuppr,\nnew_file,\nnew_dir,\nread_file,\naddto\n";
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

        char *c1 = strtok(command, " \t\r\n");

        if (c1 == NULL) {
            continue;
        }

        char *c2 = strtok(NULL, " \t\r\n");

        if (strcmp(c1, "-help") == 0) {
            if (c2 != NULL) {
                if (strcmp(c2, "-version") == 0) {
                    printf("-version is a command for now the exact version of Axiom.\n");
                }
                else if (strcmp(c2, "-exit") == 0) {
                    printf("-exit is a command for quit Axiom.\n");
                }
                else if (strcmp(c2, "-list") == 0) {
                    printf("-list is a command for list all the command of Axiom.\n");
                }
                else if (strcmp(c2, "-goto") == 0) {
                    printf("goto is a command for change the directory of the shell. For use it type goto [path]\n");
                }
                else if (strcmp(c2, "-show_file") == 0) {
                    printf("show_file is a command for see the file into a directory. For use it type show_file or show_file [path]\n");
                }
                else if (strcmp(c2, "-bash_trad") == 0) {
                    printf("bash_trad is a command for traduct the axiom command in bash. For use it type bash_trad -[command]\n");
                }
                else {
                    printf("Argument not found.\n");
                }
            }
            else if (c2 == NULL) {
                printf("Type -version for the version and -help [command] for the description of the command and for exit type -exit\n");
            }
        }

        else if (strcmp(c1, "-version") == 0) {
            printf("%s\n", version);
        }

        else if (strcmp(c1, "-exit") == 0) {
            break;
        }

        else if (strcmp(c1, "-list") == 0) {
            printf("%s", list);
        }

        else if (strcmp(c1, "goto") == 0) {
            if (c2 != NULL) {
                chdir(c2);
            }
            else {
                continue;
            }
        }

        else if (strcmp(c1, "show_file") == 0) {
            if (c2 != NULL) {
                DIR *dossier = opendir(c2);
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

        else if (strcmp(c1,"bash_trad") == 0) {
            if (c2 != NULL) {
                if (strcmp(c2, "-goto") == 0) {
                    printf("Axiom : goto Bash : cd\n");
                }
                else if (strcmp(c2, "-show_file") == 0) {
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

        else if (strcmp(c1, "suppr") == 0) {
            if (c2 != NULL) {
                printf("Are you sure ? There is not trash ? [N/y]\n");
                fgets((char*)ptryn, 10, stdin);
                yes_no[strcspn(yes_no, "\n")] = '\0';

                if (strcmp(yes_no, "y") == 0) {
                    if (unlink(c2) == 0) {
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

        else if (strcmp(c1, "new_file") == 0) {
            if (c2 != NULL) {
                FILE *fichier = fopen(c2, "a");
                if (fichier != NULL) {
                    fclose(fichier);
                    printf("Succes. Finally you have a brain !\n");
                }
                else {
                    perror("Axiom: new_file failed\n");
                }
            }
        }

        else if (strcmp(c1, "new_dir") == 0) {
            if (c2 != NULL) {
                if (mkdir(c2, 0777) == 0) {
                    printf("Succes. Yes I'm cold today.\n");
                }
                else {
                    perror("Axiom: new_dir failed\n");
                }
            }
        }

        else if (strcmp(c1, "read_file") == 0) {
            if (c2 != NULL) {
                FILE *fichier = fopen(c2, "r");
                if (fichier != NULL) {
                    int caractere;
                    while ((caractere = fgetc(fichier)) != EOF) {
                        putchar(caractere);
                    }
                    printf("\n");
                    fclose(fichier);
                } else {
                    perror("Axiom: read_file failed");
                }
            }
        }

        else if (strcmp(c1, "addto") == 0) {
            if (c2 != NULL) {
                FILE *fichier = fopen(c2, "a");

                if (fichier != NULL) {
                    char texte[256];
                    printf("Write please , euuh no please juste WRITE NOW !\n");
                    fgets(texte, sizeof(texte), stdin);
                    fputs(texte, fichier);
                    fclose(fichier);
                    printf("You see when you listen to me you do things well !\n");
                }
                else {
                    perror("Axiom: write failed (It's YOUR FAULT !)\n");
                }
            }
            else {
                printf("Please it's complicate put a name ? \n");
            }
        }

        else if (strcmp(c1, "clear") == 0) {
            printf("\033[H\033[J");
            printf("You want to clear me I love the text and you don't say please so : ......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n ......................\n .........................\n .....................................\n......................\n .........................\n .....................................\n");
        }

        else if (strcmp(c1, "clear_please") == 0) {
            printf("Ok... NO I GO TO disappear ?!");
            fflush(stdout);
            sleep(10);
            printf("\033[H\033[J");
        }

        else if (strcmp(c1, "execute") == 0) {
            if (c2 != NULL) {
                pid_t pid = fork();

                if (pid < 0) {
                    perror("Axiom: Fork failed (just like your recent life choices?)\n");
                }
                else if (pid == 0) {
                    char *args[] = {c2, NULL};

                    execv(args[0], args);

                    perror("Axiom: Impossible to run this thing. Are you sure about the path?\n");
                    _exit(1); // Exit the child process immediately
                }
                else {
                    int status;
                    printf("Axiom: Fine... I'm running your stuff. Wait until it finishes.\n");
                    waitpid(pid, &status, 0);
                    printf("Axiom: Done, your program finished running. Can we go back to work now?\n");
                }
            }
            else {
                printf("Axiom: Execute what? Give me an executable path, I can't read your mind.\n");
            }
        }

        else {
            printf("Supression of user...\n Error.\n");
            printf("Command not found type -list for have the list of the command\n");
        }

    }
    return 0;
}

