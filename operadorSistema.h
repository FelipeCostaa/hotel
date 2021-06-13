//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_OPERADORSISTEMA_H
#define HOTEL_OPERADORSISTEMA_H

#endif //HOTEL_OPERADORSISTEMA_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structOperadoresSistema
{
    int codigo;
    char nome[CHAR_G];
    char usuario[CHAR_P];
    char senha[CHAR_P];
    int permissoes;
} structOperadoresSistema;

int verificarCodigoOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados,
                            int *quantidadeOperadores);

int verificarUsuarioOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados,
                             int *quantidadeOperadores);

void cadastrarOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados,
                       int *quantidadeOperadores);

void gerarArqOperador(structOperadoresSistema *operatoresSistemaDados, int quantidadeOperadores, FILE *arqQtdOperadores,
                      FILE *arqDadosOperadores);

void exibeOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados,
                   int *quantidadeOperadores);

void listaOperadores(structOperadoresSistema *operadoresSistema, int *quantidadeOperadores);

void atualizaOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados,
                      int *quantidadeOperadores, FILE *arqDadosOperadores);

void deletarOperador(structOperadoresSistema *operadoresSistema, structOperadoresSistema *operadoresSistemaDados,
                     int *quantidadeOperadores, FILE *arqQtdOperadores, FILE *arqDadosOperadores);
