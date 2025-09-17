#include <stdio.h>
#include <string.h>
#include <strings.h> //solo para poder correr en entorno fuera de UNIX

#define MAX_INPUT 2048
#define MAX_OUTPUT (MAX_INPUT * 6 + 16)

//Revisamos si es numero, dependiendo del valor ascii
int check_number(char param){
  return ( param >= '0' && '9' >= param);
}
//Revisamos si es letra
int check_letter(char param){
  return( (param >= 'a' && 'z' >= param) || (param >= 'A' && 'Z' >= param));
}

int check_letter_number (char param){
  return ( check_number(param) || check_letter(param));
}
//Si es letra la pasamos a mayuscula
char capitalize_letter(char letter){
  if (letter >= 'a' && 'z' >= letter){
    return (char)(letter - 'a' + 'A');
  }else {
    return letter;
  }
}

const char* morse_values(char param){
  param = capitalize_letter(param);
  switch (param) {
      case 'A': return ".-";
      case 'B': return "-...";
      case 'C': return "-.-.";
      case 'D': return "-..";
      case 'E': return ".";
      case 'F': return "..-.";
      case 'G': return "--.";
      case 'H': return "....";
      case 'I': return "..";
      case 'J': return ".---";
      case 'K': return "-.-";
      case 'L': return ".-..";
      case 'M': return "--";
      case 'N': return "-.";
      case 'O': return "---";
      case 'P': return ".--.";
      case 'Q': return "--.-";
      case 'R': return ".-.";
      case 'S': return "...";
      case 'T': return "-";
      case 'U': return "..-";
      case 'V': return "...-";
      case 'W': return ".--";
      case 'X': return "-..-";
      case 'Y': return "-.--";
      case 'Z': return "--..";
      case '0': return "-----";
      case '1': return ".----";
      case '2': return "..---";
      case '3': return "...--";
      case '4': return "....-";
      case '5': return ".....";
      case '6': return "-....";
      case '7': return "--...";
      case '8': return "---..";
      case '9': return "----.";
      default:  return NULL; 
  }
}

int append_single_char(char *param, int character_count, int buffer_capacity, char c){
  if (character_count +1 >= buffer_capacity) return -1; // revisamos si al agregar pasamos mas alla del tama;o maximo establecido para el array
  param[character_count++] = c;
  param[character_count] = '\0';
  return character_count;
}

int append_multiple_char(char *param, int character_count, int buffer_capacity, const char *s){
  if(!s) return character_count; // si el string se encueentra vacio se retorna character_count
  for (int i = 0; s[i] != '\0'; i++){
    if(character_count +1 >= buffer_capacity) return -1; // revisamos nuevamente si se excede el tama;o establecido
    param[character_count++] = s[i];
  }
  param[character_count] = '\0';
  return character_count;

}

int in_between_letter_gap(char *param, int character_count, int buffer_capacity){
  return append_single_char(param, character_count, buffer_capacity, ' ');
}

int in_between_words_gap(char *param, int character_count, int buffer_capacity){
  character_count = append_single_char(param, character_count, buffer_capacity, ' ');
  return character_count;
}



int convert_text_to_morse(const char *text, char *output, int buffer_capacity){
  int used = 0;
  int inside_word = 0;
  int first_letter = 1;
  output[0] = '\0';

  for(int i = 0; text[i] != '\0'; i++){
    char c = text[i];
    if(check_letter_number(c)) {
      const char *code = morse_values(c);
      if(!code) continue;
      if(!first_letter) {
        used = in_between_letter_gap(output, used, buffer_capacity);
        if(used < 0 ) return -1;
      }
      used = append_multiple_char(output, used, buffer_capacity, code);
      if(used < 0) return -1;
      inside_word = 1;
      first_letter = 0;
    } else if ( c == ' '){
        if(inside_word) {
          used = in_between_words_gap(output, used, buffer_capacity);
          if(used < 0) return -1;
          inside_word = 0;
          first_letter = 1;
      }
    }
  }
  return used;
}

void print_morse(char *text){
  char output[MAX_OUTPUT];
  if(convert_text_to_morse(text, output, MAX_INPUT) < 0) {
    printf("Error por buffer insuficiente");
    return;
  }
  puts(output);
}

int main(int argc, char **argv) {
  char input[MAX_INPUT];
  if(argc > 1){
    for(int i =1; i< argc; i++){
      strncat(input, argv[i], MAX_INPUT - strlen(input) -1);
      if(i+1 < argc) strncat(input, " ", MAX_INPUT - strlen(input)-1);
    }
  } else {
    printf("Que desea traducir a Morse: ");
    if(fgets(input, MAX_INPUT, stdin) != NULL) {
      size_t n = strlen(input);
      if (n > 0 && input[n-1] == '\n') input[n-1] = '\0';
    } else {
        input[0] = '\0';
    }
  }
  print_morse(input);
  return 0;
}
