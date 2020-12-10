#include "smpl/smpl.h"

int main(){
  OutSMPL *out;
  out = malloc(4*sizeof(OutSMPL));
  int n_values;
  ParseSMPL("string.smpl", &out, &n_values);
  printf("n_values %i\n",n_values);
  for(int i=0;i<4;i++){
    printf("%p\n",out[i]);
    printf("out: %s\n",out);
    printf("NAME: %s\n",out[i].NAME);
    printf("length : %i\n",out[i].LEN);
    //DestroyOutSMPL(&out[i]);
  }
  return 0;
}
