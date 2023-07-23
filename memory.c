# include <Windows.h>
# include <stdio.h>

int main(){

    PVOID pAddress = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 100);

    char* cString = "My name is Jean";

    memcpy(pAddress, cString, strlen(cString));

}

