int XOR ( int a, int b)
{
    /*int k = sizeof(int), i = 0;
    int result = 0;

    while (i < k) {
        result |= (a & (1 << i)) 
            (a|b) & (1 << i);
            */

    //return a^b;
    
    int x = a & b;
    int y = ~(a | b);
    int z = ~(x | y);
    return z;
}

/*
Missing number in array array  searching
Given an array of size n-1 and given that there are numbers from 1 to n with one missing, 
the missing number is to be found.
*/

int get_missing_number (int *arr, int size)
{
    for (int i = 1; i < size; i++) {
        if ((i ^ arr[i-1]) != 0) {
            return i;
        }
    }
    return 0;
}
