#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<math.h>

typedef struct net{
    unsigned char dig1;
    unsigned char dig2;
    unsigned char dig3;
    unsigned char dig4;
}IP;

typedef struct maquina{
    unsigned int id;
    char marca[30];
    char modelo[30];
    char SO[30];
    char estado;
    IP ip;
}MAQUINA;

typedef struct node {
    MAQUINA pc;
    struct node *left;
    struct node *right;
}NODE;

typedef NODE * ARV_BIN_ENC;

ARV_BIN_ENC maketree(ARV_BIN_ENC, MAQUINA);
void listarNo(ARV_BIN_ENC);
ARV_BIN_ENC ins_ele(ARV_BIN_ENC, MAQUINA);
void InOrdem(ARV_BIN_ENC);
ARV_BIN_ENC left(ARV_BIN_ENC);
ARV_BIN_ENC right(ARV_BIN_ENC);
ARV_BIN_ENC brother(ARV_BIN_ENC);
ARV_BIN_ENC pesqID(ARV_BIN_ENC, int);
ARV_BIN_ENC remocaoPorCopia(ARV_BIN_ENC,int);

void cabecalho();
void fpause2();
MAQUINA lerinfos(MAQUINA);

int conta_nodoright(ARV_BIN_ENC arvaux){
    int aux ;
    for(aux = 0;arvaux; ++aux, arvaux=arvaux->right);
    return aux;
}
int conta_nodoleft(ARV_BIN_ENC arvaux){
    int aux ;
    for(aux = 0;arvaux; ++aux, arvaux=arvaux->left);
    return aux;
}

ARV_BIN_ENC rotacao_direita(ARV_BIN_ENC arvore){
    ARV_BIN_ENC aux1, aux2;
    aux1 = (arvore)->left;        
    aux2 = aux1->right;
    (arvore)->left = aux2;
    aux1->right = (arvore);
    arvore = aux1;
    return(arvore);
}

ARV_BIN_ENC rotacao_esquerda(ARV_BIN_ENC arvore){
    ARV_BIN_ENC aux1, aux2;
    aux1 = (arvore)->right;        
    aux2 = aux1->left;
    (arvore)->right = aux2;
    aux1->left = (arvore);
    arvore = aux1;
    return(arvore);
}

ARV_BIN_ENC EspinhaDorsal(ARV_BIN_ENC arvore){
    ARV_BIN_ENC tmp,father, ant;
    int aux = 1;
    father = tmp = ant = arvore;
    while(tmp){
        printf("tmp atual %d!\n",(tmp->pc).id);
        if(tmp->left){
            tmp = rotacao_direita(tmp);
            if(aux)
                father = tmp;   //GAMBIARRA
            else
                ant->right = tmp;
            printf("tmp = rotacao direita %d!\n",(tmp->pc).id);
        }else{
            aux = 0;
            ant = tmp;
            tmp = tmp->right;
            if(tmp)
                printf("tmp = right%d!\n",(tmp->pc).id);
        }
    }
    printf("father %d!\n",(father->pc).id);
    return father;
}
ARV_BIN_ENC balancearDorsal(ARV_BIN_ENC arvore){
    int n = conta_nodoright(arvore), m, i;
    ARV_BIN_ENC aux = arvore,aux2;
    m = (pow(2,floor(log2(n+1))))-1;
    printf("m = %d , n = %d \n",m,n);
    for(i=0 ; i<(n-m) ; i++){
        if(!i){
            printf("aux antes rotacao esq %d!\n",(aux->pc).id);            
            aux = rotacao_esquerda(arvore);
            arvore = aux;
            aux2= arvore;
            printf("new arv = %d!\n",(arvore->pc).id); 
        }else{           
            aux = rotacao_esquerda(aux->right);
            printf("new aux %d!\n",(aux->pc).id); 
            printf("aux2 %d!\n",(aux2->pc).id);             
            aux2->right = aux;
            aux2 = aux2->right;
            
            printf("new aux2 %d!\n",(aux2->pc).id);    
           
            if(aux->right)
                printf("aux right %d!\n",(aux->right->pc).id);            
            
        }
            printf("\naux atual %d!\n",(aux->pc).id); 
            if (aux->right)
                printf("aux atual right %d!\n",(aux->right->pc).id);   
            if (aux->left) 
                printf("aux atual left %d!\n",(aux->left->pc).id);   
            printf("arvore = %d!\n\n",(arvore->pc).id); 
            
    }
            printf("primeiro for passou! nodo direita : %d\n",conta_nodoright(arvore));            
            
    while(m>1){
        m = m/2;
        printf("m %d!\n",m);   
        printf("aux atual %d!\n",(aux->pc).id);
        aux = rotacao_esquerda(arvore);
        printf("new aux rot%d!\n",(aux->pc).id);
        arvore = aux2 = aux;
        if (aux->right)
                printf("aux atual right %d!\n",(aux->right->pc).id);   
        if (aux->left) 
                printf("aux atual left %d!\n",(aux->left->pc).id); 
        for(i=0;i< m-1;i++){
            printf("aux atual %d!\n",(aux->pc).id);
            if (aux->right)
                printf("aux atual right %d!\n",(aux->right->pc).id);   
            if (aux->left) 
                printf("aux atual left %d!\n",(aux->left->pc).id);  
            aux = rotacao_esquerda(aux->right);
            printf("new aux rot%d!\n",(aux->pc).id); 
            printf("aux2 %d!\n",(aux2->pc).id);                
            aux2->right = aux;
            aux2 = aux2->right;
            printf("new aux2 %d!\n",(aux2->pc).id);                
        }
    }
    return aux;
}

