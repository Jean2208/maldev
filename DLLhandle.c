# include <windows.h>
# include <stdio.h>



int main() {


    HMODULE hModule = LoadLibraryA("C:\\Windows\\System32\\shell32.dll");

    if (hModule != NULL) {

        printf("DLL's handle loaded succesfully");

        getchar();

        FreeLibrary(hModule);
        
    } else {

        printf("DLL not loaded successfully");

    }

    return 0;


}




