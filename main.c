#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char *readDataFile() {
    char *buf = NULL;
    FILE *f = fopen("tmp", "rb");
    if (f != NULL) {
        fseek(f, 0, SEEK_END);
        int fsize = (int) ftell(f);
        fseek(f, 0, SEEK_SET);
        buf = (char *) calloc(fsize, 1);
        fread(buf, 1, fsize, f);
        fclose(f);
        return buf;
    } else
        return NULL;
}

void writeDataFile(char *string) {
    FILE *f = fopen("tmp", "wb");
    if (f != NULL) {
        fwrite(string, 1, strlen(string), f);
        fclose(f);
    }
}
void commit(char *string) {
    writeDataFile(string);


}
int main() {
    time_t now = time(NULL);
    srand(now);
    struct tm *info = localtime(&now);
    char string[100] = {0};
    strftime(string, 30, "%d/%m/%Y", info);
    printf("today: %s", string);

    char *input = readDataFile();
    if (input != NULL) {
        if(strcmp(input, string) != 0) {
            printf("change");
            int random = rand() % 5 + 1;
            for (int i = 0; i < random; ++i) {
                commit(string);
                sleep(1);
            }
        }
    }
    return 0;
}
