#include <stdio.h>

const char *MORSE_DIGITS[10] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..","----." //0,1,2,3,4,5,6,7,8,9 
};

const char* morse_for_digit(char c) {
    if (c >= '0' && c <= '9') {
        return MORSE_DIGITS[c - '0'];
    }
    return NULL; 
}

int main() {
    char input[100];  

    printf("nuumero: ");
    scanf("%99s", input);   

    for (int i = 0; input[i] != '\0'; i++) {
        const char *num = morse_for_digit(input[i]);
        if (num) {
            printf("%s ", num); 
        }
    }
    printf("\n");

    return 0;
}

