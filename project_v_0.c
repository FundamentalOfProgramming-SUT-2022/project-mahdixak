#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int find_index (char *word,char find) ;
void removeSpaces (char*address);
char *strremove(char *str,const char *sub) ;


char input[150];

void inputs(char input[])
{
    printf("Enter your command : ");
    fgets(input, 150, stdin);
    input[strlen(input) - 1] = '\0';
    // printf("Your command is : %s \n" ,input) ;
}

void command_search(char input[])
{
    char main_command[] = "--file";
    if (strstr(input, main_command))
    {
        // createfile 
        if (strstr(input, "createfile --file"))
        {
            char *address;
            address = strremove(input,"createfile --file ") ;
            if (*address+0=='"') {
                //printf("doubleqot dre\n");
                strremove(address," ");
                strremove(address,"\"");
                //printf("the new address : %s\n" ,address);
            }
            create_file(address);
        }
        else if (strstr(input, "insertstr --file"))
        {
            printf("inja bayd text to file nvhste bshe!\n");
            insert(input);
        }
        else if (strstr(input, "cat --file"))
        {
            printf("inj bayd cat o bnvism!\n");
            char *address;
            address = strremove(input,"cat --file ") ;
            if (*address+0=='"') {
                //printf("doubleqot dre\n");
                strremove(address," ");
                strremove(address,"\"");
                //printf("the new address : %s\n" ,address);
            }
            strremove(address,"/root/");
            read_file(address);
            
        }
        else if (strstr(input, "removestr --file"))
        {
            printf("inja bayd remove konm!\n");
        }
        else if (strstr(input, "copystr --file"))
        {
            printf("inja bayd copy konm!\n");
        }
        else if (strstr(input, "cutstr --file"))
        {
            printf("inja bayd cut konm!\n");
        }
        else if (strstr(input, "pastestr --file"))
        {
            printf("age in oomd bayd paste konm!\n");
        }
        else if (strstr(input, "find --str"))
        {
            printf("inja bayd find kone!\n");
        }
        else if (strstr(input, "replace --str1"))
        {
            printf("inja commande replace hast!\n");
        }
        else if (strstr(input, "grep"))
        {
            printf("in ghesmat braye grep krdne!\n");
        }
        else if (strstr(input, "undo --file"))
        {
            printf("age in oomd bayd undo konim");
        }
        else if (strstr(input, "tree"))
        {
            printf("inja byad tree ro bezanm!\n");
        }
        else
        {
            printf("ddsh commandet invalide bld nisti --help ro bzn!\n");
        }
    }
    else if (strstr(input, "compare"))
    {
        printf("eee compare ham peyda shod!\n");
    }
    else if (strstr(input, "auto-indent"))
    {
        printf("khob inja bayd auto indent konim!\n");
        sdf
    }
    else
    {
        printf("Ooops! you enter an invalid command\n");
    }
}

void create_file(const char address[]) {
    FILE *fp;
    address = strremove(address,"/root/") ;
    printf("your address is : %s\n" ,address);
    char test[100];
    for (int i=0;i<strlen(address);i++) {
        test[i] = address[i] ;
        if (test[i]=='/') {
            printf("%s\n" ,test);
            if (mkdir(test)==-1) {
                perror("Error") ;
            }
        }
        if (test[i]=='.') {
            for (int j=0;j<strlen(address);j++) {
                test[j] = address [j] ;
            }
        //inja bra file sakhtane
        printf("%s\n" ,test);
        fp = fopen(test,"w");
        fclose(test);
        }
    }
}

void insert(char *address) {
    FILE *pf;
    

}

void read_file(const char *address)
{
    FILE *readf;
    char ch;
    printf("%s\n" ,address);
    char test[100] ;
    strcmp(test,address);
    //printf("%s\n" ,test);
    readf = fopen(test, "r");
    if (NULL == readf) {
        printf("file can't be opened \n");
    }
    do {
        ch = fgetc(readf);
        printf("%c", ch);
    } while (ch != EOF);
    fclose(readf);
}

void delete()
{
}

void copy()
{
}

void paste()
{
}

void search()
{
}

void undo()
{
}

void grep()
{
}

void comprator()
{
}

void dr_tree()
{
}

void pipe()
{
}

void closingpair(char *address) {
    FILE *file;
    file = fopen(address, "r") ;
    strremove(address," ");
    strremove(address,"\n");
    wedf
}

int main()
{
    inputs(input);
    printf("Your command is : %s \n", input);
    command_search(input);
    return 0;
}

//subfunctions :
int find_index (char *word,char find) {
    int index=0;
    int valid=0;
    for (int i=0;i<strlen(word);i++) {
        printf("[%c]" ,*(word+i)) ;
        if (*(word+i)==find) {
            valid=1;
            printf("hooo");
            return index;
        }
        else index++;
    }
    if (valid==0) return -1;
}

void removeSpaces (char*address) {
    char *test;
    char space;
    test = address;
    for (int i=0;i<strlen(address);i++) {
        if (*(test+i)==" ") {
            strremove(address," ");
        } 
    }
}

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}