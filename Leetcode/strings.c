#include<stdio.h>
#include<string.h>

int firstUniqChar(char* s) {
int jumlah[26] = {0};

for (int i = 0; i < strlen(s); i++)
{
    jumlah[s[i] - 'a']++;    
}

for (int i = 0; i < strlen(s); i++)
{
    if (jumlah[s[i] - 'a'] == 1)
    {
        return i;
    }
    
}
}





int main(int argc, char const *argv[])
{
    printf("%i", firstUniqChar("boobs"));
    return 0;
}
