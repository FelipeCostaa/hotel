//
// Created by felipe on 25/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "reserva.h"
#include "horaData.h"
#include "hotel.h"
#include "hospede.h"
#include "acomodacao.h"
#include "categoriaAcomodacao.h"
#include "fornecedor.h"
#include "operadorSistema.h"
#include "produtosDisponiveis.h"

int verifDatas(structReserva *reservaDados)
{
  int r1 = reservaDados->mesEntrada * 30;
  r1 += reservaDados->diaEntrada;

  int r2 = reservaDados->mesSaida * 30;
  r2 += reservaDados->diaSaida;

  if (reservaDados->anoEntrada < reservaDados->anoSaida)
  {
    return 1;
  }
  else
  {
    if (r1 > r2)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
}

int qtdDiasReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas, int i)
{
  int totalDias = 0;

  if (reserva[i].codigo == reservaDados->codigo)
  {
//    if (reserva[i].anoEntrada < reserva[i].anoSaida || reserva[i].mesEntrada < reserva[i].mesSaida || reserva[i].diaEntrada < reserva[i].diaSaida)
//    {
//      return -1; // data invalida
//    }
    if (reserva[i].mesEntrada == reserva[i].mesSaida)
    {
      totalDias = reserva[i].diaSaida - reserva[i].diaEntrada;
      return totalDias;
    }
    else
    {
      totalDias = 30 - reserva[i].diaEntrada + reserva[i].diaSaida;
      return totalDias;
    }
  }
}

void cadastrarReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas)
{
  (reserva + (*quantidadeReservas))->codigo = reservaDados->codigo;
  (reserva + (*quantidadeReservas))->diaEntrada = reservaDados->diaEntrada;
  (reserva + (*quantidadeReservas))->mesEntrada = reservaDados->mesEntrada;
  (reserva + (*quantidadeReservas))->anoEntrada = reservaDados->anoEntrada;
  (reserva + (*quantidadeReservas))->diaSaida = reservaDados->diaSaida;
  (reserva + (*quantidadeReservas))->mesSaida = reservaDados->mesSaida;
  (reserva + (*quantidadeReservas))->anoSaida = reservaDados->anoSaida;
  (reserva + (*quantidadeReservas))->codigoAcomodacao = reservaDados->codigoAcomodacao;
  (reserva + (*quantidadeReservas))->codigoHospede = reservaDados->codigoHospede;
  (*quantidadeReservas)++;
}

void gerarArqReservas(structReserva *reservaDados, int quantidadeReservas, FILE *arqQtdReservas, FILE *arqDadosReservas)
{
  arqDadosReservas = fopen("..//bancoDeDados//arqDadosReservas", "a+b");
  fwrite(reservaDados, sizeof (structReserva),1, arqDadosReservas);
  fflush(arqDadosReservas);
  fclose(arqDadosReservas);

  arqDadosReservas = fopen("..//bancoDeDados//arqDadosReservas.txt", "a+");
  fprintf(arqDadosReservas, "%d,", reservaDados->codigo);
  fprintf(arqDadosReservas, "%d,", reservaDados->diaEntrada);
  fprintf(arqDadosReservas, "%d,", reservaDados->mesEntrada);
  fprintf(arqDadosReservas, "%d,", reservaDados->anoEntrada);
  fprintf(arqDadosReservas, "%d,", reservaDados->diaSaida);
  fprintf(arqDadosReservas, "%d,", reservaDados->mesSaida);
  fprintf(arqDadosReservas, "%d,", reservaDados->anoSaida);
  fprintf(arqDadosReservas, "%d,", reservaDados->codigoAcomodacao);
  fprintf(arqDadosReservas, "%d\n", reservaDados->codigoHospede);
  fflush(arqDadosReservas);
  fclose(arqDadosReservas);

  arqQtdReservas =  fopen("..//arqQuantidades//arqQtdReservas.txt", "w+");
  fprintf(arqQtdReservas, "%d", quantidadeReservas);
  fflush(arqQtdReservas);
  fclose(arqQtdReservas);
}

int verificarCodigoReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas)
{
  for (int i = 0; i < (*quantidadeReservas); ++i) {
    if (reservaDados->codigo == (reserva + i)->codigo)
    {
      return 1;
    }
  }
  return 0;
}

int retornaPosicaoCodigoReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas)
{
  for (int i = 0; i < (*quantidadeReservas); ++i) {
    if (reservaDados->codigo == (reserva + i)->codigo)
    {
      return i;
    }
  }
}

