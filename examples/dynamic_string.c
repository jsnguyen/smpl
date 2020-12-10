#include "smpl/smpl.h"

int main(){
  DynStr dstr;
  InitDynStr(&dstr);

  AppendDynStr(&dstr, '0', 0);
  AppendDynStr(&dstr, '1', 1);
  AppendDynStr(&dstr, '2', 2);
  AppendDynStr(&dstr, '3', 3);
  AppendDynStr(&dstr, '\0', 4);

  printf("size: %i\n",dstr.size);
  printf("str: %s\n",dstr.str);
  DestroyDynStr(&dstr);
}
