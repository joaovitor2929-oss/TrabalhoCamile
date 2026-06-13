#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

typedef struct Questoes{  //struct onde armazena as questoes, alternativas, resposta do usuario e gabarito
    char pergunta[100];
    char alternativaA[30];
    char alternativaB[30];
    char resposta;
    char gabarito;
}QUESTOES;

void cadastrarQuestoes(QUESTOES *Quiz, int cont){ //função para cadastrar as questões do quiz
    char entrada[10];
    for(int i = 0; i < cont; i++){
        printf("\n%d° pergunta: ", i + 1);
        scanf(" %99[^\n]", Quiz[i].pergunta);
        
        printf("\nalternativa A: ");
        scanf(" %29[^\n]", Quiz[i].alternativaA);
        
        printf("\nalternativa B: ");
        scanf(" %29[^\n]", Quiz[i].alternativaB);
        
        printf("\nGabarito: ");
        do{
            scanf(" %9s", entrada);
            if(strlen(entrada) == 1 && 
            (toupper(entrada[0]) == 'A' || toupper(entrada[0]) == 'B')){
                Quiz[i].gabarito = toupper(entrada[0]);
            }
            else{
                Quiz[i].gabarito = '\0'; // Define um valor inválido para o gabarito
                printf("APENAS 'A' ou 'B': ");
            }
        }while(Quiz[i].gabarito != 'A' && Quiz[i].gabarito != 'B');
    }
}

void validarEntrada(int *retorno, int *valor) { //função para validar a entrada do usuário
    *retorno = scanf("%d", valor);
    if(*retorno != 1){
        while(getchar() != '\n'); // Limpa o buffer do teclado
        *valor = 0; // Define um valor inválido para a variável de controle
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *banco; FILE *resultados; 
    int opcao = 0; int pontuacao = 0; 
    int quant = 0;  int editar = 0; 
    char nome[100];  float percentual = 0.0; 
    int retornoQuant;
    int retornoOpcao; 
    int retornoEditar; char entrada[10];

    printf("\t----SISTEMA DE QUIZ----");
    do{
        printf("\n\nQuantas questões deseja fazer: ");
        validarEntrada(&retornoQuant, &quant);

        if(retornoQuant != 1){
            printf("Entrada inválida. Por favor, digite um número válido.\n");
            continue; // Volta para o início do loop para solicitar a quantidade de questões novamente
        }
        else if(quant <= 0 || quant > 50){
            printf("Quantidade inválida. Por favor, digite um número entre 1 e 50.\n");
        }

    }while(retornoQuant != 1 || quant <= 0 || quant > 50); //valida quantidade entre 1 e 50
    QUESTOES quiz[quant];
    cadastrarQuestoes(quiz, quant);//cadastrar as questões iniciais do quiz
    printf("\n- %d questões cadastradas com sucesso !-\n", quant);
    
    do{
        printf("\n\t-----MENU-----\n");
        printf("\n1 - Editar perguntas");
        printf("\n2 - Iniciar Quiz");
        printf("\n3 - Sair");
        printf("\nEscolha uma opção: ");
        validarEntrada(&retornoOpcao, &opcao);

        if(retornoOpcao != 1){
            printf("Entrada inválida. Por favor, digite um número válido.\n");
            continue; // Volta para o início do loop para solicitar a opção novamente
        }
    
    if(opcao == 1){ /*opção para editar perguntas*/
        printf("\nPerguntas cadastradas:");
        for(int j = 0; j < quant; j++){  //mostra as perguntas para o usuario decidir qual editar
            printf("\n%d° pergunta: ", j + 1);
            printf(" %s\n", quiz[j].pergunta);
        }
        
        printf("\n99 - para editar todas\n");
        do{
            printf("Qual pergunta deseja editar: ");
            validarEntrada(&retornoEditar, &editar);

            if(retornoEditar != 1){
                printf("Opção inválida. Por favor, digite um número válido.\n");
                continue; // Volta para o início do loop para solicitar a questão a ser editada novamente
            }

            if( ((editar < 1) || (editar > quant)) && editar != 99){ //validação para mostrar mensagem de erro
                printf("Opção inválida. Escolha uma pergunta existente ou 99.\n");
            }
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

            do{
                scanf(" %9s", entrada);
                if(strlen(entrada) == 1 && 
                (toupper(entrada[0]) == 'A' || toupper(entrada[0]) == 'B')){
                    quiz[editar - 1].gabarito = toupper(entrada[0]);
                }
                else{
                    quiz[editar - 1].gabarito = '\0'; // Define um valor inválido para o gabarito
                    printf("APENAS 'A' ou 'B': ");
                }
            }while(quiz[editar - 1].gabarito != 'A' && quiz[editar - 1].gabarito != 'B'); //validação
        }
        banco = fopen("C:\\Users\\Samsung\\Desktop\\Questoes.txt", "w");
        if(banco == NULL){//validação para mostrar mensagem de erro em caso de falha ao abrir o arquivo
            printf("Erro ao abrir o arquivo!");
            return 1;
        }
        for(int k = 0; k < quant; k++){
            fprintf(banco, " %s\n", quiz[k].pergunta);
            fprintf(banco, " %s\n", quiz[k].alternativaA);
            fprintf(banco, " %s\n", quiz[k].alternativaB);
            fprintf(banco, " %c\n\n", quiz[k].gabarito);
        } 
            fclose(banco);  //salvar as Questoes no arquivo
    }
    
        else if(opcao == 2){ 
            pontuacao = 0; //reseta a pontuação para o caso do usuário fazer o quiz mais de uma vez
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
                while(getchar() != '\n');
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
            if(resultados == NULL){ //validação para mostrar mensagem de erro
                printf("Erro ao abrir o arquivo!");
                return 1;
            }
            fprintf(resultados, "Nome: %s\n", nome);
            fprintf(resultados, "Pontuação: %d\n\n", pontuacao);
            fclose(resultados); //salva resultados no arquivo
        }
        else if(opcao == 3){ //opção para sair do programa
            printf("\nEncerrando programa...");
        }
        else{ //validação para mostrar mensagem de erro em caso de opção inválida
            printf("\nOpção inválida. Por favor, escolha entre 1, 2 ou 3.");
        }
    }while(opcao != 3);//validação para repetir o menu até o usuário escolher a opção de sair

    return 0;
}