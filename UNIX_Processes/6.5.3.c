#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
void f(int sgn) {
 char s[32];
 printf("Are you sure you want me to stop [y/N]? ");
 scanf("%s", s);
 if(strcmp(s, "y") == 0) {
 exit(0);
 }
}
int main(int argc, char** argv) {
 signal(SIGINT, f);
 while(1);
 return 0;
}

