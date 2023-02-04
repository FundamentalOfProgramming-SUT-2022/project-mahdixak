// ------------MAHDI AKBARI--------------
// --------------401105601---------------

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <dirent.h>


#define MAX 1000

char clipboard[MAX];
int find_index (char *word,char find) ;
void removeSpaces (char*address);
char *strremove(char *str,char *sub) ;
void *findname(const char *path,char *final) ;
void *raw_address(char *path,char *result);
void create_file(const char *address);
void insert(const char *address,const char *text,int line,int position);
void read_file(const char *address);
void removestr(const char *address,char *position,int size,char*attribute);
void copystr(const char*address,const char *position,int size,char *attribute) ;
void cutstr(const char *address,char *position,int size,char *attribute) ;
void treeshow(int depth) ;
void listfiles(const char* dirname) ;
void grep(const char *text,char *addresses,char *attribute);




char input[150];


void inputs(char input[])
{
    fgets(input, 150, stdin);
    input[strlen(input) - 1] = '\0';
}

void command_search(char input[])
{
    if (strstr(input,"grep")) {
        strremove(input,"grep ");
        char option[20];
        char text[MAX];
        char projects[MAX];
        char alaki[MAX];
        char *tempx = (char *)malloc(sizeof(char)*MAX);
        strcpy(alaki,input);
        char *temp = (char *)malloc(sizeof(char)*MAX);
        temp = strtok(alaki," ");
        if (strstr(temp,"-c")||strstr(temp,"-l")) {
            //with option
            strcpy(option,temp);
            temp = strtok(NULL," ");
            temp = strtok(NULL," ");
            strcpy(text,temp);
            temp = strtok(NULL," ");
            temp = strtok(NULL," ");
            strcpy(projects,temp);
            strcat(projects," ");
            tempx = strtok(input," ");
            for (int i=0;i<4;i++) {
                tempx = strtok(NULL," ");
            }
            while (tempx!=NULL)
            {
                strcat(projects,tempx);
                strcat(projects," ");
                tempx = strtok(NULL," ");
            }
            //printf("%s\n" ,projects);
            grep(text,projects,option);
        }
        else {
            temp = strtok(NULL," ");
            strcpy(text,temp);
            //printf("%s\n" ,text);
            temp = strtok(NULL," ");
            temp = strtok(NULL," ");
            strcpy(projects,temp);
            strcat(projects," ");
            tempx = strtok(input," ");
            for (int i=0;i<4;i++) {
                tempx = strtok(NULL," ");
            }
            while (tempx!=NULL)
            {
                strcat(projects,tempx);
                strcat(projects," ");
                tempx = strtok(NULL," ");
            }
            //printf("%s\n" ,projects);
            strcpy(option,"0");
            grep(text,projects,option);            
        }  
    }
    else if (strstr(input,"--file"))
    {
        // createfile 
        if (strstr(input, "createfile --file"))
        {
            char *address;
            address = strremove(input,"createfile --file ") ;
            // age double quotation dasht 
            if (*address+0=='"') {
                strremove(address,"\"");
                char name[MAX];
                char rawaddress[MAX];
                raw_address(address,rawaddress);
                findname(address,name);
                strremove(rawaddress," ");
                strcat(rawaddress,name);
                create_file(rawaddress);
            }
            else 
                create_file(address);
        }
        // insert
        else if (strstr(input, "insertstr --file"))
        {
            input = strremove(input,"insertstr --file ");
            char path[MAX];
            char text[MAX];
            int line=1;
            int pos=0;
            if (*input+0=='"') {
                // age double quotation dasht
                input[0] = '\0';
                for (int i=0;i<strlen(input);i++) {
                    if (input[i]=='"') break;
                    path[i] = input[i+1];
                }
                printf("address:%s\n" ,path);
            }
            else {
                char *diraddress;
                diraddress = strtok(input," ");
                int index =1 ;
                while (diraddress!=NULL) {
                    if (index==1) {
                        //address
                        strcpy(path,diraddress);
                    }
                    if (index==3) {
                        //text
                        strcpy(text,diraddress);
                    }
                    if(index==5) {
                        //position
                        char l;
                        l = strtok(diraddress,":");
                        l = atoi(l);
                        line = l;
                        l = strtok(NULL,":");
                        l = atoi(l);
                        pos = l;
                    }
                    diraddress = strtok(NULL," ");
                    index ++;
                }
                insert(path,text,line,pos);
            }
        }
        //cat
        else if (strstr(input, "cat --file"))
        {
            char *address;
            address = strremove(input,"cat --file ") ;
            // age double quotation dasht 
            if (*address+0=='"') {
                strremove(address,"\"");
                char name[MAX];
                char rawaddress[MAX];
                raw_address(address,rawaddress);
                findname(address,name);
                strremove(rawaddress," ");
                strcat(rawaddress,name);
                read_file(rawaddress);
            }
            else 
                read_file(address);
        }
        //remove
        else if (strstr(input, "removestr --file"))
        {
            strremove(input,"removestr --file ");
            printf("%s\n" ,input);
            char path[MAX];
            char position[20];
            char attribute[20];    
            int line,pos,size;
            if (*input+0=='"') {
                char *temp;
                temp = strtok(input,"\"");
                strcpy(path,temp);
                temp = strtok(NULL,"\"");
                int index =0;
                char *tempx;
                tempx = strtok(temp," ");
                while (tempx!=NULL) {
                    if (index==1) {
                        //position
                        strcpy(position,tempx);
                    }
                    else if (index==3){
                        //size
                        size = atoi(tempx);
                    }
                    else if (index==4){
                        //attribute
                        strcpy(attribute,tempx);
                    }
                    tempx = strtok(NULL," ");
                    index ++;
                }
                removestr(path,position,size,attribute);
            }
            else {
                char *diraddress;
                diraddress = strtok(input," ");
                int index =1 ;
                while (diraddress!=NULL) {
                    if (index==1) {
                    //address
                    strcpy(path,diraddress);
                    //printf("%s" ,path);
                    }
                    if(index==3) {
                    //position
                        strcpy(position,diraddress);
                        //printf("%s\n" ,position);
                    }
                    if (index==5) {
                        //size
                        size = atoi(diraddress);
                        //printf("%d\n" ,size);
                    }
                    if (index==6) {
                        //attribute
                        strcpy(attribute,diraddress);
                        //printf("%s\n" ,attribute);
                    }
                    index ++;
                    diraddress = strtok(NULL," ");
                }
                removestr(path,position,size,attribute);
            }
        }
        //copy
        else if (strstr(input, "copystr --file"))
        {
            strremove(input,"copystr --file ");
            //printf("%s\n" ,input);
            char path[MAX];
            char position[20];
            char attribute[20];    
            int line,pos,size;
            if (*input+0=='"') {
                char *temp;
                temp = strtok(input,"\"");
                strcpy(path,temp);
                temp = strtok(NULL,"\"");
                int index =0;
                char *tempx;
                tempx = strtok(temp," ");
                while (tempx!=NULL) {
                    if (index==1) {
                        //position
                        strcpy(position,tempx);
                    }
                    else if (index==3){
                        //size
                        size = atoi(tempx);
                    }
                    else if (index==4){
                        //attribute
                        strcpy(attribute,tempx);
                    }
                    tempx = strtok(NULL," ");
                    index ++;
                }
                //printf("%s\n%s\n%d\n%s\n" ,path,position,size,attribute);
                copystr(path,position,size,attribute);
            }
            else {
                char *diraddress;
                diraddress = strtok(input," ");
                int index =1 ;
                while (diraddress!=NULL) {
                    if (index==1) {
                        //address
                        strcpy(path,diraddress);
                        //printf("path is :%s\n" ,path);
                    }
                    if(index==3) {
                        //position
                        strcpy(position,diraddress);
                        //printf("%s\n" ,position);
                    }
                    if (index==5) {
                        //size
                        size = atoi(diraddress);
                        //printf("%d\n" ,size);
                    }
                    if (index==6) {
                        //attribute
                        strcpy(attribute,diraddress);
                    }
                    index ++;
                    diraddress = strtok(NULL," ");
                }
                //printf("%s\t%s\n%d\t%s\n" ,path,position,size,attribute);
                copystr(path,position,size,attribute);
            }
        }
        //cut
        else if (strstr(input, "cutstr --file"))
        {
            strremove(input,"cutstr --file ");
            //printf("%s\n" ,input);
            char path[MAX];
            char position[20];
            char attribute[20];    
            int line,pos,size;
            if (*input+0=='"') {
                char *temp;
                temp = strtok(input,"\"");
                strcpy(path,temp);
                temp = strtok(NULL,"\"");
                int index =0;
                char *tempx;
                tempx = strtok(temp," ");
                while (tempx!=NULL) {
                    if (index==1) {
                        //position
                        strcpy(position,tempx);
                    }
                    else if (index==3){
                        //size
                        size = atoi(tempx);
                    }
                    else if (index==4){
                        //attribute
                        strcpy(attribute,tempx);
                    }
                    tempx = strtok(NULL," ");
                    index ++;
                }
                //printf("%s\n%s\n%d\n%s\n" ,path,position,size,attribute);
                cutstr(path,position,size,attribute);
            }
            else {
                char *diraddress;
                diraddress = strtok(input," ");
                int index =1 ;
                while (diraddress!=NULL) {
                    if (index==1) {
                        //address
                        strcpy(path,diraddress);
                        //printf("path is :%s\n" ,path);
                    }
                    if(index==3) {
                        //position
                        strcpy(position,diraddress);
                        //printf("%s\n" ,position);
                    }
                    if (index==5) {
                        //size
                        size = atoi(diraddress);
                        //printf("%d\n" ,size);
                    }
                    if (index==6) {
                        //attribute
                        strcpy(attribute,diraddress);
                    }
                    index ++;
                    diraddress = strtok(NULL," ");
                }
                //printf("%s\t%s\n%d\t%s\n" ,path,position,size,attribute);
                cutstr(path,position,size,attribute);
            }
        }
        //paste
        else if (strstr(input, "pastestr --file"))
        {
            strremove(input,"pastestr --file ");
            char *temp;
            char address[MAX];
            char position[20];
            if (*input+0=='"') {
                //double quotation
                temp = strtok(input,"\"");
                strcpy(address,temp);
                temp = strtok(NULL,"\"");
                int index =0;
                char *tempx;
                tempx = strtok(temp," ");
                while (tempx!=NULL) {
                    if (index==1) {
                        //position
                        strcpy(position,tempx);
                    }
                    tempx = strtok(NULL," ");
                    index ++;
                }                
                //printf("%s\t%s\n" ,address,position);
                pastestr(address,position);
            }
            else {
                temp = strtok(input," ");
                int index =0;
                while (temp!=NULL) {
                    if (index==0) {
                        //address
                        strcpy(address,temp);
                    }
                    if (index==2) {
                        //position
                        strcpy(position,temp);
                    }
                    temp = strtok(NULL," ");
                    index++;
                }
                //printf("%s\t%s\n" ,address,position);
                pastestr(address,position);
            }
        }
        //find
        else if (strstr(input, "find --str"))
        {
            strremove(input,"find --str");
            char text[MAX];
            char address[MAX];
            char attribute[MAX];
            char alaki[MAX];
            strcpy(alaki,input);
            char *temp = (char *)malloc(sizeof(char)*MAX);
            char *tempx = (char *)malloc(sizeof(char)*MAX);
            if (*input+0=='"') {
                //double quotation
                printf("double  quotation\n");
            }
            else {
                temp = strtok(input," ");
                strcpy(text,temp);
                strcpy(tempx,temp);
                strcat(tempx," ");
                temp = strtok(NULL," ");
                strcat(tempx,temp);
                strcat(tempx," ");
                temp = strtok(NULL," ");
                strcat(tempx,temp);
                strcat(tempx," ");
                strcpy(address,temp);
                //strcat(tempx," ");
                strremove(alaki,tempx);
                strcpy(attribute,alaki);
                search(address,text,attribute);
            }
        }
        //replace
        else if (strstr(input, "replace --str1"))
        {
            printf("inja commande replace hast!\n");
        }
        //undo 
        else if (strstr(input, "undo --file"))
        {
            printf("age in oomd bayd undo konim");
        }
        //invalid command
        else
        {
            printf("Oops! you enter INVALID command!\n");
        }
    }
    else if (strstr(input,"compare"))
    {
        strremove(input,"compare ");
        char *dir1;
        char *dir2;
        if (*input+0=='"') {
            //double quotatoin
        }
        else {
            dir1 = strtok(input," ");
            dir2 = strtok(NULL," ");
            printf("%s %s\n" ,dir1,dir2);
            comprator(dir1,dir2);
        }
    }
    //tree
    else if (strstr(input,"tree")) {
        strremove(input,"tree");
        int a;
        a = atoi(input);
        treeshow(a);
    }
    //closing pair
    else if (strstr(input, "auto-indent"))  
    {
        strremove(input,"auto-indent");
        strremove(input,"/root/");
        closingpair(input);
    }
    //invalid command
    else
    {
        printf("Ooops! you enter INVALID command\n");
    }
}

