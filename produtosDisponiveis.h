//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_PRODUTOSDISPONIVEIS_H
#define HOTEL_PRODUTOSDISPONIVEIS_H

#endif //HOTEL_PRODUTOSDISPONIVEIS_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structProdutosConsumo
{
    int codigo;
    char descricao[CHAR_G];
    int estoque;
    int estoqueMinimo;
    float precoCusto;
    float precoVenda;
} structProdutosConsumo;

int verificarCodigoProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos);

void cadastrarProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos);

void gerarArqProdutos(structProdutosConsumo *produtosConsumoDados, int quantidadesProdutos, FILE *arqQtdProdutos, FILE *arqDadosProdutos);

void exibirProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos);

void listarProdutos(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos);

void atualizarProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos,
                      FILE *arqDadosProdutos);

void deletarProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos,
                    FILE *arqQtdProdutos, FILE *arqDadosProdutos);
