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

// função para verificar se o codigo do hospede já está ou não cadastrado no sistema
int verificarCodigoHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes)
{
  for (int i = 0; i < (*quantidadeHospedes); ++i)
  {
    if ((hospede + i)->codigo == hospedeDados->codigo)
    {
      return 1; // o codigo ja foi cadastrado
    }
  }
  return 0;
}

// função que recebe os dados da struct e o tranfere para o ponteiro referente aos hospedes adiciona +1 na
// quantidade de hospedes total já cadastrados gera um arquivo .txt com a quantidade de hospedes
void cadastrarHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes)
{
  (hospede + (*quantidadeHospedes))->codigo = hospedeDados->codigo;
  strcpy((hospede + (*quantidadeHospedes))->nome, hospedeDados->nome);
  strcpy((hospede + (*quantidadeHospedes))->endereco.cidade, hospedeDados->endereco.cidade);
  strcpy((hospede + (*quantidadeHospedes))->endereco.bairro, hospedeDados->endereco.bairro);
  strcpy((hospede + (*quantidadeHospedes))->endereco.rua, hospedeDados->endereco.rua);
  strcpy((hospede + (*quantidadeHospedes))->endereco.numero, hospedeDados->endereco.numero);
  strcpy((hospede + (*quantidadeHospedes))->cpf, hospedeDados->cpf);
  strcpy((hospede + (*quantidadeHospedes))->telefone, hospedeDados->telefone);
  strcpy((hospede + (*quantidadeHospedes))->email, hospedeDados->email);
  strcpy((hospede + (*quantidadeHospedes))->sexo, hospedeDados->sexo);
  strcpy((hospede + (*quantidadeHospedes))->estadoCivil, hospedeDados->estadoCivil);
  (hospede + (*quantidadeHospedes))->diaNasc = hospedeDados->diaNasc;
  (hospede + (*quantidadeHospedes))->mesNasc = hospedeDados->mesNasc;
  (hospede + (*quantidadeHospedes))->anoNasc = hospedeDados->anoNasc;
  (*quantidadeHospedes)++;
}

void gerarArqHospedes(structHospede *hospedeDados, int quantidadeHospedes, FILE *arqQtdHospedes, FILE *arqDadosHospedes)
{
  arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes", "a+b");
  fwrite(hospedeDados, sizeof(structHospede), 1, arqDadosHospedes);
  fflush(arqDadosHospedes);
  fclose(arqDadosHospedes);

  arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes.txt", "a+");
  fprintf(arqDadosHospedes, "%d,", hospedeDados->codigo);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->endereco.cidade);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->endereco.bairro);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->endereco.rua);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->endereco.numero);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->cpf);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->telefone);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->email);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->sexo);
  fprintf(arqDadosHospedes, "%s,", hospedeDados->estadoCivil);
  fprintf(arqDadosHospedes, "%d,", hospedeDados->diaNasc);
  fprintf(arqDadosHospedes, "%d,", hospedeDados->mesNasc);
  fprintf(arqDadosHospedes, "%d\n", hospedeDados->anoNasc);
  fflush(arqDadosHospedes);
  fclose(arqDadosHospedes);

  arqQtdHospedes = fopen("..//arqQuantidades//arqQtdHospedes.txt", "w+");
  fprintf(arqQtdHospedes, "%d", quantidadeHospedes);
  fflush(arqQtdHospedes);
  fclose(arqQtdHospedes);
}

// função que recebe o codigo do hospede, procura a sua posição e exibe na tela os dados correspondentes
void exibeHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes)
{
  for (int i = 0; i < (*quantidadeHospedes); ++i)
  {
    if ((hospede + i)->codigo == hospedeDados->codigo)
    {
      printf("\nCodigo: %d", (hospede + i)->codigo);
      printf("\nNome: %s", (hospede + i)->nome);
      printf("\nCPF: %s", (hospede + i)->cpf);
      printf("\nTelefone: %s", (hospede + i)->telefone);
      printf("\nEstado civil: %s", (hospede + i)->estadoCivil);
      printf("\nData de nascimento: %d/%d/%d", (hospede + i)->diaNasc, (hospede + i)->mesNasc, (hospede + i)->anoNasc);
      printf("\n");
    }
  }
}

