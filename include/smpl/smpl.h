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

#define CHUNKSIZE 2

typedef struct{
  char* NAME;
  int* LEN_ARR;
  int* INT;
  char* STR;
  double* DBL;
} OutSMPL;

typedef struct{
  size_t size;
  char *str;
} DynStr;

int ParseSMPL(char* filename);

void ToggleValue(int* val); 

void InitDynStr(DynStr* dstr);
void DestroyDynStr(DynStr* dstr);
void DynamicString(DynStr* dstr, char c, int i);

#endif
