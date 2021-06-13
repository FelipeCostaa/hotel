//
// Created by felipe on 09/04/2021.
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
#include "feedback.h"

void csvHospede(structHospede *hospede, int qtd)
{
  FILE *arq;
  arq = fopen("..//csv//csvHospede.txt", "w+");
  for (int i = 0; i < qtd; ++i) {
    fprintf(arq, "%d,%s,%s,%s,%s,%s,%s,%d,%d,%d\n", hospede[i].codigo, hospede[i].nome, hospede[i].cpf, hospede[i].telefone,
            hospede[i].email, hospede[i].sexo, hospede[i].estadoCivil, hospede[i].diaNasc, hospede[i].mesNasc, hospede[i].anoNasc);
  }
  fclose(arq);
}

void csvAcomodacoes(structAcomodacao *a, int qtd)
{
  FILE *arq;
  arq = fopen("..//csv//csvAcomodacao.txt", "w+");
  for (int i = 0; i < qtd; ++i) {
    fprintf(arq, "%d,%s,%s,%d\n", a[i].codigo, a[i].descricao, a[i].facilidades, a[i].categoria);
  }
  fclose(arq);
}

void csvReservas(structReserva *r, int qtd)
{
  FILE *arq;
  arq = fopen("..//csv//csvReserva.txt", "w+");
  for (int i = 0; i < qtd; ++i) {
    fprintf(arq, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", r[i].codigo, r[i].diaEntrada, r[i].mesEntrada, r[i].anoEntrada, r[i].diaSaida, r[i].mesSaida, r[i].anoSaida, r[i].codigoAcomodacao, r[i].codigoHospede);
  }
  fclose(arq);
}

void csvProdutosConsumo(structProdutosConsumo *p, int qtd)
{
  FILE *arq;
  arq = fopen("..//csv//csvProduto.txt", "w+");
  for (int i = 0; i < qtd; ++i) {
    fprintf(arq, "%d,%s,%d,%d,%f,%f\n", p[i].codigo, p[i].descricao, p[i].estoque, p[i].estoqueMinimo, p[i].precoCusto, p[i].precoVenda);
  }
  fclose(arq);
}

void csvCategorias(structCategoriaAcomodacao *c, int qtd)
{
  FILE *arq;
  arq = fopen("..//csv//csvProduto.txt", "w+");
  for (int i = 0; i < qtd; ++i) {
    fprintf(arq, "%d,%s,%f,%d\n", c[i].codigo, c[i].descricao, c[i].valorDiaria, c[i].quantMaxDePessoas);
  }
  fclose(arq);
}
