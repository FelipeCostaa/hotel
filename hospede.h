//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_HOSPEDE_H
#define HOTEL_HOSPEDE_H

#endif //HOTEL_HOSPEDE_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structHospede
{
    int codigo;
    char nome[CHAR_G];
    structEndereco endereco;
    char cpf[CHAR_P];
    char telefone[CHAR_P];
    char email[CHAR_G];
    char sexo[CHAR_P];
    char estadoCivil[CHAR_P];
    int diaNasc, mesNasc, anoNasc;
} structHospede;

int verificarCodigoHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes);

void cadastrarHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes);

void gerarArqHospedes(structHospede *hospedeDados, int quantidadeHospedes, FILE *arqQtdHospedes, FILE *arqDadosHospedes);

void exibeHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes);

void listarHospedes(structHospede *hospede, int *quantidadeHospedes);

void atualizarHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes, FILE *arqDadosHospedes);

void deletarHospede(structHospede *hospede, structHospede *hospedeDados, int *quantidadeHospedes, FILE *arqQtdHospedes,
                    FILE *arqDadosHospedes);
