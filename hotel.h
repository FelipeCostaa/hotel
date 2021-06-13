//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_HOTEL_H
#define HOTEL_HOTEL_H

#endif //HOTEL_HOTEL_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structEndereco
{
    char numero[8];
    char rua[CHAR_M];
    char bairro[CHAR_P];
    char cidade[CHAR_M];
} structEndereco;

typedef struct structHotel
{
    char nomeFantasia[CHAR_G];
    char razaoSocial[CHAR_G];
    char inscricaoEstadual[CHAR_P];
    char cnpj[CHAR_P];
    structEndereco endereco;
    char telefone[CHAR_P];
    char email[CHAR_G];
    char nomeResponsavel[CHAR_P];
    char telefoneResponsavel[CHAR_P];
    int horaCheckin, minutoCheckin;
    int horaCheckout, minutoCheckout;
    float margemLucro;
} structHotel;

int confirmaSeExisteHotelCadastrado(int *confirmacaoHotel);

void cadastrarHotel(structHotel *hotelDados, structHotel *hotel, int *confirmacaoHotel, FILE *arqConfirmacaoHotel, FILE *arqDadosHotel);

void exibeHotel(structHotel *hotel);
