#include <stdio.h>
#define TAM 2
#include <ctype.h>
#include <locale.h>

typedef struct Questoes{
    char pergunta[50];
    char alternativaA[20];
    char alternativaB[20];
    char res;
    char gabarito;
}QUESTOES;
int main()
{
    setlocale(LC_ALL, "Portuguese");
    QUESTOES quiz[TAM];
    int editar = 0;
    int pontuação = 0;
    for(int i = 0; i < TAM; i++){
        printf("\n%d° pergunta:\n", i + 1);
        scanf(" %49[^\n]", &quiz[i].pergunta);
        
        printf("\nalternativaA:\n");
        scanf(" %19[^\n]", quiz[i].alternativaA);
        
        printf("\nalternativaB:\n");
        scanf(" %19[^\n]", quiz[i].alternativaB);
        
        printf("\nGabarito:\n");
        scanf(" %c", &quiz[i].gabarito);
        quiz[i].gabarito = toupper(quiz[i].gabarito);
    }

    
    for(int i = 0; i < TAM; i++){
        printf("\n%d° pergunta:\n", i + 1);
        printf(" %s\n", quiz[i].pergunta);
        
        printf("\nalternativa A:\n");
        printf(" %s\n", quiz[i].alternativaA);
        
        printf("\nalternativa B:\n");
        printf(" %s\n", quiz[i].alternativaB);
        
        printf("\nSua respo (A ou B):\n");
        scanf(" %c", &quiz[i].res);
        quiz[i].res = toupper(quiz[i].res);
        if(quiz[i].gabarito == quiz[i].res){
            pontuação++;
        }
    }
    printf("Sua pontuação: %d", pontuação);
    return 0;
}