void create_file(const char *address) {
    FILE *fp;
    address = strremove(address,"/root/") ;
    char test[100];
    for (int i=0;i<strlen(address);i++) {
        test[i] = address[i] ;
        // creating directories 
        if (test[i]=='/') {
            if (mkdir(test)==-1) {
                //printf("the Directory already EXIST!\n");
                //return ;
            }
        }
        if (test[i]=='.') {
            for (int j=0;j<strlen(address);j++) {
                test[j] = address [j] ;
            }
            // creating file 
            test[strlen(test)-1] = '\0';
            fp = fopen(test, "r");
            if (fp==NULL) {
                fclose(fp);
                fp = fopen(test,"w");
                fclose(fp);
            }
            else {
                printf("The file already EXIST!\n");
                return;
            }
        }
    }
}

void insert(const char *address,const char *text,int line,int position) {
    address = strremove(address,"/root/") ;
    FILE *file;
    FILE *temp;
    file = fopen(address,"r");
    if (file==NULL) {
        printf("the selected file doesn't exist");
        printf("%s\n" ,address);
        return;
    }
    char c;
    char nameOFfile[MAX];
    char temp_a[MAX];
    strcpy(temp_a,address);
    findname(address,nameOFfile);
    char *secondpath = (char*) malloc(sizeof(char) * MAX);
    raw_address(temp_a,secondpath);
    strremove(secondpath," ");
    strcat(secondpath,"temp_");
    strcat(secondpath,nameOFfile) ;
    char temp_f[MAX];
    char buffer[MAX];
    char newline[MAX]={0};
    char *diraddress;
    temp = fopen(secondpath , "a+");
    bool keep_reading = true ;
    int current_l = 1;
    while(keep_reading == true){
        fgets(buffer , MAX ,file) ;
        if(feof(file)){
            if(current_l < line ) {
                fputs("\n" , temp ) ;
                }
            if(current_l == line){
                for(int i = 0 ; i < position ; i ++ ) newline[i] = ' ' ; 
                strcat(newline , text ) ; 
                fputs(newline , temp) ; 
                keep_reading = false ;
            }
            if(current_l > line ){
                fputs(buffer,temp);
                keep_reading = false ; 
            } 
        }else{
            if(current_l == line){
                if(position > strlen(buffer) - 1 ){
                    buffer[strlen(buffer) - 1 ] = buffer[strlen(buffer)] ; 
                    strcpy(newline , buffer) ; 
                    for(int i = 0 ; i < position - strlen(buffer)   ; i ++ ) strcat(newline , " ")  ; 
                    strcat(newline , text) ; 
                    strcat(newline , "\n") ; 
                    fputs(newline , temp) ; 
               }else{
                    memcpy(newline  , buffer , position) ; 
                    strcat(newline , text) ;  
                    int temp_size = strlen(newline) ;  
                    for(int i  = 0 ; i+position < strlen(buffer) ; i++){
                        newline[temp_size + i] = buffer[i + position] ; 
                    }
                    fputs(newline , temp) ; 
               }
            }else{
                if(buffer[strlen(buffer) - 1] != '\n') strcat(buffer, "\n") ; 
                fputs(buffer, temp) ; 
            }
        }
        current_l ++ ; 
   }
    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);   
}

