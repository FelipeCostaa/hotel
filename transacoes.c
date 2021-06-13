//
// Created by felipe on 25/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "transacoes.h"
#include "reserva.h"
#include "horaData.h"
#include "hotel.h"
#include "hospede.h"
#include "acomodacao.h"
#include "categoriaAcomodacao.h"
#include "fornecedor.h"
#include "operadorSistema.h"
#include "produtosDisponiveis.h"

int verifCodigoCheckin(structCheckin *checkin, structCheckin *checkinDados, int *quantidadeCheckin)
{
  for (int i = 0; i < (*quantidadeCheckin); ++i)
  {
    if ((checkin + i)->codigo == checkinDados->codigo)
    {
      return 1;
    }
  }
  return 0;
}

void cadastrarCheckin(structCheckin *checkin, structCheckin *checkinDados, int *quantidadeCheckin)
{
  (checkin + (*quantidadeCheckin))->codigo = checkinDados->codigo;
  (checkin + (*quantidadeCheckin))->codigoReserva = checkinDados->codigoReserva;
  (checkin + (*quantidadeCheckin))->formaPagamento = checkinDados->formaPagamento;
  (checkin + (*quantidadeCheckin))->valorDiaria = checkinDados->valorDiaria;
  (checkin + (*quantidadeCheckin))->totalConta = checkinDados->totalConta;

  (*quantidadeCheckin)++;
}

void gerarArqChecki(structCheckin *checkinDados, int quantidadeCheckin, FILE *arqQtdCheckin, FILE *arqDadosCheckin)
{
  arqDadosCheckin = fopen("..//bancoDeDados//arqDadosCheckin", "a+b");
  fwrite(checkinDados, sizeof (structCheckin),1, arqDadosCheckin);
  fflush(arqDadosCheckin);
  fclose(arqDadosCheckin);

  arqQtdCheckin =  fopen("..//arqQuantidades//arqQtdCheckin.txt", "w+");
  fprintf(arqQtdCheckin, "%d", quantidadeCheckin);
  fflush(arqQtdCheckin);
  fclose(arqQtdCheckin);
}






















