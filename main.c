
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//DECLARANDO FUNCOES
char* diaDaSemana(int);
void vendaIngresso();
int verificarEscolha(char escolha);

typedef struct comprador{
   int assento;
   int idade;
   char *estudante;
   char *professor;
   double precoIngresso;
   struct comprador *proximo;
}celula;

celula *pLista =NULL;

int assentos[60];

void initLista(celula **pRecebido);
void insertLista(celula **pRecebido);
void buscaListaSimples(celula **pRecebido);
void removeElementoListaSimples(celula **pRecebido);
int leValor(int *valorRecebido);

//CONSTANTES SISTEMA
int OPC_SYSTEM;
int EXIT_PROGRAM = 99;
char NOME_PECA[60];
char CLEAR[5]="clear";


//CONSTANTES DIA DA SEMANA
int DOMINGO = 0;
int SEGUNDA = 1;
int TERCA = 2;
int QUARTA = 3;
int QUINTA = 4;
int SEXTA = 5;
int SABADO = 6;

int DIA_SEMANA =-1;



void main() {
    char opc;
    DIA_SEMANA = getDiaSemana();
    getNomePeca();
    do {
        menu();
        printf("DIGITE UMA OPCAO:");
        scanf("%d",&OPC_SYSTEM);
        verificarOpcao();
        getchar();
        limparTela();
    } while(OPC_SYSTEM != EXIT_PROGRAM);

}

void menu(){
    char opc;
    limparTela();
    printf("*********** MENU ***************\n\n");
    printf("1 - TABELA DE PRECOS.\n");
    printf("2 - VENDER INGRESSO.\n");
    printf("3 - LISTAR ASSENTOS.\n");
    printf("4 - FLUXO DE COMPRAS.\n\n");
    printf("9 - FECHAR.\n\n");

}


void getNomePeca(){

    printf("DIGITE O NOME DA PECA:");
    getchar();
    scanf("%[^\n]s", &NOME_PECA);
    //scanf("%[^\n]",&NOME_PECA);
    //flush_in();
    //getchar();
}


void verificarOpcao() {

    limparTela();
    switch(OPC_SYSTEM){
        case  1:
            imprimirTabelaPreco();
            break;
        case  2:
            vendaIngresso();
            break;
        case  3:
            listarAssentos();
            break;
             break;
        case  4:
            imprimirLista(pLista);
            break;
        case 9:
            OPC_SYSTEM = 99;
            break;
    }
}

void imprimirTabelaPreco(){

    printf("+======================================+\n");
    printf("|                INGRESSOS             |\n");
    printf("+======================================+\n");
    printf("| INTEIRA : R$ 24,00                   |\n");
    printf("| MEIA :    R$ 12,00                   |\n");
    printf("+======================================+\n\n");
    printf("REGRAS INGRESSOS MEIA-ENTRADA:\n\n");
    printf("a - ESTUDANTES CRIANCAS DE 2 A 12 ANOS.\n");
    printf("b - ADULTOS A PARTIR DOS 60 ANOS.\n");
    printf("c - PROFESSORES DA REDE PUBLICA.\n\n");

    printf("REGRAS INGRESSOS GRATUITOS:\n\n");
    printf("a - ESTUDANTES CARENTES REDE PUBLICA (AS TERCAS-FEIRAS).\n");
    getchar();

}

char* diaDaSemana(int dia){

   char *result;
    result=malloc(7*sizeof(char));

    switch(dia){
        case 0:
                result = "DOMINGO";
            break;
            case 1:
                result ="SEGUNDA";
            break;
            case 2:
                result ="TERCA";
            break;
            case 3:
                result ="QUARTA";
            break;
            case 4:
                result ="QUINTA";
           break;
           case 5:
                result ="SEXTA";
            break;
            case 6:
                result ="SABADO";
            break;
    }

    return result;
}
void limparTela() {
     system(CLEAR);
}

