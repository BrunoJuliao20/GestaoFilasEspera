#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 50
#define TRIAGEM_VERDE 1
#define TRIAGEM_LARANJA 2
#define TRIAGEM_VERMELHO 3

int cont_vermelho=0, cont_laranja=0;


typedef struct
{
    int dia;
    int mes;
    int ano;
    int segundos;
    int minutos;
    int horas;
} Tempo;

typedef struct lnode *List;
typedef struct lnode
{
    char nome[MAX];
    int pulseira;
    int bi;
    Tempo tempo_entrada;
    List next;
} Paciente;


void file_doentes(List lista)
{
    List aux = (lista -> next);
    FILE *fich = fopen("doentes.txt","a");
    while(aux!=NULL)
    {
        fprintf(fich,"%s\n%d\n%02d/%02d/%d\t%02d:%02d:%02d\n",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);
        aux = aux->next;
    }
    fclose(fich);
}

void file_consultas_vermelho(List lista)
{
    List aux = lista -> next;
    FILE *fich = fopen("doentesvermelho.txt","w");
    while (aux!=NULL)
    {
      fprintf(fich,"%s\n%d\n%02d/%02d/%d\t%02d:%02d:%02d\n",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);
      aux = aux->next;
    }
    fclose(fich);
}

void file_consultas_verde(List lista)
{
    List aux = lista -> next;
    FILE *fich = fopen("doentesverde.txt","w");
    while (aux!=NULL)
    {
      fprintf(fich,"%s\n%d\n%02d/%02d/%d\t%02d:%02d:%02d\n",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);
      aux = aux->next;
    }
    fclose(fich);
}

void file_consultas_laranja(List lista)
{
    List aux = lista -> next;
    FILE *fich = fopen("doenteslaranja.txt","w");
    while (aux!=NULL)
    {
      fprintf(fich,"%s\n%d\n%02d/%02d/%d\t%02d:%02d:%02d\n",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);
      aux = aux->next;
    }
    fclose(fich);
}



List inicia_lista()
{
    List root = (List) malloc(sizeof(Paciente));
    root -> next = NULL;
    return root;
}


void insere_paciente(List root, Paciente paciente)
{
    List novo_paciente, tmp;
    struct tm * timeinfo;
    time_t rawtime;
    novo_paciente = (List) malloc( sizeof(Paciente) );
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (novo_paciente != NULL)
    {
        novo_paciente -> bi = paciente.bi;
        strcpy(novo_paciente->nome,paciente.nome);
        novo_paciente -> tempo_entrada.dia = timeinfo->tm_mday;
        novo_paciente -> tempo_entrada.mes = timeinfo->tm_mon+1;
        novo_paciente -> tempo_entrada.ano = timeinfo->tm_year+1900;
        novo_paciente -> tempo_entrada.horas = timeinfo->tm_hour;
        novo_paciente -> tempo_entrada.minutos = timeinfo->tm_min;
        novo_paciente -> tempo_entrada.segundos = timeinfo->tm_sec;
        novo_paciente -> next = NULL;
    }
    tmp = root;
    while (tmp -> next != NULL)
        tmp = tmp -> next;

    tmp -> next = novo_paciente;
}


