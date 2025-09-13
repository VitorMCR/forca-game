#ifndef FORCAGAME_H_INCLUDED
#define FORCAGAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXWORDLENGTH 64

char chosenWord[MAXWORDLENGTH];
char wordProgress[MAXWORDLENGTH];
char pastLetters[6]; // 6 tentativas
int pasti = 0;

char input;
int lives = 6;

void printHangman()
{
    switch(lives)
    {
    case 6:
        printf("  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n\n");
        break;
    case 5:
        printf("  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n\n");
        break;
    case 4:
        printf("  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n\n");
        break;
    case 3:
        printf("  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n\n");
        break;
    case 2:
        printf("  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n\n");
        break;
    case 1:
        printf("  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n\n");
        break;
    case 0:
        printf("  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n\n");
        break;
    }
}

void checkLetter()
{
    int foundCount = 0;
    for (int i = 0; i < strlen(chosenWord); i++)
    {
        if (chosenWord[i] == input)
        {
            wordProgress[i] = input;
            foundCount++;
        }
    }

    if (foundCount == 0)
    {
        if (strlen(pastLetters) == 0)
        {
            pastLetters[pasti] = input;
            pasti++;
        }
        else
        {
            for (int i = 0; i < strlen(pastLetters); i++)
            {
                if (pastLetters[i] == input)
                {
                    break;
                }
                else if (i + 1 == strlen(pastLetters))
                {
                    pastLetters[pasti] = input;
                    pasti++;
                }
            }
        }
        lives--;
    }
}

void getRandomLine(FILE* fptr) {
    char buffer[MAXWORDLENGTH];
    int linecount = 1;

    srand(time(NULL)); // randomizar utilizando o horário atual
    while(!feof(fptr)) {
        size_t r = fread(buffer, 1, MAXWORDLENGTH, fptr);
        for (int i = 0; i < r; i++) {
            if (buffer[i] == '\n') {
                linecount++;
            }
        }
    }

    char words[linecount][MAXWORDLENGTH];
    fseek(fptr, 0, SEEK_SET);
    int j = 0;
    while (fgets(buffer, MAXWORDLENGTH, fptr)) {
        strcpy(words[j], buffer);
        words[j][strcspn(words[j], "\n")] = 0;
        j++;
    }

    strcpy(chosenWord, words[rand() % linecount]);
}

int ForcaGame()
{
    setlocale(LC_ALL, "Portuguese");
    int status;

    FILE *fptr;
    fptr = fopen("palavras.txt", "r");

    if (!fptr) {
        printf("Arquivo \"palavras.txt\" não foi encontrado. Certifique-se que está no mesmo diretório que o código compilado.\n");
        system("pause");
        return -1;
    }
    getRandomLine(fptr);
    fclose(fptr);

    for (int i = 0; i < strlen(chosenWord); i++)
    {
        if (chosenWord[i] == ' ')
        {
            wordProgress[i] = ' ';
        }
        else
        {
            wordProgress[i] = '_';
        }
    }

    do
    {
        system("cls");
        printf("|| JOGO DA FORCA ||\n");
        printf("Acerte a palavra para ganhar!\n\n");
        printHangman();
        for (int i = 0; i < strlen(chosenWord); i++)
        {
            printf("%c ", wordProgress[i]);
        }

        if (strcmp(chosenWord, wordProgress) == 0 || lives == 0)
        {
            break;
        }

        printf("\n\nLETRAS INCORRETAS: ");
        for (int i = 0; i < strlen(pastLetters); i++)
        {
            if (i + 1 == strlen(pastLetters))
            {
                printf("%c", pastLetters[i]);
            }
            else
            {
                printf("%c, ", pastLetters[i]);
            }
        }
        printf("\n\n\nDigite uma letra para testar:\n\n> ");
        scanf("%c", &input);
        fflush(stdin);
        if (isalpha(input))
        {
            input = toupper(input);
            checkLetter();
        }
    }
    while (1);

    if (lives == 0)
    {
        printf("\n\nPERDEU...\n");
        status = 0;
    }
    else
    {
        printf("\n\nACERTOU!!!\n");
        status = 1;
    }

    return status;
}

#endif // FORCAGAME_H_INCLUDED
