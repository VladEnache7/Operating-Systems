#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char strings[100][100];  // assuming a maximum of 100 strings of length 100
  int n, i;
  char filename[16];
  char command[100];
  char reversed[100];
  FILE *fp;

  printf("Enter the number of strings: ");
  scanf("%d", &n);

  printf("Enter %d strings: ", n);
  for(i = 0; i < n; i++) {
    scanf("%s", strings[i]);
    sprintf(filename, "temp%d.txt", i+1);
    sprintf(command, "./hw6-1 %s %s", filename, strings[i]);
    system(command);
  }

  printf("Reversed strings: ");
  for(i = n-1; i >= 0; i--) {
    sprintf(filename, "temp%d.txt", i+1);
    fp = fopen(filename, "r");
    if(fp == NULL) {
      printf("Error opening file %s for reading.\n", filename);
      return 1;
    }
    fgets(reversed, 100, fp);
    fclose(fp);
    printf("%s", reversed);
  }

  printf("\n");
  return 0;
}

