//
// Created by felipe on 08/04/2021.
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
#include "vendas.h"

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

void cadastrarVenda(structVendas *vendas, structVendas *vendaDados, int *qtdVendas)
{
  (vendas + (*qtdVendas))->codigoCheckin = vendaDados->codigoCheckin;
  (vendas + (*qtdVendas))->valorTotalProtudos = vendaDados->valorTotalProtudos;
  (vendas + (*qtdVendas))->codigoCheckin = vendaDados->codigoCheckin;
  (vendas + (*qtdVendas))->codigoCheckin = vendaDados->codigoCheckin;
}

void gerarArqVenda(structVendas *vendaDados, int qtdVendas, FILE *arqQtdVendas, FILE *arqDadosVendas)
{
  arqDadosVendas = fopen("..//bancoDeDados//arqDadosVendas", "a+b");
  fwrite(vendaDados, sizeof(structVendas), 1, arqDadosVendas);
  fflush(arqDadosVendas);
  fclose(arqDadosVendas);

  arqQtdVendas = fopen("..//arqQuantidades//arqQtdVendas.txt", "w+");
  fprintf(arqQtdVendas, "%d", qtdVendas);
  fflush(arqQtdVendas);
  fclose(arqQtdVendas);
}