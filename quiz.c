#include <stdio.h>
#include <ctype.h>
#include <locale.h>

typedef struct Questoes{  //struct onde armazena as questoes, alternativas, resposta do usuario e gabarito
    char pergunta[100];
    char alternativaA[30];
    char alternativaB[30];
    char resposta;
    char gabarito;
}QUESTOES;

void cadastrarQuestoes(QUESTOES *Quiz, int cont){ //função para cadastrar as questões, recebe o vetor de questões e a quantidade de questões a serem cadastradas
    for(int i = 0; i < cont; i++){
        printf("\n%d° pergunta: ", i + 1);
        scanf(" %99[^\n]", Quiz[i].pergunta);
        
        printf("\nalternativa A: ");
        scanf(" %29[^\n]", Quiz[i].alternativaA);
        
        printf("\nalternativa B: ");
        scanf(" %29[^\n]", Quiz[i].alternativaB);
        
        printf("\nGabarito: ");
        do{
            scanf(" %c", &Quiz[i].gabarito);
            Quiz[i].gabarito = toupper(Quiz[i].gabarito);
            if(Quiz[i].gabarito != 'A' && Quiz[i].gabarito != 'B'){
                printf("APENAS 'A' ou 'B': ");
            }
        }while(Quiz[i].gabarito != 'A' && Quiz[i].gabarito != 'B');
    }
}


int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *banco; FILE *resultados; //arquivo de banco de questões e arquivo de resultados
    int opcao = 0;/*variavel que armazena a opção escolhida pelo usuário*/ int pontuacao = 0; /*variavel de pontuação do quiz*/
    int quant = 0; /* variavel de quantidade de questões*/ int editar = 0; //variavel auto explicativa
    char nome[100]; /*variavel de nome do usuário*/ float percentual = 0.0; /*variavel de percentual de acertos do quiz*/
    
    printf("\t----SISTEMA DE QUIZ----");
    printf("\n\nQuantas quest�es deseja fazer: ");
    scanf("%d", &quant);
    
    QUESTOES quiz[quant];
    cadastrarQuestoes(quiz, quant);//chama a função de cadastrar questões para cadastrar as questões iniciais do quiz
    printf("\n- %d questões cadastradas com sucesso !-\n", quant);
    
    do{
        printf("\n\t-----MENU-----\n");
        printf("\n1 - Editar perguntas");
        printf("\n2 - Iniciar Quiz");
        printf("\n3 - Sair");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
    
    if(opcao == 1){
        printf("\nPerguntas cadastradas:");
        for(int j = 0; j < quant; j++){  //mostra as perguntas para o usuario decidir qual editar
            printf("\n%d° pergunta: ", j + 1);
            printf(" %s\n", quiz[j].pergunta);
        }
        
        printf("\n99 - para editar todas\n");
        do{
            printf("Qual pergunta deseja editar: ");
            scanf("%d", &editar);
        }while( ((editar < 1) || (editar > quant)) && editar != 99); //validação
        
        if(editar == 99){
            cadastrarQuestoes(quiz, quant);//chama a função de cadastrar questões para editar todas as questões
        }
        else{ //edita apenas a questão escolhida
            printf("\n%d° pergunta: ", editar);
            scanf(" %99[^\n]", quiz[editar - 1].pergunta);
            
            printf("\nalternativa A: ");
            scanf(" %29[^\n]", quiz[editar - 1].alternativaA);
            
            printf("\nalternativa B: ");
            scanf(" %29[^\n]", quiz[editar - 1].alternativaB);
            
            printf("\nGabarito: ");

            do{ //validação do gabarito para aceitar apenas 'A' ou 'B'
                scanf(" %c", &quiz[editar - 1].gabarito);
                quiz[editar - 1].gabarito = toupper(quiz[editar - 1].gabarito);
                if(quiz[editar - 1].gabarito != 'A' && quiz[editar - 1].gabarito != 'B'){ //validação para mostrar mensagem de erro
                printf("APENAS 'A' ou 'B': ");
                }
            }while(quiz[editar - 1].gabarito != 'A' && quiz[editar - 1].gabarito != 'B'); //validação para repetir a pergunta em caso de erro
        }
        banco = fopen("C:\\Users\\Samsung\\Desktop\\Questoes.txt", "w");
        for(int k = 0; k < quant; k++){
            fprintf(banco, " %s\n", quiz[k].pergunta);
            fprintf(banco, " %s\n", quiz[k].alternativaA);
            fprintf(banco, " %s\n", quiz[k].alternativaB);
            fprintf(banco, " %c\n\n", quiz[k].gabarito);
        } 
            fclose(banco);  //salvar as Questoes no arquivo
    }
    
        if(opcao == 2){ //inicia o quiz, mostrando as perguntas e alternativas para o usuário responder, e ao final mostra a pontuação e percentual de acertos
            printf("\n\t******QUIZ******\n");
            printf("Digite seu nome: ");
            scanf(" %99[^\n]", nome);
            
            for(int x = 0; x < quant; x++){
                printf("----------------------------------");
                printf("\n%d° pergunta: ", x + 1);
                printf(" %s\n", quiz[x].pergunta);
                
                printf("\nalternativa A: ");
                printf(" %s\n", quiz[x].alternativaA);
                
                printf("\nalternativa B: ");
                printf(" %s\n", quiz[x].alternativaB);
                
                printf("\nSua resposta (A ou B): ");
                scanf(" %c", &quiz[x].resposta);
                quiz[x].resposta = toupper(quiz[x].resposta);
                if(quiz[x].gabarito == quiz[x].resposta){
                    pontuacao++;
                }
            }
            printf("----------------------------------");
            percentual = (pontuacao * 100.0) / quant;

            if(percentual >= 80){
                printf("\nExcelente desempenho.");
            }
            else if(percentual >= 50){
                printf("\nBom desempenho.");
            }
            else{
                printf("\nPrecisa melhorar.");
            }
            printf("\n%s, Acertou %d de %d", nome, pontuacao, quant);
            printf("\nAproveitamento: %.1f%%", percentual);

            resultados = fopen("C:\\Users\\Samsung\\Desktop\\Resultados.txt", "a");
            fprintf(resultados, "Nome: %s\n", nome);
            fprintf(resultados, "Pontuação: %d\n\n", pontuacao);
            fclose(resultados); //salva resultados no arquivo
        }
    }while(opcao != 3);//validação

    return 0;
}