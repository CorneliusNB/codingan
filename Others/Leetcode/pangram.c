#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



bool checkIfPangram(char* sentence) {
    int abjad[26] = {0};
    for(int i = 0; i < strlen(sentence); i++){
        abjad[sentence[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (abjad[i] = 0)
        {
            return false;
        }
        
    }
    return true;
    
}