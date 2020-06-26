#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_BUFFER 200

int main()
{
    FILE* f;
    FILE* f2;
    char fileName[50];
    char fileName2[50];

    printf("Entrez le nom du fichier cnf sans extension\n");
    scanf("%s", fileName);

    strcpy(fileName2,fileName);

    strcat(fileName,".cnf");
    strcat(fileName2,"-inference.cnf");

    f = fopen(fileName, "r");
    f2 = fopen(fileName2, "w");

    if (f == NULL || f2 == NULL){
        printf("Erreur lors de la lecture du fichier \n");
        exit(0);
    }

    char* line = malloc(READ_BUFFER);

    fgets(line,READ_BUFFER,f);

    char* newLine = malloc(READ_BUFFER);

    char *ch;
    ch = strtok(line, " ");
    strcpy(newLine,ch);
    strcat(newLine," ");
    ch = strtok(NULL, " ");
    strcat(newLine,ch);
    strcat(newLine," ");
    ch = strtok(NULL, " ");

    int nbClauses = atoi(ch);

    nbClauses++;


    itoa(nbClauses,ch,10);

    strcat(newLine,ch);
    strcat(newLine," ");

    ch = strtok(NULL, " ");
    strcat(newLine,ch);
    strcat(newLine," ");

    fputs(newLine,f2);

    while(fgets(line,READ_BUFFER,f) != NULL){
        fputs(line,f2);
    }

    printf("Saisissez votre formule but (sous forme FNC séparée par des espaces)\n");
    char c;

    scanf(" %[^\n]s",ch);


    line = strtok(ch, " ");


    while(line !=NULL){
        int lineN = atoi(line);

        lineN*=-1;

        char tempLine[READ_BUFFER];

        itoa(lineN,tempLine,10);

        strcat(tempLine," 0\n");


        fputs(tempLine,f2);

        line = strtok(NULL," ");
    }

    fclose(f);
    fclose(f2);

    execlp("./UBSCAT/ubcsat.exe","ubcsat","-r","solution","null","-r","stats","null","-r","out","null"/*,"-r","model","stdin"*/,"-alg","saps","-i",fileName2,"-solve",NULL);

    FILE* f3;

    f3 = fopen("tmp_results.txt","r");

    if (f3 != NULL){
        char* line = malloc(READ_BUFFER);

        fgets(line,READ_BUFFER,f);
        if(strstr(line, "No Solution found") != NULL) {
            printf("BC ==> But\n");
        }else{
            printf("BC =/=> But\n");
        }
    }else{
        printf("Erreur\n");
    }

    return 0;
}
