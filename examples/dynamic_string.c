#include "smpl/smpl.h"

int main(){
  DynStr dstr;
  InitDynStr(&dstr);

  DynamicString(&dstr, '0', 0);
  DynamicString(&dstr, '1', 1);
  DynamicString(&dstr, '2', 2);
  DynamicString(&dstr, '3', 3);
  DynamicString(&dstr, '\0', 4);

  printf("size: %i\n",dstr.size);
  printf("str: %s\n",dstr.str);
  DestroyDynStr(&dstr);
}
