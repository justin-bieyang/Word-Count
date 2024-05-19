#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    if (argc != 3) { // 检查输入参数的数量
        printf("Usage: %s -c|-w filename\n", argv[0]);
        return 1;
    }
    
    char parameter = argv[1][1]; // 获取控制参数，argv[1][1]而不是argv[1][0]，因为我们希望检查"-c"或"-w"中的第二个字符
    char* inputFileName = argv[2]; // 获取输入文件名
    
    FILE* file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Error: Failed to open file %s\n", inputFileName);
        return 1;
    }
    
    int characterCount = 0;
    int wordCount = 0;
    
    int inWord = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c) || isdigit(c) || c == '\'' || c == '#') { // 判断是否为字母、数字或指定的特殊字符
            if (!inWord) {
                inWord = 1;
                wordCount++;
            }
        } else {
            inWord = 0;
        }
        
        if (!isspace(c)) { // 判断是否为非空格字符
            characterCount++;
        }
    }
    
    if (parameter == 'c') { // 输出字符数
        printf("字符数：%d\n", characterCount);
    } else if (parameter == 'w') { // 输出单词数
        printf("单词数：%d\n", wordCount);
    } else {
        printf("无效参数: %c\n", parameter);
        return 1;
    }
    
    fclose(file);
    return 0;
}