int conta_digitos(int num)
{
    int count = 0;
    while(num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}


void move_para_lista_triagem(List paciente, List triagem)
{
    List tmp, novo_paciente;
    novo_paciente = (List) malloc(sizeof(Paciente));
    if (novo_paciente != NULL)
    {
        novo_paciente -> bi = paciente->bi;
        novo_paciente -> pulseira = paciente->pulseira;
        strcpy(novo_paciente->nome,paciente->nome);
        novo_paciente -> tempo_entrada.dia = paciente -> tempo_entrada.dia;
        novo_paciente -> tempo_entrada.mes = paciente -> tempo_entrada.mes;
        novo_paciente -> tempo_entrada.ano = paciente -> tempo_entrada.ano;
        novo_paciente -> tempo_entrada.horas = paciente -> tempo_entrada.horas;
        novo_paciente -> tempo_entrada.minutos = paciente -> tempo_entrada.minutos;
        novo_paciente -> tempo_entrada.segundos = paciente -> tempo_entrada.segundos;
        novo_paciente -> next = NULL;
    }
    tmp = triagem;
    while (tmp -> next != NULL)
        tmp = tmp -> next;

    tmp -> next = novo_paciente;
}


void move_para_lista_global(List paciente, List total)
{
    List tmp, novopaciente;
    novopaciente = (List) malloc(sizeof(Paciente));
    if (novopaciente != NULL)
    {
        novopaciente -> bi = paciente -> bi;
        novopaciente -> pulseira = paciente -> pulseira;
        strcpy(novopaciente->nome,paciente->nome);
        novopaciente -> tempo_entrada.dia = paciente -> tempo_entrada.dia;
        novopaciente -> tempo_entrada.mes = paciente -> tempo_entrada.mes;
        novopaciente -> tempo_entrada.ano = paciente -> tempo_entrada.ano;
        novopaciente -> tempo_entrada.horas = paciente -> tempo_entrada.horas;
        novopaciente -> tempo_entrada.minutos = paciente -> tempo_entrada.minutos;
        novopaciente -> tempo_entrada.segundos = paciente -> tempo_entrada.segundos;
        novopaciente -> next = NULL;
    }
    tmp = total;
    while (tmp -> next != NULL)
        tmp = tmp -> next;

    tmp -> next = novopaciente;
}


List atribui_cor(List lista, int num_bi, int cor, List verde, List laranja, List vermelho, List total)
{
    List p;
    for (p=lista ; p!=NULL ; p=p->next)
    {
        if (p->bi == num_bi)
        {
            p->pulseira=cor;

            if(cor==TRIAGEM_VERDE)
            {
                move_para_lista_triagem(p, verde);
                move_para_lista_global(p, total);
            }
            else if(cor==TRIAGEM_LARANJA)
            {
                move_para_lista_triagem(p, laranja);
                move_para_lista_global(p, total);
            }
            else if(cor==TRIAGEM_VERMELHO)
            {
                move_para_lista_triagem(p, vermelho);
                move_para_lista_global(p, total);
            }
            return p;
        }
    }
    return NULL;
}


int cancelar_paciente(List lista, int num_bi)
{
    List aux,ant;
    int cor = 4;
    ant = lista;
    aux = lista->next;
    if(aux==NULL)
    {
        printf("\nNao existe nenhum doente na lista para consulta\n");
        return 0;
    }
    while(aux != NULL)
    {
        if(aux->bi==num_bi)
        {
            cor=aux->pulseira;
            ant->next = aux->next;
            free(aux);
            return cor;
        }
        ant = aux;
        aux = aux->next;
    }
    return cor;
}


int verifica_lista(List lista)
{
    if(lista->next == NULL)
        return 1;
    else
        return 0;
}


List imprime_proximo(List lista)
{
    List ant,atual;
    ant = lista;
    lista = lista->next;

    printf( "  | Nome: %s  | BI: %d\n  | Data: %d/%d/%d  %d:%d:%d\n  | Cor da pulseira: ",lista->nome, lista->bi, (lista->tempo_entrada).dia,(lista->tempo_entrada).mes,(lista->tempo_entrada).ano,(lista->tempo_entrada).horas,(lista->tempo_entrada).minutos,(lista->tempo_entrada).segundos);
    if(lista->pulseira == TRIAGEM_VERDE)
    {
        printf( "VERDE\n\n");
    }
    else if(lista->pulseira == TRIAGEM_LARANJA)
    {
        printf( "LARANJA\n\n");
    }
    else if(lista->pulseira == TRIAGEM_VERMELHO)
    {
        printf( "VERMELHO\n\n");
    }
    atual = ant -> next;
    ant -> next = atual -> next;
    free(atual);
    lista=ant;
    return 0;
}


void proximo_atendido(List vermelho, List laranja, List verde)
{
    if(cont_vermelho < 3 && vermelho->next != NULL)
    {
        cont_vermelho++;
        vermelho = imprime_proximo(vermelho);
    }
    else if(cont_laranja <5 && laranja->next != NULL)
    {
        cont_vermelho = 0;
        cont_laranja++;
        laranja = imprime_proximo(laranja);
    }
    else if ((vermelho->next == NULL && laranja->next == NULL && verde->next != NULL) || (laranja->next == NULL && cont_vermelho == 3 && verde->next != NULL) || (cont_laranja == 5 && verde->next != NULL))
    {
        cont_vermelho = 0;
        cont_laranja = 0;
        verde = imprime_proximo(verde);
    }
    else if(vermelho->next == NULL && laranja->next == NULL && verde->next == NULL)
    {
        printf("\n\tLista de espera vazia, não existem doentes\n\n");
    }
}

void imprime_lista(List lista)
{
    List aux = (lista -> next);
    int cont = 0;
    while (aux != NULL)
    {
        printf( "  | Nome: %s  | BI: %d\n  | Data: %d/%d/%d  %d:%d:%d\n  | Cor da pulseira: ",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);

        if(aux->pulseira == TRIAGEM_VERDE)
        {
            printf( "VERDE\n\n");
        }
        else if(aux->pulseira == TRIAGEM_LARANJA)
        {
            printf( "LARANJA\n\n");
        }
        else if(aux->pulseira == TRIAGEM_VERMELHO)
        {
            printf( "VERMELHO\n\n");
        }
        else
        {
            printf( "NAO DEFINIDO\n\n");
        }
        aux = aux -> next;
        cont++;
    }
    if(cont==0)
    {
        printf( "\tLISTA VAZIA - Nao existem pacientes registados.\n\n");
    }
}


void imprime_contrario(List lista)
{
    List aux;
    aux = lista;
    if (aux -> next == NULL)
    {
        printf("  | Nome: %s  | BI: %d\n  | Data: %d/%d/%d  %d:%d:%d\n  ",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);
    }
    else
    {
        imprime_contrario(aux->next);
        printf( "\n  | Nome: %s  | BI: %d\n  | Data: %d/%d/%d  %d:%d:%d\n  ",aux->nome, aux->bi, (aux->tempo_entrada).dia,(aux->tempo_entrada).mes,(aux->tempo_entrada).ano,(aux->tempo_entrada).horas,(aux->tempo_entrada).minutos,(aux->tempo_entrada).segundos);
    }
}


int main()
{
    int opcao=1,num_bi,numbi,aux_bi,aux_digitos,aux_cancela,vazia;
    Paciente paciente;
    List aux, root=inicia_lista();
    List verde=inicia_lista();
    List laranja=inicia_lista();
    List vermelho=inicia_lista();
    List total=inicia_lista();
    while (opcao!=11)
    {
        system("cls");
        printf(" Bruno Juliao 2014203839\tDiana Pinheiro 2014214519\n\n\t\tProjeto de PPP");
        printf("\n MENU:\n\n");
        printf("\n\t\t1-Fila para triagem");
        printf("\n\t\t2-Atribuir uma prioridade");
        printf("\n\t\t3-Cancelar um paciente para triagem");
        printf("\n\t\t4-Cancelar um paciente para consulta");
        printf("\n\t\t5-Listar os pacientes por prioridades");
        printf("\n\t\t6-Listar os pacientes por data e hora");
        printf("\n\t\t7-Determinar o proximo paciente a ser atendido");
        printf("\n\t\t8-Listar os pacientes lista verde");
        printf("\n\t\t9-Listar os pacientes lista laranja");
        printf("\n\t\t10-Listar os pacientes lista vermelha");
        printf("\n\t\t11-Sair");
        printf("\n--------------------------------------------------------------------------------");
        printf("\nQue opcao pretende escolher? ");
        scanf("%d",&opcao);
        printf("\n");
        switch(opcao)
        {
        case 1:
            printf("Nome do paciente: ");
            getchar();
            fgets(paciente.nome,MAX,stdin);
            printf("Numero do bi: ");
            scanf("%d",&paciente.bi);
            aux_digitos = conta_digitos(paciente.bi);
            if (aux_digitos == 8)
                insere_paciente(root, paciente);
            else
                printf("\n **Indroduza de o novo o paciente, o bi nao era valido**\n\n");
            break;
        case 2:
            printf("Lista de Triagem: \n");
            imprime_lista(root);
            printf("Introduza o bi do primeiro paciente da lista triagem: ");
            scanf("%d",&num_bi);
            printf("Cor da pulseira (1 - Verde | 2 - Laranja | 3 - Vermelho): ");
            scanf("%d", &paciente.pulseira);
            aux=atribui_cor(root,num_bi,paciente.pulseira, verde, laranja, vermelho, total);
            if (aux==NULL)
                printf("\n **O paciente nao esta na lista**\n");
            else
            {
                cancelar_paciente(root,num_bi);
                file_doentes(total);
                switch(paciente.pulseira)
                {
                case 1:
                    file_consultas_verde(verde);
                case 2:
                    file_consultas_laranja(laranja);
                case 3:
                    file_consultas_vermelho(vermelho);
                }
            }
            break;
        case 3:
            printf("Indroduza o BI do paciente a remover: ");
            scanf("%d",&aux_bi);
            cancelar_paciente(root,aux_bi);
            break;
        case 4:
            printf("Introduza o BI do paciente a remover: ");
            scanf("%d",&numbi);
            aux_cancela=cancelar_paciente(total,numbi);
            if (aux_cancela == 1)
                cancelar_paciente(verde,numbi);
            else if (aux_cancela == 2)
                cancelar_paciente(laranja,numbi);
            else if (aux_cancela == 3)
                cancelar_paciente(vermelho,numbi);
            else if (aux_cancela == 4)
                printf("O BI introduzido nao corresponde a nenhum paciente em espera para consulta\n");
            break;
        case 5:
            printf("Lista de pacientes: \n");
            imprime_lista(total);
            break;
        case 6:
            printf("Lista de pacientes: \n");
            vazia=verifica_lista(total);
            if (vazia==0)
                imprime_contrario(total->next);
            else
                printf("\tLISTA VAZIA - Nao existem pacientes registados.\n\n");
            break;
        case 7:
            printf("Proximo paciente a ter consulta: \n");
            proximo_atendido(vermelho,laranja,verde);
            break;
        case 8:
            printf("Lista de pacientes da lista verde: \n");
            imprime_lista(verde);
            break;
        case 9:
            printf("Lista de pacientes da lista laranja: \n");
            imprime_lista(laranja);
            break;
        case 10:
            printf("Lista de pacientes da lista vermelha: \n");
            imprime_lista(vermelho);
            break;
        case 11:
            printf("\n--------------------------------------------------------------------------------");
            printf("\n\t\t           *** Sessao terminada ***\n");
            printf("\n--------------------------------------------------------------------------------\n\n");
            exit(0);
        default:
            printf("\nIntroduza uma opcao valida (1 a 11). Prima QUALQUER TECLA para continuar.\n\n");
            break;
        }
        if(opcao<=11 && opcao>0)
        {
            printf("\nOperacao realizada com sucesso. Prima QUALQUER TECLA para continuar.\n\n");
        }
        getch();
    }
    return 0;
}