void read_file(const char *address)
{
    FILE *readf;
    char ch;
    strremove(address,"/root/");
    printf("%s\n" ,address);
    readf = fopen(address, "r");
    if (NULL == readf) {
        printf("file can't be opened \n");
    }
    do {
        ch = fgetc(readf);
        printf("%c", ch);
    } while (ch != EOF);
    fclose(readf);
}

void removestr(const char *address,char *position,int size,char*attribute)
{
    int l;
    l = strtok(position,":");
    l = atoi(l);
    int line = l;
    l = strtok(NULL,":");
    l = atoi(l);
    int pos = l;
    ////////////////////////////
    FILE *file;
    FILE *temp;
    strremove(address,"/root/");
    file = fopen(address , "r");
    if (file==NULL) {
        printf("the selected file doesn't exist");
        return;
    }
    char c;
    char nameOFfile[MAX];
    char temp_a[MAX];
    strcpy(temp_a,address);
    findname(address,nameOFfile);
    char *secondpath = (char*) malloc(sizeof(char) * MAX);
    raw_address(temp_a,secondpath);
    strremove(secondpath," ");
    strcat(secondpath,"temp_");
    strcat(secondpath,nameOFfile) ;
    char temp_f[MAX];
    char buffer[MAX];
    char newline[MAX] ={0};
    char *diraddress;
    temp = fopen(secondpath , "a+");
    if (temp==NULL) printf("EROR\n");
    bool keep_reading = true ;
    int current_l = 1;
    if (strstr(attribute,"-b")) {
        pos -= size;
        //pos ++;
    }
    while(keep_reading == true){
        fgets(buffer , MAX ,file) ;
        if (feof(file)) keep_reading = false ;
        else {
            if(current_l == line){
                memcpy(newline  , buffer , pos) ;   
                int temp_size = strlen(newline) ;  
                for(int i  = 0 ; i < size ; i++){
                    newline[temp_size + i] = NULL ; 
                    //for clip board
                }
                //printf("buffer is :%s\n" ,buffer);
                int x = pos;
                for (int j=2*pos-1;j<strlen(buffer);j++) {
                    newline[x] = buffer[j];
                    x ++;
                }
                fputs(newline , temp) ; 
                //fputc('\n' ,temp);
            }else{
                if(buffer[strlen(buffer) - 1] != '\n') strcat(buffer, "\n") ; 
                fputs(buffer, temp) ; 
            }
            current_l ++ ; 
        }
    }
    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);
}

