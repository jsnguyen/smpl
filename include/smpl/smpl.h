#ifndef SMPL_H
#define SMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SMPL_DEC '@'
#define SMPL_VAL ':'
#define SMPL_INT 'I'
#define SMPL_STR 'S'
#define SMPL_DBL 'D'
#define SMPL_EOL ';'
#define SMPL_NLL '#'
#define SMPL_ATR '/'
#define SMPL_COM '%'

typedef struct{
  char* NAME;
  int* LEN_ARR;
  int* INT;
  char* STR;
  double* DBL;
} OutSMPL;

int ParseSMPL(char* filename);

void ToggleValue(int* val); 

void DynamicString(char* str, int i);

#endif
