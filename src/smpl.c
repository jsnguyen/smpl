#include "smpl/smpl.h"

int ParseSMPL(char* filename, OutSMPL** out, int* n_values){
  FILE *file;

  file = fopen(filename, "r");

  char c;
  int step=0;
  DynStr var;
  DynStr val;
  int counter = 0;
  int string = 0;
  int comment = 0;
  char type;
  int digit_place;
  int length;
  int n_declarations=0;
  int len_name=0;
  int len_value=0;

  OutSMPL *temp_out=NULL;

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
      InitDynStr(&var);
      InitDynStr(&val);
      temp_out = InitOutSMPL();
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
          AppendDynStr(&var, '\0',counter++);
          printf("var: %s\n", var.str);
          printf("size: %i\n",var.size);
          printf("len_name: %i\n",len_name);
          step++;
          counter=0;
          continue;
        }

        len_name++;
        AppendDynStr(&var, c,counter++);
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
          AppendDynStr(&val,'\0',counter);
          printf("value: %s\n",val.str);
          printf("size: %i\n",val.size);
          printf("len_value: %i\n",len_value);
          step++;
          counter=0;
          step = 0;
          printf("\n");

          printf("copying string to temp_out\n");
          temp_out->NAME = malloc((len_name+1)*sizeof(char));
          temp_out->LEN = length;
          strcpy(temp_out->NAME,var.str);
          printf("temp_out->NAME %s\n");
          printf("temp_out->LEN  %i\n",temp_out->LEN);
          printf("done copying string to temp_out\n");

          /*
          switch(type){
            case SMPL_STR:
              temp_out->STR = malloc(length*sizeof(char));
              for(int i=0; i<length; i++){
                strcpy(val.str,temp_out->NAME);
              }
            case SMPL_INT:
              temp_out->INT = malloc(length*sizeof(int));
              for(int i=0; i<length; i++){
                temp_out->INT[i]=atoi(val.str);
              }
            case SMPL_DBL:
              temp_out->DBL = malloc(length*sizeof(double));
              for(int i=0; i<length; i++){
                temp_out->DBL[i]=atof(val.str);
              }
          }
          if(n_declarations == 1){
            printf("malloc-ed out!\n");
            out = malloc(sizeof(OutSMPL));
          }
          else{
            printf("realloc-ed out!\n");
            out = realloc(out,n_declarations*sizeof(OutSMPL));
          }
          */

          out[n_declarations-1]=temp_out;

          //DestroyDynStr(&var);
          //DestroyDynStr(&val);
          continue;
        }

        switch(type){
          case SMPL_STR:
            if (c == '\"'){
              ToggleValue(&string);
              continue;
            }

            AppendDynStr(&val,c,counter++);
            break;

          case SMPL_INT:
            AppendDynStr(&val,c,counter++);
            break;

          case SMPL_DBL:
            AppendDynStr(&val,c,counter++);
            break;

        }
        len_value++;
        break;

    }


  } while (c != EOF);

  fclose(file);
  printf("n_declarations %i\n",n_declarations);
  *n_values = n_declarations;

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

OutSMPL* InitOutSMPL(){
  OutSMPL* out;
  printf("initOUT\n");
  out = malloc(sizeof(OutSMPL));
  out->NAME=NULL;
  out->INT=NULL;
  out->STR=NULL;
  out->DBL=NULL;
  return out;
}

void DestroyOutSMPL(OutSMPL* out){
  if (out->NAME!=NULL){
    free(out->NAME);
  }
  if (out->INT!=NULL){
    free(out->NAME);
  }
  if (out->STR!=NULL){
    free(out->NAME);
  }
  if (out->DBL!=NULL){
    free(out->NAME);
  }
}

void InitDynStr(DynStr* dstr){
  dstr->size=0;
  dstr->str=NULL;
}

void DestroyDynStr(DynStr* dstr){
  free(dstr->str);
}

void AppendDynStr(DynStr* dstr, char c, int i){
  size_t s = ((i/CHUNKSIZE)+1)*CHUNKSIZE*sizeof(char);

  if (dstr->str == NULL){
    dstr->size = s;
    dstr->str = malloc(s);
  }

  else if(dstr->size < i+1){
    char* temp = realloc(dstr->str,s);
    if (temp != NULL){
      dstr->size = s;
      dstr->str  = temp;
    }
  }

  dstr->str[i] = c;
}
