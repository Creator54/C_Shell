#include "headers.h"
#include "commands.h"
#include "childHandler.h"

int numbgChilds=0;

process bgProcess[50];

int getiofid(int id){
    int i;
    for(i=0;i<numbgChilds;i++)
        if(bgProcess[i].id==id)
            return i;
}

void killChilds(int id){
    int status;
    int pid=waitpid(-1, &status, WNOHANG);
    if(pid>0){
        printf("[] %s pid %d exited successfully\n", bgProcess[getiofid(pid)].name, pid);
        bgProcess[getiofid(pid)].inbg=1;
    }
}

int killallChilds(){
    int i;
    for(i=0;i<numbgChilds;i++){
        if(!bgProcess[i].inbg){
            kill(bgProcess[i].id, SIGKILL);
            printf("[] %s Stopped pid: %d\n", bgProcess[i].name, bgProcess[i].id);
        }
    }    
}