void copystr(const char*address,const char *position,int size,char *attribute)
{
    for (int i=0;i<strlen(clipboard);i++) {
        clipboard[i] = '\0';
    }    
    int l;
    l = strtok(position,":");
    l = atoi(l);
    int line = l;
    l = strtok(NULL,":");
    l = atoi(l);
    int pos = l;
    ////////////////////////////
    strremove(address,"/root/");
    FILE *file;
    file = fopen(address,"r");
    if (file==NULL) {
        printf("the selected file doesn't exist!\n");
        return;
    }
    char c;
    bool keep_reading = true;
    int current_line = 1;
    char buffer[MAX];
    if (strstr(attribute,"-b")) {
        pos -= size;
        pos ++;
    }
    do {
        fgets(buffer,MAX,file) ;
        buffer[strlen(buffer)-1] = '\0';
        if(current_line == line){
            int i = 0 ;
            do {
                c = buffer[i];
                if (i==pos) {
                    for (int j=0;j<size;j++) {
                        clipboard[j] = buffer[pos];
                        pos ++ ;
                    }
                    keep_reading = false;
                    break;
                }
                i++;
            } while(c!='\0');
        }else{
            current_line ++;
        }
    }   while(keep_reading);
    fclose(file);
    //printf("clip board is :%s\n" ,clipboard);
}

