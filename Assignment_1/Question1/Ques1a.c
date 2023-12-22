#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main(void) {
  printf("Parent (P) is having ID %d\n", (int) getpid());
  int pid = fork();
  if(pid<0){
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (pid ==0){
    printf("Child is having ID %d\n", (int)getpid());
    printf("My Parent ID is %d\n",(int) getppid());
  }
  else{
    wait(NULL);
    printf("ID of P's Child is %d\n",(int)pid);
  }
  return 0;
}













// One page note on it




// fork -----> It is found in standard c library.
// It creates the new child process with different memory space and same content unless 
// exec is called which means that both the parent and child process will run simultaneously using timesharing
// fprintf  ---> file print formatted ====> found in c/c++ commonly used when we have to direct our output to 
// a file or stream or our choice, useful when we want to log information or generate reports in files
// syntax:
//        fprintf(file/stream where output to write, what contents to write)
// now coming to code
// when we call fork
// child gets created 
// all the codes below this line are common to parent and child unless and untill exec is called in child
// fork returns 0 for child process and Pid of child for parent process
// After this using timesharing and if else statements we will 
// write the conditional for childprocess and parent process 
// 
// Makefiles are used to compile the code and automate the task 
// IF codes are in tandem then makefile is very usefull tool
// To compile on shell write this given below code
// gcc Question1.c -o Ques1   // to compile and rename the exe file to Ques1a
// ./Ques1     to execute it on shell(bash)
// To Run it open terminal in code and then 
// type wsl
// then using cd commmand get into Question1 directory and type make 
// compiled .exe file will be there with the name Ques1a































