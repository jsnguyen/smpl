#include "smpl/smpl.h"

int ParseSMPL(char* filename){
  FILE *file;

  file = fopen(filename, "r");

  char c;
  int step=0;
  char var[32];
  char value[64];
  int counter = 0;
  int string = 0;
  int comment = 0;
  char type;
  int digit_place;
  int length;
  int n_declarations=0;
  int len_name=0;
  int len_value=0;

  do {
    c = fgetc(file);

    if (c == SMPL_COM){
      ToggleValue(&comment);
      continue;
    }

    if ( ( ( (c == ' ' || c == '\n') || comment ) && (!string)) || comment){
      continue;
    }

    if (c == SMPL_DEC){
      n_declarations++;
      type = SMPL_NLL;
      digit_place = 0;
      length = 0;
      len_name = 0;
      len_value = 0;
      step++;
      continue;
    }

    switch(step){
      // reading type

      // declaration
      case 1 :
        if (c == SMPL_ATR){
          var[counter++]='\0';
          printf("var: %s\n", var);
          printf("len_name: %i\n",len_name);
          step++;
          counter=0;
          continue;
        }

        len_name++;
        var[counter++]=c;
        break;

      case 2 :
        // if type has not been assigned yet, then it should be
        if (type == SMPL_NLL){
          type = c;
          continue;
        }
        // if we find a digit, that must be the length
        // valid from 1 to MAX_INT
        else if (isdigit(c)){
          length += digit_place++ *10+atoi(&c);
          continue;
        }

        if (c == SMPL_VAL){
          // if length was never set, then by default it should be 1
          // a length of 1 will be a length of 2 without this check
          if(length == 0){
            length=1;
          }
          printf("type: %c\n",type);
          printf("length: %i\n",length);
          step++;
          continue;
        }
        break;


      // reading actual value
      case 3 :
        if (c == SMPL_EOL){
          value[counter] = '\0';
          printf("value: %s\n",value);
          printf("len_value: %i\n",len_value);
          step++;
          counter=0;
          continue;
        }

        switch(type){
          case SMPL_STR:
            if (c == '\"'){
              ToggleValue(&string);
              continue;
            }

            value[counter++] = c;
            break;

          case SMPL_INT:
            value[counter++] = c;
            break;

          case SMPL_DBL:
            value[counter++] = c;
            break;

        }
        len_value++;
        break;

       case 4 :
        // OutSMPL
        step = 0;
        continue;
    }

  } while (c != EOF);

  fclose(file);
  printf("n_declarations %i\n",n_declarations);

  return 0;
}

void ToggleValue(int* val){
  if(*val == 0){
    *val = 1;
  }
  else {
    *val = 0;
  }
}

void DynamicString(char* str, int i, int CHUNKSIZE){
  char* temp;
  if (str == NULL){
    str = malloc(CHUNKSIZE*sizeof(str));
  }
}
