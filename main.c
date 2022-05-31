#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* loadFile(const char* fileName, int* size) {
    FILE* fp;
    fp = fopen(fileName, "r");

    if(!fp) {
        *size = 0L;
        return 0;
    }
    else {
        fseek(fp, 0L, SEEK_END);
        int fsize = ftell(fp);
        ++fsize;
        fseek(fp, 0L, SEEK_SET);

        char* fileBytes = malloc(fsize);
        if(!fileBytes) {
            fclose(fp);
            *size = 0L;
            return 0;
        }
        else {
            fgets(fileBytes, fsize, fp);
            fclose(fp);
            *size = fsize;
            return fileBytes;
        }
    }
}

char** split(char* str, const int size, int* strCount, const char delim) {
    int wordsCount = 1;
    for(int i = 0; str[i] != '\0' ;i++)
        if(str[i] == delim) ++wordsCount;
    char** result = malloc(wordsCount * sizeof(char*));
    for(int i = 0; i < wordsCount; i++)
        *result = malloc(size);

    result[0] = strtok(str, &delim);
    for(int i = 1; i < wordsCount ; i++)
        result[i] = strtok(NULL, &delim);
    *strCount = wordsCount;

    return result;
}

int main() {
    int fsize = 0L;
    char* fileStr = loadFile("TestFile.txt", &fsize);
    int wordsCount = 0;
    char** strArray = split(fileStr, fsize, &wordsCount, ' ');
    for(int i = 0; i < wordsCount; i++) {
        printf("%s", strArray[i]);
        printf("\n");
    }

    free(fileStr);
    free(strArray);

    return 0;
}
