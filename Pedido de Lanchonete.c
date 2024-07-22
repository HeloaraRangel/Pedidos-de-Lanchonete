    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <windows.h>
    #define MAX 100

    struct Lanche 
    {
        char nome[MAX], ingredientes[MAX];
        float preco;
    };
    typedef struct Lanche Lanche;

    struct Pedido 
    {
        int num_Pedido, qt_Lanche;
        char nome_Cliente[MAX];
        Lanche lanche;
    };
    typedef struct Pedido Pedido;

    int pesquisar (Pedido *p, int *cont, int numero_pedido) 
    {
        int i;
        for (i = 0; i < *cont; i++) 
        {
            if (p[i].num_Pedido == numero_pedido) 
            {
                return i;
            }
        }
        return -1;
    }

    void lerPedido(Pedido *p) 
    {
        do {
        printf("Digite a quantidade do lanche: ");
        scanf("%d", &p->qt_Lanche);
        } while (p -> qt_Lanche < 1) ;
        
        printf("Digite o nome do cliente: ");
        scanf(" %99[^\n]s", p->nome_Cliente);
        
        printf("\nDADOS DO LANCHE\n");
        
        printf("Digite o nome do lanche: ");
        scanf(" %99[^\n]s", p->lanche.nome);
        
        printf("Digite os ingredientes: ");
        scanf(" %99[^\n]s", p->lanche.ingredientes);
        
        do {
        printf("Digite o preço do lanche: ");
        scanf("%f", &p->lanche.preco);
        } while (p -> lanche.preco < 1) ;
    }

    int num_dos_pedidos () 
    {
        int numero_pedido;
        printf("\nDigite o número do pedido: ");
        scanf("%d", & numero_pedido);
    return numero_pedido;
    }

    void inserir(Pedido *p, int *cont) 
    {
        int numero_pedido, pesquisa;
        
        numero_pedido = num_dos_pedidos();
        
        pesquisa = pesquisar(p, cont, numero_pedido);
        
        if (pesquisa != -1) 
        {
            printf("Número já existente!\n");
        }
        else 
        {
            p[*cont].num_Pedido = numero_pedido;
            lerPedido(&p[*cont]);
            (*cont)++;
        }
    }

    void imprimir (Pedido *p, int i) 
    {
            printf("\nPedido %d - Número do pedido: %d \n", i + 1, p[i].num_Pedido);
            printf("Nome do cliente: %s\n", p[i].nome_Cliente);
            printf("Nome do lanche: %s\n", p[i].lanche.nome);
            printf("Ingredientes: %s\n", p[i].lanche.ingredientes);
            printf("Preço do lanche: %.2f\n", p[i].lanche.preco);
            printf("Quantidade do lanche: %d\n", p[i].qt_Lanche);
            printf("Preço total: %.2f R$\n", p[i].lanche.preco * p[i].qt_Lanche);
    }

    void pedidos_registrados (Pedido *p, int *cont) 
    {
        int i;
        printf("Números dos pedidos registrados\n");
        for (i=0; i < *cont; i++) 
        {
            if (i == 0 || p[i].num_Pedido != p[i - 1].num_Pedido) 
            {
                printf("%d\t", p[i].num_Pedido);
            }
        }
    }

    void pesquisarPorNumero(Pedido *p, int cont) 
    {
        int numero_pedido;

        pedidos_registrados(p, &cont);
        
        numero_pedido = num_dos_pedidos();
        
        int pesquisa = pesquisar(p, &cont, numero_pedido);
    
        if (pesquisa != -1) 
        {
            imprimir (p, pesquisa);
        }
        else 
        {
            printf("Pedido não encontrado\n");
        }
    }

    void pesquisarPorNome(Pedido *p, int cont) 
    {
        int i;
        char nome_Pesquisa[MAX];
        int encontrados = 0;
    
        printf("\nDigite o nome do cliente que deseja pesquisar: ");
        scanf(" %99[^\n]s", nome_Pesquisa);
    
        for (i = 0; i < cont; i++) 
        {
            if (strcmp(p[i].nome_Cliente, nome_Pesquisa) == 0) 
            {
                imprimir (p, i);
                encontrados = 1;
            }
        }

        if (encontrados == 0) 
        {
            printf("Nenhum pedido encontrado para o cliente com o nome '%s'.\n", nome_Pesquisa);
        }
    }

    void atualizar(Pedido *p, int cont) 
    {
        int numero_pedido, pesquisa;
        
        pedidos_registrados(p, &cont);
        
        numero_pedido = num_dos_pedidos();
        
        pesquisa = pesquisar(p, &cont, numero_pedido);
        
        if (pesquisa != -1) 
        {
            printf("Digite a nova quantidade do lanche: ");
            scanf("%d", &p[pesquisa].qt_Lanche);
            printf("Atualizado com sucesso!\n");
        }
        else 
        {
            printf("Pedido não encontrado\n");
        }
    }

    void maior(Pedido *p, int cont) 
    {
        int i, indic_maior = 0;
        float maior = p[0].lanche.preco * p[0].qt_Lanche, valor_atual;

        printf("\nPedido com maior valor");
        for (i = 1; i < cont; i++) 
        {
            valor_atual = p[i].lanche.preco * p[i].qt_Lanche;
            if (valor_atual > maior) 
            {
                maior = valor_atual;
                indic_maior = i;
            }
        }
        
        imprimir (p, indic_maior);
    }

    void remover (Pedido *vetor, int **qtde, int pos) 
    {
        int i;
        for (i = pos; i < **qtde- 1; i++) {
        vetor[i] = vetor[i+1];
        }
        (**qtde)--;
    }


    void excluir(Pedido *p, int *cont) 
    {
        int numero_pedido, pesquisa;
        
        pedidos_registrados(p, cont);
        
        numero_pedido = num_dos_pedidos();
        
        pesquisa = pesquisar(p, cont, numero_pedido);
        
        if (pesquisa != -1) 
        {
            remover(p, &cont, pesquisa);
            printf("Excluído com sucesso\n");
        }
        else 
        {
            printf("Pedido não encontrado\n");
        }
    }

    void listar(Pedido *p, int cont) 
    {
        int i;
        printf("\nNúmero de pedidos registrados: %d\n", cont);
    
        for (i = 0; i < cont; i++) 
        {
            if (i == 0 || p[i].num_Pedido != p[i - 1].num_Pedido) 
            {
                imprimir (p, i);
            }
        }

    }

