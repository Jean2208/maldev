#include <Windows.h>
#include <stdio.h>

BOOL getusernameA(
  OUT     LPSTR   lpBuffer,
  IN OUT LPDWORD pcbBuffer
);

int main() {
    DWORD bufferSize = MAX_PATH;      // Initial size of the buffer
    char username[MAX_PATH];          // Buffer to receive the username

    if (GetUserNameA(username, &bufferSize)) {
        printf("Username: %s\n", username);
    } else {
        DWORD error = GetLastError();
        printf("Failed to retrieve username. Error code: %lu\n", error);
    }

    return 0;
}

//QUESTIONS

//You assigend a value of MAX_PATH to the bufferSize and that seemed to work, what does MAX_PATH represent?

//Why in the second parameter we are passing the memory address of an integer if what the function is asking is the pointer of an integer?

//Why is the variable in the first parameter that we are passing altered if we are passing by value? wouldn't we be passing the copy of the variable?

//If the function is gonna output a pointer to a string, like how it's stated in the parameters (OUT     LPSTR   lpBuffer) then why are we getting a string back instead of a pointer value?
