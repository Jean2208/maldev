# include <windows.h>
# include <stdio.h>


HANDLE createfileW(
  IN          LPCWSTR               lpFileName, //A pointer to a constant null-terminated string of 16-bit Unicode characters 
  IN          DWORD                 dwDesiredAccess, //A 32-bit unsigned integer
  IN OPTIONAL LPSECURITY_ATTRIBUTES lpSecurityAttributes, //A pointer to a SECURITY_ATTRIBUTES structure
  IN          DWORD                 dwCreationDisposition, 
  IN            DWORD                 dwFlagsAndAttributes,
  IN OPTIONAL HANDLE                hTemplateFile //A value that specifies a particular object that the operating system is managing
);


BOOL getusernameA(
  OUT     LPSTR   lpBuffer,
  IN OUT LPDWORD pcbBuffer
);




int main(){

  HANDLE hFile = INVALID_HANDLE_VALUE;

  LPCWSTR filePath = L"C:\\Users\\jeanp\\OneDrive\\Desktop\\jean.txt";

  hFile = CreateFileW(filePath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

  if (hFile == INVALID_HANDLE_VALUE){
    printf("CreateFileW function failed with error code: %d\n", GetLastError());
    return -1;
  }

}