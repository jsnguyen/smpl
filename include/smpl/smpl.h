#ifndef SMPL_H
#define SMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SMPL_DEC '@'
#define SMPL_VAL ':'
#define SMPL_INT 'I'
#define SMPL_STR 'S'
#define SMPL_DBL 'D'
#define SMPL_EOL ';'
#define SMPL_NLL '#'
#define SMPL_ATR '/'
#define SMPL_COM '%'

#define CHUNKSIZE 16

typedef struct{
  char* NAME;
  int LEN;
  int* INT;
  char** STR;
  double* DBL;
} OutSMPL;

typedef struct{
  size_t size;
  char *str;
} DynStr;

int ParseSMPL(char* filename, OutSMPL** out, int* n_values);

void ToggleValue(int* val); 

OutSMPL* InitOutSMPL();
void DestroyOutSMPL(OutSMPL* out);

void InitDynStr(DynStr* dstr);
void DestroyDynStr(DynStr* dstr);
void AppendDynStr(DynStr* dstr, char c, int i);

#endif
