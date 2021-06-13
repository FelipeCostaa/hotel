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

int verificaCodigoCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados, int *quantidadeCategorias)
{
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    if ((categoriaAcomodacao + i)->codigo == categoriaAcomodacaoDados->codigo)
    {
      return 1; // o codigo ja foi cadastrado
    }
  }
  return 0;
}

int retornaPosicaoCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados, int *quantidadeCategorias)
{
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    if ((categoriaAcomodacao + i)->codigo == categoriaAcomodacaoDados->codigo)
    {
      return i;
    }
  }
}

void cadastrarCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados, int *quantidadeCategorias)
{
  (categoriaAcomodacao + (*quantidadeCategorias))->codigo = categoriaAcomodacaoDados->codigo;
  strcpy((categoriaAcomodacao + (*quantidadeCategorias))->descricao, categoriaAcomodacaoDados->descricao);
  (categoriaAcomodacao + (*quantidadeCategorias))->valorDiaria = categoriaAcomodacaoDados->valorDiaria;
  (categoriaAcomodacao + (*quantidadeCategorias))->quantMaxDePessoas = categoriaAcomodacaoDados->quantMaxDePessoas;
  (*quantidadeCategorias)++;
}

void gerarArqCategoria(structCategoriaAcomodacao *categoriaAcomodacaoDados, int quantidadeCategorias, FILE *arqQtdCategorias, FILE *arqDadosCategorias)
{
  arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias", "a+b");
  fwrite(categoriaAcomodacaoDados, sizeof(structCategoriaAcomodacao), 1, arqDadosCategorias);
  fflush(arqDadosCategorias);
  fclose(arqDadosCategorias);

  arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias.txt", "a+");
  fprintf(arqDadosCategorias, "%d,", categoriaAcomodacaoDados->codigo);
  fprintf(arqDadosCategorias, "%s,", categoriaAcomodacaoDados->descricao);
  fprintf(arqDadosCategorias, "%f,", categoriaAcomodacaoDados->valorDiaria);
  fprintf(arqDadosCategorias, "%d\n", categoriaAcomodacaoDados->quantMaxDePessoas);
  fflush(arqDadosCategorias);
  fclose(arqDadosCategorias);

  arqQtdCategorias = fopen("..//arqQuantidades//arqQtdCategorias.txt", "w+");
  fprintf(arqQtdCategorias, "%d", quantidadeCategorias);
  fflush(arqQtdCategorias);
  fclose(arqQtdCategorias);
}

void exibeCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados, int *quantidadeCategorias)
{
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    if (categoriaAcomodacaoDados->codigo == (categoriaAcomodacao + i)->codigo)
    {
      printf("\nCodigo: %d", (categoriaAcomodacao + i)->codigo);
      printf("\nDescrição: %s", (categoriaAcomodacao + i)->descricao);
      printf("\nValor da diaria: R$%.2f", (categoriaAcomodacao + i)->valorDiaria);
      printf("\nQuantidade de pessoas suportadas: %d", (categoriaAcomodacao + i)->quantMaxDePessoas);
      printf("\n");
    }
  }
}

void listarCategorias(structCategoriaAcomodacao *categoriaAcomodacao, int *quantidadeCategorias)
{
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    printf("\nCodigo: %d", (categoriaAcomodacao + i)->codigo);
    printf("\nDescrição: %s", (categoriaAcomodacao + i)->descricao);
    printf("\nValor da diaria: R$%.2f", (categoriaAcomodacao + i)->valorDiaria);
    printf("\nQuantidade de pessoas suportadas: %d", (categoriaAcomodacao + i)->quantMaxDePessoas);
    printf("\n--------------------------------------\n");
  }
}

void atualizarCategorias(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados, int *quantidadeCategorias, FILE *arqDadosCategorias)
{
  arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias", "w+");
  fclose(arqDadosCategorias);
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    if ((categoriaAcomodacao + i)->codigo == categoriaAcomodacaoDados->codigo)
    {
      (categoriaAcomodacao + i)->codigo = categoriaAcomodacaoDados->codigo;
      strcpy((categoriaAcomodacao + i)->descricao, categoriaAcomodacaoDados->descricao);
      (categoriaAcomodacao + i)->valorDiaria = categoriaAcomodacaoDados->valorDiaria;
      (categoriaAcomodacao + i)->quantMaxDePessoas = categoriaAcomodacaoDados->quantMaxDePessoas;
    }
    arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias", "a+b");
    fwrite(arqDadosCategorias + i, sizeof(structCategoriaAcomodacao), 1, arqDadosCategorias);
    fflush(arqDadosCategorias);
    fclose(arqDadosCategorias);
  }
}

void deletarCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados, int *quantidadeCategorias, FILE *arqQtdCategorias, FILE *arqDadosCategorias)
{
  arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias", "w+");
  fclose(arqDadosCategorias);
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    if ((categoriaAcomodacao + i)->codigo == categoriaAcomodacaoDados->codigo)
    {
      for (int j = i; j < (*quantidadeCategorias); ++j)
      {
        (categoriaAcomodacao + j)->codigo = (categoriaAcomodacao + j + 1)->codigo;
        strcpy((categoriaAcomodacao + j)->descricao, (categoriaAcomodacao + j + 1)->descricao);
        (categoriaAcomodacao + j)->valorDiaria = (categoriaAcomodacao + j + 1)->valorDiaria;
        (categoriaAcomodacao + j)->quantMaxDePessoas = (categoriaAcomodacao + j + 1)->quantMaxDePessoas;
      }
    }
    arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias", "a+b");
    fwrite(arqDadosCategorias + i, sizeof(structCategoriaAcomodacao), 1, arqDadosCategorias);
    fflush(arqDadosCategorias);
    fclose(arqDadosCategorias);
  }
  (*quantidadeCategorias)--;

  arqQtdCategorias = fopen("..//arqQuantidades//arqQtdCategorias.txt", "w+"); //altera a quandidade de hospedes
  fprintf(arqQtdCategorias, "%d", (*quantidadeCategorias));
  fflush(arqQtdCategorias);
  fclose(arqQtdCategorias);
}
