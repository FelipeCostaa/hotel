//
// Created by felipe on 08/04/2021.
//

#ifndef HOTEL_VENDAS_H
#define HOTEL_VENDAS_H

#endif //HOTEL_VENDAS_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structVendas{
    int quantidadeProdutos;
    float valorProduto;
    float totalTemp;
    float valorTotalProtudos;
    int codigoCheckin;
} structVendas;

void cadastrarVenda(structVendas *vendas, structVendas *vendaDados, int *qtdVendas);

void gerarArqVenda(structVendas *vendaDados, int qtdVendas, FILE *arqQtdVendas, FILE *arqDadosVendas);

