//
// Created by felipe on 25/02/2021.
//

#ifndef HOTEL_RESERVA_H
#define HOTEL_RESERVA_H

#endif //HOTEL_RESERVA_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structReserva{
    int codigo;
    int diaEntrada;
    int mesEntrada;
    int anoEntrada;
    int diaSaida;
    int mesSaida;
    int anoSaida;
    int codigoAcomodacao;
    int codigoHospede;
} structReserva;

int verifDatas(structReserva *reservaDados);

int qtdDiasReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas, int i);

void cadastrarReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas);

void gerarArqReservas(structReserva *reservaDados, int quantidadeReservas, FILE *arqQtdReservas, FILE *arqDadosReservas);

int verificarCodigoReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas);

int retornaPosicaoCodigoReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas);

int verificaSePodeCadastrar(structReserva *reserva, structReserva *reservaDados, int quantidadeReservas);

void exibeReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas);

void deletaReserva(structReserva *reserva, structReserva *reservaDados, int *quantidadeReservas, FILE *arqQtdReservas,
                   FILE *arqDadosReservas);

void listarReservas(structReserva *reserva, int *quantidadeReservas);