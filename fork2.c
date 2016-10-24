#include <stdio.h>
#include <signal.h>

#include <unistd.h>
int main(void) {
  pid_t ret;
  char *name;

  ret = fork();

  if (ret == 0) { /* Child */
    name = "child";sleep(20);

  } else {
    name = "parent";
    sleep(2);kill(ret, SIGKILL);



  }

  /* name[1] = 'o'; */

  printf("process %s ret  = %ld\n", name, ret);
}
