#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int fds1 [2];
int fds2 [2];

char buf[100];
char *msg;
int n;

void parent()
{
 n = read(fds1[0], buf , 100);
 write(1, buf, n);
 msg = "Parent here: message receives.\n";
 write(fds2[1], msg, strlen(msg));
 close(fds1[0]);
 close(fds2[1]);
}

void child()
{
 msg = "Child here: hello parent!\n";
 write(fds1[1], msg, strlen(msg));
 n = read(fds2[0], buf, 100);
 write(1, buf, n);
 close(fds1[0]);
 close(fds2[1]);
 }
int main()
{
 pipe(fds1);
 pipe(fds2);
 
 if (fork() ==0){
   child();
}else{
 parent();
 wait(0);
}
exit(0);
}
