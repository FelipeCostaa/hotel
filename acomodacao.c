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

int verificarCodigoAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes)
{
  for (int i = 0; i < (*quantidadeAcomodacoes); ++i)
  {
    if ((acomodacao + i)->codigo == acomodacaoDados->codigo)
    {
      return 1; // codigo ja cadastrado
    }
  }
  return 0;
}

int retornaPosicaoAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes)
{
  for (int i = 0; i < (*quantidadeAcomodacoes); ++i)
  {
    if ((acomodacao + i)->codigo == acomodacaoDados->codigo)
    {
      return i;
    }
  }
}

void cadastrarAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes)
{
  (acomodacao + (*quantidadeAcomodacoes))->codigo = acomodacaoDados->codigo;
  strcpy((acomodacao + (*quantidadeAcomodacoes))->descricao, acomodacaoDados->descricao);
  strcpy((acomodacao + (*quantidadeAcomodacoes))->facilidades, acomodacaoDados->facilidades);
  (acomodacao + (*quantidadeAcomodacoes))->categoria = acomodacaoDados->categoria;
  (*quantidadeAcomodacoes)++;
}

void gerarArqAcomodacao(structAcomodacao *acomodacaoDados, int quantidadeAcomodacoes, FILE *arqQtdAcomodacoes, FILE *arqDadosAcomodacoes)
{
  arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes", "a+b");
  fwrite(acomodacaoDados, sizeof(structAcomodacao), 1, arqDadosAcomodacoes);
  fflush(arqDadosAcomodacoes);
  fclose(arqDadosAcomodacoes);

  arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes.txt", "a+");
  fprintf(arqDadosAcomodacoes, "%d,",acomodacaoDados->codigo);
  fprintf(arqDadosAcomodacoes, "%s,",acomodacaoDados->descricao);
  fprintf(arqDadosAcomodacoes, "%s,",acomodacaoDados->facilidades);
  fprintf(arqDadosAcomodacoes, "%d\n",acomodacaoDados->categoria);
  fflush(arqDadosAcomodacoes);
  fclose(arqDadosAcomodacoes);

  arqQtdAcomodacoes = fopen("..//arqQuantidades//arqQtdAcomodacoes.txt", "w+");
  fprintf(arqQtdAcomodacoes, "%d", quantidadeAcomodacoes);
  fflush(arqQtdAcomodacoes);
  fclose(arqQtdAcomodacoes);
}

void exibeAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes)
{
  for (int i = 0; i < (*quantidadeAcomodacoes); ++i)
  {
    if ((acomodacao + i)->codigo == acomodacaoDados->codigo)
    {
      printf("\nCodigo: %d", (acomodacao + i)->codigo);
      printf("\nDescrição: %s", (acomodacao + i)->descricao);
      printf("\nFacilidades: %s", (acomodacao + i)->facilidades);
      printf("\nCategocia: %d", (acomodacao + i)->categoria);
      printf("\n");
    }
  }
}

void listarAcomodacoes(structAcomodacao *acomodacao, int *quantidadeAcomodacoes)
{
  for (int i = 0; i < (*quantidadeAcomodacoes); ++i)
  {
    printf("\nCodigo: %d", (acomodacao + i)->codigo);
    printf("\nDescrição: %s", (acomodacao + i)->descricao);
    printf("\nFacilidades: %s", (acomodacao + i)->facilidades);
    printf("\nCategoria: %d", (acomodacao + i)->categoria);
    printf("\n--------------------------------------\n");
  }
}

void atualizarAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes, FILE *arqDadosAcomodacoes)
{
  arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes", "w+");
  fclose(arqDadosAcomodacoes);
  for (int i = 0; i < (*quantidadeAcomodacoes); ++i)
  {
    if ((acomodacao + i)->codigo == acomodacaoDados->codigo)
    {
      (acomodacao + i)->codigo = acomodacaoDados->codigo;
      strcpy((acomodacao + i)->descricao, acomodacaoDados->descricao);
      strcpy((acomodacao + i)->facilidades, acomodacaoDados->facilidades);
      (acomodacao + i)->categoria = acomodacaoDados->categoria;
    }
    arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes", "a+b");
    fwrite(acomodacao + i, sizeof(structAcomodacao), 1, arqDadosAcomodacoes);
    fflush(arqDadosAcomodacoes);
    fclose(arqDadosAcomodacoes);
  }
}

void deletarAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes, FILE *arqQtdAcomodacoes, FILE *arqDadosAcomodacoes)
{
  arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes", "w+");
  fclose(arqDadosAcomodacoes);
  for (int i = 0; i < (*quantidadeAcomodacoes); ++i)
  {
    if ((acomodacao + i)->codigo == acomodacaoDados->codigo)
    {
      for (int j = i; j < (*quantidadeAcomodacoes); ++j)
      {
        (acomodacao + j)->codigo = (acomodacao + j + 1)->codigo;
        strcpy((acomodacao + j)->descricao, (acomodacao + j + 1)->descricao);
        strcpy((acomodacao + j)->facilidades, (acomodacao + j + 1)->facilidades);
        (acomodacao + j)->categoria = (acomodacao + j + 1)->categoria;
      }
    }
    arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes", "a+b");
    fwrite(acomodacao + i, sizeof(structAcomodacao), 1, arqDadosAcomodacoes);
    fflush(arqDadosAcomodacoes);
    fclose(arqDadosAcomodacoes);
  }
  (*quantidadeAcomodacoes)--;

  arqQtdAcomodacoes = fopen("..//arqQuantidades//arqQtdAcomodacoes.txt", "w+");
  fprintf(arqQtdAcomodacoes, "%d", (*quantidadeAcomodacoes));
  fflush(arqQtdAcomodacoes);
  fclose(arqQtdAcomodacoes);
}
