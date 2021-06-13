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

int verificarCodigoFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores)
{
  for (int i = 0; i < (*quantidadeFornecedores); ++i)
  {
    if ((fornecedores + i)->codigo == fornecedoresDados->codigo)
    {
      return 1; // codigo ja cadastrado
    }
  }
  return 0;
}

void cadastrarFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores)
{
  (fornecedores + (*quantidadeFornecedores))->codigo = fornecedoresDados->codigo;
  strcpy((fornecedores + (*quantidadeFornecedores))->nomeFantasia, fornecedoresDados->nomeFantasia);
  strcpy((fornecedores + (*quantidadeFornecedores))->razaoSocial, fornecedoresDados->razaoSocial);
  strcpy((fornecedores + (*quantidadeFornecedores))->inscricaoEstadual, fornecedoresDados->inscricaoEstadual);
  strcpy((fornecedores + (*quantidadeFornecedores))->cnpj, fornecedoresDados->cnpj);
  strcpy((fornecedores + (*quantidadeFornecedores))->endereco.cidade, fornecedoresDados->endereco.cidade);
  strcpy((fornecedores + (*quantidadeFornecedores))->endereco.bairro, fornecedoresDados->endereco.bairro);
  strcpy((fornecedores + (*quantidadeFornecedores))->endereco.rua, fornecedoresDados->endereco.rua);
  strcpy((fornecedores + (*quantidadeFornecedores))->endereco.numero, fornecedoresDados->endereco.numero);
  strcpy((fornecedores + (*quantidadeFornecedores))->telefone, fornecedoresDados->telefone);
  strcpy((fornecedores + (*quantidadeFornecedores))->email, fornecedoresDados->email);
  (*quantidadeFornecedores)++;
}

void gerarArqFornecedor(structFornecedores *fornecedorDados, int quantidadeFornecedores, FILE *arqQtdFornecedores, FILE *arqDadosFornecedores)
{
  arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores", "a+b");
  fwrite(fornecedorDados, sizeof(structFornecedores), 1, arqDadosFornecedores);
  fflush(arqDadosFornecedores);
  fclose(arqDadosFornecedores);

  arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores.txt", "a+");
  fprintf(arqDadosFornecedores, "%d,", fornecedorDados->codigo);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->nomeFantasia);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->razaoSocial);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->inscricaoEstadual);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->cnpj);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->endereco.cidade);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->endereco.bairro);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->endereco.rua);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->endereco.numero);
  fprintf(arqDadosFornecedores, "%s,", fornecedorDados->telefone);
  fprintf(arqDadosFornecedores, "%s\n", fornecedorDados->email);
  fflush(arqDadosFornecedores);
  fclose(arqDadosFornecedores);

  arqQtdFornecedores = fopen("..//arqQuantidades//arqQtdFornecedores.txt", "w+");
  fprintf(arqQtdFornecedores, "%d", quantidadeFornecedores);
  fflush(arqQtdFornecedores);
  fclose(arqQtdFornecedores);
}

void exibeFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores)
{
  for (int i = 0; i < (*quantidadeFornecedores); ++i)
  {
    if ((fornecedores + i)->codigo == fornecedoresDados->codigo)
    {
      printf("\nCodigo: %d", (fornecedores + i)->codigo);
      printf("\nNome fantasia: %s", (fornecedores + i)->nomeFantasia);
      printf("\nRazão social: %s", (fornecedores + i)->razaoSocial);
      printf("\nInscrição estadual: %s", (fornecedores + i)->inscricaoEstadual);
      printf("\nCNPJ: %s", (fornecedores + i)->cnpj);
      printf("\nEndereço: ");
      printf("\n\tCidade: %s", (fornecedores + i)->endereco.cidade);
      printf("\n\tBairro: %s", (fornecedores + i)->endereco.bairro);
      printf("\n\tRua: %s", (fornecedores + i)->endereco.rua);
      printf("\n\tNumero: %s", (fornecedores + i)->endereco.numero);
      printf("\nTelefone: %s", (fornecedores + i)->telefone);
      printf("\nE-mail: %s", (fornecedores + i)->email);
      printf("\n");
    }
  }
}