/*createPerfectTree (root, n) {
m = (2 elevado ao menor valor de lg(n+1)) -
1;
faça n –
m rotações começando da raiz;
while (m > 1) {
m = m / 2;
faça m rotações começando da raiz;
}
}
*/
ARV_BIN_ENC ALGORITMODSW(ARV_BIN_ENC arvore){
    if(arvore)
        return balancearDorsal(EspinhaDorsal(arvore)); 
    return NULL;
}


//--------------------------------------------------------------------------------------------------------
int main(){
    int menu,aux;
    ARV_BIN_ENC info = NULL,arvaux = NULL;
    MAQUINA computador;
    do{
        cabecalho();
        printf("1 - CADASTRAR COMPUTADOR\n");
        printf("2 - LISTAR EM ORDEM CRESCENTE (PERCURSO IN-ORDEM): \n");
        printf("3 - REMOVER: \n");
        printf("4 - : \n");
        printf("5 - BALANCEAR: \n");
        printf("6 - PESQUISA POR ID: \n");
        printf("7 - FILHOS A DIREITA (ESPINHA DORSAL): \n");
        printf("8 - SAIR: \n");
        scanf("%d",&menu);

        switch(menu){
            case 1:
            		cabecalho();
                    info = ins_ele(info,lerinfos(computador));
                    fpause2();
                break;
            case 2:
			        InOrdem(info);
                    fpause2();
                break;
            case 3:
                    printf("Informe o ID a ser removido: \n");
                    scanf("%d",&aux);
                    if(pesqID(info,aux)){
                        info = remocaoPorCopia(info, aux);
                        printf("Removido com sucesso!\n");
                    }else{
                        printf("ID nao encontrado na base de dados!\n");
                    }
                    fpause2();
                break;
            case 4:
                    
                   
                break;
            case 5:
                if(info){
                    info = ALGORITMODSW(info);
                    printf("Base otimizada com sucesso!\n");
                }else{
                    printf("base de dados vazia!\n");
                }
                fpause2();
                break;
            case 6:
                printf("Informe o ID a ser procurado: \n");
                scanf("%d",&aux);
                arvaux = pesqID(info, aux);
                if(!arvaux){
                    printf("ID nao encontrado! \n");
                }else{
                    listarNo(arvaux);
                }
                fpause2();   
                break;
            case 7:
                arvaux = info;
                printf("contador nivel filho direita %d e esq: %d\n",conta_nodoright(arvaux), conta_nodoleft(arvaux));
                fpause2();
                break;
            case 8:
                printf("Sistema finalizado. \n");
		        fpause2();               
              break;
            default: 
                printf("Opcao invalida\n");
               fpause2();   
        }
    }while(menu != 8);

    return 0;
}

//--------------------------------------------------------------------------------------------------------

//void buscaIDprint(ARV_BIN_ENC, int);

//void balancearArv(ARV_BIN_ENC *);