void cutstr(const char *address,char *position,int size,char *attribute) {
    for (int i=0;i<strlen(clipboard);i++) {
        clipboard[i] = '\0';
    }
    int l;
    l = strtok(position,":");
    l = atoi(l);
    int line = l;
    l = strtok(NULL,":");
    l = atoi(l);
    int pos = l;
    ////////////////////////////
    FILE *file;
    FILE *temp;
    strremove(address,"/root/");
    file = fopen(address , "r");
    if (file==NULL) {
        printf("the selected file doesn't exist");
        return;
    }
    char c;
    char nameOFfile[MAX];
    char temp_a[MAX];
    strcpy(temp_a,address);
    findname(address,nameOFfile);
    char *secondpath = (char*) malloc(sizeof(char) * MAX);
    raw_address(temp_a,secondpath);
    strremove(secondpath," ");
    strcat(secondpath,"temp_");
    strcat(secondpath,nameOFfile) ;
    char temp_f[MAX];
    char buffer[MAX];
    char newline[MAX] ={0};
    char *diraddress;
    temp = fopen(secondpath , "a+");
    if (temp==NULL) printf("EROR\n");
    bool keep_reading = true ;
    int current_l = 1;
    if (strstr(attribute,"-b")) {
        pos -= size;
        //pos ++;
    }
    while(keep_reading == true){
        fgets(buffer , MAX ,file) ;
        if (feof(file)) keep_reading = false ;
        else {
            if(current_l == line){
                memcpy(newline  , buffer , pos) ;   
                int temp_size = strlen(newline) ;  
                for(int i  = 0 ; i < size ; i++){
                    newline[temp_size + i] = NULL ; 
                    //for clip board
                    clipboard[i] = buffer[temp_size+i];
                }
                //printf("buffer is :%s\n" ,buffer);
                int x = pos;
                for (int j=2*pos-1;j<strlen(buffer);j++) {
                    newline[x] = buffer[j];
                    x ++;
                }
                fputs(newline , temp) ; 
                //fputc('\n' ,temp);
            }else{
                if(buffer[strlen(buffer) - 1] != '\n') strcat(buffer, "\n") ; 
                fputs(buffer, temp) ; 
            }
            current_l ++ ; 
        }
    }
    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);
    printf("clip board is :%s\n" ,clipboard);
}

