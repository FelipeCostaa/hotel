//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_ACOMODACAO_H
#define HOTEL_ACOMODACAO_H

#endif //HOTEL_ACOMODACAO_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structAcomodacao
{
    int codigo;
    char descricao[CHAR_G];
    char facilidades[CHAR_G];
    int categoria; // verificar atraves do codigo na struct categoriaAcomodacao
} structAcomodacao;

int verificarCodigoAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes);

int retornaPosicaoAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes);

void cadastrarAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes);

void gerarArqAcomodacao(structAcomodacao *acomodacaoDados, int quantidadeAcomodacoes, FILE *arqQtdAcomodacoes, FILE *arqDadosAcomodacoes);

void exibeAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes);

void listarAcomodacoes(structAcomodacao *acomodacao, int *quantidadeAcomodacoes);

void atualizarAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes, FILE *arqDadosAcomodacoes);

void deletarAcomodacao(structAcomodacao *acomodacao, structAcomodacao *acomodacaoDados, int *quantidadeAcomodacoes,
                       FILE *arqQtdAcomodacoes, FILE *arqDadosAcomodacoes);

