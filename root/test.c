#include <stdio.h>
#include <string.h>
#include <errno.h>

void rek_mkdir(char *path) {
    char *sep = strrchr(path, '/');
    if(sep != NULL) {
        *sep = 0;
        rek_mkdir(path);
        *sep = '/';
    }
    if(mkdir(path, 0777) && errno != EEXIST)
        printf("error while trying to create '%s'\n%m\n", path); 
}

FILE *fopen_mkdir(char *path, char *mode) {
    char *sep = strrchr(path, '/');
    if(sep) { 
        char *path0 = strdup(path);
        path0[ sep - path ] = 0;
        rek_mkdir(path0);
        free(path0);
    }
    return fopen(path,mode);
}

int main () {
    FILE * fptr;
    char address[150] = "/root/file1/dir2/file4.txt" ;
    rek_mkdir(address);
    fptr=fopen("test.txt","r");
    char singleline[150] ;
    while (!feof(fptr)) {
        fgets(singleline,150,fptr);
        puts(singleline);
    }
    fclose(fptr);
    return 0 ;
}