void pastestr(const char *address,const char *position)
{
    int l;
    l = strtok(position,":");
    l = atoi(l);
    int line = l;
    l = strtok(NULL,":");
    l = atoi(l);
    int pos = l;
    ////////////////////////////
    FILE *file;
    FILE *temp;
    strremove(address,"/root/");
    file = fopen(address , "r");
    if (file==NULL) {
        printf("the selected file doesn't exist");
        return;
    }
    char c;
    char nameOFfile[MAX];
    char temp_a[MAX];
    strcpy(temp_a,address);
    findname(address,nameOFfile);
    char *secondpath = (char*) malloc(sizeof(char) * MAX);
    raw_address(temp_a,secondpath);
    strremove(secondpath," ");
    strcat(secondpath,"temp_");
    strcat(secondpath,nameOFfile) ;
    char temp_f[MAX];
    char buffer[MAX];
    char newline[MAX] ={0};
    char *diraddress;
    temp = fopen(secondpath , "a+");
    if (temp==NULL) printf("EROR\n");
    bool keep_reading = true ;
    int current_l = 1;
    while(keep_reading == true){
        fgets(buffer , MAX ,file) ;
        if (feof(file)) keep_reading = false ;
        else {
            if(current_l == line){
                memcpy(newline  , buffer , pos) ;   
                int temp_size = strlen(newline) ;  
                strcat(newline,clipboard);
                //printf("buffer is :%s\n" ,buffer);
                for (int a=strlen(newline);a<strlen(buffer);a++) {
                    newline[a] = buffer[pos];
                    pos ++;
                }
                fputs(newline , temp) ; 
                //fputc('\n' ,temp);
            }else{
                if(buffer[strlen(buffer) - 1] != '\n') strcat(buffer, "\n") ; 
                fputs(buffer, temp) ; 
            }
            current_l ++ ; 
        }
    }
    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);
}

void search(const char *find,const char *text,char *attribute)
{
    if (strstr(attribute,"-at")&&strstr(attribute,"all")) {
        printf("It can't be possible dude!\n");
        return ;
    }
    bool count = false;
    bool at = false ;
    int num=0;
    bool byword = false ;
    bool all = false ;
    bool wildcard = false;
    char *temp = (char *)malloc(sizeof(char)*MAX);
    temp = strtok(attribute," ");
    while (temp!=NULL) {
        if (strstr(temp,"-at")) {
            at = true;
            temp = strtok(NULL," ");
            num = atoi(temp);
        }
        else if (strstr(temp,"count")) {
            count = true ;
        }
        else if (strstr(temp,"byword")) {
            byword = true;


        }
        else if (strstr(temp,"all")) {
            all = true;

        }
        printf("%s\n" ,temp);
        temp = strtok(NULL," ");
    }
    if (byword) {

    }
    else {

    }

}

