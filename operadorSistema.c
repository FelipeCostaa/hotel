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

int verificarCodigoOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados, int *quantidadeOperadores)
{
  for (int i = 0; i < (*quantidadeOperadores); ++i)
  {
    if ((operadoresSistema + i)->codigo == operadoresSistemaDados->codigo)
    {
      return 1;
    }
  }
  return 0;
}

int verificarUsuarioOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados, int *quantidadeOperadores)
{
  for (int i = 0; i < (*quantidadeOperadores); ++i)
  {
    if (strcmp(((operadoresSistema + i)->usuario), operadoresSistemaDados->usuario) == 0)
    {
      return 1; // usuario já cadastrado
    }
  }
  return 0;
}

void cadastrarOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados, int *quantidadeOperadores)
{
  (operadoresSistema + (*quantidadeOperadores))->codigo = operadoresSistemaDados->codigo;
  strcpy((operadoresSistema + (*quantidadeOperadores))->nome, operadoresSistemaDados->nome);
  strcpy((operadoresSistema + (*quantidadeOperadores))->usuario, operadoresSistemaDados->usuario);
  strcpy((operadoresSistema + (*quantidadeOperadores))->senha, operadoresSistemaDados->senha);
  (operadoresSistema + (*quantidadeOperadores))->permissoes = operadoresSistemaDados->permissoes;
  (*quantidadeOperadores)++;
}

void gerarArqOperador(structOperadoresSistema *operatoresSistemaDados, int quantidadeOperadores, FILE *arqQtdOperadores, FILE *arqDadosOperadores)
{
  arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores", "a+b");
  fwrite(operatoresSistemaDados, sizeof (structOperadoresSistema),1,arqDadosOperadores);
  fflush(arqDadosOperadores);
  fclose(arqDadosOperadores);

  arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores.txt", "a+");
  fprintf(arqDadosOperadores, "%d,", operatoresSistemaDados->codigo);
  fprintf(arqDadosOperadores, "%s,", operatoresSistemaDados->nome);
  fprintf(arqDadosOperadores, "%s,", operatoresSistemaDados->usuario);
  fprintf(arqDadosOperadores, "%s,", operatoresSistemaDados->senha);
  fprintf(arqDadosOperadores, "%d\n", operatoresSistemaDados->permissoes);
  fflush(arqDadosOperadores);
  fclose(arqDadosOperadores);

  arqQtdOperadores = fopen("..//arqQuantidades//arqQtdOperadores.txt", "w+");
  fprintf(arqQtdOperadores, "%d", quantidadeOperadores);
  fflush(arqQtdOperadores);
  fclose(arqQtdOperadores);
}

void exibeOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados, int *quantidadeOperadores)
{
  for (int i = 0; i < (*quantidadeOperadores); ++i)
  {
    if ((operadoresSistema + i)->codigo == operadoresSistemaDados->codigo)
    {
      printf("\nCodigo: %d", (operadoresSistema + i)->codigo);
      printf("\nNome: %s", (operadoresSistema + i)->nome);
      printf("\nUsuario: %s", (operadoresSistema + i)->usuario);
      printf("\nNivel de permissão: %d", (operadoresSistema + i)->permissoes);
      printf("\n");
    }
  }
}

void listaOperadores(structOperadoresSistema *operadoresSistema, int *quantidadeOperadores)
{
  for (int i = 0; i < (*quantidadeOperadores); ++i)
  {
    printf("\nCodigo: %d", (operadoresSistema + i)->codigo);
    printf("\nNome: %s", (operadoresSistema + i)->nome);
    printf("\nUsuario: %s", (operadoresSistema + i)->usuario);
    printf("\nNivel de permissão: %d", (operadoresSistema + i)->permissoes);
    printf("\n--------------------------------------\n");
  }
}

void atualizaOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados, int *quantidadeOperadores, FILE *arqDadosOperadores)
{
  arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores", "w+");
  fclose(arqDadosOperadores);
  for (int i = 0; i < (*quantidadeOperadores); ++i)
  {
    if (operadoresSistemaDados->codigo == (operadoresSistema + i)->codigo)
    {
      strcpy((operadoresSistema + i)->nome, operadoresSistemaDados->nome);
      strcpy((operadoresSistema + i)->usuario, operadoresSistemaDados->usuario);
      strcpy((operadoresSistema + i)->senha, operadoresSistemaDados->senha);
      (operadoresSistema + i)->permissoes = operadoresSistemaDados->permissoes;
    }
    arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores", "a+b");
    fwrite(operadoresSistema + i, sizeof(structOperadoresSistema), 1, arqDadosOperadores);
    fflush(arqDadosOperadores);
    fclose(arqDadosOperadores);
  }
}

void deletarOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados, int *quantidadeOperadores, FILE *arqQtdOperadores, FILE *arqDadosOperadores)
{
  arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores", "w+");
  fclose(arqDadosOperadores);
  for (int i = 0; i < (*quantidadeOperadores); ++i)
  {
    if ((operadoresSistema + i)->codigo == operadoresSistemaDados->codigo)
    {
      for (int j = i; j < (*quantidadeOperadores); ++j)
      {
        (operadoresSistema + j)->codigo = (operadoresSistema + j + 1)->codigo;
        strcpy((operadoresSistema + j)->nome, (operadoresSistema + j + 1)->nome);
        strcpy((operadoresSistema + j)->usuario, (operadoresSistema + j + 1)->usuario);
        strcpy((operadoresSistema + j)->senha, (operadoresSistema + j + 1)->senha);
        (operadoresSistema + j)->permissoes = (operadoresSistema + j + 1)->permissoes;
      }
    }
    arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores", "a+b");
    fwrite(operadoresSistema + i, sizeof(structOperadoresSistema), 1, arqDadosOperadores);
    fflush(arqDadosOperadores);
    fclose(arqDadosOperadores);
  }
  (*quantidadeOperadores)--;

  arqQtdOperadores = fopen("..//arqQuantidades//arqQtdOperadores.txt", "w+");
  fprintf(arqQtdOperadores, "%d", (*quantidadeOperadores));
  fflush(arqQtdOperadores);
  fclose(arqQtdOperadores);
}
