#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

int main(){
    
    time_t rawtime = 0;
    struct tm *pTime = NULL;
    bool isRunning = true;
    while (isRunning){
        time(&rawtime);
        pTime = localtime(&rawtime);
        printf("%s", asctime(pTime));
        sleep(1);
        system("clear");
    }


    return 0;

}