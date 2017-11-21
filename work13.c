#include <stdio.h>
#include <unistd.h>

int main()
{
  int arr0[2]; // to store descriptors for first pipe
  int arr1[2]; // to store descriptors for second pipe
  int READ = 0;
  int WRITE = 1;
  int f; // to store pid of child or 0 after fork
  
  pipe(arr0);
  pipe(arr1);
  f = fork();

  if(f) {
    int buffer0 = 15; // to store number to send to & receive from child
    
    close(arr0[READ]);
    // close(arr1[READ]);
    close(arr1[WRITE]);
    
    printf("[parent] sending: %d\n", buffer0);
    write(arr0[WRITE], &buffer0, sizeof(buffer0));
    close(arr0[WRITE]);

    /*
    wait(&status);
    if (WIFEXITED(status)) {
      printf("[parent] received: %d\n", WEXITSTATUS(status));
    } else {
      printf("The child did not terminate normally.\n");
    }
    */

    read(arr1[READ], &buffer0, sizeof(buffer0));
    printf("[parent] received: %d\n", buffer0);
    close(arr1[READ]);
    
  } else {
    int buffer1; // to store number to receive from and send to parent
    
    close(arr0[WRITE]);
    close(arr1[READ]);

    // receive number from parent
    read(arr0[READ], &buffer1, sizeof(buffer1));
    close(arr0[READ]);

    printf("[child] doing maths on: %d\n", buffer1);
    buffer1 = buffer1 * buffer1;

    // send modified number back
    write(arr1[WRITE], &buffer1, sizeof(buffer1));
    close(arr1[WRITE]);
  }

  return 0;
}
