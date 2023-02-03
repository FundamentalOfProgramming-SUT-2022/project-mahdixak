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
void treeshow(int depth) ;
void listfiles(const char* dirname) ;




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
        printf("%s\n" ,input);
        char option[20];
        char text[MAX];
        char projects[MAX];
        if (*input+0=='-') {
            //with option
            char *temp;
            temp = strtok(input," ");
            int index = 0;
            while (index!=3) {
                if (index==0) {
                    //option
                    strcpy(option,temp);
                }
                else if (index==2) {
                    //text
                    strcpy(text,temp);
                }
                index ++;
                temp = strtok(NULL," ");
            }
            strcpy(projects,temp);
            while (temp!=NULL)
            {
                temp = strtok(NULL," ");
                strcat(projects,temp);
            }
            printf("%s\n%s\n%s\n" ,option,text,projects);
        }
//        else {
//
//        }
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
                        int l;
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
            char *attribute;    
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
                    }
                    if(index==3) {
                    //position
                        strcpy(position,diraddress);
                    }
                    if (index==5) {
                        //size
                        size = atoi(diraddress);
                    }
                    if (index==6) {
                        //attribute
                        strcpy(attribute,diraddress);
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
    else if (strstr(input,"compare"))
    {
        printf("eee compare ham peyda shod!\n");
    }
    else if (strstr(input,"tree")) {
        strremove(input,"tree");
        int a;
        a = atoi(input);
        treeshow(a);
    }
    else if (strstr(input, "auto-indent"))  
    {
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
    char *diraddress;
    temp = fopen(secondpath , "a+");
    bool keep_reading = true ;
    int current_l = 1;
    do {
        fgets(buffer,MAX,file) ;
        buffer[strlen(buffer)-1] = '\0';
        int size=strlen(buffer);
        if (feof(file)) {    
            if (current_l==line) {
                int i=0;
                do {
                    if (i==position) {
                        fputs(text,temp);   
                    }
                    else {fputc(' ',temp);
                    }
                    i++;
                } while(i<=position);
                keep_reading = false;
            }else{
                fputs("\n" , temp) ; 
            }
        }else{
            if(current_l == line){
                int i = 0 ;
                do {
                    c = buffer[i];
                    if (i==position) {
                        fputs(text,temp);   
                    }
                    else if (buffer==' ') {
                        fputc(' ',temp);
                    }
                    else fputc(c,temp);
                    i++;
                } while(c!='\0');
                //inja b bad dige edame matne file rikhte nmishe
                if (!feof(file)) 
                    keep_reading = false;
                else {
                    printf("aslan inka miyay?\n");
                    current_l ++;
                    continue;
                }
            }else{
                fputs(buffer , temp) ;  
                fputc('\n',temp);
            }
        }
        current_l ++ ; 
    }   while(keep_reading);
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
    char *diraddress;
    temp = fopen(secondpath , "a+");
    bool keep_reading = true ;
    int current_l = 1;
    do {
        //printf("the buffer is : {%s}{%d}\n" ,buffer,current_l);
        fgets(buffer,MAX,file) ;
        buffer[strlen(buffer)-1] = '\0';
        int size=strlen(buffer);
        if (feof(file)) {
            keep_reading = false;    
            if (current_l==line) {
                fputs("\n",temp);
            }else{
                fputs("\n" , temp) ; 
            }
        }else{
            if(current_l == line){
                fputs("\n",temp);
            }else{
                fputs(buffer , temp) ;
                fputs("\n",temp) ; 
            }
        }
        current_l ++ ; 
    }   while(keep_reading);
    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);
}

void copystr(const char*address,const char *position,int size,char *attribute)
{
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
                        buffer[pos] = '\0';
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
    printf("clip board is :%s\n" ,clipboard);  
}

void pastestr(const char *address,const char *position,int size,char * attribute)
{
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
    FILE *temp;
    file = fopen(address,"r");
    if (file==NULL) {
        printf("the selected file doesn't exist!\n");
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
    char *diraddress;
    temp = fopen(secondpath , "a+");
    bool keep_reading = true;
    int current_line = 1;
    //lopp
    fclose(file);
    fclose(temp);
    remove(temp_a);
    rename(secondpath,temp_a);   

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

void comprator(char *path1,char *path2) {
    FILE *file1;
    FILE *file2;
    file1 = fopen(path1 , "r");
    file2 = fopen(path2 ,"r");
    if (file1==NULL||file2==NULL) {
        printf("Error while reading files\n");
        return ;
    }
    bool reading_status = true;
    int current_line=1;
    int show_line=1;
    char buffer1[MAX];
    char buffer2[MAX];
    int v1=1,v2=1,end =1,co = 0;
    char first;
    char second;
    char temp[MAX][MAX];
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
            show_line = current_line;
            strcpy(first,buffer1);
            strcpy(second,buffer2);
        }
        current_line ++;
    } while(reading_status);
    printf("==================== #%d ====================\n" ,show_line);
    printf("file1 is : %s\n" ,first);
    printf("file2 is : %s\n" ,second);
    if (end = 1) {
        printf(">>>>>>>>>>>>>>>>>>>> #%d >>>>>>>>>>>>>>>>>>>>\n" ,show_line+1);
        for (int i=0;i<current_line;i++) {
            printf("%s\n" ,temp[i]);
        }
    }
    fclose(file1);
    fclose(file2);

    reading_status = true ;
    file1 = fopen(path1 , "r");
    file2 = fopen(path2 ,"r");
    current_line = 1;
    do {
        if (v1!=0) {
            fgets(buffer1,MAX,file1);
            if (current_line>show_line) {
                //print the file 1 after ending file 2
            }
        }
        else if (v2!=0) {

        }
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
    //while (true) {
        inputs(input);
        command_search(input);
    //}
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