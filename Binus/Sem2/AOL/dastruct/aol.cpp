#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_CHARS 256
#define MAX_SLANG_LEN 100
#define MAX_MEANING_LEN 500

typedef struct SlangNode {
    struct SlangNode *charPaths[MAX_CHARS];
    char *wordDefinition;
    bool isCompleteWord;
} SlangNode;

int dictionarySize = 0;

SlangNode* initSlangNode() {
    SlangNode* newNode = (SlangNode*)malloc(sizeof(SlangNode));
    newNode->isCompleteWord = false;
    newNode->wordDefinition = NULL;
    for (int i = 0; i < MAX_CHARS; i++) {
        newNode->charPaths[i] = NULL;
    }
    return newNode;
}

void flushInput() {
    int keyPress;
    while ((keyPress = getchar()) != '\n' && keyPress != EOF);
}

void removeTrailingEnter(char *inputText) {
    int length = strlen(inputText);
    if (length > 0 && inputText[length - 1] == '\n') {
        inputText[length - 1] = '\0';
    }
}

bool checkSlangFormat(char* term) {
    int length = strlen(term);
    if (length <= 1) return false;
    for (int i = 0; i < length; i++) {
        if (isspace(term[i])) return false;
    }
    return true;
}

bool checkMeaningFormat(char* meaningText) {
    int wordTally = 0;
    bool isReadingWord = false;
    for (int i = 0; meaningText[i] != '\0'; i++) {
        if (!isspace(meaningText[i])) {
            if (!isReadingWord) {
                wordTally++;
                isReadingWord = true;
            }
        } else {
            isReadingWord = false;
        }
    }
    return wordTally >= 2;
}

void saveSlangData(SlangNode* baseRoot, char* term, char* meaningText) {
    SlangNode* tracker = baseRoot;
    for (int i = 0; term[i] != '\0'; i++) {
        unsigned char letterIndex = term[i];
        if (tracker->charPaths[letterIndex] == NULL) {
            tracker->charPaths[letterIndex] = initSlangNode();
        }
        tracker = tracker->charPaths[letterIndex];
    }
    
    if (tracker->isCompleteWord) {
        free(tracker->wordDefinition);
        tracker->wordDefinition = strdup(meaningText);
        printf("\nSuccessfully updated a slang word.\n");
    } else {
        tracker->isCompleteWord = true;
        tracker->wordDefinition = strdup(meaningText);
        dictionarySize++;
        printf("\nSuccessfully released new slang word.\n");
    }
}

SlangNode* findSlangNode(SlangNode* baseRoot, char* term) {
    SlangNode* tracker = baseRoot;
    for (int i = 0; term[i] != '\0'; i++) {
        unsigned char letterIndex = term[i];
        if (tracker->charPaths[letterIndex] == NULL) {
            return NULL;
        }
        tracker = tracker->charPaths[letterIndex];
    }
    return tracker->isCompleteWord ? tracker : NULL;
}

void displayAlphabetically(SlangNode* currentNode, char* wordTemp, int level, int* orderNum) {
    if (!currentNode) return;
    
    if (currentNode->isCompleteWord) {
        wordTemp[level] = '\0';
        printf("%d. %s\n", (*orderNum)++, wordTemp);
    }
    
    for (int i = 0; i < MAX_CHARS; i++) {
        if (currentNode->charPaths[i] != NULL) {
            wordTemp[level] = i;
            displayAlphabetically(currentNode->charPaths[i], wordTemp, level + 1, orderNum);
        }
    }
}

void waitForEnter() {
    printf("Press enter to continue...\n");
    flushInput();
}

int main() {
    SlangNode* mainRoot = initSlangNode();
    int userMenu;
    char slangTerm[MAX_SLANG_LEN];
    char slangMeaning[MAX_MEANING_LEN];
    char printBuffer[MAX_SLANG_LEN];

    do {
        printf("\n=== Boogle Slang Dictionary ===\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Choose menu: ");
        
        if (scanf("%d", &userMenu) != 1) {
            flushInput();
            continue;
        }
        flushInput();

        switch(userMenu) {
            case 1: {
                do {
                    printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
                    fgets(slangTerm, MAX_SLANG_LEN, stdin);
                    removeTrailingEnter(slangTerm);
                } while (!checkSlangFormat(slangTerm));

                do {
                    printf("Input a new slang word description [Must be more than 1 word]: ");
                    fgets(slangMeaning, MAX_MEANING_LEN, stdin);
                    removeTrailingEnter(slangMeaning);
                } while (!checkMeaningFormat(slangMeaning));

                saveSlangData(mainRoot, slangTerm, slangMeaning);
                waitForEnter();
                break;
            }
            case 2: {
                do {
                    printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
                    fgets(slangTerm, MAX_SLANG_LEN, stdin);
                    removeTrailingEnter(slangTerm);
                } while (!checkSlangFormat(slangTerm));

                SlangNode* searchResult = findSlangNode(mainRoot, slangTerm);
                if (searchResult) {
                    printf("\nSlang word  : %s\n", slangTerm);
                    printf("Description : %s\n\n", searchResult->wordDefinition);
                } else {
                    printf("\nThere is no word \"%s\" in the dictionary.\n\n", slangTerm);
                }
                waitForEnter();
                break;
            }
            case 3: {
                printf("Input a prefix to be searched: ");
                fgets(slangTerm, MAX_SLANG_LEN, stdin);
                removeTrailingEnter(slangTerm);
                
                SlangNode* prefixTracker = mainRoot;
                bool isPrefixFound = true;
                for (int i = 0; slangTerm[i] != '\0'; i++) {
                    unsigned char letterIndex = slangTerm[i];
                    if (prefixTracker->charPaths[letterIndex] == NULL) {
                        isPrefixFound = false;
                        break;
                    }
                    prefixTracker = prefixTracker->charPaths[letterIndex];
                }

                if (!isPrefixFound) {
                    printf("\nThere is no prefix \"%s\" in the dictionary.\n\n", slangTerm);
                } else {
                    printf("\nWords starts with \"%s\":\n", slangTerm);
                    int currentNum = 1;
                    strcpy(printBuffer, slangTerm);
                    displayAlphabetically(prefixTracker, printBuffer, strlen(slangTerm), &currentNum);
                    printf("\n");
                }
                waitForEnter();
                break;
            }
            case 4: {
                if (dictionarySize == 0) {
                    printf("\nThere is no slang word yet in the dictionary.\n\n");
                } else {
                    printf("\nList of all slang words in the dictionary:\n");
                    int currentNum = 1;
                    displayAlphabetically(mainRoot, printBuffer, 0, &currentNum);
                    printf("\n");
                }
                waitForEnter();
                break;
            }
            case 5: {
                printf("\nThank you... Have a nice day :)\n");
                break;
            }
            default: {
                printf("\nInvalid menu choice. Try again.\n");
                break;
            }
        }
    } while (userMenu != 5);

    return 0;
}
