#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main(void) {
  printf("Parent (P) is having ID %d\n", (int) getpid());
  int pid = vfork();
  if(pid<0){
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (pid ==0){
    int fac = 1;
    int n = 4;
    while (n!=0)
    {
        fac = fac *n;
        n--;
    }
    printf("The value of 4 factorial is %d\n",fac);
    
  }
  else{
    wait(NULL);
    int fib_arr[17];
    int n = 17;
    fib_arr[0] = 0;
    fib_arr[1] = 1;
    fib_arr[2] = 1;

    for(int i=2;i<n;i++){
        fib_arr[i] = fib_arr[i-1]+fib_arr[i-2];
    }
    
    for (int i = 0; i<n;i++){
        printf("The fibonacci of %d is %d\n",i,fib_arr[i]);
        }
  }
  return 0;
}



// One page note 
// it is similar to what we did in previous question
// wait(Null) is a system call used to make parents wait till child execution finishes
// if pehle if statement pe bhi jaayega tab bhi 
