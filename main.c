#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <winsock2.h>

char *readDataFile() {
    char *buf = malloc(100);
    FILE *f = fopen("C:\\Data\\C\\AutoCommit\\README.MD", "r");
    if (f != NULL) {
        fscanf(f, "%s ", buf);
        fclose(f);
        return buf;
    }
    return "Error";
}

void writeDataFile(char *string) {
        FILE *f = fopen("C:\\Data\\C\\AutoCommit\\README.MD", "wb");
        fwrite(string, 1, strlen(string), f);
        fclose(f);
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
    free(tmp);
    tmp = NULL;
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    struct hostent *hostinfo;
    while (hostinfo == NULL)
        hostinfo = gethostbyname ("google.com");
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
            }
            system("git push");
        }
    }
    return 0;
}
