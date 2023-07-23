# include <windows.h>
# include <stdio.h>


int main(){

    HANDLE hopenProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, 11476);


    if(hopenProcess != NULL){

        printf("Handle aquired\n");

        if (CloseHandle(hopenProcess)){
            printf("Handle closed successfully");
        } else {
            printf("Handle didnt close");
        }

    } else {

        printf("Error");

    }

}