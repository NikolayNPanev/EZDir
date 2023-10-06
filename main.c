#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/////////////////////////
// PRE-PROCESSOR LOGIC //
/////////////////////////
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#pragma message ("COMPILING FOR NT SYSTEMS - OK")
const char* OS = "WIN";
#else
#pragma message ("COMPILING FOR UNIX SYSTEMS - OK")
const char* OS = "UNIX";
#endif

//////////////////////
// DEFAULT ERR CODE //
//////////////////////
char errCode[] = "000";

//////////////////////
// CATCH ERROR CODE //
//////////////////////

int catchError(char *errCode){
    if(errCode[0]!='0'){
        char EndCmd[8] = "echo ";
        EndCmd[5] = errCode[0];
        EndCmd[6] = errCode[1];
        EndCmd[7] = errCode[2];
        printf("\n==========\nEXITED WITH CODE:\n");
        system(EndCmd);
        system("echo");
        return 1;
    }
    printf("\n==========\n");
    return 0;
}

///////////////////
// VALIDATE ARGC //
///////////////////
int minArgc(int min,int argc){
    if(argc<min) return 0;
    return 1;
}

////////////////////
// FLAG FUNCTIONS //
////////////////////

        // HELP //
void printHelp(){
if(OS=="WIN")system("type help.txt");
else         system("cat help.txt");

}

        // MAKE DESCRIPTION FILE //
void makeDescription(int argc,char **argv){
    char cat[] = "echo '";
    size_t catlen = strlen(cat);
    size_t arg1len = strlen(argv[1]);
    size_t arg2len = strlen(argv[2]);
    int cmdlen = catlen+1;
    cmdlen+=arg1len;
    cmdlen+=arg2len;
    char cmd[cmdlen];
    strcpy(cmd,cat);
    strcat(cmd,argv[2]);
    strcat(cmd,"' >> ~/");
    strcat(cmd,argv[1]);
    strcat(cmd,"/description.ezd");
    system(cmd);
}

        // MAKE DIRECTORY //
void makeDir(int argc, char **argv, bool hasDesc){
    const char* mkdir = "mkdir ~/";

    if(hasDesc==1) {
        size_t mkdlen = strlen(mkdir);
        size_t arglen = strlen(argv[1]);
        int cmdlen = mkdlen+1;
        cmdlen+=arglen;
        char cmd[cmdlen];
        strcpy(cmd,mkdir);
        strcat(cmd,argv[1]);
        system(cmd);
        }
    else {
        size_t mkdlen = strlen(mkdir);
        size_t arglen = strlen(argv[2]);
        int cmdlen = mkdlen+1;
        cmdlen+=arglen;
        char cmd[cmdlen];
        strcpy(cmd,mkdir);
        strcat(cmd,argv[2]);
        system(cmd);
    }
    
    if(hasDesc==1) printf("\n\tSuccessfully created ~/%s \n",argv[1]);
    else printf("\n\tSuccessfully created ~/%s \n",argv[2]);
}

        // REMOVE DIRECTORY //
void rmDir(int argc, char **argv){
    const char *rmdir = "rm -r ~/";
    size_t rmdlen = strlen(rmdir);
    size_t arglen = strlen(argv[2]);
    int cmdlen = rmdlen+1;
    cmdlen+= arglen;
    char cmd[cmdlen];
    strcpy(cmd,rmdir);
    strcat(cmd,argv[2]);
    system(cmd);
    printf("\n\tSuccessfully removed ~/%s \n",argv[2]);
}

/////////////////////
// ARGUMENT PARSER //
/////////////////////
char *argOperationParser(int argc, char **argv){
    if(argc==1){
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
                if(!minArgc(3,argc)) return "102"; //not enough arguments
                rmDir(argc,argv);
                return "000";
            case 'e':           //no description flag
                if(!minArgc(3,argc)) return "102"; //not enough arguments
                hasDesc=0;
                break;
            default:            //invalid flag, error 101
                return "101";
        }
    }
    //if no flags, create the dir
    if(hasDesc==1){
        if(!minArgc(3,argc)) return "102"; //not enough arguments
        makeDir(argc,argv,hasDesc);
        makeDescription(argc,argv);
    }
    else{
        makeDir(argc,argv,hasDesc);
    }
    return "000";
}

int main(int argc,char **argv){
    printf("\nEZDir v0.0.1\n==========\n\n");
    strcpy(errCode,argOperationParser(argc,argv));

    //Show error code if there is an error
    if(catchError(errCode) == 1)return 1;
    return 0;
}