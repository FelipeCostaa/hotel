//
// Created by felipe on 25/03/2021.
//

#ifndef HOTEL_TRANSACOES_H
#define HOTEL_TRANSACOES_H

#endif //HOTEL_TRANSACOES_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structCheckin
{
    int codigo;
    int codigoReserva;
    int formaPagamento; // 1 check in ou 2 check out
    float valorDiaria;
    float totalConta;
} structCheckin;

int verifCodigoCheckin(structCheckin *checkin, structCheckin *checkinDados, int *quantidadeCheckin);

void cadastrarCheckin(structCheckin *checkin, structCheckin *checkinDados, int *quantidadeCheckin);

void gerarArqChecki(structCheckin *checkinDados, int quantidadeCheckin, FILE *arqQtdCheckin, FILE *arqDadosCheckin);
