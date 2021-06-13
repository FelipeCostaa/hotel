//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_CATEGORIAACOMODACAO_H
#define HOTEL_CATEGORIAACOMODACAO_H

#endif //HOTEL_CATEGORIAACOMODACAO_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structCategoriaAcomodacao
{
    int codigo;
    char descricao[CHAR_G];
    float valorDiaria;
    int quantMaxDePessoas;
} structCategoriaAcomodacao;

int verificaCodigoCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados,
                            int *quantidadeCategorias);

int retornaPosicaoCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados,
                            int *quantidadeCategorias);

void cadastrarCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados,
                        int *quantidadeCategorias);

void gerarArqCategoria(structCategoriaAcomodacao *categoriaAcomodacaoDados, int quantidadeCategorias, FILE *arqQtdCategorias,
                       FILE *arqDadosCategorias);

void exibeCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados,
                    int *quantidadeCategorias);

void listarCategorias(structCategoriaAcomodacao *categoriaAcomodacao, int *quantidadeCategorias);

void atualizarCategorias(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados,
                         int *quantidadeCategorias, FILE *arqDadosCategorias);

void deletarCategoria(structCategoriaAcomodacao *categoriaAcomodacao, structCategoriaAcomodacao *categoriaAcomodacaoDados,
                      int *quantidadeCategorias, FILE *arqQtdCategorias, FILE *arqDadosCategorias);
