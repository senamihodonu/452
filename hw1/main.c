#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
//0///////////////////////////////////////////////////////
/*Testing the deq_head_put(Deq q, Data d) 
function with 1 element(s) to the list
from the head direction*/
double test0_deq_head_put_1_elements(Deq q) {
  printf("==================================\n");
  printf("0 - Testing deq_head_put(Deq q, Data d)\n");
  printf("w/ 1 element\n");
  printf("----------------------------------\n");
  char expected[] = "1";
  q = deq_new();
  
  //List before adding 1 element
  char *s=deq_str(q,0);
  printf("list before operation --> [ %s ]\n",s);
  free(s);

  //adding 1 element to list
  deq_head_put(q, "1");
  char *result=deq_str(q,0);
  printf("list after operation --> [ %s ]\n",result);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    free(result);
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    free(result);
    deq_del(q,0);
    return 0;
  }
}
//1///////////////////////////////////////////////////////
/*Testing the deq_head_put(Deq q, Data d) 
function by adding 2 elements to the list
from the head direction*/
double test1_deq_head_put_2_elements(Deq q) {
  printf("==================================\n");
  printf("1 - Testing deq_head_put(Deq q, Data d) \n");
  printf("w/ 2 element\n");
  printf("----------------------------------\n");
  char expected[] = "2 1";
  q = deq_new();
  //List before adding 2 element
  char *s=deq_str(q,0);
  printf("list before operation --> [ %s ]\n",s);
  free(s);

  //adding 2 elements to list
  deq_head_put(q, "1");
  deq_head_put(q, "2");
  char *result=deq_str(q,0);
  printf("list after operation --> [ %s ]\n",result);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    free(result);
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    free(result);
    deq_del(q,0);
    return 0;
  }
}

//2///////////////////////////////////////////////////////
/*Testing the deq_tail_put(Deq q, Data d) 
function by adding 1 element(s) to the list 
from the tail direction*/
double test2_deq_tail_put_1_elements(Deq q) {
  printf("==================================\n");
  printf("2 - Testing deq_tail_put(Deq q, Data d) \n");
  printf("w/ 1 element\n");
  printf("----------------------------------\n");
  char expected[] = "1";
  q = deq_new();
  
  //List before adding 2 element
  char *s=deq_str(q,0);
  printf("list before operation --> [ %s ]\n",s);
  free(s);

  //adding 1 element to the list
  deq_tail_put(q, "1");
  char *result=deq_str(q,0);
  printf("list after operation --> [ %s ]\n",result);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    free(result);
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    free(result);
    deq_del(q,0);
    return 0;
  }
}

//3///////////////////////////////////////////////////////
/*Testing the deq_tail_put(Deq q, Data d) 
function by adding 2 element(s) to the list 
from the tail direction*/
double test3_deq_tail_put_2_elements(Deq q) {
  printf("==================================\n");
  printf("3 - Testing deq_tail_put(Deq q, Data d) \n");
  printf("w/ 2 element\n");
  printf("----------------------------------\n");
  char expected[] = "1 2";
  q = deq_new();
  
  //List before adding 2 element
  char *s=deq_str(q,0);
  printf("list before operation --> [ %s ]\n",s);
  free(s);

  //adding 1 element to the list
  deq_tail_put(q, "1");
  deq_tail_put(q, "2");
  char *result=deq_str(q,0);
  printf("list after operation --> [ %s ]\n",result);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    free(result);
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    free(result);
    deq_del(q,0);
    return 0;
  }
}

//4///////////////////////////////////////////////////////
/*Testing the deq_head_ith(Deq q, int i) 
function with 1 element*/
double test4_deq_head_ith_1_element_0th_term(Deq q) {
  printf("==================================\n");
  printf("4 - Testing deq_head_ith(Deq q, int i) \n");
  printf("Returning element at index 0\n");
  printf("w/ 1 element\n");
  printf("----------------------------------\n");
  char expected[] = "1";
  q = deq_new();

  //List before operation
  deq_head_put(q, "1"); //adding one element to list
  char *s=deq_str(q,0);
  printf("list --> [ %s ]\n",s);
  free(s);

  //first 0th term from the head direction
  char* result =(char*)deq_head_ith(q, 0);

  printf("result = %s\n",result);
  printf("expected = %s\n",expected);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    deq_del(q,0);
    return 0;
  }
}

//5///////////////////////////////////////////////////////
/*Testing the deq_head_ith(Deq q, int i) 
function with 1 element*/
double test5_deq_head_ith_2_element_0th_term(Deq q) {
  printf("==================================\n");
  printf("5 - Testing deq_head_ith(Deq q, int i) \n");
  printf("Returning element at index 0\n");
  printf("w/ 2 element\n");
  printf("----------------------------------\n");
  char expected[] = "2";
  q = deq_new();

  //List before operation
  deq_head_put(q, "1"); //adding element to list
  deq_head_put(q, "2");
  char *s=deq_str(q,0);
  printf("list --> [ %s ]\n",s);
  free(s);

  //first 0th term from the head direction
  char* result =(char*)deq_head_ith(q, 0);

  printf("result = %s\n",result);
  printf("expected = %s\n",expected);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    deq_del(q,0);
    return 0;
  }
}

