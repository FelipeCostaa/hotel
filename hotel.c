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

int confirmaSeExisteHotelCadastrado(int *confirmacaoHotel)
{
  if ((*confirmacaoHotel) == 1)
  {
    return 1; // ja existe hotel cadastrado
  }
  return 0; // não existe hotel cadastrado
}

void cadastrarHotel(structHotel *hotelDados, structHotel *hotel, int *confirmacaoHotel, FILE *arqConfirmacaoHotel, FILE *arqDadosHotel)
{
  strcpy(hotel->nomeFantasia, hotelDados->nomeFantasia);
  strcpy(hotel->razaoSocial, hotelDados->razaoSocial);
  strcpy(hotel->inscricaoEstadual, hotelDados->inscricaoEstadual);
  strcpy(hotel->cnpj, hotelDados->cnpj);
  strcpy(hotel->endereco.numero, hotelDados->endereco.numero);
  strcpy(hotel->endereco.rua, hotelDados->endereco.rua);
  strcpy(hotel->endereco.bairro, hotelDados->endereco.bairro);
  strcpy(hotel->endereco.cidade, hotelDados->endereco.cidade);
  strcpy(hotel->telefone, hotelDados->telefone);
  strcpy(hotel->email, hotelDados->email);
  strcpy(hotel->nomeResponsavel, hotelDados->nomeResponsavel);
  strcpy(hotel->telefoneResponsavel, hotelDados->telefoneResponsavel);
  hotel->horaCheckin = hotelDados->horaCheckin;
  hotel->minutoCheckin = hotelDados->minutoCheckin;
  hotel->horaCheckout = hotelDados->horaCheckout;
  hotel->minutoCheckout = hotelDados->minutoCheckout;
  hotel->margemLucro = hotelDados->margemLucro;

  if ((*confirmacaoHotel) == 0)
  {
    (*confirmacaoHotel) += 1;
  }

  arqConfirmacaoHotel = fopen("..//arqQuantidades//arqConfirmacaoHotel.txt", "w+");
  fprintf(arqConfirmacaoHotel, "%d", (*confirmacaoHotel));
  fflush(arqConfirmacaoHotel);
  fclose(arqConfirmacaoHotel);

  arqDadosHotel = fopen("..//bancoDeDados//arqDadosHotel", "w+b");
  fwrite(hotel, sizeof(structHotel), 1, arqDadosHotel);
  fflush(arqDadosHotel);
  fclose(arqDadosHotel);
}

void exibeHotel(structHotel *hotel)
{
  printf("\nDados do hotel: ");
  printf("\nNome fantasia: %s", hotel->nomeFantasia);
  printf("\nRazão social: %s", hotel->razaoSocial);
  printf("\nInscrição estadual: %s", hotel->inscricaoEstadual);
  printf("\nCNPJ: %s", hotel->cnpj);
  printf("\nEndereço: ");
  printf("\n\tCidade: %s", hotel->endereco.cidade);
  printf("\n\tBairro: %s", hotel->endereco.bairro);
  printf("\n\tRua: %s", hotel->endereco.rua);
  printf("\n\tNumero: %s", hotel->endereco.numero);
  printf("\nTelefone: %s", hotel->telefone);
  printf("\nE-mail: %s", hotel->email);
  printf("\nNome do responsável: %s", hotel->nomeResponsavel);
  printf("\nTelefone do responsável: %s", hotel->telefoneResponsavel);
  printf("\nHorario de check-in: %d:%d hrs", hotel->horaCheckin, hotel->minutoCheckin);
  printf("\nHorario de check-out: %d:%d hrs", hotel->horaCheckout, hotel->minutoCheckout);
  printf("\nMargem de lucro: %2.f%%", hotel->margemLucro);
  printf("\n");
}
