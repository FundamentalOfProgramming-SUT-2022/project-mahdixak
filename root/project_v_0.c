#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

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
        if (strstr(input, "createfile --file"))
        {
            char address[200] ;
            //strremove(input,"createfile --file ") ;
            create_file(strremove(input,"createfile --file"));
            //printf("inja bayd file create bshe!\n");

        }
        else if (strstr(input, "insertstr --file"))
        {
            printf("inja bayd text to file nvhste bshe!\n");
        }
        else if (strstr(input, "cat --file"))
        {
            printf("inj bayd cat o bnvism!\n");
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
    }
    else
    {
        printf("Ooops! you enter an invalid command\n");
    }
}

void create_file(const char address[])
{
    FILE *fp;
    char *x = "/root/" ;
    address = strremove(address,x) ;
    printf("your address is : %s\n" ,address);
    char test[100];
    char slash[] = "/";
    strcpy(test,address);
    char* dirname;
    for (int x=0;x<strlen(address);x++) {
        dirname = strtok(test,slash);
        printf("root name is : %s\n" ,dirname);
        test = strremove(test,dirname);
        test = strremove(test,slash);
    }    
    //printf("test is : %s\n" ,test);
    //address = strremove(address,"dir2");
    printf("%s\n" ,address);
    printf("problem solved!\ngood work team\n");
    //int r = mkdir(dirname,0777);
    //fp = fopen("address","a") ;

}

void read_file()
{
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

int main()
{
    inputs(input);
    printf("Your command is : %s \n", input);
    command_search(input);
    return 0;
}



///sasdfsffsdffsdfsdf