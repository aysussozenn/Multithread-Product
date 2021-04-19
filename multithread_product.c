#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#include<pthread.h>
#define MAX_THREAD 16
#define MAX 8


int a[]={1,5,7,10,12,14,15,18,20,22,25,27,30,64,110,220};
long double product[8];
int part=0;
void *product_array(){
  int thread_part= part++;
  int i;
  for(i=thread_part*(MAX/8); i<(thread_part+1)*MAX/8;i++){
      product[thread_part]=product[thread_part]+a[i];
      }
}

int main(void){

   pthread_t threads[MAX_THREAD];
   int i;
   for(i=0 ; i<MAX_THREAD;i++){
   
      pthread_create(&threads[i],NULL,product_array,(void*)NULL);   
   }
   for(i=0 ; i<MAX_THREAD;i++){
      pthread_join(threads[i],NULL);   
   }
   
   long double total_product=1;
   for(i=0 ; i<MAX_THREAD;i++){
     total_product= total_product*product[i];  
     
   }
   
   printf("Product is %.0Lf",total_product);
   return 0;

}
