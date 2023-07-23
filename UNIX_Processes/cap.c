#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINIE 100
int main(int argc, char* argv[]) {
	if (argc != 3){
		printf("Provide the write number of arguments");
		exit(0);
		}
    printf("Fiu: %d ...> %s %s\n", getpid(), argv[1], argv[2]);
    FILE *fi, *fo;
    char linie[MAXLINIE], *p;
	// opening the files for reading and writing
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "w");
    while(1) {
        p = fgets(linie, MAXLINIE, fi);
        linie[MAXLINIE-1] = '\0';
        if (p == NULL) 
			break; // end of file
        if (strlen(linie) == 0) 
			continue; // empty line
		if (linie[0] != ' ') {
        	linie[0] -= 32; // Pentru cuvantul care incepe in coloana 0
        }
		for (p = linie; ; ) {
            p = strstr(p, " "); // searching for the next space
            if (p == NULL) break;
            p++;
            if (*p == '\n') break;
            *p -= 32; // Caracterul de dupa spatiu este facut litera mare
        }
        fprintf(fo, "%s", linie);
    }
    fclose(fo);
    fclose(fi);
}