int menu() 
{
    int op;
    
    printf("\nPedido de Lanchonete\n");
    printf("1 - Inserir pedido\n");
    printf("2 - Pesquisar por número\n");
    printf("3 - Pesquisar por nome\n");
    printf("4 - Atualizar\n");
    printf("5 - Maior\n");
    printf("6 - Excluir\n");
    printf("7 - Listar pedidos\n");
    printf("0 - Sair\n");
    
    do 
    {
        printf("Escolha sua opção: ");
        scanf(" %d", & op);
    } while (op < 0 || op > 7);
    
    return op;
}

FILE * abrirArquivo(char * Pedidos, char * rb) {
    // ABRIR o arquivo
    FILE * arq;
    arq = fopen( Pedidos, rb );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

void gravarArquivo(FILE * arquivo, Pedido * vetProd, int qtde) {

    fwrite( &qtde, sizeof(int), 1, arquivo  );
    fwrite( vetProd, sizeof(Pedido), qtde, arquivo  );

}

void carregarArquivo(FILE * arquivo, Pedido * vetProd, int *qtde) {

    fread( qtde, sizeof(int), 1, arquivo  );
    fread( vetProd, sizeof(Pedido), *qtde, arquivo  );
}

int main() 
{
    SetConsoleOutputCP(65001);
    FILE * arq;
    int op, cont = 0;
    Pedido pedidos[MAX];
    
    arq = abrirArquivo("Pedidos.bin" , "rb");
    
    carregarArquivo(arq, pedidos, &cont);
    
    while ( ! feof(arq) ) {
        fread(pedidos,  sizeof(Pedido), 1, arq );
    }

    do {
        op = menu();
        switch (op) {
            case 0:
                // SAIR. NÃO PRECISA FAZER NADA
                arq = abrirArquivo("Pedidos.bin" , "wb");
                gravarArquivo(arq, pedidos, cont);
                fclose(arq);
                break;
            case 1:
                // INSERIR PEDIDO
                inserir(pedidos, &cont);
                arq = abrirArquivo("Pedidos.bin" , "wb");
                gravarArquivo(arq, pedidos, cont);
                fclose(arq);
                break;
            case 2:
                // PESQUISAR POR NÚMERO
                pesquisarPorNumero(pedidos, cont);
                break;
            case 3:
                // PESQUISAR POR NOME
                pesquisarPorNome(pedidos, cont);
                break;
            case 4:
                // ATUALIZAR
                atualizar(pedidos, cont);
                break;
            case 5:
                // MAIOR
                maior(pedidos, cont);
                break;
            case 6:
                // EXCLUIR
                excluir(pedidos, &cont);
                break;
            case 7:
                // LISTAR PEDIDOS
                carregarArquivo(arq, pedidos, &cont);
                listar(pedidos, cont);
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (op != 0);
    
    return 0;
}