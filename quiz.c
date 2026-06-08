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
    FILE *banco;
    QUESTOES quiz[TAM];
    int editar = 0;
    int pontuação = 0;
    for(int i = 0; i < TAM; i++){
        printf("\n%d° pergunta:\n", i + 1);
        scanf(" %49[^\n]", quiz[i].pergunta);
        
        printf("\nalternativaA:\n");
        scanf(" %19[^\n]", quiz[i].alternativaA);
        
        printf("\nalternativaB:\n");
        scanf(" %19[^\n]", quiz[i].alternativaB);
        
        printf("\nGabarito:\n");
        scanf(" %c", &quiz[i].gabarito);
        quiz[i].gabarito = toupper(quiz[i].gabarito);
    }
    
    do{
        printf("Editar pergunta: \n");
        printf("0 para NÃO\n1 para SIM\n");
        scanf("%d", &editar);
    }while(editar != 0 && editar != 1);
    
    if(editar == 1){
        for(int i = 0; i < TAM; i++){
        printf("\n%d° pergunta:\n", i + 1);
        scanf(" %49[^\n]", quiz[i].pergunta);
        }
    }
    
    banco = fopen("C:\\Users\\Samsung\\Desktop\\Questoes.txt", "w");
    for(int j = 0; j < TAM; j++){
        fprintf(banco, " %s\n", quiz[j].pergunta);
    } 
    fclose(banco);
    
    for(int k = 0; k < TAM; k++){
        printf("\n%d° pergunta:\n", k + 1);
        printf(" %s\n", quiz[k].pergunta);
        
        printf("\nalternativa A:\n");
        printf(" %s\n", quiz[k].alternativaA);
        
        printf("\nalternativa B:\n");
        printf(" %s\n", quiz[k].alternativaB);
        
        printf("\nSua respo (A ou B):\n");
        scanf(" %c", &quiz[k].res);
        quiz[k].res = toupper(quiz[k].res);
        if(quiz[k].gabarito == quiz[k].res){
            pontuação++;
        }
    }
    printf("Sua pontuação: %d", pontuação);
    return 0;
}