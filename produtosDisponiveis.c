//
// Created by felipe on 27/01/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hotel.h"
#include "hospede.h"
#include "acomodacao.h"
#include "categoriaAcomodacao.h"
#include "fornecedor.h"
#include "operadorSistema.h"
#include "produtosDisponiveis.h"

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

int verificarCodigoProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos)
{
  for (int i = 0; i < (*quantidadeProdutos); ++i)
  {
    if (produtosConsumoDados->codigo == (produtosConsumo + i)->codigo)
    {
      return 1;
    }
  }
  return 0;
}

void cadastrarProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos)
{
  (produtosConsumo + (*quantidadeProdutos))->codigo = produtosConsumoDados->codigo;
  strcpy((produtosConsumo + (*quantidadeProdutos))->descricao, produtosConsumoDados->descricao);
  (produtosConsumo + (*quantidadeProdutos))->estoque = produtosConsumoDados->estoque;
  (produtosConsumo + (*quantidadeProdutos))->estoqueMinimo = produtosConsumoDados->estoqueMinimo;
  (produtosConsumo + (*quantidadeProdutos))->precoCusto = produtosConsumoDados->precoCusto;
  (produtosConsumo + (*quantidadeProdutos))->precoVenda = produtosConsumoDados->precoVenda;
  (*quantidadeProdutos)++;
}

void gerarArqProdutos(structProdutosConsumo *produtosConsumoDados, int quantidadesProdutos, FILE *arqQtdProdutos, FILE *arqDadosProdutos)
{
  arqDadosProdutos = fopen("..//bancoDeDados//arqDadosProdutos", "a+b"); // binario
  fwrite(produtosConsumoDados, sizeof (structProdutosConsumo), 1, arqDadosProdutos);
  fflush(arqDadosProdutos);
  fclose(arqDadosProdutos);

  arqDadosProdutos = fopen("..//bancoDeDados//arqDadosProdutos.txt", "a+");
  fprintf(arqDadosProdutos, "%d,", produtosConsumoDados->codigo);
  fprintf(arqDadosProdutos, "%s,", produtosConsumoDados->descricao);
  fprintf(arqDadosProdutos, "%d,", produtosConsumoDados->estoque);
  fprintf(arqDadosProdutos, "%d,", produtosConsumoDados->estoqueMinimo);
  fprintf(arqDadosProdutos, "%f,", produtosConsumoDados->precoCusto);
  fprintf(arqDadosProdutos, "%f\n", produtosConsumoDados->precoVenda);
  fflush(arqDadosProdutos);
  fclose(arqDadosProdutos);

  arqQtdProdutos = fopen("../arqQuantidades//arqQtdProdutos.txt", "w+"); // texto
  fprintf(arqQtdProdutos, "%d", quantidadesProdutos);
  fflush(arqQtdProdutos);
  fclose(arqQtdProdutos);
}

void exibirProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos)
{
  for (int i = 0; i < (*quantidadeProdutos); ++i)
  {
    if ((produtosConsumo + i)->codigo == produtosConsumoDados->codigo)
    {
      printf("\nCodigo: %d", (produtosConsumo + i)->codigo);
      printf("\nDescrição: %s", (produtosConsumo + i)->descricao);
      printf("\nEstoque: %d", (produtosConsumo + i)->estoque);
      printf("\nEstoque minimo: %d", (produtosConsumo + i)->estoqueMinimo);
      printf("\nPreço de custo: R$%.2f", (produtosConsumo + i)->precoCusto);
      printf("\nPreço de venda: R$%.2f", (produtosConsumo + i)->precoVenda);
      printf("\n");
    }
  }
}

void listarProdutos(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos)
{
  for (int i = 0; i < (*quantidadeProdutos); ++i)
  {
    printf("\nCodigo: %d", (produtosConsumo + i)->codigo);
    printf("\nDescrição: %s", (produtosConsumo + i)->descricao);
    printf("\nEstoque: %d", (produtosConsumo + i)->estoque);
    printf("\nEstoque minimo: %d", (produtosConsumo + i)->estoqueMinimo);
    printf("\nPreço de custo: R$%.2f", (produtosConsumo + i)->precoCusto);
    printf("\nPreço de venda: R$%.2f", (produtosConsumo + i)->precoVenda);
    printf("\n--------------------------------------\n");
  }
}

void atualizarProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos, FILE *arqDadosProdutos)
{
  arqDadosProdutos = fopen("../bancoDeDados//arqDadosProdutos", "w+");
  fclose(arqDadosProdutos);
  for (int i = 0; i < (*quantidadeProdutos); ++i)
  {
    if ((produtosConsumo + i)->codigo == produtosConsumoDados->codigo)
    {
      strcpy((produtosConsumo + i)->descricao, produtosConsumoDados->descricao);
      (produtosConsumo + i)->estoque = produtosConsumoDados->estoque;
      (produtosConsumo + i)->estoqueMinimo = produtosConsumoDados->estoqueMinimo;
      (produtosConsumo + i)->precoCusto = produtosConsumoDados->precoCusto;
      (produtosConsumo + i)->precoVenda = produtosConsumoDados->precoVenda;
    }
    arqDadosProdutos = fopen("..//bancoDeDados//arqDadosProdutos", "a+b");
    fwrite(produtosConsumoDados + 1, sizeof(structProdutosConsumo), 1, arqDadosProdutos);
    fflush(arqDadosProdutos);
    fclose(arqDadosProdutos);
  }
}

void deletarProduto(structProdutosConsumo *produtosConsumo, structProdutosConsumo *produtosConsumoDados, int *quantidadeProdutos, FILE *arqQtdProdutos, FILE *arqDadosProdutos)
{
  arqDadosProdutos = fopen("../bancoDeDados//arqDadosProdutos", "w+");
  fclose(arqDadosProdutos);
  for (int i = 0; i < (*quantidadeProdutos); ++i)
  {
    if ((produtosConsumo + i)->codigo == produtosConsumoDados->codigo)
    {
      for (int j = i; j < (*quantidadeProdutos); ++j)
      {
        (produtosConsumo + j)->codigo = (produtosConsumo + j + 1)->codigo;
        strcpy((produtosConsumo + j)->descricao, (produtosConsumo + j + 1)->descricao);
        (produtosConsumo + j)->estoque = (produtosConsumo + j + 1)->estoque;
        (produtosConsumo + j)->estoqueMinimo = (produtosConsumo + j + 1)->estoqueMinimo;
        (produtosConsumo + j)->precoCusto = (produtosConsumo + j + 1)->precoCusto;
        (produtosConsumo + j)->precoVenda = (produtosConsumo + j + 1)->precoVenda;
      }
    }
    arqDadosProdutos = fopen("..//bancoDeDados//arqDadosProdutos", "a+b");
    fwrite(produtosConsumo + i, sizeof(structProdutosConsumo), 1, arqDadosProdutos);
    fflush(arqDadosProdutos);
    fclose(arqDadosProdutos);
  }
  (*quantidadeProdutos)--;

  arqQtdProdutos = fopen("..//arqQuantidades//arqQtdProdutos.txt", "w+");
  fprintf(arqQtdProdutos, "%d", (*quantidadeProdutos));
  fflush(arqQtdProdutos);
  fclose(arqQtdProdutos);
}
