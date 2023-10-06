#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void makeDescription(int argc,char **argv){
    char cat[] = "echo '";
    char cmd[1000];
    strcpy(cmd,cat);
    strcat(cmd,argv[2]);
    strcat(cmd,"' >> ~/");
    strcat(cmd,argv[1]);
    strcat(cmd,"/description.ezd");
    system(cmd);
    return;
}

        // MAKE DIRECTORY //
void makeDir(int argc, char **argv, bool hasDesc){
    char mkdir[] = "mkdir ~/";
    char cmd[256];
    strcpy(cmd,mkdir);
    if(hasDesc==1) strcat(cmd,argv[1]);
    else strcat(cmd,argv[2]);
    system(cmd);
    if(hasDesc==1) printf("\n\tSuccessfully created ~/%s \n",argv[1]);
    else printf("\n\tSuccessfully created ~/%s \n",argv[2]);
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
    if(argc==1){
        printf("Use -h for help\n");
        return "102";           //not enough arguments
    }
    bool hasDesc = 1;

    //parse flags
    if(argv[1][0]=='-' ){
        switch(argv[1][1]){
            case 'h':           //help flag
                printHelp();
                return "000";
            case 'r':           //remove flag
                rmDir(argc,argv);
                return "000";
            case 'e':
                hasDesc=0;
                break;
            default:            //invalid flag, error 101
                printf("Invalid flag!\n");
                printf("Use -h for help\n");
                return "101";
        }
    }
    //if no flags, create the dir
    if(hasDesc==1){
        if(argc<3){
        printf("Use -h for help\n");
        return "102";           //not enough arguments
        }
        makeDir(argc,argv,hasDesc);
        makeDescription(argc,argv);
    }
    else{
        makeDir(argc,argv,hasDesc);
    }
    return "000";
}

// void printArgs(int argc, char **argv){
//     printf("You have entered %d arguments:\n", argc-1);
//     for (int i = 1; i < argc; i++) {
//         printf("%s\n", argv[i]);
//     }
// }

int main(int argc,char **argv){
    printf("\nEZDir v0.0.1\n==========\n\n");
    strcpy(errCode,argOperationParser(argc,argv));

    //Show error code if there is an error
    if(errCode[0]!='0'){
        char EndCmd[8] = "echo    ";
        EndCmd[5] = errCode[0];
        EndCmd[6] = errCode[1];
        EndCmd[7] = errCode[2];
        printf("\n==========\nEXITED WITH CODE:\n");
        system(EndCmd);
        system("echo");
        return 1;
    }
    else{
        printf("\n==========\n");
    }
    return 0;
}