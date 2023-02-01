#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#define MAX 1000

int find_index (char *word,char find) ;
void removeSpaces (char*address);
char *strremove(char *str,const char *sub) ;
void *findname(const char *path,char *final) ;
void *raw_address(char *path,char *result);




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
            input = strremove(input,"insertstr --file");
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
        //printf("khob inja bayd auto indent konim!\n");
        strremove(input,"auto-indent");
        strremove(input,"/root/");
        closingpair(input);
    }
    else
    {
        printf("Ooops! you enter an invalid command\n");
    }
}

void create_file(const char *address) {
    FILE *fp;
    address = strremove(address,"/root/") ;
    printf("your address is : %s\n" ,address);
    char test[100];
    for (int i=0;i<strlen(address);i++) {
        test[i] = address[i] ;
        if (test[i]=='/') {
            //printf("%s\n" ,test);
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

void insert(const char *address) {
    FILE *file;
    FILE *temp;
    char temp_f[MAX];
    char buffer[MAX];
    char path[MAX];
    char secondpath[MAX];
    char text[MAX];
    int line=1;
    int pos=0;
    char *diraddress;
    diraddress = strtok(address," ");
    int index =1 ;
    while (diraddress!=NULL) {
        if (index==1) {
            //address
            strcpy(path,diraddress);
           /// printf("the address is %s\n" ,path);
        }
        if (index==3) {
            //text
            strcpy(text,diraddress);
            //printf("the text is : %s\n" ,text);
        }
        if(index==5) {
            //position
            int l;
            l = strtok(diraddress,":");
            l = atoi(l);
            line = l;
            l = strtok(NULL,":");
            l = atoi(l);
            pos = l;
            //printf("line and char are :%d&%d" ,line,pos);
        }
        diraddress = strtok(NULL," ");
        index ++;
    }
    strremove(path,"/root/");
    strcpy(temp_f,"temp_");
    strcat(temp_f,file);
    file = fopen(path ,"r");
    if (file==NULL) {
        printf("the selected file doesn't exist");
        return 1;
    }
    int numofslashes = 0;
    for (int a=0;a<strlen(path);a++) {
        if (path[a]=='/') {
            numofslashes++;
        }
    }
    int counter = 0;
    for (int i=0;i<strlen(path);i++) {
        secondpath[i] = path[i] ;
        if (path[i]=='/') {
            counter ++;
        }
        if (path[i]=='/'&&counter==numofslashes) {
            break;
        } 
    }
    strcat(secondpath,"temp.txt");
    printf("second temp is : %s\n" ,secondpath);
    temp = fopen(secondpath , "a+");
    bool keep_reading = true ;
    int current_l = 1;
    do {
        printf("the buffer is : {%s}{%s}\n" ,buffer,current_l);
        fgets(buffer,MAX,file) ;
        int size=strlen(buffer);
        if (feof(file)) {
            printf("mosavi shod k %d" ,current_l);
        if (current_l==line) {
            fputs(text,temp);
            keep_reading = false;
        }else{
            fputs("\n" , temp) ; 
        }
        }else{
            if(current_l == line){
                fputs(text,temp);
            }else{

                fputs(buffer , temp) ;  
            }
        }
    current_l ++ ; 
    }   while(keep_reading);
    fclose(file);
    fclose(temp);
    remove(file);
    rename(temp,file);
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
    FILE *temp;
    strremove(address," ");
    file = fopen(address, "r") ;
    if (file==NULL) {
        printf("can't open the file\n");
        return 1;
    }
    char nameOFfile[MAX];
    char temp_a[MAX];
    strcpy(temp_a,address);
    findname(address,nameOFfile);
    char *secondpath = (char*) malloc(sizeof(char) * MAX);
    raw_address(temp_a,secondpath);
    strremove(secondpath," ");
    strcat(secondpath,"temp_");
    strcat(secondpath,nameOFfile) ;
    //printf("\t%s\n" ,secondpath);
    //printf("\t%s" ,temp_a);
    temp = fopen(secondpath , "w");
    if (temp==NULL) {
        printf("Error");
        return 1;
    }
    char a;
    char pre = '\0';
    int numofbraces = 0;
    do {
        a = fgetc(file);
        if (a=='{') {
            numofbraces ++ ;
            if (pre=='\n') {
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }
            }
            if (pre=='}') {
                fputc('\n',temp);
            }
            fputc(a,temp);
            fputc('\n',temp);
            for (int a=0;a<4*numofbraces;a++) {
                fputc(' ' ,temp);
            }
            pre = a;
        }
        else if (a=='}') {
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }  
                fputc('}',temp);
                pre = a;          
                numofbraces--;
        }
        else if (a==' ') {
            if (pre =='{') {
            }
            else if (pre==' ') {

            }
            else {
                fputc(a ,temp);
                pre = a;
            }
        }
        //else if (a=='\n') {
        //    
        //}
        else {
            //a = fgetc(file);
            fputc(a,temp);
            pre = a;
        }
        if (a==EOF) {
            break;
        }
    }   while (a!=EOF);

    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);    
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

void *findname(const char *path,char *final) {
    int numofslashes =0;
    char *name;
    char last[MAX][MAX];
    int size [MAX];
    name = strtok(path,"/");
    int co = 0;
    while (name!=NULL) 
    {
        size[co] = strlen(name);
        strcpy(last[co],name);
        //printf("%s %d" ,last[co],size[co]); 
        name = strtok(NULL,"/");
        co++;
    }
    for (int i=0;;i++) {
        if (i==(co-1)) {
            last[i][size[i]] = '\0';
            strcpy(final,last[i]);
            break;
        }
    }
}

void *raw_address(char *path,char *result) {
    int numberofslashes = 0;
    char test[MAX];
    int counter=0;
    for (int a=0;a<strlen(path);a++) {
        if (path[a]=='/') {
            counter ++;
        }
    }
    for (int i=0;i<strlen(path);i++) {
        test[i] = path[i] ;
        if (test[i]=='/') {
            numberofslashes ++;
            if (counter==numberofslashes) {
                test[i+1] = '\0';
                break;
            }
        }
    }
    
    strcpy(result,test);
}