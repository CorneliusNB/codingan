#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isAnagram(char* s, char* t) {
    int counter1[26] = {0};
    int counter2[26] = {0};

    if (strlen(s) != strlen(t))
    {
        return false;
    }
    

    for (int i = 0; i < strlen(s); i++)
    {
        counter1[s[i] - 'a']++;
        counter2[t[i] - 'a']++;
    }
    
    for (int i = 0; i < strlen(s); i++)
    {
        if (counter1[i] != counter2[i])
        {
            return false;
        }
        
    }
    return true;
    
}