ARV_BIN_ENC remocaoPorCopia(ARV_BIN_ENC arvore,int id) {
    if(!arvore)
        return arvore;
    if (id < (arvore->pc).id)
        arvore->left = remocaoPorCopia(arvore->left, id);
    else if (id > (arvore->pc).id)
        arvore->right = remocaoPorCopia(arvore->right, id);
    else{
        ARV_BIN_ENC tmp= arvore, father;
        if ((arvore)->right == NULL){
            arvore = (arvore)->left;
            free (tmp);
            return arvore;
        }else if ((arvore)->left == NULL){
            arvore = (arvore)->right;
            free (tmp);
            return arvore;
        }
            tmp = (arvore)->left;
            father = arvore;
            while (tmp->right!=NULL) {
                father = tmp;
                tmp = tmp->right;
            }
            (arvore)->pc = tmp->pc;
            if (father==arvore)
                father->left = tmp->left;
            else
                father->right = tmp->left;
            free (tmp);
    }
        return arvore;
}
void InOrdem(ARV_BIN_ENC arv) {
    if (arv) {
        InOrdem(left(arv)); 
        listarNo(arv);
        InOrdem(right(arv)); 
    }
}

void fpause2(){                     
	setbuf(stdin,NULL);
    fflush(stdin);
	printf("Pressione alguma tecla pra continuar... \n");
	getchar();
}

MAQUINA lerinfos(MAQUINA pc){
    printf("CADASTRO DE MAQUINA: \n\n");

    printf("Informe o Numero de Serie (ID): ");
    scanf("%d",&pc.id);

    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe a Marca: ");
    scanf("%29[^\n]",pc.marca);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o modelo: ");
    scanf("%29[^\n]",pc.modelo);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o Sistema Operacional: ");
    scanf("%29[^\n]",pc.SO);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o estado atual da maquina: \nM - Manutencao. \n B - Bom estado/em uso. \n D - Deposito. \n");
    scanf("%c",&(pc).estado);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o IP da maquina: (0 a 255, com espacos)Ex: 192 168 0 20 \n");
    scanf("%d %d %d %d", &(pc.ip).dig1, &(pc.ip).dig2, &(pc.ip).dig3, &(pc.ip).dig4);

    return pc;
}

ARV_BIN_ENC maketree(ARV_BIN_ENC arv, MAQUINA comp){
	arv = (ARV_BIN_ENC) malloc (sizeof (NODE));
    if (!(arv)){
        printf("Memoria nao alocada!");
        exit(1);
    }
    (arv)->pc = comp;
    (arv)->left = NULL;
    (arv)->right = NULL;
}

void listarNo(ARV_BIN_ENC arv){
    printf("\n-----------------------------------------------------------------\n");
    printf("Numero de Serie (ID): %d\n\n",((arv)->pc).id);
    printf("Marca: %s\n",((arv)->pc).marca);
    printf("Modelo: %s\n",((arv)->pc).modelo);
    printf("Sistema Operacional: %s\n",((arv)->pc).SO);
    printf("Estado da Maquina: ");
    if(((arv->pc).estado == 'M') || ((arv->pc).estado == 'm'))
        printf("M - Manutencao.\n");
    else if(((arv->pc).estado == 'B') || ((arv->pc).estado == 'b'))
        printf("B - Bom estado / Em uso.\n");
    else
         printf("D - Deposito.\n");
    printf("IP: %d.%d.%d.%d \n", ((arv)->pc).ip.dig1, ((arv)->pc).ip.dig2, ((arv)->pc).ip.dig3, ((arv)->pc).ip.dig4);

    printf("\n-----------------------------------------------------------------\n");
}



ARV_BIN_ENC ins_ele(ARV_BIN_ENC arv, MAQUINA comp){ //recursiva, ubuntu
    if (!(arv)){
        return maketree(arv,comp);
    }
    if ((comp.id) < ((arv->pc).id))
        (arv)->left = ins_ele(arv->left, comp);
    else
        (arv)->right = ins_ele(arv->right, comp);
    return(arv);
}
ARV_BIN_ENC pesqID(ARV_BIN_ENC arv, int id){
     if (!(arv))
        printf("Não consta no cadastro! \n");
    else{ 
        while(arv){
            if (id < ((arv->pc).id)){
                arv = arv->left;    
            }else{
                if(id == ((arv->pc).id)){   
                    return arv;
                    break;
                }
                arv = arv->right;
            }
        }  
        return NULL;
    }
}

ARV_BIN_ENC left(ARV_BIN_ENC arv){
    return arv->left;
}
ARV_BIN_ENC right(ARV_BIN_ENC arv){
    return arv->right;
}


void cabecalho(){
    system("clear > nul"); //verificar ubuntu
    system("cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}