// recebe o ponteiro de hospede e a quantidade de hospedes cadastrados em seguida
void listarHospedes(structHospede *hospede, int *quantidadeHospedes)
{
  for (int i = 0; i < (*quantidadeHospedes); ++i)
  {
    printf("\nCodigo: %d", (hospede + i)->codigo);
    printf("\nNome: %s", (hospede + i)->nome);
    printf("\nTelefone: %s", (hospede + i)->telefone);
    printf("\nData de nascimento: %d/%d/%d", (hospede + i)->diaNasc, (hospede + i)->mesNasc, (hospede + i)->anoNasc);
    printf("\n--------------------------------------\n");
  }
}

void atualizarHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes, FILE *arqDadosHospedes)
{
  arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes", "w+");
  fclose(arqDadosHospedes);
  for (int i = 0; i < (*quantidadeHospedes); ++i)
  {
    if (hospedeDados->codigo == (hospede + i)->codigo)
    {
      strcpy((hospede + i)->nome, hospedeDados->nome);
      strcpy((hospede + i)->endereco.cidade, hospedeDados->endereco.cidade);
      strcpy((hospede + i)->endereco.bairro, hospedeDados->endereco.bairro);
      strcpy((hospede + i)->endereco.rua, hospedeDados->endereco.rua);
      strcpy((hospede + i)->endereco.numero, hospedeDados->endereco.numero);
      strcpy((hospede + i)->cpf, hospedeDados->cpf);
      strcpy((hospede + i)->telefone, hospedeDados->telefone);
      strcpy((hospede + i)->email, hospedeDados->email);
      strcpy((hospede + i)->sexo, hospedeDados->sexo);
      strcpy((hospede + i)->estadoCivil, hospedeDados->estadoCivil);
      (hospede + i)->diaNasc = hospedeDados->diaNasc;
      (hospede + i)->mesNasc = hospedeDados->mesNasc;
      (hospede + i)->anoNasc = hospedeDados->anoNasc;
    }
    arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes", "a+b");
    fwrite(hospede + i, sizeof(structHospede), 1, arqDadosHospedes);
    fflush(arqDadosHospedes);
    fclose(arqDadosHospedes);
  }
}

void deletarHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes, FILE *arqQtdHospedes, FILE *arqDadosHospedes)
{
  arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes", "w+");
  fclose(arqDadosHospedes);
  for (int i = 0; i < (*quantidadeHospedes); ++i)
  {
    if ((hospede + i)->codigo == hospedeDados->codigo)
    {
      for (int j = i; j < (*quantidadeHospedes); ++j)
      {
        (hospede + j)->codigo = (hospede + j + 1)->codigo;
        strcpy((hospede + j)->nome, (hospede + j + 1)->nome);
        strcpy((hospede + j)->endereco.cidade, (hospede + j + 1)->endereco.cidade);
        strcpy((hospede + j)->endereco.bairro, (hospede + j + 1)->endereco.bairro);
        strcpy((hospede + j)->endereco.rua, (hospede + j + 1)->endereco.rua);
        strcpy((hospede + j)->endereco.numero, (hospede + j + 1)->endereco.numero);
        strcpy((hospede + j)->cpf, (hospede + j + 1)->cpf);
        strcpy((hospede + j)->telefone, (hospede + j + 1)->telefone);
        strcpy((hospede + j)->email, (hospede + j + 1)->email);
        strcpy((hospede + j)->sexo, (hospede + j + 1)->sexo);
        strcpy((hospede + j)->estadoCivil, (hospede + j + 1)->estadoCivil);
        (hospede + j)->diaNasc = (hospede + j + 1)->diaNasc;
        (hospede + j)->mesNasc = (hospede + j + 1)->mesNasc;
        (hospede + j)->anoNasc = (hospede + j + 1)->anoNasc;
      }
    }
    arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes", "a+b");
    fwrite(hospede + i, sizeof(structHospede), 1, arqDadosHospedes);
    fflush(arqDadosHospedes);
    fclose(arqDadosHospedes);
  }
  (*quantidadeHospedes)--;

  arqQtdHospedes = fopen("..//arqQuantidades//arqQtdHospedes.txt", "w+"); //altera a quandidade de hospedes
  fprintf(arqQtdHospedes, "%d", (*quantidadeHospedes));
  fflush(arqQtdHospedes);
  fclose(arqQtdHospedes);
}
