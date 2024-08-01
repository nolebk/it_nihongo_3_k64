#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char *today_t = NULL;

char *readDataFile() {
    char *buf = malloc(100);
    FILE *f = fopen("D:\\Data\\source_code\\C\\AutoCommit\\README.MD", "r");
    if (f != NULL) {
        fscanf(f, "%s ", buf);
        fclose(f);
        return buf;
    }
    return "Error";
}

void writeDataFile(const char *string) {
    FILE *f = fopen("D:\\Data\\source_code\\C\\AutoCommit\\README.MD", "wb");
    fwrite(string, 1, strlen(string), f);
    fclose(f);
}

void commit(const char *string, const int i) {
    char *tmp = strdup(string);
    sprintf(tmp + strlen(tmp), " %d", i);
    writeDataFile(tmp);
    char command[100] = {0};
    sprintf(command, "cd D:\\Data\\source_code\\C\\AutoCommit && git add . && git commit -m \"update %s\"", tmp);
    system(command);
    free(tmp);
    tmp = NULL;
}

char *today() {
    const time_t now = time(NULL);
    const struct tm *info = localtime(&now);
    char *string = calloc(100, sizeof(char));
    strftime(string, 30, "%d/%m/%Y", info);
    return string;
}

void commitInTime(char *date) {
    const int random = rand() % 5 + 1;
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
    system("cd cd D:\\Data\\source_code\\C\\AutoCommit && git push");
}

char *addADay(char *input_date) {
    int day, month, year;

    // Phân tích chuỗi ngày vào các biến số nguyên
    sscanf(input_date, "%d/%d/%d", &day, &month, &year);

    // Tạo cấu trúc tm và thiết lập các giá trị
    struct tm date = {0};
    date.tm_mday = day;
    date.tm_mon = month - 1; // Tháng trong struct tm từ 0 đến 11
    date.tm_year = year - 1900; // Năm trong struct tm tính từ 1900

    // Thêm 1 ngày
    date.tm_mday += 1;

    // Điều chỉnh lại thời gian để có ngày hợp lệ
    mktime(&date);

    // Đưa kết quả trở lại chuỗi
    strftime(input_date, 11, "%d/%m/%Y", &date);
}
void randomDayToDay(const char *date1, const char *date2) {
    char *date = malloc(11);
    strcpy(date, date1);
    while (1) {
        addADay(date);
        if (strcmp(date, date2) == 0) {
            break;
        }
        const int random = rand() % 3;
        if (random == 0) {
            commitInTime(date);
        }
    }
}
int main() {
    srand(time(NULL));
    today_t = today();
//    char date[][11] = {"29/12/2021","4/1/2022","5/1/2022","6/1/2022","12/1/2022","13/1/2022","14/1/2022","18/1/2022","19/1/2022","20/1/2022","26/1/2022"};
//    for (int i = 0; i < 11; ++i) {
//        printf("%s\n", date[i]);
//        commitInTime(date[i]);
//    }
//    push();
//    return 0;
    randomDayToDay("01/08/2024", "02/09/2024");
//    push();
    return 0;
}
