#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "bitmap.h"
#include "balloc.h"

///////////////////////////////////////////////////////
/*Testing the test0_e2size_exp_3()*/
double test_e2size_exp_3() {
  printf("----------------------------------\n");
  printf("test_e2size_exp_3()\n");
  int expected = 8;
  int result = e2size(3);

  //comparing the expected with the result
  if(result==expected){
    printf("Pass!\n");
    printf("expected = %d\n", expected);
    printf("result = %d\n", result);
    return 1;
  } else{
    printf("Fail!\n");
    return 0;
  }
}

///////////////////////////////////////////////////////
/*Testing the e2size()*/
double test_size2e_8() {
  printf("----------------------------------\n");
  printf("test_size2e_8()\n");
  int expected = 8;
  int result = size2e(8);

  //comparing the expected with the result
  if(result==expected){
    printf("Pass!\n");
    printf("expected = %d\n", expected);
    printf("result = %d\n", result);
    return 1;
  } else{
    printf("Fail!\n");
    return 0;
  }
}
///////////////////////////////////////////////////////
double test_size2e_10() {
  printf("----------------------------------\n");
  printf("test_size2e_10()\n");
  int expected = 16;
  int result = size2e(10);

  //comparing the expected with the result
  if(result==expected){
    printf("Pass!\n");
    printf("expected = %d\n", expected);
    printf("result = %d\n", result);
    return 1;
  } else{
    printf("Fail!\n");
    return 0;
  }
}

/////////////////////////////////////////////////////
double test_balloc_001() {
  void * p1, *p2;
  bnew(64, 2, 7);
  Balloc pool = NULL;
  p1 = balloc(pool, 2);

  bprint(pool);
  return 1;
}

int main() {
  int i;
  int n = 3;
  double count = 0;
  double test_list[n]; 

  for (i = 0; i < n; i++)
    test_list[i] = 0;

  test_list[0] = test_e2size_exp_3();
  test_list[1] = test_size2e_8();
  test_list[2] = test_size2e_10();
  bnew(64, 2, 7);
  test_list[3] = test_balloc_001();


  for(i = 0; i < n; i++){
    count = count+test_list[i];
  }

  double p = (count/(double)n)*100;

  printf("----------------------------------\n");
  printf("%f percent success\n", p);
  printf("----------------------------------\n");

  return 0;
}