int getIdade(){
    int idade;
    do{
        printf("\nIDADE:");
        scanf("%d",&idade);

        if (idade < 2){
            printf("\nENTRADA NAO PERMITIDA PARA MENORES DE 2 ANOS");
        } else if(idade > 100) {
            printf("\nIDADE LIMITE DE 100 ANOS");
        }

    }while(idade < 2 || idade > 100);

    return idade;
}

void flush_in()
{
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

int isProfessor() {
    int escolha;
    do {
        printf("\nPROFESSOR DE REDE PUBLICA? 1 para (SIM)  0 para (NAO)");
        scanf("%d",&escolha);
        flush_in();   // Limpa o teclado
       // professor = verificarEscolha(escolha);
    } while(escolha != 1 && escolha != 0);

    return escolha;
}

int diaValido(int dia){
    int result = 0;

    switch(dia){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
             result = 1;
        break;
    }

    return result;
}

 //PEGA O DIA DA SEMANA  DE ACORDO COM OS VALORES DA CONSTANTES NO TOPO DO ARQUIVO
int getDiaSemana(){
    int dia;
    do {
        printf("\nQUE DIA E HOJE?\n\n");
        printf("0-DOMINGO\n");
        printf("1-SEGUNDA\n");
        printf("2-TERCA\n");
        printf("3-QUARTA\n");
        printf("4-QUINTA\n");
        printf("5-SEXTA\n");
        printf("6-SABADO\n");
        printf("\nESCOLHA UM DIA:");
        scanf("%d",&dia);

        if(!diaValido(dia)){
            printf("\n DIA INCORRETO\n");
        }

    } while(!diaValido(dia));

    return dia;
}

int getAssento() {
    int assento;
    int sair =0;
    int ocupado;
    char *cadeira =malloc(3*sizeof(char));
    do {
        limparTela();
        listarAssentos();

        printf("\n\nESCOLHA UM ASSENTO:");
        scanf("%d",&assento);

        if (assento > 0 && assento < 61 ) {
             if(assentos[assento-1] != 0){
                printf("\nCADEIRA OCUPADA\n");
            } else {
                assentos[assento-1] =1;
                sair =-99;
            }
        }



    }while(sair != -99 );

    return assento;
}

void imprimirTicket(int assento,double valorIngresso) {
    //ponteiro para struct que armazena data e hora
      struct tm *data_hora_atual;

      //variável do tipo time_t para armazenar o tempo em segundos
      time_t segundos;

      //obtendo o tempo em segundos
      time(&segundos);

      //para converter de segundos para o tempo local
      //utilizamos a função localtime
      data_hora_atual = localtime(&segundos);

    limparTela();
    printf("+======================================+\n");
    printf("|                TICKET                |\n");
    printf("+======================================+\n");
    printf("DATA/HORA:%d/%d/%d %d:%d \n",
            data_hora_atual->tm_mday,
            data_hora_atual->tm_mon+1,
            data_hora_atual->tm_year+1900,
            data_hora_atual->tm_hour,
            data_hora_atual->tm_min
            );
    printf("PECA :%s\n",NOME_PECA);
    printf("ASSENTO:%d\n", assento);
    printf("PRECO INGRESSO: %.2f\n",valorIngresso);
    printf("TIPO:%s\n",(valorIngresso == 12.0 ? "MEIA-ENTRADA":valorIngresso ==0.0 ?"GRATUITO":"INTEIRA"));

    getchar();

}

void vendaIngresso(){
    char opc='n';
   do {
    limparTela();
    printf("+======================================+\n");
    printf("|          VENDA DE INGRESSOS          |\n");
    printf("+======================================+\n");

    inserirComprador(&pLista);

   }while(opc =='s');

}

int verificarEscolha(char escolha){
    int result;
    printf("VERIFICAR ESCOLHA %d",escolha);
    switch (escolha){
        case 's':
        case 'S':
            result = 1;
            break;
        case'n':
        case'N':
            result = 0;
            break;

    }

    return result;
}


/*
   Inicialização da Lista Encadeada
*/
void initLista(celula **pRecebido){
   (*pRecebido)->proximo = NULL;
}

/*
   Função para Inserção no Início
*/
void inserirComprador(celula **pRecebido){
   // Declarações
    celula *temporario;
    // IDADE DO COMPRADOR.
    int idade;
    // RESULTADO PERGUNA PROFESSOR REDE PUBLICA : TRUE OR FALSE
    int eProfessor=0;
    int condicaoEspecial = 0;

    int assento;
    double valorIngresso;


    idade =getIdade();

    if(idade > 18  && idade < 60){
         eProfessor = isProfessor();
    } else if(idade >1 && idade < 13 || idade > 59){
        condicaoEspecial = 1;
    }

    assento = getAssento();

    if(idade >  1 && idade  < 13){
        eProfessor = 0;
        valorIngresso = DIA_SEMANA == TERCA ? 0.0 : 12.0;
    } else if(idade > 59  || eProfessor){
        valorIngresso = 12.0;
    } else {
        valorIngresso = 24.0;
    }

   temporario = (celula *)malloc(sizeof(celula));
   temporario->idade = idade;
   temporario->estudante = malloc(3*sizeof(char)) ;
   temporario->estudante = idade > 1 && idade < 13 ? "SIM" : "NAO";
   temporario->professor = malloc(3*sizeof(char)) ;
   temporario->professor = eProfessor == 0 ? "NAO" : "SIM";
   temporario->precoIngresso = valorIngresso;
   temporario->assento = assento;

   if(pLista == NULL){
      (*pRecebido) = temporario;
   }else {
      temporario->proximo = (*pRecebido)->proximo;
      (*pRecebido)->proximo = temporario;

   }

    imprimirTicket(assento,valorIngresso);

}

void listarAssentos() {
    int assento;
    int sair =0;
    int ocupado;
    char *cadeira =malloc(3*sizeof(char));

    printf("+======================================+\n");
    printf("|                ASSENTOS              |\n");
    printf("+======================================+\n\n");

    for(int i = 1; i < 61 ; i ++){
        ocupado = assentos[i-1] == 0 ? 0 : 1;
        //cadeira = ocupado == 1 ? "[X]" : "[ ]";


        if(ocupado == 1){
            cadeira = "[#]";
        } else {
            cadeira ="[ ]";
        }

        if(i % 10 == 0){
            printf("%d-%s\n",i,cadeira);
        }else {
            printf("%d-%s\t",i,cadeira);
        }
    }

    getchar();

}
/*
   Função para Percorrer Elementos
*/
/*void buscaListaSimples(celula **pRecebido){
   // Declarações
      celula *temporario;
   // Instruções
      if((*pRecebido)->proximo == NULL){
         printf("Lista Vazia!\n");
      }
      else{
         temporario = (celula *)malloc(sizeof(celula));
         temporario = (*pRecebido)->proximo;
         while(temporario != NULL){
            printf("Valor : %d\n", temporario->informacao);
            temporario = temporario->proximo;
         }
      }
}*/
/*
   Remove Elemento da Cabeça
*/
void removeElementoListaSimples(celula **pRecebido){
   // Declarações
      celula *temporario;
   // Instruções
      if((*pRecebido)->proximo == NULL){
         printf("\nLista Vazia!");
      }
      else{
         temporario = (*pRecebido)->proximo;
         (*pRecebido)->proximo = temporario->proximo;
         free(temporario);
      }
}

void imprimirLista(celula *p)
{
    limparTela();
    printf("%s\n\n",NOME_PECA);
    double sum =0.0;
    while(p!=NULL)
    {
        printf("ASSENTO:%d\t",p->assento);
        printf("IDADE:%d\t",p->idade);
        printf("ESTUDANTE:%s\t",p->estudante);
        printf("PROFESSOR:%s\t",p->professor);
        printf("INGRESSO:%.2f",p->precoIngresso);
        printf("\n");
        sum += p->precoIngresso;
        p=p->proximo;
    }
    printf("-----------------------------------------\n\n");
    printf("TOTAL: R$ %.2f",sum);
    getchar();
}


