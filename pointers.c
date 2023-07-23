#include <stdio.h>

int add(int x, int y)
{
    int sum = x+y;
    return sum;
}

int add2(int* x, int* y, int* sum)
{
    return *sum = *x + *y; // here we are de-referencing the pointers
}

int main()
{
    char* name = "Jean";

    printf("Name: %p", name);


}