void undo()
{
}

void grep(const char *text,char *addresses,char *attribute)
{
    FILE *file;
    char buffer[MAX];
    char result[MAX][MAX];
    char l[MAX][MAX];
    int c = 0;
    int print = 0;
    bool _c = false;
    bool _l = false;
    if (strstr(attribute,"-c")) {
        _c = true ;
        print = 1;
    }
    else if (strstr(attribute,"-l")) {
        _l = true;
        print = 2;
    }
    char *temp = (char *)malloc(sizeof(char)*MAX) ;
    temp = strtok(addresses," ");
    file = fopen(temp, "r") ;
    if (file==NULL) {
        printf("ERROR while opening file(s).\n");
        return;
    }
    bool keep_reading = true;
    int co = 0,cs =0;
    while (keep_reading==true) {
        fgets(buffer,MAX,file);
        //printf("buffer is :%s" ,buffer);
        if (strstr(buffer,text)) {
            strcpy(result[co],temp);
            strcat(result[co],": ");
            strcat(result[co],buffer);
            //printf("%s" ,result[co]);
            co ++;
            c++;
            strcpy(l[cs],temp);
            cs ++;
            //keep_reading = false;
        }
        if (feof(file)) keep_reading = false ;
    }
    fclose(file);
    keep_reading = true;
    while (temp!=NULL) {
        temp = strtok(NULL," ");
        temp = strtok(NULL," ");
        file = fopen(temp,"r");
        if (file==NULL) {
            //printf("ERROR while opening file(s).\n");
            break;
        }
        while (keep_reading==true) {
            fgets(buffer,MAX,file);
            if (strstr(buffer,text)) {
                strcpy(result[co],temp);
                strcat(result[co],": ");
                strcat(result[co],buffer);
                //printf("%s" ,result[co]);
                co ++;
                c++;
                strcpy(l[cs],temp);
                cs ++;
                //keep_reading = false;
            }
            if (feof(file)) keep_reading = false ;
        }
        fclose(file);
    }
    if (print==0) {
        //printe mamooli
        for (int j=0;j<co;j++) {
            printf("%s" ,result[j]);
        }
    }
    else if (print==1) {
        //printe -c
        printf("%d\n" ,c);
    }
    else if (print==2) {
        //printe -l
        int a=1;
        for (int i=1;i<cs;i++) {
            if (a==1) {
                printf("%s\n" ,l[0]);
                a++ ;
            }
            if (strcmp(l[i],l[i-1])!=0) {
                printf("%s\n" ,l[i]);
            }
        }
    }
}

void comprator(char *path1,char *path2) {
    FILE *file1;
    FILE *file2;
    file1 = fopen(path1 ,"r");
    file2 = fopen(path2 ,"r");
    if (file1==NULL||file2==NULL) {
        printf("Error while reading files\n");
        return ;
    }
    bool reading_status = true;
    int current_line=1;
    int show_line = 1;
    int show_line2 = 1;
    char buffer1[MAX];
    char buffer2[MAX];
    int v1=1,v2=1,end =1,co = 0;
    char first[MAX];
    char second[MAX];
    char temp[MAX][MAX];
    int val =1 ;
    do {
        fgets(buffer1,MAX,file1);
        fgets(buffer2,MAX,file2);
        if (feof(file1)) {
            v1 = 0;
            reading_status = false ;
            if (feof(file2)) end = 0;
            else {
                strcpy(temp[co],buffer2) ;
                co ++ ;
            }
        }
        if (feof(file2)) {
            v2=0;
            reading_status = false ;
            if (feof(file1)) end =0;
            else {
                strcpy(temp[co],buffer1);
                co ++;
            }
        }
        if (strcmp(buffer1,buffer2)!=0) {
            show_line2 = current_line;
            if (val==1) {
                show_line = current_line;
                strcpy(first,buffer1);
                strcpy(second,buffer2);
                val ++;
            }
        }
        current_line ++;
    } while(reading_status);
    printf("==================== #%d ====================\n" ,show_line);
    printf("file1 is : %s" ,first);
    printf("file2 is : %s" ,second);
    fclose(file1);
    fclose(file2);

    reading_status = true ;
    file1 = fopen(path1 ,"r");
    file2 = fopen(path2 ,"r");
    current_line = 1;
    if (end = 1) {
        printf(">>>>>>>>>>>>>>>>> #%d  -  #%d >>>>>>>>>>>>>>>>>\n" ,show_line2,show_line2);
    }
    do {
        fgets(buffer1,MAX,file1);
        fgets(buffer2,MAX,file2);
        if (strcmp(buffer1,buffer2)!=0) {
            if (v1!=0) {
                if (feof(file1)) reading_status = false ;
                if (current_line>=show_line2) {
                    if (*(buffer1+0)=='\n'||*(buffer1+0)==' ') {
                    }   
                    else 
                        printf("%s" ,buffer1);
                }
            }
            else if (v2!=0) {
                if (feof(file2)) reading_status = false ;
                if (current_line>=show_line2) {
                if (*(buffer2+0)=='\n'||*(buffer2+0)==' ') {
                }   
                else 
                    printf("%s" ,buffer2);
                }
            }
        }
        else show_line++;
        current_line ++;
    }   while (reading_status);
    fclose(file1);
    fclose(file2);
}

