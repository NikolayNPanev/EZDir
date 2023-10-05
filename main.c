#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////
// DEFAULT ERR CODE //
//////////////////////
char errCode[] = "000";

//////////////////////////
// PREDECLARE FUNCTIONS //
//////////////////////////
void printArgs(int argc, char **argv);

////////////////////
// FLAG FUNCTIONS //
////////////////////
        // HELP //
void printHelp(){
    system("cat help.txt");
}
        // MAKE DESCRIPTION FILE //
void makeDescription(argc,argv){
    return;
}
        // MAKE DIRECTORY //
void makeDir(int argc, char **argv){
    char mkdir[] = "mkdir ~/";
    char cmd[256];
    strcpy(cmd,mkdir);
    strcat(cmd,argv[1]);

    system(cmd);
    printf("\n\tSuccessfully created ~/%s \n",argv[1]);
}
        // REMOVE DIRECTORY //
void rmDir(int argc, char **argv){
    char mkdir[] = "rm -r ~/";
    char cmd[256];
    strcpy(cmd,mkdir);
    strcat(cmd,argv[2]);

    system(cmd);
    printf("\n\tSuccessfully removed ~/%s \n",argv[2]);

}

/////////////////////
// ARGUMENT PARSER //
/////////////////////
char *argOperationParser(int argc, char **argv){
    if(argv[1][0]=='-' ){
        if(argv[1][1]=='h'){
            printHelp();
            return "000";
        }
        if(argv[1][1]=='r'){
            rmDir(argc,argv);
            return "000";
        }
        return "101";
    }
    makeDir(argc,argv);
    //printArgs(argc,argv);
 

    return "000";
}

void printArgs(int argc, char **argv){
    printf("You have entered %d arguments:\n", argc-1);
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
}

int main(int argc,char **argv){
    printf("\nEZDir v0.0.1\n==========\n\n\n");
    strcpy(errCode,argOperationParser(argc,argv));

    if(errCode[0]!='0'){
    char EndCmd[8] = "echo    ";
    EndCmd[5] = errCode[0];
    EndCmd[6] = errCode[1];
    EndCmd[7] = errCode[2];
    printf("\n\n==========\nEXITED WITH CODE:\n");
        system(EndCmd);
        system("echo");
    }
    else{
        printf("\n==========\n");
    }

    return 0;
}