void listarFornecedores(structFornecedores *fornecedores, int *quantidadeFornecedores)
{
  for (int i = 0; i < (*quantidadeFornecedores); ++i)
  {
    printf("\nCodigo: %d", (fornecedores + i)->codigo);
    printf("\nNome fantasia: %s", (fornecedores + i)->nomeFantasia);
    printf("\nRazão social: %s", (fornecedores + i)->razaoSocial);
    printf("\nInscrição estadual: %s", (fornecedores + i)->inscricaoEstadual);
    printf("\nCNPJ: %s", (fornecedores + i)->cnpj);
    printf("\nEndereço: ");
    printf("\n\tCidade: %s", (fornecedores + i)->endereco.cidade);
    printf("\n\tBairro: %s", (fornecedores + i)->endereco.bairro);
    printf("\n\tRua: %s", (fornecedores + i)->endereco.rua);
    printf("\n\tNumero: %s", (fornecedores + i)->endereco.numero);
    printf("\nTelefone: %s", (fornecedores + i)->telefone);
    printf("\nE-mail: %s", (fornecedores + i)->email);
    printf("\n--------------------------------------\n");
  }
}

void atualizaFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores, FILE *arqDadosFornecedores)
{
  arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores", "w+");
  fclose(arqDadosFornecedores);
  for (int i = 0; i < (*quantidadeFornecedores); ++i)
  {
    if (fornecedoresDados->codigo == (fornecedoresDados + i)->codigo)
    {
      strcpy((fornecedores + i)->nomeFantasia, fornecedoresDados->nomeFantasia);
      strcpy((fornecedores + i)->razaoSocial, fornecedoresDados->razaoSocial);
      strcpy((fornecedores + i)->inscricaoEstadual, fornecedoresDados->inscricaoEstadual);
      strcpy((fornecedores + i)->cnpj, fornecedoresDados->cnpj);
      strcpy((fornecedores + i)->endereco.cidade, fornecedoresDados->endereco.cidade);
      strcpy((fornecedores + i)->endereco.bairro, fornecedoresDados->endereco.bairro);
      strcpy((fornecedores + i)->endereco.rua, fornecedoresDados->endereco.rua);
      strcpy((fornecedores + i)->endereco.numero, fornecedoresDados->endereco.numero);
      strcpy((fornecedores + i)->telefone, fornecedoresDados->telefone);
      strcpy((fornecedores + i)->email, fornecedoresDados->email);
    }
    arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores", "a+b");
    fwrite(fornecedores + i, sizeof (structFornecedores), 1, arqDadosFornecedores);
    fflush(arqDadosFornecedores);
    fclose(arqDadosFornecedores);
  }
}

void deletarFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores, FILE *arqQtdFornecedores, FILE *arqDadosFornecedores)
{
  arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores", "w+");
  fclose(arqDadosFornecedores);
  for (int i = 0; i < (*quantidadeFornecedores); ++i)
  {
    if (fornecedoresDados->codigo == (fornecedores + i)->codigo)
    {
      for (int j = i; j < (*quantidadeFornecedores); ++j)
      {
        (fornecedores + j)->codigo = (fornecedores + j + 1)->codigo;
        strcpy((fornecedores + j)->nomeFantasia, (fornecedores + j + 1)->nomeFantasia);
        strcpy((fornecedores + j)->razaoSocial, (fornecedores + j + 1)->razaoSocial);
        strcpy((fornecedores + j)->inscricaoEstadual, (fornecedores + j + 1)->inscricaoEstadual);
        strcpy((fornecedores + j)->cnpj, (fornecedores + j + 1)->cnpj);
        strcpy((fornecedores + j)->endereco.cidade, (fornecedores + j + 1)->endereco.cidade);
        strcpy((fornecedores + j)->endereco.bairro, (fornecedores + j + 1)->endereco.bairro);
        strcpy((fornecedores + j)->endereco.rua, (fornecedores + j + 1)->endereco.rua);
        strcpy((fornecedores + j)->endereco.numero, (fornecedores + j + 1)->endereco.numero);
        strcpy((fornecedores + j)->telefone, (fornecedores + j + 1)->telefone);
        strcpy((fornecedores + j)->email, (fornecedores + j + 1)->email);
      }
    }
    arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores", "a+b");
    fwrite(fornecedores + i, sizeof(structFornecedores),1,arqDadosFornecedores);
    fflush(arqDadosFornecedores);
    fclose(arqDadosFornecedores);
  }
  (*quantidadeFornecedores)--;

  arqQtdFornecedores = fopen("..//arqQuantidades//arqQtdFornecedores.txt", "w+");
  fprintf(arqQtdFornecedores, "%d", (*quantidadeFornecedores));
  fflush(arqQtdFornecedores);
  fclose(arqQtdFornecedores);
}