void listfiles(const char* dirname) {
    DIR *dir = opendir(dirname);
    if (dir==NULL) {
        printf("Something wrong!\n");
        return;
    }
    struct dirent* entity;
    entity = readdir(dir);
    while (entity!=NULL) {
    if (*entity->d_name=='.') {
    }
    else 
        printf("---%s\n" ,entity->d_name);
    entity = readdir(dir);
    }  
}

void treeshow(int depth)
{
    if (depth<-1) {
        printf("Invalid depth!\n");
        return ;
    }
    DIR *dir = opendir(".");
    if (dir==NULL) {
        printf("Something wrong!\n");
        return;
    }
    struct dirent* entity;
    if (depth==2) {
        entity = readdir(dir);
        while (entity!=NULL) {
        if (*entity->d_name=='.') {
        }
        else if (entity->d_type==DT_DIR&&*entity->d_name!='.') {
            printf("%s\n" ,entity->d_name);
            printf("|\n");
            char path[100] = { 0 };
            strcat(path, ".");
            strcat(path, "/");
            strcat(path, entity->d_name);
            //printf("\t%s\n" ,path);
            listfiles(path);
        }
        else 
            printf("%s\n" ,entity->d_name);
        entity = readdir(dir);
        }
    }
    else if(depth==1) {
        entity = readdir(dir);
        while (entity!=NULL) {
        if (*entity->d_name=='.') {
        }
        else 
            printf("%s\n" ,entity->d_name);
        entity = readdir(dir);
        }
    }
    else if(depth==0) {
        printf("root\n");
    }
    else if (depth==-1) {
        printf("emtiazi stuff!\n");
    }
    closedir(dir);
}

void arman()
{
    printf("arman o tahrim krdm XD!\n");
}

void closingpair(char *address) {
    FILE *file;
    FILE *temp;
    strremove(address," ");
    file = fopen(address, "r") ;
    if (file==NULL) {
        printf("can't open the file\n");
        return;
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
        return;
    }
    char a;
    char pre = '\0';
    int numofbraces = 0;
    do {
        a = fgetc(file);
        if (a=='{') {
            numofbraces ++ ;
            if (pre==' ') {
                fputc(a,temp);
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }
                pre = a;            
            }
            else {
                if (pre!='\n')
                    fputc(' ',temp);
                fputc(a,temp);
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }
                pre = a;
            }
            if (pre=='\n') {
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }
            }
            if (pre=='}') {
                fputc('\n',temp);
            }
        }
        else if (a=='}') {
            if (pre!='\n') {
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }  
                fputc('}',temp);
                pre = a;          
                numofbraces--;
            }
            if (fgetc(file)!='\n') {
                fputc('\n',temp);
                for (int a=0;a<4*numofbraces;a++) {
                    fputc(' ' ,temp);
                }  
                fputc('}',temp);
                pre = a;          
                numofbraces--;
            }
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
        else {
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
    while (true) {
        inputs(input);
        command_search(input);
    }
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

char *strremove(char *str,char *sub) {
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