int verificaSePodeCadastrar(structReserva *reserva, structReserva *reservaDados, int quantidadeReservas)
{
  int aux = 0;

  for (int i = 0; i < quantidadeReservas; ++i) {
    if ((reserva + i)->codigoAcomodacao == reservaDados->codigoAcomodacao)
    {
      if ((reserva + i)->anoEntrada > reservaDados->anoSaida || reservaDados->anoSaida > (reserva + i)->anoEntrada)
      {
        aux = 0;
      }
      else
      {
        int r1 = (reserva + i)->mesEntrada * 30;
        r1 += (reserva + i)->diaEntrada;
        int r2 = reservaDados->mesSaida * 30;
        r2 += reservaDados->diaSaida;
        if (r2 > r1)
        {
          r1 = (reserva + i)->mesSaida * 30;
          r1 += (reserva + i)->diaSaida;
          r2 = reservaDados->mesEntrada * 30;
          r2 += reservaDados->diaEntrada;
          if (r2 > r1)
          {
            aux = 0;
          }
          else
          {
            return 1;
          }
        }
        else
        {
          aux = 0;
        }
      }
    }
  }
  return aux;
}

void exibeReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas)
{
  for (int i = 0; i < (*quantidadeReservas); ++i) {
    if ((reserva + i)->codigo == reservaDados->codigo)
    {
      printf("\nCodigo: %d", (reserva + i)->codigo);
      printf("\nData entrada: %d-%d-%d", (reserva + i)->diaEntrada, (reserva + i)->mesEntrada, (reserva + i)->anoEntrada);
      printf("\nData saida: %d-%d-%d", (reserva + i)->diaSaida, (reserva + i)->mesSaida, (reserva + i)->anoSaida);
      printf("\nCodigo da acomodação usada: %d", (reserva + i)->codigoAcomodacao);
      printf("\nCodigo do hospede: %d", (reserva + i)->codigoHospede);
      printf("\n");
    }
  }
}

void listarReservas(structReserva *reserva, int *quantidadeReservas)
{
  for (int i = 0; i < (*quantidadeReservas); ++i)
  {
    printf("\nCodigo: %d", (reserva + i)->codigo);
    printf("\nData entrada: %d-%d-%d", (reserva + i)->diaEntrada, (reserva + i)->mesEntrada, (reserva + i)->anoEntrada);
    printf("\nData saida: %d-%d-%d", (reserva + i)->diaSaida, (reserva + i)->mesSaida, (reserva + i)->anoSaida);
    printf("\nCodigo da acomodação usada: %d", (reserva + i)->codigoAcomodacao);
    printf("\nCodigo do hospede: %d", (reserva + i)->codigoHospede);
    printf("\n");
  }
}


void deletaReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas, FILE *arqQtdReservas, FILE *arqDadosReservas)
{
  arqDadosReservas = fopen("..//bancoDeDados//arqDadosReservas", "w+");
  fclose(arqDadosReservas);
  for (int i = 0; i < (*quantidadeReservas); ++i) {
    if ((reserva + i)->codigo == reservaDados->codigo)
    {
      for (int j = 0; j < (*quantidadeReservas); ++j) {
        (reserva + i)->codigo = (reserva + j + 1)->codigo;
        (reserva + i)->diaEntrada = (reserva + j + 1)->diaEntrada;
        (reserva + i)->mesEntrada = (reserva + j + 1)->mesEntrada;
        (reserva + i)->anoEntrada = (reserva + j + 1)->anoEntrada;
        (reserva + i)->diaSaida = (reserva + j + 1)->diaSaida;
        (reserva + i)->mesSaida = (reserva + j + 1)->mesSaida;
        (reserva + i)->anoSaida = (reserva + j + 1)->anoSaida;
        (reserva + i)->codigoAcomodacao = (reserva + j + 1)->codigoAcomodacao;
        (reserva + i)->codigoHospede = (reserva + j + 1)->codigoHospede;
      }
    }
    arqDadosReservas = fopen("..//bancoDeDados//arqDadosReservas", "a+b");
    fwrite(reserva + i, sizeof(structReserva), 1, arqDadosReservas);
    fflush(arqDadosReservas);
    fclose(arqDadosReservas);
  }
  (*quantidadeReservas)--;

  arqQtdReservas = fopen("..//arqQuantidades//arqQtdReservas.txt", "w+");
  fprintf(arqQtdReservas, "%d", (*quantidadeReservas));
  fflush(arqQtdReservas);
  fclose(arqQtdReservas);
}

























