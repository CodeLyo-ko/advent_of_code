#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int endsWith(char* str, char* end, int n){
    if (strlen(end) > n){
        return 0;
    }
    char* str2 = &(str[n - strlen(end)]);
    
    if (str2 != NULL){
        //printf("%s\n", str2);
        return !strcmp(str2, end);
    }
    return 0;
}

int main(){
    char* num[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    FILE* f = fopen("input.txt", "r");
    int res = 0;
    int digit1;
    int digit2;
    char c = fgetc(f);
    int first = 0;
    char test[500];
    test[0] = c;
    test[1] = '\0';
    int n = 1;
    while (c != EOF){
        
        while (c != '\n'){
            if (isdigit(c)){
                
                if (!first){
                    digit1 = c - '0';
                    first = 1;
                }
                digit2 = c - '0';
            }
            else {
                for (int i = 0; i < 9; i++){
                    //printf("%s\n", test);
                    if (endsWith(test, num[i], n)){
                        printf("%s\n", test);
                        if (!first){
                            digit1 = i + 1;
                            first = 1;
                        }
                        digit2 = i + 1;
                        break;
                    }
                }
            }
            c = fgetc(f);
            test[n++] = c;
            test[n] = '\0';
            //printf("%s\n", test);
        }
        c = fgetc(f);
        test[0] = c;
        n = 1;
        test[1] = '\0';
        first = 0;
        res += digit1 * 10 + digit2;
    printf("%d %d %d\n", res, digit1, digit2);    
    close(f);
    }
}