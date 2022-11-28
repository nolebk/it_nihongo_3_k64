#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char *today_t = NULL;

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
    writeDataFile(tmp);
    char *command = malloc(200);
    sprintf(command, "cd C:\\Data\\C\\AutoCommit && git add . && git commit -m \"update %s\"", tmp);
    system(command);
    free(tmp);
    tmp = NULL;
}

char *today() {
    time_t now = time(NULL);
    struct tm *info = localtime(&now);
    char *string = calloc(100, sizeof(char));
    strftime(string, 30, "%d/%m/%Y", info);
    return string;
}

void commitInTime(char *date) {

    int random = rand() % 5 + 1;
    printf("commit %s\n", date);
    fflush(stdout);
    char *command = calloc(120, sizeof(char));
    sprintf(command, "date %s", date);
    system(command);
    for (int i = 0; i < random; ++i) {
        commit(date, i + 1);
        usleep(500000);
    }

    sprintf(command, "date %s", today_t);
    system(command);
    free(command);
}

void push() {
    system("cd C:\\Data\\C\\AutoCommit && git push");
}

char *addADay(char *date) {
    struct tm *info = malloc(sizeof(struct tm));
    memset(info, 0, sizeof(struct tm));
    sscanf(date, "%d/%d/%d", &info->tm_mday, &info->tm_mon, &info->tm_year);
    info->tm_mon -= 1;
    info->tm_year -= 1900;
    time_t oldtime = mktime(info);
    time_t newtime = oldtime + 24 * 60 * 60;
    struct tm *newinfo = localtime(&newtime);
    char *string = calloc(100, sizeof(char));
    strftime(string, 30, "%d/%m/%Y", newinfo);
    free(info);
    free(newinfo);
    return string;
}

int main() {
    srand(time(NULL));
    today_t = today();
    char date[] = "28/11/2021";
    for (int i = 0; i < 7; ++i) {
        sprintf(date, "%s", addADay(date));
        commitInTime(date);
    }
    push();
    return 0;
}
