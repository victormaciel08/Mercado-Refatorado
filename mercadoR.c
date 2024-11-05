#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 50

typedef struct {
    int cod;
    char nome[30];
    float preco;
    int qntEstq;
} Produto;

typedef struct {
    Produto produto;
    int qntCarrinho;
} Carrinho;

typedef struct {
    Produto produtos[MAX_PRODUTOS];
    Carrinho carrinho[MAX_PRODUTOS];
    int qntProdutos;
    int qntCarrinho;
} Loja;

void limparTela();
void exibirProduto(Produto p);
void exibirMenu();
void cadastrarProduto(Loja *loja);
void listarProdutos(Loja *loja);
void adicionarEstoque(Loja *loja);
void buscarProdutoPorCodigo(Loja *loja);
void comprarProduto(Loja *loja);
void visualizarCarrinho(Loja *loja);
void limparCarrinho(Loja *loja);
void fecharPedido(Loja *loja);

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    Loja loja = { .qntProdutos = 0, .qntCarrinho = 0 };
    int opcao;

    while (1) {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1:
                cadastrarProduto(&loja);
                break;
            case 2:
                adicionarEstoque(&loja);
                break;
            case 3:
                listarProdutos(&loja);
                break;
            case 4:
                comprarProduto(&loja);
                break;
            case 5:
                visualizarCarrinho(&loja);
                break;
            case 6:
                limparCarrinho(&loja);
                break;
            case 7:
                fecharPedido(&loja);
                break;
            case 8:
                printf("Até a próxima!\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        limparTela();
    }
}

void exibirMenu() {
    printf("-------------MENU-------------\n");
    printf("(1) Cadastrar Produto\n");
    printf("(2) Adicionar ao Estoque\n");
    printf("(3) Listar Produtos\n");
    printf("(4) Comprar Produto\n");
    printf("(5) Visualizar Carrinho\n");
    printf("(6) Limpar Carrinho\n");
    printf("(7) Fechar Pedido\n");
    printf("(8) Sair\n");
}

void exibirProduto(Produto p) {
    printf("Código: %d\n", p.cod);
    printf("Nome: %s\n", p.nome);
    printf("Preço: %.2f\n", p.preco);
    printf("Quantidade em Estoque: %d\n", p.qntEstq);
    printf("--------------------------\n");
}

void cadastrarProduto(Loja *loja) {
    int quantidade;
    printf("Quantos produtos deseja cadastrar? ");
    scanf("%d", &quantidade);
    limparTela();

    for (int i = 0; i < quantidade && loja->qntProdutos < MAX_PRODUTOS; i++) {
        Produto *p = &loja->produtos[loja->qntProdutos++];
        p->cod = loja->qntProdutos;
        
        printf("Digite o nome do produto: ");
        scanf(" %[^\n]", p->nome);
        
        printf("Digite o preço do produto: ");
        scanf("%f", &p->preco);
        
        printf("Digite a quantidade em estoque: ");
        scanf("%d", &p->qntEstq);
        limparTela();
    }
    printf("Cadastro concluído!\n");
}

void listarProdutos(Loja *loja) {
    printf("Produtos cadastrados:\n");
    for (int i = 0; i < loja->qntProdutos; i++) {
        exibirProduto(loja->produtos[i]);
    }
}

void adicionarEstoque(Loja *loja) {
    int cod, quantidade;
    listarProdutos(loja);
    printf("Digite o código do produto para adicionar estoque: ");
    scanf("%d", &cod);

    printf("Quantidade a adicionar: ");
    scanf("%d", &quantidade);
    limparTela();

    if (cod > 0 && cod <= loja->qntProdutos) {
        loja->produtos[cod - 1].qntEstq += quantidade;
        printf("Estoque atualizado.\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

void buscarProdutoPorCodigo(Loja *loja) {
    int cod;
    printf("Digite o código do produto: ");
    scanf("%d", &cod);
    limparTela();

    if (cod > 0 && cod <= loja->qntProdutos) {
        exibirProduto(loja->produtos[cod - 1]);
    } else {
        printf("Produto não encontrado.\n");
    }
}

void limparTela() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    system("clear");
}