//6///////////////////////////////////////////////////////
/*Testing the deq_head_ith(Deq q, int i) 
function with 2 element*/
double test6_deq_head_ith_2_element_1st_term(Deq q) {
  printf("==================================\n");
  printf("6 - Testing deq_head_ith(Deq q, int i) \n");
  printf("Returning element at index 1\n");
  printf("w/ 1 element\n");
  printf("----------------------------------\n");
  char expected[] = "1";
  q = deq_new();

  //List before operation
  deq_head_put(q, "1"); //adding elements to list
  deq_head_put(q, "2");
  
  char *s=deq_str(q,0);
  printf("list --> [ %s ]\n",s);
  free(s);

  //first 0th term from the head direction
  char* result =(char*)deq_head_ith(q, 1);

  printf("result = %s\n",result);
  printf("expected = %s\n",expected);

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    deq_del(q,0);
    return 0;
  }
}

//7///////////////////////////////////////////////////////
/*Testing the deq_head_ith(Deq q, int i) 
function with 2 element*/
double test7_deq_tail_ith_1_element_0th_term(Deq q) {
  printf("==================================\n");
  printf("7 - Testing deq_tail_ith(Deq q, int i) \n");
  printf("Returning element at index 0\n");
  printf("w/ 1 element\n");
  printf("----------------------------------\n");
  char expected[] = "1";
  q = deq_new();

  //List before operation
  deq_head_put(q, "1"); //adding elements to list
  deq_head_put(q, "2"); //adding elements to list
  
  char *s=deq_str(q,0);
  printf("list --> [ %s ]\n",s);
  free(s);

  //first 0th term from the head direction
  char* result = (char*)deq_tail_ith(q, 0);

  printf("result = %s\n",result);
  printf("expected = %s\n",expected);

  if(result == expected){
    printf("happy");
  }

  //comparing the expected with the result
  if(strcmp(result,expected)==0){
    fprintf(stderr, "Pass!\n");
    // deq_del(q,0);
    return 1;
  } else{
    fprintf(stderr, "Fail!\n");
    // deq_del(q,0);
    return 0;
  }
}

//8///////////////////////////////////////////////////////
/*Testing the deq_head_ith(Deq q, int i) 
function with 2 element*/
double test8_deq_tail_ith_2_element_0th_term(Deq q) {
    return 0;
}

//9///////////////////////////////////////////////////////
/*Testing the deq_head_ith(Deq q, int i) 
function with 2 element*/
double test9_deq_tail_ith_2_element_1st_term(Deq q) {
    return 0;
}


int main() {
  int i;
  int n = 5;
  double count = 0;
  double test_list[n]; 

  for (i = 0; i < n; i++)
    test_list[i] = 0;

  Deq q=deq_new();

  test_list[0] = test0_deq_head_put_1_elements(q);
  test_list[1] = test1_deq_head_put_2_elements(q);
  test_list[2] = test2_deq_tail_put_1_elements(q); 
  test_list[3] = test3_deq_tail_put_2_elements(q); 
  test_list[4] = test4_deq_head_ith_1_element_0th_term(q);
  test_list[5] = test5_deq_head_ith_2_element_0th_term(q);
  test_list[6] = test6_deq_head_ith_2_element_1st_term(q);
  test_list[7] = test7_deq_tail_ith_1_element_0th_term(q);
  test_list[8] = test8_deq_tail_ith_2_element_0th_term(q);
  test_list[9] = test9_deq_tail_ith_2_element_1st_term(q);
  // test_list[9] = test3_deq_tail_put_2_elements(q); 
  // test_list[10] = test4_deq_head_ith_1_element_0th_term(q);
  // test_list[5] = test5_deq_head_ith_2_element_0th_term(q);


  for(i = 0; i < n; i++){
    count = count+test_list[i];
  }

  double p = (count/(double)n)*100;


  printf("----------------------------------\n");
  printf("%f percent success\n", p);
  printf("----------------------------------\n");

  free(q);




  // //Testing empty list
  // deq_head_put(q, "1");
  // deq_tail_put(q, "2");
  // deq_tail_put(q, "3");
  // deq_tail_put(q, "4");
  // deq_head_put(q, "5");
  // // deq_len(q);
  // deq_head_ith(q, 0);
  // char *s=deq_str(q,0);
  
  // printf("%s\n",s);
  // myFunction();

  // //printf("%d\n",deq_len(q));
  // //printf("%s\n",(char*)deq_tail_ith(q, 5));
  // free(s);

  // deq_del(q,0);
  return 0;
}
