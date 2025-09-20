#include <stdio.h>

int main() {
    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL) {
        perror("无法打开文件");
        return 1;
    }
    fprintf(fp, "Hello,World\n");
    fclose(fp);
    return 0;
}