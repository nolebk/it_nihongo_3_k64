#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char *readDataFile() {
    char *buf = malloc(100);
    FILE *f = fopen("..//README.MD", "r");
    if (f != NULL) {
        fscanf(f, "%s ", buf);
        fclose(f);
        return buf;
    } else {
        f = fopen("README.MD", "r");
        if (f != NULL) {
            fscanf(f, "%s", buf);
            fclose(f);
            return buf;
        } else {
            return NULL;
        }
    }
}

void writeDataFile(char *string) {
    FILE *f = fopen("../README.MD", "r");
    if (f != NULL) {
        fclose(f);
        f = fopen("../README.MD", "wb");
        fwrite(string, 1, strlen(string), f);
        fclose(f);
    } else {
        f = fopen("README.MD", "wb");
        if (f != NULL) {
            fwrite(string, 1, strlen(string), f);
            fclose(f);
        }
    }
}

void commit(char *string, int i) {
    char *tmp = strdup(string);
    sprintf(tmp + strlen(tmp), " %d", i);
    printf("committing %s\n", tmp);
    fflush(stdout);
    writeDataFile(tmp);
    system("git add .");
    char *command = malloc(200);
    sprintf(command, "git commit -m \"update %s\"", tmp);
    system(command);
    system("git push");
    free(tmp);
    tmp = NULL;
}

int main() {
    time_t now = time(NULL);
    srand(time(NULL));
    struct tm *info = localtime(&now);
    char string[100] = {0};
    strftime(string, 30, "%d/%m/%Y", info);
    printf("today: %s\n", string);
    fflush(stdout);

    char *input = readDataFile();
    if (input != NULL) {
        if (strcmp(input, string) != 0) {
            int random = rand() % 5 + 1;
            printf("change %d\n", random);
            fflush(stdout);
            for (int i = 0; i < random; ++i) {
                commit(string, i + 1);
                sleep(2);
            }
        }
    }
    return 0;
}
