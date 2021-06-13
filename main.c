/*
  Autor: Felipe de Assis Costa
  RA: 0049539
  Data: 23/12/2020
*/

/*
 *      Modulo de cadastros:
 * Crud do menu cadastros funcina 100%
 * O programa gera arquivos binarios e de texto
 * Só está funcional o armazenamento por binario o de texto só tem os arquivos gerados e salvos
 *
 *      Modulo de reservas:
 * Cadastro, cancelamento e pesquisa das reservas já feitas funciona
 * Verifica a disponibilidade por meio da data e da categoria de acomodação
 *
 *      Modulo trasançoes:
 * Checkout não ficou funcional
 *
 *      Modulo feedback
 * Relatorios na tela e CSV funcionam
 *
 *      Documentação
 * Documentação feita
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "reserva.h"
#include "horaData.h"
#include "hotel.h"
#include "hospede.h"
#include "acomodacao.h"
#include "categoriaAcomodacao.h"
#include "fornecedor.h"
#include "operadorSistema.h"
#include "produtosDisponiveis.h"
#include "transacoes.h"
#include "vendas.h"
#include "feedback.h"
#include "exportar.h"
#include <time.h>

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

int verificarAcomodacaoECategoria(structAcomodacao *acomodacaoDados, structCategoriaAcomodacao *categoriaAcomodacao, int *quantidadeCategorias);
int verificarAcomodacaoECategoriaReserva(structReserva *reservaDados, structCategoriaAcomodacao *categoriaAcomodacao, int *quantidadeCategorias);
int verificarCodigoHospedeReserva(structHospede *hospede, structReserva *structReservaDados, int *quantidadeHospedes);;

int main()
{
  /*--------------hora e  data atual-------------------*/
  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime);


  // variaveis de menu
  int menu = 0, submenuCadastro = 0;
  int submenuLvl3 = 0; // submenuLvl3 é usado para todos os menus de cadastros

  // variaveis auxiliares de quantidades
  int quantidadeHospedes = 0, quantidadeAcomodacoes = 0, quantidadeCategorias = 0, quantidadeProdutos = 0;
  int quantidadeFornecedores = 0, quantidadeOperadores = 0, confirmacaoHotel = 0, quantidadeReservas = 0;
  int quantidadeCheckin = 0;
  int posicao, aux, aux2;

  // codigo da reserva
  int codigoReserva = 0;

  // usada no menu de cadastros
  int confirmacao = 0;

  // variaveis com estrutura do modulo cadastro
  structHotel hotelDados;
  structHospede hospedeDados;
  structAcomodacao acomodacaoDados;
  structCategoriaAcomodacao categoriaAcomodacaoDados;
  structProdutosConsumo produtosConsumoDados;
  structFornecedores fornecedoresDados;
  structOperadoresSistema operadoresSistemaDados;
  structReserva reservaDados;
  structCheckin checkinDados;

  // alocaçao dinamica vendas
  structVendas *vendas;
  vendas = calloc(1, sizeof (structVendas));
  if (vendas == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }

  // alocacao dinamica checkin
  structCheckin *checkin;
  checkin = calloc(1, sizeof (structCheckin));
  if (checkin == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados do checkin
  FILE *arqQtdCheckin;
  FILE *arqDadosCheckin;
  arqQtdCheckin = fopen("..//arqQuantidades//arqQtdCheckin.txt", "r");
  if (arqQtdCheckin == NULL)
  {
    arqQtdCheckin = fopen("..//arqQuantidades//arqQtdCheckin.txt", "w+");
    if (arqQtdCheckin == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdCheckin);
    arqQtdCheckin = 0;
  }
  else
  {
    fscanf(arqQtdCheckin, "%d", &quantidadeCheckin);
    fclose(arqQtdCheckin);
  }
  if (quantidadeCheckin > 0)
  {
    checkin = realloc(checkin, (quantidadeCheckin + 1) * sizeof(structCheckin));
    arqDadosCheckin = fopen("..//bancoDeDados//arqDadosCheckin", "rb");
    if (arqDadosCheckin == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosCheckin*!\n");
    fread(checkin, sizeof(structCheckin), quantidadeCheckin, arqDadosCheckin);
    fflush(arqDadosCheckin);
    fclose(arqDadosCheckin);
  }

  // alocacao dinamica hotel
  structHotel *hotel;
  hotel = calloc(1, sizeof(structHotel));
  if (hotel == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados do hotel
  FILE *arqConfirmacaoHotel;
  FILE *arqDadosHotel;
  arqConfirmacaoHotel = fopen("..//arqQuantidades//arqConfirmacaoHotel.txt", "r");
  if (arqConfirmacaoHotel == NULL)
  {
    arqConfirmacaoHotel = fopen("..//arqQuantidades//arqConfirmacaoHotel.txt", "w+");
    if (arqConfirmacaoHotel == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqConfirmacaoHotel);
    confirmacaoHotel = 0;
  }
  else
  {
    fscanf(arqConfirmacaoHotel, "%d", &confirmacaoHotel);
    fclose(arqConfirmacaoHotel);
  }
  if (confirmacaoHotel == 1)
  {
    arqDadosHotel = fopen("..//bancoDeDados//arqDadosHotel", "rb");
    fread(hotel, sizeof(structHotel), 1, arqDadosHotel);
    fflush(arqDadosHotel);
    fclose(arqDadosHotel);
  }

  // alocacao dinamica hospede
  structHospede *hospede;
  hospede = (structHospede *)malloc((quantidadeHospedes + 1) * sizeof(structHospede));
  if (hospede == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados dos hospedes
  FILE *arqQtdHospedes;
  FILE *arqDadosHospedes;
  arqQtdHospedes = fopen("..//arqQuantidades//arqQtdHospedes.txt", "r"); // carrega a variavel &quantidadeHospedes
  if (arqQtdHospedes == NULL)
  {
    arqQtdHospedes = fopen("..//arqQuantidades//arqQtdHospedes.txt", "w+");
    if (arqQtdHospedes == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdHospedes);
    arqQtdHospedes = 0;
  }
  else
  {
    fscanf(arqQtdHospedes, "%d", &quantidadeHospedes);
    fclose(arqQtdHospedes);
  }
  if (quantidadeHospedes > 0) // carrega o ponteiro hospede com os dados do arquivo de dados
  {
    hospede = realloc(hospede, (quantidadeHospedes + 1) * sizeof(structHospede));
    arqDadosHospedes = fopen("..//bancoDeDados//arqDadosHospedes", "rb");
    if (arqDadosHospedes == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosHospodes*!\n");
    fread(hospede, sizeof(structHospede), quantidadeHospedes, arqDadosHospedes);
    fflush(arqDadosHospedes);
    fclose(arqDadosHospedes);
  }

  // alocacao dinamica acomodacao
  structAcomodacao *acomodacao;
  acomodacao = (structAcomodacao *)malloc((quantidadeAcomodacoes + 1) * sizeof(structAcomodacao));
  if (acomodacao == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados de acomodacoes
  FILE *arqQtdAcomodacoes;
  FILE *arqDadosAcomodacoes;
  arqQtdAcomodacoes = fopen("..//arqQuantidades//arqQtdAcomodacoes.txt", "r"); // carrega a variavel &quantidadeAcomodacoes
  if (arqQtdAcomodacoes == NULL)
  {
    arqQtdAcomodacoes = fopen("..//arqQuantidades//arqQtdAcomodacoes.txt", "w+");
    if (arqQtdAcomodacoes == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdAcomodacoes);
    arqQtdAcomodacoes = 0;
  }
  else
  {
    fscanf(arqQtdAcomodacoes, "%d", &quantidadeAcomodacoes);
    fclose(arqQtdAcomodacoes);
  }
  if (quantidadeAcomodacoes > 0) // carrega o ponteiro acomodacao com os dados do arquivo de dados
  {
    acomodacao = realloc(acomodacao, (quantidadeAcomodacoes + 1) * sizeof(structAcomodacao));
    arqDadosAcomodacoes = fopen("..//bancoDeDados//arqDadosAcomodacoes", "rb");
    if (arqDadosAcomodacoes == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosAcomodacoes*!\n");
    fread(acomodacao, sizeof(structAcomodacao), quantidadeAcomodacoes, arqDadosAcomodacoes);
    fflush(arqDadosAcomodacoes);
    fclose(arqDadosAcomodacoes);
  }

  // alocacao dinamica categoriaAcomodação
  structCategoriaAcomodacao *categoriaAcomodacao;
  categoriaAcomodacao = (structCategoriaAcomodacao *)malloc((quantidadeCategorias + 1) * sizeof(structCategoriaAcomodacao));
  if (acomodacao == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados de acomodacoes
  FILE *arqQtdCategorias;
  FILE *arqDadosCategorias;
  arqQtdCategorias = fopen("..//arqQuantidades//arqQtdCategorias.txt", "r"); // carrega a variavel &quantidadeAcomodacoes
  if (arqQtdCategorias == NULL)
  {
    arqQtdCategorias = fopen("..//arqQuantidades//arqQtdCategorias.txt", "w+");
    if (arqQtdCategorias == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdCategorias);
    arqQtdCategorias = 0;
  }
  else
  {
    fscanf(arqQtdCategorias, "%d", &quantidadeCategorias);
    fclose(arqQtdCategorias);
  }
  if (quantidadeCategorias > 0) // carrega o ponteiro categoriaAcomodacao com os dados do arquivo de dados
  {
    categoriaAcomodacao = realloc(categoriaAcomodacao, (quantidadeCategorias + 1) * sizeof(structCategoriaAcomodacao));
    arqDadosCategorias = fopen("..//bancoDeDados//arqDadosCategorias", "rb");
    if (arqDadosCategorias == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosCategorias*!\n");
    fread(categoriaAcomodacao, sizeof(structCategoriaAcomodacao), quantidadeCategorias, arqDadosCategorias);
    fflush(arqDadosCategorias);
    fclose(arqDadosCategorias);
  }

  // alocacao dinamica produtosConsumo
  structProdutosConsumo *produtosConsumo;
  produtosConsumo = (structProdutosConsumo *)malloc((quantidadeProdutos + 1) * sizeof(structProdutosConsumo));
  if (produtosConsumo == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados dos produtosConsumo
  FILE *arqQtdProdudos;
  FILE *arqDadosProdutos;
  arqQtdProdudos = fopen("..//arqQuantidades//arqQtdProdutos.txt", "r");
  if (arqQtdProdudos == NULL)
  {
    arqQtdProdudos = fopen("..//arqQuantidades//arqQtdProdutos.txt", "w+");
    if (arqQtdProdudos == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdProdudos);
    arqQtdProdudos = 0;
  }
  else
  {
    fscanf(arqQtdProdudos, "%d", &quantidadeProdutos);
    fclose(arqQtdProdudos);
  }
  if (quantidadeProdutos > 0)
  {
    produtosConsumo = realloc(produtosConsumo, (quantidadeProdutos + 1) * sizeof(structProdutosConsumo));
    arqDadosProdutos = fopen("..//bancoDeDados//arqDadosProdutos", "rb");
    if (arqDadosProdutos == NULL)
      printf("\nErro ao abrir arquivo *arqDadosProdutos*");
    fread(produtosConsumo, sizeof(structProdutosConsumo), quantidadeProdutos, arqDadosProdutos);
    fflush(arqDadosProdutos);
    fclose(arqDadosProdutos);
  }

  // alocacao dinamimica de fornecedores
  structFornecedores *fornecedores;
  fornecedores = (structFornecedores *)malloc((quantidadeFornecedores + 1) * sizeof(structFornecedores));
  if (fornecedores == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados dos fornecedores
  FILE *arqQtdFornecedores;
  FILE *arqDadosFornecedores;
  arqQtdFornecedores = fopen("..//arqQuantidades//arqQtdFornecedores.txt", "r");
  if (arqQtdFornecedores == NULL)
  {
    arqQtdFornecedores = fopen("..//arqQuantidades//arqQtdFornecedores.txt", "w+");
    if (arqQtdFornecedores == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdFornecedores);
    arqQtdFornecedores = 0;
  }
  else
  {
    fscanf(arqQtdFornecedores, "%d", &quantidadeFornecedores);
    fclose(arqQtdFornecedores);
  }
  if (quantidadeFornecedores > 0)
  {
    fornecedores = realloc(fornecedores, (quantidadeFornecedores + 1) * sizeof(structFornecedores));
    arqDadosFornecedores = fopen("..//bancoDeDados//arqDadosFornecedores", "rb");
    if (arqDadosFornecedores == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosHospodes*!\n");
    fread(fornecedores, sizeof(structFornecedores), quantidadeFornecedores, arqDadosFornecedores);
    fflush(arqDadosFornecedores);
    fclose(arqDadosFornecedores);
  }

  // alocacao dinamica operadoresSistema
  structOperadoresSistema *operadoresSistema;
  operadoresSistema = (structOperadoresSistema *)malloc((quantidadeOperadores + 1) * sizeof(structOperadoresSistema));
  if (operadoresSistema == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados dos operadores do sistema
  FILE *arqQtdOperadores;
  FILE *arqDadosOperadores;
  arqQtdOperadores = fopen("..//arqQuantidades//arqQtdOperadores.txt", "r");
  if (arqQtdOperadores == NULL)
  {
    arqQtdOperadores = fopen("..//arqQuantidades//arqQtdOperadores.txt", "w+");
    if (arqQtdOperadores == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdOperadores);
    arqQtdOperadores = 0;
  }
  else
  {
    fscanf(arqQtdOperadores, "%d", &quantidadeOperadores);
    fclose(arqQtdOperadores);
  }
  if (quantidadeOperadores > 0)
  {
    operadoresSistema = realloc(operadoresSistema, (quantidadeOperadores + 1) * sizeof(structOperadoresSistema));
    arqDadosOperadores = fopen("..//bancoDeDados//arqDadosOperadores", "rb");
    if (arqDadosOperadores == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosOperadores*!\n");
    fread(operadoresSistema, sizeof(structOperadoresSistema), quantidadeOperadores, arqDadosOperadores);
    fflush(arqDadosOperadores);
    fclose(arqDadosOperadores);
  }

  //  alocaçao dinamica reserva
  structReserva *reserva;
  reserva = (structReserva *)malloc((quantidadeReservas + 1) * sizeof(structReserva));
  if (reserva == NULL)
  {
    printf("\nERRO! Memoria Insuficiente\n\n");
    exit(1);
  }
  // carrega os dados das reservas
  FILE *arqQtdReservas;
  FILE *arqDadosReservas;
  arqQtdReservas = fopen("..//arqQuantidades//arqQtdReservas.txt", "r");
  if (arqQtdReservas == NULL)
  {
    arqQtdReservas = fopen("..//arqQuantidades//arqQtdReservas.txt", "w+");
    if (arqQtdReservas == NULL)
    {
      printf("\nErro na abertura do arquivo.\n");
      exit(1);
    }
    fclose(arqQtdReservas);
    arqQtdReservas = 0;
  }
  else
  {
    fscanf(arqQtdReservas, "%d", &quantidadeReservas);
    fclose(arqQtdReservas);
  }
  if (quantidadeReservas > 0)
  {
    reserva = realloc(reserva, (quantidadeReservas + 1) * sizeof(structReserva));
    arqDadosReservas = fopen("..//bancoDeDados//arqDadosReservas", "rb");
    if (arqDadosReservas == NULL)
      printf("\nErro ao abrir o arquivo *arqDadosReservas*!\n");
    fread(reserva, sizeof(structReserva), quantidadeReservas, arqDadosReservas);
    fflush(arqDadosReservas);
    fclose(arqDadosReservas);
  }

  while (1)
  {
    menu = 0;

    data();

    printf("\n\t***MENU PRINCIPAL***");
    printf("\n1 - Módulo de Cadastros e gestão de dados");
    printf("\n2 - Módulo de Reservas");
    printf("\n3 - Módulo de Transações");
    printf("\n4 - Módulo de Feedback");
    printf("\n5 - Módulo de importação/exportação de dados");
    printf("\n6 - Sair");
    printf("\n--> ");
    scanf("%d", &menu);

    switch (menu)
    {
    case 1: // cadastros
      submenuCadastro = 0;
      while (submenuCadastro != 8)
      {
        printf("\nCadastros: ");
        printf("\n1 - Hotel");
        printf("\n2 - Hóspede");
        printf("\n3 - Acomodações");
        printf("\n4 - Categoria de Acomodações");
        printf("\n5 - Produtos disponiveis para consumo dos hospedes");
        printf("\n6 - Fornecedores");
        printf("\n7 - Operadores do sistema");
        printf("\n8 - Sair");
        printf("\n--> ");
        scanf("%d", &submenuCadastro);

        switch (submenuCadastro)
        {
        case 1: // crud hotel
          do
          {
            submenuLvl3 = 0;

            printf("\n1 - Atualizar dados do hotel");
            printf("\n2 - Ver dados");
            printf("\n3 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);

            switch (submenuLvl3)
            {
            case 1: // atualizar
              if (confirmaSeExisteHotelCadastrado(&confirmacaoHotel) == 1)
              {
                printf("\nJé existe um hotel cadastrado.");
                printf("\nDeseja altera-lo:\n1 - Sim | 2 - Não\n--> ");
                scanf("%d", &confirmacao);
                if (confirmacao == 2)
                {
                  break;
                }
              }
              setbuf(stdin, NULL);
              printf("\nNome fantasia do hotel: ");
              scanf("%[^\n]s", &hotelDados.nomeFantasia);
              setbuf(stdin, NULL);
              printf("\nRazão social: ");
              scanf("%[^\n]s", &hotelDados.razaoSocial);
              setbuf(stdin, NULL);
              printf("\nInscrição estadual: ");
              scanf("%[^\n]s", &hotelDados.inscricaoEstadual);
              setbuf(stdin, NULL);
              printf("\nCNPJ: ");
              scanf("%[^\n]s", &hotelDados.cnpj);
              printf("\nEndereço: ");
              setbuf(stdin, NULL);
              printf("\nCidade: ");
              scanf("%[^\n]s", &hotelDados.endereco.cidade);
              setbuf(stdin, NULL);
              printf("\nBairro: ");
              scanf("%[^\n]s", &hotelDados.endereco.bairro);
              setbuf(stdin, NULL);
              printf("\nRua: ");
              scanf("%[^\n]s", &hotelDados.endereco.rua);
              setbuf(stdin, NULL);
              printf("\nNumero: ");
              scanf("%[^\n]s", &hotelDados.endereco.numero);
              setbuf(stdin, NULL);
              printf("\nTelefone do hotel: ");
              scanf("%[^\n]s", &hotelDados.telefone);
              setbuf(stdin, NULL);
              printf("\nE-mail: ");
              scanf("%[^\n]s", &hotelDados.email);
              setbuf(stdin, NULL);
              printf("\nNome do responsavel (dono ou gerente): ");
              scanf("%[^\n]s", &hotelDados.nomeResponsavel);
              setbuf(stdin, NULL);
              printf("\nTelefone do responsavel: ");
              scanf("%[^\n]s", &hotelDados.telefoneResponsavel);
              setbuf(stdin, NULL);
              printf("\nHora de check-in (hh mm): ");
              do
              {
                scanf("%d", &hotelDados.horaCheckin);
                scanf("%d", &hotelDados.minutoCheckin);
              } while (hotelDados.horaCheckin > 24 || hotelDados.minutoCheckin > 60);
              setbuf(stdin, NULL);
              printf("\nHora de check-out (hh mm): ");
              do
              {
                scanf("%d", &hotelDados.horaCheckout);
                scanf("%d", &hotelDados.minutoCheckout);
              } while (hotelDados.horaCheckout > 24 || hotelDados.minutoCheckout > 60);
              setbuf(stdin, NULL);
              printf("\nMargem de lucro do produtos vendidos: ");
              scanf("%f", &hotelDados.margemLucro);

              printf("\nConfirma o cadastro do hotel?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              cadastrarHotel(&hotelDados, hotel, &confirmacaoHotel, arqConfirmacaoHotel, arqDadosHotel);
              printf("\nHotel cadastrado!\n\n");
              break;

            case 2: // exibe dados
              if (confirmacaoHotel != 1)
              {
                printf("\nNenhum hotel cadastrado!\n\n");
                break;
              }
              exibeHotel(hotel);
              break;

            case 3: // sair
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 3);

          break;

        case 2: // crud hospedes
          submenuLvl3 = 0;
          do
          {
            printf("\n1 - Cadastrar hospede");
            printf("\n2 - Buscar hospede");
            printf("\n3 - Listar todos os hospedes");
            printf("\n4 - Atualizar hospede");
            printf("\n5 - Deletar hospede");
            printf("\n6 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);

            switch (submenuLvl3)
            {
            case 1: // cadastro hospede
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &hospedeDados.codigo);
              if ((verificarCodigoHospede(hospede, &hospedeDados, &quantidadeHospedes)) == 1)
              {
                printf("\nCodigo ja cadastrado!\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nNome: ");
              scanf("%[^\n]s", &hospedeDados.nome);
              setbuf(stdin, NULL);
              printf("\nEndereço: ");
              printf("\nCidade: ");
              scanf("%[^\n]s", &hospedeDados.endereco.cidade);
              setbuf(stdin, NULL);
              printf("\nBairro: ");
              scanf("%[^\n]s", &hospedeDados.endereco.bairro);
              setbuf(stdin, NULL);
              printf("\nRua: ");
              scanf("%[^\n]s", &hospedeDados.endereco.rua);
              setbuf(stdin, NULL);
              printf("\nNumero: ");
              scanf("%[^\n]s", &hospedeDados.endereco.numero);
              setbuf(stdin, NULL);
              printf("\nCPF: ");
              scanf("%[^\n]s", &hospedeDados.cpf);
              setbuf(stdin, NULL);
              printf("\nTelefone: ");
              scanf("%[^\n]s", &hospedeDados.telefone);
              setbuf(stdin, NULL);
              printf("\nE-mail: ");
              scanf("%[^\n]s", &hospedeDados.email);
              do
              {
                setbuf(stdin, NULL);
                printf("\nSexo: \n1 - Masculino | 2 - Feminino: ");
                scanf("%d", &confirmacao);
                if (confirmacao == 1)
                {
                  strcpy(hospedeDados.sexo, "Masculino");
                }
                else if (confirmacao == 2)
                {
                  strcpy(hospedeDados.sexo, "Feminino");
                }
                else
                {
                  printf("\nOpção invalida.\n");
                }
              } while (confirmacao > 2);
              setbuf(stdin, NULL);
              do
              {
                printf("\nEstado civil\n(1 - Solteiro, 2 - Casado, 3 - Separado, 4 - Divorciado, 5 - Viuvo): ");
                scanf("%d", &confirmacao);
                if (confirmacao == 1)
                {
                  strcpy(hospedeDados.estadoCivil, "Solteiro");
                }
                else if (confirmacao == 2)
                {
                  strcpy(hospedeDados.estadoCivil, "Casado");
                }
                else if (confirmacao == 3)
                {
                  strcpy(hospedeDados.estadoCivil, "Separado");
                }
                else if (confirmacao == 4)
                {
                  strcpy(hospedeDados.estadoCivil, "Divorciado");
                }
                else if (confirmacao == 5)
                {
                  strcpy(hospedeDados.estadoCivil, "Viuvo");
                }
                else
                {
                  printf("\nOpção invalida.\n");
                }
              } while (confirmacao > 5);
              setbuf(stdin, NULL);
              printf("\nData de nascimento: ");
              do
              {
                printf("\nDia: ");
                scanf("%d", &hospedeDados.diaNasc);
              } while (hospedeDados.diaNasc > 30);
              do
              {
                printf("\nMes: ");
                scanf("%d", &hospedeDados.mesNasc);
              } while (hospedeDados.mesNasc > 12);
              do
              {
                printf("\nAno: ");
                scanf("%d", &hospedeDados.anoNasc);
              } while (hospedeDados.anoNasc < 1900);

              printf("\nConfirma o cadastro desse hospede?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              cadastrarHospede(hospede, &hospedeDados, &quantidadeHospedes);
              gerarArqHospedes(&hospedeDados, quantidadeHospedes, arqQtdHospedes, arqDadosHospedes);
              hospede = realloc(hospede, (quantidadeHospedes + 1) * sizeof(structHospede));
              printf("\nHospede cadastrado com sucesso!\n");

              break;

            case 2: // buscar hospede
              printf("\nInforme o codigo do hospede: ");
              scanf("%d", &hospedeDados.codigo);
              if ((verificarCodigoHospede(hospede, &hospedeDados, &quantidadeHospedes)) == 1)
              {
                exibeHospede(hospede, &hospedeDados, &quantidadeHospedes);
              }
              else
              {
                printf("\nCodigo não cadastrado!\n");
              }
              break;

            case 3: // listar todos os hospedes
              if (quantidadeHospedes > 0)
              {
                listarHospedes(hospede, &quantidadeHospedes);
              }
              else
              {
                printf("\nNenhum hospede cadastrado!\n");
              }
              break;

            case 4: // atualizar hospedes
              setbuf(stdin, NULL);
              printf("\nCodigo do hospede para ser alterado: ");
              scanf("%d", &hospedeDados.codigo);

              if (verificarCodigoHospede(hospede, &hospedeDados, &quantidadeHospedes) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nNome: ");
              scanf("%[^\n]s", &hospedeDados.nome);
              setbuf(stdin, NULL);
              printf("\nEndereço: ");
              printf("\nCidade: ");
              scanf("%[^\n]s", &hospedeDados.endereco.cidade);
              setbuf(stdin, NULL);
              printf("\nBairro: ");
              scanf("%[^\n]s", &hospedeDados.endereco.bairro);
              setbuf(stdin, NULL);
              printf("\nRua: ");
              scanf("%[^\n]s", &hospedeDados.endereco.rua);
              setbuf(stdin, NULL);
              printf("\nNumero: ");
              scanf("%[^\n]s", &hospedeDados.endereco.numero);
              setbuf(stdin, NULL);
              printf("\nCPF: ");
              scanf("%[^\n]s", &hospedeDados.cpf);
              setbuf(stdin, NULL);
              printf("\nTelefone: ");
              scanf("%[^\n]s", &hospedeDados.telefone);
              setbuf(stdin, NULL);
              printf("\nE-mail: ");
              scanf("%[^\n]s", &hospedeDados.email);
              do
              {
                setbuf(stdin, NULL);
                printf("\nSexo: \n1 - Masculino | 2 - Feminino: ");
                scanf("%d", &confirmacao);
                if (confirmacao == 1)
                {
                  strcpy(hospedeDados.sexo, "Masculino");
                }
                else if (confirmacao == 2)
                {
                  strcpy(hospedeDados.sexo, "Feminino");
                }
                else
                {
                  printf("\nOpção invalida.\n");
                }
              } while (confirmacao > 2);
              setbuf(stdin, NULL);
              do
              {
                printf("\nEstado civil\n(1 - Solteiro, 2 - Casado, 3 - Separado, 4 - Divorciado, 5 - Viuvo): ");
                scanf("%d", &confirmacao);
                if (confirmacao == 1)
                {
                  strcpy(hospedeDados.estadoCivil, "Solteiro");
                }
                else if (confirmacao == 2)
                {
                  strcpy(hospedeDados.estadoCivil, "Casado");
                }
                else if (confirmacao == 3)
                {
                  strcpy(hospedeDados.estadoCivil, "Separado");
                }
                else if (confirmacao == 4)
                {
                  strcpy(hospedeDados.estadoCivil, "Divorciado");
                }
                else if (confirmacao == 5)
                {
                  strcpy(hospedeDados.estadoCivil, "Viuvo");
                }
                else
                {
                  printf("\nOpção invalida.\n");
                }
              } while (confirmacao > 5);

              scanf("%[^\n]s", &hospedeDados.estadoCivil);
              setbuf(stdin, NULL);
              printf("\nData de nascimento: ");
              do
              {
                printf("\nDia: ");
                scanf("%d", &hospedeDados.diaNasc);
              } while (hospedeDados.diaNasc > 30);
              do
              {
                printf("\nMes: ");
                scanf("%d", &hospedeDados.mesNasc);
              } while (hospedeDados.mesNasc > 12);
              do
              {
                printf("\nAno: ");
                scanf("%d", &hospedeDados.anoNasc);
              } while (hospedeDados.anoNasc < 1900);

              printf("\nConfirma o atualização desse hospede?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              atualizarHospede(hospede, &hospedeDados, &quantidadeHospedes, arqDadosHospedes);
              printf("\nHospede atualizado!\n");

              break;

            case 5: // deletar hospede
              printf("\nCodigo do hospede: ");
              scanf("%d", &hospedeDados.codigo);
              if ((verificarCodigoHospede(hospede, &hospedeDados, &quantidadeHospedes)) == 0)
              {
                printf("\nCódigo não cadastrado!");
                break;
              }
              printf("\nRealmente deseja deletar esse hospede?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              deletarHospede(hospede, &hospedeDados, &quantidadeHospedes, arqQtdHospedes, arqDadosHospedes);
              hospede = realloc(hospede, (quantidadeHospedes + 1) * sizeof(structHospede));
              printf("\nHospede deletado!\n");

              break;

            case 6:
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 6);
          break;

        case 3: // crud acomodaçoes
          submenuLvl3 = 0;
          do
          {
            printf("\n1 - Cadastrar acomodação");
            printf("\n2 - Buscar acomodação");
            printf("\n3 - Listar todos os acomodações");
            printf("\n4 - Atualizar acomodação");
            printf("\n5 - Deletar acomodação");
            printf("\n6 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);

            switch (submenuLvl3)
            {
            case 1: // cadastrar acomodacao
              printf("\nCodigo: ");
              scanf("%d", &acomodacaoDados.codigo);
              if ((verificarCodigoAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes)) == 1)
              {
                printf("\nCodigo já cadastrado!\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nDescrição: ");
              scanf("%[^\n]s", &acomodacaoDados.descricao);
              setbuf(stdin, NULL);
              printf("\nFacilidades: ");
              scanf("%[^\n]s", &acomodacaoDados.facilidades);
              setbuf(stdin, NULL);
              printf("\nCategoria: ");
              scanf("%d", &acomodacaoDados.categoria);
              if (verificarAcomodacaoECategoria(&acomodacaoDados, categoriaAcomodacao, &quantidadeCategorias) == 0)
              {
                printf("\nCategoria não cadastrada.\nUtilize uma categoria já cadastrada ou cadastre uma nova.\n");
                break;
              }
              printf("\nConfirma o cadastro dessa acomodacao?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              cadastrarAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes);
              gerarArqAcomodacao(&acomodacaoDados, quantidadeAcomodacoes, arqQtdAcomodacoes, arqDadosAcomodacoes);
              acomodacao = realloc(acomodacao, (quantidadeAcomodacoes + 1) * sizeof(structAcomodacao));
              printf("\nAcomodação cadastrada com sucesso!\n");

              break;

            case 2: // buscar acomodacao
              setbuf(stdin, NULL);
              printf("\nInforme o codigo da acomodação: ");
              scanf("%d", &acomodacaoDados.codigo);
              if ((verificarCodigoAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes)) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
              }
              else
              {
                exibeAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes);
              }
              break;

            case 3: // listar acomodacoes
              if (quantidadeAcomodacoes > 0)
              {
                listarAcomodacoes(acomodacao, &quantidadeAcomodacoes);
              }
              else
              {
                printf("\nNenhuma acomodação cadastrada!\n");
              }
              break;

            case 4: // atualizar acomodacao
              setbuf(stdin, NULL);
              printf("\nCodigo da acomodação a ser alterada: ");
              scanf("%d", &acomodacaoDados.codigo);

              if ((verificarCodigoAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes)) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nDescrição: ");
              scanf("%[^\n]s", &acomodacaoDados.descricao);
              setbuf(stdin, NULL);
              printf("\nFacilidades: ");
              scanf("%[^\n]s", &acomodacaoDados.facilidades);
              setbuf(stdin, NULL);
              printf("\nCategoria: ");
              scanf("%d", &acomodacaoDados.categoria);
              if (verificarAcomodacaoECategoria(&acomodacaoDados, categoriaAcomodacao, &quantidadeCategorias) == 0)
              {
                printf("\nCategoria não cadastrada.\nUtilize uma categoria já cadastrada ou cadastre uma nova.\n");
                break;
              }
              printf("\nConfirma a atualização dessa acomodacao?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              atualizarAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes, arqDadosAcomodacoes);
              printf("\nAcomodação atualizada!\n");

              break;

            case 5: // deletar acomodacao
              setbuf(stdin, NULL);
              printf("\nCodigo da acomodacao: ");
              scanf("%d", &acomodacaoDados.codigo);
              if ((verificarCodigoAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes)) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }

              deletarAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes, arqQtdAcomodacoes, arqDadosAcomodacoes);
              acomodacao = realloc(acomodacao, (quantidadeAcomodacoes + 1) * sizeof(structAcomodacao));
              printf("\nAcomodação deletada.\n");

              break;

            case 6: // sair
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 6);
          break;

        case 4: // crud categorias acomodacoes
          submenuLvl3 = 0;
          do
          {
            printf("\n1 - Cadastrar categoria de acomodação");
            printf("\n2 - Buscar categoria de acomodação");
            printf("\n3 - Listar todas as categorias de acomodação");
            printf("\n4 - Atualizar categoria de acomodação");
            printf("\n5 - Deletar categoria de acomodação");
            printf("\n6 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);
            switch (submenuLvl3)
            {
            case 1: // cadastrar categoria
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &categoriaAcomodacaoDados.codigo);

              if ((verificaCodigoCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias)) == 1)
              {
                printf("\nCodigo ja cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nDescrição: \n1 - Standard | 2 - Luxo | 3 - Presidencial | 4 - Suite Familia | 5 - Super");
              printf("\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 1)
              {
                strcpy(categoriaAcomodacaoDados.descricao, "Standard");
              }
              else if (confirmacao == 2)
              {
                strcpy(categoriaAcomodacaoDados.descricao, "Luxo");
              }
              else if (confirmacao == 3)
              {
                strcpy(categoriaAcomodacaoDados.descricao, "Presidencial");
              }
              else if (confirmacao == 4)
              {
                strcpy(categoriaAcomodacaoDados.descricao, "Suite Familia");
              }
              else if (confirmacao == 5)
              {
                strcpy(categoriaAcomodacaoDados.descricao, "Super");
              }
              else
              {
                printf("\nOpção invalida!\nTente outra\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nValor da diaria: R$");
              scanf("%f", &categoriaAcomodacaoDados.valorDiaria);
              setbuf(stdin, NULL);
              printf("\nQuantidade de pessoas que comporta: ");
              scanf("%d", &categoriaAcomodacaoDados.quantMaxDePessoas);

              printf("\nConfirma o cadastro dessa categoria de acomodação?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              cadastrarCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias);
              gerarArqCategoria(&categoriaAcomodacaoDados, quantidadeCategorias, arqQtdCategorias, arqDadosCategorias);
              categoriaAcomodacao = realloc(categoriaAcomodacao, (quantidadeCategorias + 1) * sizeof(structCategoriaAcomodacao));
              printf("\nCategoria de acomodação cadastrada com sucesso!\n");

              break;

            case 2: // buscar categoria
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &categoriaAcomodacaoDados.codigo);

              if ((verificaCodigoCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias)) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
              }
              else
              {
                exibeCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias);
              }
              break;

            case 3: // listar categorias
              if (quantidadeCategorias > 0)
              {
                listarCategorias(categoriaAcomodacao, &quantidadeCategorias);
              }
              else
              {
                printf("\nNenhuma categoria de acomodação cadastrada!\n");
              }
              break;

            case 4: // atualizar categorias
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &categoriaAcomodacaoDados.codigo);
              if ((verificaCodigoCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias)) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nDescrição: ");
              scanf("%[^\n]s", &categoriaAcomodacaoDados.descricao);
              setbuf(stdin, NULL);
              printf("\nValor da diaria: R$");
              scanf("%f", &categoriaAcomodacaoDados.valorDiaria);
              setbuf(stdin, NULL);
              printf("\nQuantidade de pessoas que comporta: ");
              scanf("%d", &categoriaAcomodacaoDados.quantMaxDePessoas);
              printf("\nConfirma a atualização dessa categoria de acomodação?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              atualizarCategorias(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias, arqDadosCategorias);
              printf("\nCategoria atualizada!\n");
              break;

            case 5: // deletar categorias
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &categoriaAcomodacaoDados.codigo);
              if ((verificaCodigoCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias)) == 0)
              {
                printf("\nCodigo não cadastrado\n");
                break;
              }
              printf("\nRealmente deseja deletar essa categoria de acomodação?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              deletarCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias, arqQtdCategorias, arqDadosCategorias);
              categoriaAcomodacao = realloc(categoriaAcomodacao, (quantidadeCategorias + 1) * sizeof(structCategoriaAcomodacao));
              break;

            case 6: // voltar menu
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 6);
          break;

        case 5: // crud produtos
          submenuLvl3 = 0;
          do
          {
            printf("\n1 - Cadastrar produto");
            printf("\n2 - Buscar produto");
            printf("\n3 - Listar todos os produtos");
            printf("\n4 - Atualizar produto");
            printf("\n5 - Deletar produto");
            printf("\n6 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);

            switch (submenuLvl3)
            {
            case 1: // cadastrar produtos
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &produtosConsumoDados.codigo);
              if (verificarCodigoProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos) == 1)
              {
                printf("\nCodigo ja cadastrado!\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nDescrição: ");
              scanf("%[^\n]s", &produtosConsumoDados.descricao);
              setbuf(stdin, NULL);
              printf("\nEstoque: ");
              scanf("%d", &produtosConsumoDados.estoque);
              setbuf(stdin, NULL);
              printf("\nEstoque minimo: ");
              scanf("%d", &produtosConsumoDados.estoqueMinimo);
              setbuf(stdin, NULL);
              printf("\nPreço de custo: R$");
              scanf("%f", &produtosConsumoDados.precoCusto);
              setbuf(stdin, NULL);
              printf("\nPreço de venda: R$");
              scanf("%f", &produtosConsumoDados.precoVenda);

              printf("\nConfirma o cadastro desse produto?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              cadastrarProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos);
              gerarArqProdutos(&produtosConsumoDados, quantidadeProdutos, arqQtdProdudos, arqDadosProdutos);
              produtosConsumo = realloc(produtosConsumo, (quantidadeProdutos + 1) * sizeof(structProdutosConsumo));
              printf("\nProduto cadastrado com sucesso!\n");

              break;

            case 2: // buscar produtos
              setbuf(stdin, NULL);
              printf("\nInforme o codigo do produto: ");
              scanf("%d", &produtosConsumoDados.codigo);
              if (verificarCodigoProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos) == 1)
              {
                exibirProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos);
              }
              else
              {
                printf("\nCodigo não cadastrado!\n");
              }
              break;

            case 3: // listar todos os produtos
              if (quantidadeProdutos > 0)
              {
                listarProdutos(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos);
              }
              else
              {
                printf("\nNenhum produto cadastrado!\n");
              }
              break;

            case 4: // atualizar produto
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &produtosConsumoDados.codigo);
              if (verificarCodigoProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nDescrição: ");
              scanf("%[^\n]s", &produtosConsumoDados.descricao);
              setbuf(stdin, NULL);
              printf("\nEstoque: ");
              scanf("%d", &produtosConsumoDados.estoque);
              setbuf(stdin, NULL);
              printf("\nEstoque minimo: ");
              scanf("%d", &produtosConsumoDados.estoqueMinimo);
              setbuf(stdin, NULL);
              printf("\nPreço de custo: R$");
              scanf("%f", &produtosConsumoDados.precoCusto);
              setbuf(stdin, NULL);
              printf("\nPreço de venda: R$");
              scanf("%f", &produtosConsumoDados.precoVenda);

              printf("\nConfirma o atualização desse produto?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              atualizarProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos, arqDadosProdutos);
              printf("\nProduto atualizado!\n");
              break;

            case 5: // deletar produto
              setbuf(stdin, NULL);
              printf("\nCodigo do produto: ");
              scanf("%d", &produtosConsumoDados.codigo);
              if (verificarCodigoProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }
              printf("\nRealmente deseja deletar esse produto?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              deletarProduto(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos, arqQtdProdudos, arqDadosProdutos);
              produtosConsumo = realloc(produtosConsumo, (quantidadeProdutos + 1) * sizeof(structProdutosConsumo));
              printf("\nProduto deletado!\n");

              break;

            case 6:
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 6);
          break;

        case 6: // crud fornecedores
          submenuLvl3 = 0;
          do
          {
            printf("\n1 - Cadastrar fornecedor");
            printf("\n2 - Buscar fornecedor");
            printf("\n3 - Listar todos os fornecedores");
            printf("\n4 - Atualizar fornecedor");
            printf("\n5 - Deletar fornecedor");
            printf("\n6 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);

            switch (submenuLvl3)
            {
            case 1: // cadastrar fornecedor
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &fornecedoresDados.codigo);
              if ((verificarCodigoFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores)) == 1)
              {
                printf("\nCodigo já cadastrado.\n");
                break;
              }
              setbuf(stdin, NULL);
              printf("\nNome fantasia: ");
              scanf("%[^\n]s", &fornecedoresDados.nomeFantasia);
              setbuf(stdin, NULL);
              printf("\nRazão social: ");
              scanf("%[^\n]s", &fornecedoresDados.razaoSocial);
              setbuf(stdin, NULL);
              printf("\nInscrição estadual: ");
              scanf("%[^\n]s", &fornecedoresDados.inscricaoEstadual);
              setbuf(stdin, NULL);
              printf("\nCNPJ: ");
              scanf("%[^\n]s", &fornecedoresDados.cnpj);
              setbuf(stdin, NULL);
              printf("\nEndereço: ");
              printf("\nCidade: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.cidade);
              setbuf(stdin, NULL);
              printf("\nBairro: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.bairro);
              setbuf(stdin, NULL);
              printf("\nRua: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.rua);
              setbuf(stdin, NULL);
              printf("\nNumero: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.numero);
              setbuf(stdin, NULL);
              printf("\nTelefone: ");
              scanf("%[^\n]s", &fornecedoresDados.telefone);
              setbuf(stdin, NULL);
              printf("\nE-mail: ");
              scanf("%[^\n]s", &fornecedoresDados.email);

              cadastrarFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores);
              gerarArqFornecedor(&fornecedoresDados, quantidadeFornecedores, arqQtdFornecedores, arqDadosFornecedores);
              fornecedores = realloc(fornecedores, (quantidadeFornecedores + 1) * sizeof(structFornecedores));
              printf("\nFornecedor cadastrado com sucesso!\n");

              break;

            case 2: // buscar fornecedor
              setbuf(stdin, NULL);
              printf("\nInforme o codigo do fornecedor: ");
              scanf("%d", &fornecedoresDados.codigo);
              if ((verificarCodigoFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores)) == 1)
              {
                exibeFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores);
              }
              else
              {
                printf("\nCodigo não cadastrado.\n");
              }
              break;

            case 3: // listar todos os fornecedores
              if (quantidadeFornecedores > 0)
              {
                listarFornecedores(fornecedores, &quantidadeFornecedores);
              }
              else
              {
                printf("\nNenhum fornecedor cadastrado!\n");
              }
              break;

            case 4: // atualizar fornecedor
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &fornecedoresDados.codigo);

              if ((verificarCodigoFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores)) == 0)
              {
                printf("\nCodigo não cadastrado.\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nNome fantasia: ");
              scanf("%[^\n]s", &fornecedoresDados.nomeFantasia);
              setbuf(stdin, NULL);
              printf("\nRazão social: ");
              scanf("%[^\n]s", &fornecedoresDados.razaoSocial);
              setbuf(stdin, NULL);
              printf("\nInscrição estadual: ");
              scanf("%[^\n]s", &fornecedoresDados.inscricaoEstadual);
              setbuf(stdin, NULL);
              printf("\nCNPJ: ");
              scanf("%[^\n]s", &fornecedoresDados.cnpj);
              setbuf(stdin, NULL);
              printf("\nEndereço: ");
              printf("\nCidade: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.cidade);
              setbuf(stdin, NULL);
              printf("\nBairro: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.bairro);
              setbuf(stdin, NULL);
              printf("\nRua: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.rua);
              setbuf(stdin, NULL);
              printf("\nNumero: ");
              scanf("%[^\n]s", &fornecedoresDados.endereco.numero);
              setbuf(stdin, NULL);
              printf("\nTelefone: ");
              scanf("%[^\n]s", &fornecedoresDados.telefone);
              setbuf(stdin, NULL);
              printf("\nE-mail: ");
              scanf("%[^\n]s", &fornecedoresDados.email);
              printf("\nConfirma o atualização desse fornecedor?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              atualizaFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores, arqDadosFornecedores);
              printf("\nFornecedor atualizado!\n");
              break;

            case 5: // deletar fornecedor
              setbuf(stdin, NULL);
              printf("\nCodigo do fornecedor: ");
              scanf("%d", &fornecedoresDados.codigo);
              if ((verificarCodigoFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores)) == 0)
              {
                printf("\nCodigo não cadastrado.\n");
                break;
              }
              printf("\nRealmente deseja deletar esse fornecedor?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              deletarFornecedor(fornecedores, &fornecedoresDados, &quantidadeFornecedores, arqQtdFornecedores, arqDadosFornecedores);
              printf("\nFornecedor deletado!\n");
              break;

            case 6:
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 6);
          break;

        case 7: // crud operadores do sistema
          submenuLvl3 = 0;
          do
          {
            printf("\n1 - Cadastrar operador");
            printf("\n2 - Buscar operador");
            printf("\n3 - Listar todos os operadores");
            printf("\n4 - Atualizar operador");
            printf("\n5 - Deletar operador");
            printf("\n6 - Sair");
            printf("\n--> ");
            scanf("%d", &submenuLvl3);

            switch (submenuLvl3)
            {
            case 1: // casdastrar operador
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &operadoresSistemaDados.codigo);

              if (verificarCodigoOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores) == 1)
              {
                printf("\nCodigo já cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nNome: ");
              scanf("%[^\n]s", &operadoresSistemaDados.nome);
              setbuf(stdin, NULL);
              printf("\nUsuario: ");
              scanf("%[^\n]s", &operadoresSistemaDados.usuario);

              if (verificarUsuarioOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores) == 1)
              {
                printf("\nUsuario já cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nSenha: ");
              scanf("%[^\n]s", &operadoresSistemaDados.senha);

              do
              {
                setbuf(stdin, NULL);
                printf("\nNivel de permissão: ");
                printf("\n1-\tModulo de cadastros e gestão de dados\n\tModulo de Reservas\n");
                printf("\n2-\tModulo de cadastros e gestão de dados\n\tModulo de Reservas"
                       "\n\tModulo de transaçoes\n\tModulo feedback\n");
                printf("\n3-\tModulo de cadastros e gestão de dados\n\tModulo de Reservas"
                       "\n\tModulo de transaçoes\n\tModulo feedback\n\tModulo de importação e exportação de dados");
                printf("\n--> ");
                scanf("%d", &operadoresSistemaDados.permissoes);

                if (operadoresSistemaDados.permissoes < 1 || operadoresSistemaDados.permissoes > 3)
                {
                  printf("\nPermissão invalida.\nInsira uma das já cadastradas.\n");
                }
              } while (operadoresSistemaDados.permissoes < 1 || operadoresSistemaDados.permissoes > 3);

              printf("\nConfirma o cadastro desse operador?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              cadastrarOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores);
              gerarArqOperador(&operadoresSistemaDados, quantidadeOperadores, arqQtdOperadores, arqDadosOperadores);
              operadoresSistema = realloc(operadoresSistema, (quantidadeOperadores + 1) * sizeof(structOperadoresSistema));
              printf("\nOperador cadastrado com sucesso!\n");

              break;

            case 2: // buscar operador
              printf("\nInforme o codigo do operador: ");
              scanf("%d", &operadoresSistemaDados.codigo);
              if (verificarCodigoOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores) == 1)
              {
                exibeOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores);
              }
              else
              {
                printf("\nCodigo não cadastrado!\n");
              }
              break;

            case 3: // listar todos os operadores
              if (quantidadeOperadores > 0)
              {
                listaOperadores(operadoresSistema, &quantidadeOperadores);
              }
              else
              {
                printf("\nNenhum operador cadastrado!\n");
              }
              break;

            case 4: // atualizar operador
              setbuf(stdin, NULL);
              printf("\nCodigo: ");
              scanf("%d", &operadoresSistemaDados.codigo);

              if (verificarCodigoOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nNome: ");
              scanf("%[^\n]s", &operadoresSistemaDados.nome);
              setbuf(stdin, NULL);
              printf("\nUsuario: ");
              scanf("%[^\n]s", &operadoresSistemaDados.usuario);

              if (verificarUsuarioOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores) == 1)
              {
                printf("\nUsuario já cadastrado!\n");
                break;
              }

              setbuf(stdin, NULL);
              printf("\nSenha: ");
              scanf("%[^\n]s", &operadoresSistemaDados.senha);

              do
              {
                setbuf(stdin, NULL);
                printf("\nNivel de permissão: ");
                printf("\n1-\tModulo de cadastros e gestão de dados\n\tModulo de Reservas\n");
                printf("\n2-\tModulo de cadastros e gestão de dados\n\tModulo de Reservas"
                       "\n\tModulo de transaçoes\n\tModulo feedback\n");
                printf("\n3-\tModulo de cadastros e gestão de dados\n\tModulo de Reservas"
                       "\n\tModulo de transaçoes\n\tModulo feedback\n\tModulo de importação e exportação de dados");
                printf("\n--> ");
                scanf("%d", &operadoresSistemaDados.permissoes);

                if (operadoresSistemaDados.permissoes < 1 || operadoresSistemaDados.permissoes > 3)
                {
                  printf("\nPermissão invalida.\nInsira uma das já cadastradas.\n");
                }
              } while (operadoresSistemaDados.permissoes < 1 || operadoresSistemaDados.permissoes > 3);

              printf("\nConfirma o atualização desse operador?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }

              atualizaOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores, arqDadosOperadores);
              printf("\nOperador atualizado!\n");

              break;

            case 5: // deletar operador
              setbuf(stdin, NULL);
              printf("\nCodigo do operador: ");
              scanf("%d", &operadoresSistemaDados.codigo);
              if (verificarCodigoOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores) == 0)
              {
                printf("\nCodigo não cadastrado!\n");
              }
              printf("\nRealmente deseja deletar esse operador?"
                     "\n1 - Sim | 2 - Não"
                     "\n--> ");
              scanf("%d", &confirmacao);
              if (confirmacao == 2)
              {
                break;
              }
              deletarOperador(operadoresSistema, &operadoresSistemaDados, &quantidadeOperadores, arqQtdOperadores, arqDadosOperadores);
              operadoresSistema = realloc(operadoresSistema, (quantidadeOperadores + 1) * sizeof(structOperadoresSistema));
              printf("\nOperador deletado!\n");

              break;

            case 6:
              printf("\nVoltando...\n\n");
              break;

            default:
              printf("\n\nComando Inválido\n\n");
              break;
            }
          } while (submenuLvl3 != 6);
          break;

        case 8:
          printf("\nVoltando...\n\n");
          break;
        }
      }
      break;

    case 2: // crud reservas
      submenuCadastro = 0;
      while (submenuCadastro != 5)
      {
        printf("\nReservas: ");
        printf("\n1 - Fazer reserva");
        printf("\n2 - Verificar disponibilidade");
        printf("\n3 - Verificar reserva");
        printf("\n4 - Cancelar reserva");
        printf("\n5 - Sair");
        printf("\n--> ");
        scanf("%d", &submenuCadastro);

        switch (submenuCadastro)
        {
        case 1: // Fazer reserva
          printf("\nCodigo da reserva: ");
          scanf("%d", &reservaDados.codigo);
          if (verificarCodigoReserva(reserva, &reservaDados, &quantidadeReservas) == 1)
          {
            printf("\nCodigo já cadastrado!\nTente outro.\n");
            break;
          }

          do {
            printf("\nDia da entrada: ");
            scanf("%d", &reservaDados.diaEntrada);
            if (reservaDados.diaEntrada > 30 || reservaDados.diaEntrada < 1)
              printf("\nDia invaliddo!\n");
          } while (reservaDados.diaEntrada > 30 || reservaDados.diaEntrada < 1);
          do {
            printf("\nMes entrada: ");
            scanf("%d", &reservaDados.mesEntrada);
            if (reservaDados.mesEntrada > 12 || reservaDados.mesEntrada < 1)
              printf("\nMes invalido!\n");
          } while (reservaDados.mesEntrada > 12 || reservaDados.mesEntrada < 1);
          do {
            printf("\nAno de entrada: ");
            scanf("%d", &reservaDados.anoEntrada);
            if (reservaDados.anoEntrada < (tm.tm_year + 1900))
              printf("\nAno invalido!\n");
          } while (reservaDados.anoEntrada < (tm.tm_year + 1900));

          do {
            printf("\nDia da saida: ");
            scanf("%d", &reservaDados.diaSaida);
            if (reservaDados.diaSaida > 30 || reservaDados.diaSaida < 1)
              printf("\nDia invaliddo!\n");
          } while (reservaDados.diaSaida > 30 || reservaDados.diaSaida < 1);
          do {
            printf("\nMes da saida: ");
            scanf("%d", &reservaDados.mesSaida);
            if (reservaDados.mesSaida > 12 || reservaDados.mesSaida < 1)
              printf("\nMes invalido!\n");
          } while (reservaDados.mesSaida > 12 || reservaDados.mesSaida < 1);
          do {
            printf("\nAno de saida: ");
            scanf("%d", &reservaDados.anoSaida);
            if (reservaDados.anoSaida < (tm.tm_year + 1900))
              printf("\nAno invalido!\n");
          } while (reservaDados.anoSaida < (tm.tm_year + 1900));

          if (verifDatas(&reservaDados) == 0)
          {
            printf("\nData invalida!\n\n");
            break;
          }

          printf("\nCodigo da acomodação: ");
          scanf("%d", &reservaDados.codigoAcomodacao);
          if (verificarAcomodacaoECategoriaReserva(&reservaDados, categoriaAcomodacao, &quantidadeCategorias) == 0)
          {
            printf("\nCodigo não cadastrado.\nUtilize um já cadastrado anteriormente.\n");
            break;
          }

          if (verificaSePodeCadastrar(reserva, &reservaDados, quantidadeReservas) == 1)
          {
            printf("\nAcomodação não disponivel nessa data!\nTente outra data.\n");
            break;
          }

          printf("\nCodigo do hospede: ");
          scanf("%d", &reservaDados.codigoHospede);
          if (verificarCodigoHospedeReserva(hospede, &reservaDados.codigoHospede, &quantidadeHospedes) == 0)
          {
            printf("\nCodigo do hospede não cadastrado!\n");
            break;
          }

          printf("\nConfirma a reserva?\n1 - Sim | 2 - Não\n--> ");
          scanf("%d", &confirmacao);
          if (confirmacao == 2)
          {
            break;
          }

          cadastrarReserva(reserva, &reservaDados, &quantidadeReservas);
          gerarArqReservas(&reservaDados, quantidadeReservas, arqQtdReservas, arqDadosReservas);
          reserva = realloc(reserva, (quantidadeReservas + 1)*sizeof (structReserva));
          printf("\nReserva cadastrada com sucesso!\n");

          break;

        case 2: // Verificar diponibilidade
          printf("\n1 - Data (Não implementado)\n2 - Data e categoria de acomodação\n3 - Voltar");
          printf("\nVericar disponibilidade por: ");
          scanf("%d", &submenuLvl3);

          switch (submenuLvl3) {
            case 1: // verifica disponibilidade pela data
              do {
                printf("\nDia da entrada: ");
                scanf("%d", &reservaDados.diaEntrada);
                if (reservaDados.diaEntrada > 30 || reservaDados.diaEntrada < 1)
                  printf("\nDia invaliddo!\n");
              } while (reservaDados.diaEntrada > 30 || reservaDados.diaEntrada < 1);
              do {
                printf("\nMes entrada: ");
                scanf("%d", &reservaDados.mesEntrada);
                if (reservaDados.mesEntrada > 12 || reservaDados.mesEntrada < 1)
                  printf("\nMes invalido!\n");
              } while (reservaDados.mesEntrada > 12 || reservaDados.mesEntrada < 1);
              do {
                printf("\nAno de entrada: ");
                scanf("%d", &reservaDados.anoEntrada);
                if (reservaDados.anoEntrada < (tm.tm_year + 1900))
                  printf("\nAno invalido!\n");
              } while (reservaDados.anoEntrada < (tm.tm_year + 1900));

              do {
                printf("\nDia da saida: ");
                scanf("%d", &reservaDados.diaSaida);
                if (reservaDados.diaSaida > 30 || reservaDados.diaSaida < 1)
                  printf("\nDia invaliddo!\n");
              } while (reservaDados.diaSaida > 30 || reservaDados.diaSaida < 1);
              do {
                printf("\nMes da saida: ");
                scanf("%d", &reservaDados.mesSaida);
                if (reservaDados.mesSaida > 12 || reservaDados.mesSaida < 1)
                  printf("\nMes invalido!\n");
              } while (reservaDados.mesSaida > 12 || reservaDados.mesSaida < 1);
              do {
                printf("\nAno de saida: ");
                scanf("%d", &reservaDados.anoSaida);
                if (reservaDados.anoSaida < (tm.tm_year + 1900))
                  printf("\nAno invalido!\n");
              } while (reservaDados.anoSaida < (tm.tm_year + 1900));

              break;

            case 2: // verificar disponibilidade por data e acomodacao
              do {
                printf("\nDia da entrada: ");
                scanf("%d", &reservaDados.diaEntrada);
                if (reservaDados.diaEntrada > 30 || reservaDados.diaEntrada < 1)
                  printf("\nDia invaliddo!\n");
              } while (reservaDados.diaEntrada > 30 || reservaDados.diaEntrada < 1);
              do {
                printf("\nMes entrada: ");
                scanf("%d", &reservaDados.mesEntrada);
                if (reservaDados.mesEntrada > 12 || reservaDados.mesEntrada < 1)
                  printf("\nMes invalido!\n");
              } while (reservaDados.mesEntrada > 12 || reservaDados.mesEntrada < 1);
              do {
                printf("\nAno de entrada: ");
                scanf("%d", &reservaDados.anoEntrada);
                if (reservaDados.anoEntrada < (tm.tm_year + 1900))
                  printf("\nAno invalido!\n");
              } while (reservaDados.anoEntrada < (tm.tm_year + 1900));

              do {
                printf("\nDia da saida: ");
                scanf("%d", &reservaDados.diaSaida);
                if (reservaDados.diaSaida > 30 || reservaDados.diaSaida < 1)
                  printf("\nDia invaliddo!\n");
              } while (reservaDados.diaSaida > 30 || reservaDados.diaSaida < 1);
              do {
                printf("\nMes da saida: ");
                scanf("%d", &reservaDados.mesSaida);
                if (reservaDados.mesSaida > 12 || reservaDados.mesSaida < 1)
                  printf("\nMes invalido!\n");
              } while (reservaDados.mesSaida > 12 || reservaDados.mesSaida < 1);
              do {
                printf("\nAno de saida: ");
                scanf("%d", &reservaDados.anoSaida);
                if (reservaDados.anoSaida < (tm.tm_year + 1900))
                  printf("\nAno invalido!\n");
              } while (reservaDados.anoSaida < (tm.tm_year + 1900));

              printf("\nCodigo da acomodaçao: ");
              scanf("%d", &reservaDados.codigoAcomodacao);
              if (verificarCodigoReserva(reserva, &reservaDados, &quantidadeReservas) == 0)
              {
                printf("\nCodigo não cadastrado!\nTente outro.\n");
                break;
              }
              if (verificaSePodeCadastrar(reserva, &reservaDados, quantidadeReservas) == 1)
              {
                printf("\nAcomodação ocupada nessa data.\n");
              }
              else
              {
                printf("\nAcomodação livre nessa data.\n");
              }

              break;

            case 3:
              printf("\nVoltando...\n");
              break;

            default:
              printf("\nOpção invalida!\n\n");
              break;
          }

          break;

        case 3: // Verificar reserva
          printf("\nCodigo da reserva a ser verificada: ");
          scanf("%d", &reservaDados.codigo);
          if (verificarCodigoReserva(reserva, &reservaDados, &quantidadeReservas) == 1)
          {
            exibeReserva(reserva, &reservaDados, &quantidadeReservas);
          }
          else
          {
            printf("\nReserva não feita! \nTente outra.\n");
          }

          break;

        case 4: // Cancelar reserva
          printf("\nCodigo da reserva a ser cancelada: ");
          scanf("%d", &reservaDados.codigo);
          if (verificarCodigoReserva(reserva, &reservaDados, &quantidadeReservas) == 0)
          {
            printf("\nCódigo não cadastrado!\n");
            break;
          }

          printf("\nDeseja mesmo cancelar essa reserva?\n1 - Sim | 2 - Não\n--> ");
          scanf("%d", &confirmacao);
          if (confirmacao == 2)
          {
            break;
          }

          deletaReserva(reserva, &reservaDados, &quantidadeReservas, arqQtdReservas, arqDadosReservas);
          reserva = realloc(reserva, (quantidadeReservas + 1) * sizeof(structReserva));
          printf("\nReserva cancelada!\n");

          break;

        case 5: // Sair
          printf("\nVoltando...\n");
          break;

        default:
          printf("\n\nComando Invalido\n\n");
          break;
        }
      }
      break;

    case 3: // transaçoes
      submenuCadastro = 0;
      while (submenuCadastro != 8)
      {
        printf("\nTransações: ");
        printf("\n1 - Check-in");
        printf("\n2 - Check-out");
        printf("\n3 - Saida de produtos");
        printf("\n4 - Controle de caixa");
        printf("\n5 - Contas a receber");
        printf("\n6 - Entrada de produtos industrializados");
        printf("\n7 - Contas a pagar");
        printf("\n8 - Sair");
        printf("\n--> ");
        scanf("%d", &submenuCadastro);

        switch (submenuCadastro)
        {
          case 1: // check in
            printf("\nCodigo da reserva: ");
            scanf("%d", &reservaDados.codigo);
            if (verificarCodigoReserva(reserva, &reservaDados, &quantidadeReservas) == 0)
            {
              printf("\nReserva não feita. \nTente realizar o check-in com um codigo de reserva já feita.\n\n");
              break;
            }
            checkinDados.codigoReserva = reservaDados.codigo;
            posicao = retornaPosicaoCodigoReserva(reserva, &reservaDados, &quantidadeReservas);

            printf("\nCodigo do check-in: ");
            scanf("%d", &checkinDados.codigo);
            if (quantidadeCheckin > 0)
            {
              if (verifCodigoCheckin(checkin, &checkinDados, &quantidadeCheckin) == 1)
              {
                printf("\nCodigo já cadastrado!\nTente outro.\n\n");
                break;
              }
            }

            // calcular o preço da diaria
            aux2 = qtdDiasReserva(reserva, &reservaDados, &quantidadeReservas, posicao);

            checkinDados.totalConta = 0;

            acomodacaoDados.codigo = reserva[posicao].codigoAcomodacao;

            aux = retornaPosicaoAcomodacao(acomodacao, &acomodacaoDados, &quantidadeAcomodacoes);
            categoriaAcomodacaoDados.codigo = acomodacao[aux].categoria;

            aux = retornaPosicaoCategoria(categoriaAcomodacao, &categoriaAcomodacaoDados, &quantidadeCategorias);
            checkinDados.valorDiaria = categoriaAcomodacao[aux].valorDiaria * aux2; // aux2 é a qtd de dias
            printf("\nValor de aux2: %d", aux2);
            printf("\nValor de valorDiaria: %.2f", checkinDados.valorDiaria);

            printf("\n1 - Entrada | 2 - Saida\nPagar as diarias na: ");
            scanf("%d", &checkinDados.formaPagamento);

            printf("\n1 - Sim | 2 - Não\nConfirmar check-in: ");
            scanf("%d", &confirmacao);
            if (confirmacao == 2)
            {
              break;
            }
            printf("\nCheckin confirmado com sucesso!\n");

            if (checkinDados.formaPagamento == 1)
            {
              printf("\nTotal das diarias: R$%.2f", checkinDados.valorDiaria);

              printf("\n1 - Dinheiro | 2 - Cartão \nForma de pagamento: ");
              scanf("%d", &checkinDados.formaPagamento);
            }

            cadastrarCheckin(checkin, &checkinDados, &quantidadeCheckin);
            gerarArqChecki(&checkinDados, quantidadeCheckin, arqQtdCheckin, arqDadosCheckin);
            checkin = realloc(checkin, (quantidadeCheckin + 1) * sizeof(structCheckin));

            break;

          case 2: // check out (não funcional)
            printf("\nCodigo do checkin para o checkout: ");
            scanf("%d", &checkinDados.codigo);
            if(verifCodigoCheckin(checkin, &checkinDados, &quantidadeCheckin) == 0)
            {
              printf("\nCogido invalido\n\n");
              break;
            }
            break;

          case 3: // saida de produtos
            printf("\nCodigo do checkin do cliente: ");
            scanf("%d", &checkinDados.codigo);
            if(verifCodigoCheckin(checkin, &checkinDados, &quantidadeCheckin) == 0)
            {
              printf("\nCogido invalido\n\n");
              break;
            }

            vendas->codigoCheckin = checkinDados.codigo;
            vendas->totalTemp = 0;

            do {
              printf("\nAdicionar produtos vendidos?\n1 - Sim | 2 - Não\n--> ");
              scanf("%d", &confirmacao);

              printf("\nQuantidade de produtos: ");
              scanf("%d", &vendas->quantidadeProdutos);
              printf("\nValor do produto: ");
              scanf("%f", &vendas->valorProduto);

              vendas->totalTemp = vendas->valorProduto * vendas->quantidadeProdutos;
            } while (confirmacao == 1);
            vendas->valorTotalProtudos = vendas->totalTemp;

            break;

          case 8: // voltar
            printf("\nVoltando...\n");
            break;

          default:
            printf("\nOpção Invalida\n\n");
            break;
        }
      }

      break;

    case 4: // feedback
      submenuCadastro = 0;
      while (submenuCadastro != 6)
      {
        printf("\n1 - Listagem hospedes\n2 - Listagem acomodaçoes\n3 - Listagem reservas"
               "\n4 - Listagem produtos consumo\n5 - Listagem categorias acomodaçoes\n6 - Sair\n--> ");
        scanf("%d", &submenuCadastro);

        switch (submenuCadastro)
        {
          case 1: // hospedes
            printf("\n1 - CSV | 2 - Tela");
            scanf("%d", &aux);

            if(aux == 1)
            {
              csvHospede(hospede, quantidadeHospedes);
            }
            else
            {
              listarHospedes(hospede, &quantidadeHospedes);
            }

            break;

          case 2: // acomodacoes
            printf("\n1 - CSV | 2 - Tela");
            scanf("%d", &aux);

            if(aux == 1)
            {
              csvAcomodacoes(acomodacao, quantidadeAcomodacoes);
            }
            else
            {
              listarAcomodacoes(acomodacao, &quantidadeAcomodacoes);
            }
            break;

          case 3: // reservas
            printf("\n1 - CSV | 2 - Tela");
            scanf("%d", &aux);

            if(aux == 1)
            {
              csvReservas(reserva, quantidadeReservas);
            }
            else
            {
              listarReservas(reserva, &quantidadeReservas);
            }
            break;

          case 4: // produtos consumo
            printf("\n1 - CSV | 2 - Tela");
            scanf("%d", &aux);

            if(aux == 1)
            {
              csvProdutosConsumo(produtosConsumo, quantidadeProdutos);
            }
            else
            {
              listarProdutos(produtosConsumo, &produtosConsumoDados, &quantidadeProdutos);
            }
            break;

          case 5: // categoria acomodação
            printf("\n1 - CSV | 2 - Tela");
            scanf("%d", &aux);

            if(aux == 1)
            {
              csvCategorias(categoriaAcomodacao, quantidadeCategorias);
            }
            else
            {
              listarCategorias(categoriaAcomodacao, &quantidadeCategorias);
            }
            break;

          case 6:
            printf("\nSaindo...\n\n");
            break;

        }
      }

      break;

    case 5: // importaçao e exportaçao
      break;

    case 6: // sair
      printf("\nSaindo...\n\n");
      exit(1);
      break;

    default:
      printf("\n\nComando Inválido\n\n");
      break;
    }
  }

  return 0;
}

int verificarAcomodacaoECategoria(structAcomodacao *acomodacaoDados, structCategoriaAcomodacao *categoriaAcomodacao, int *quantidadeCategorias)
{
  for (int i = 0; i < (*quantidadeCategorias); ++i)
  {
    if (acomodacaoDados->categoria == (categoriaAcomodacao + i)->codigo)
    {
      return 1;
    }
  }
  return 0;
}

int verificarAcomodacaoECategoriaReserva(structReserva *reservaDados, structCategoriaAcomodacao *categoriaAcomodacao, int *quantidadeCategorias)
{
  for (int i = 0; i < (*quantidadeCategorias); ++i) {
    if (reservaDados->codigoAcomodacao == (categoriaAcomodacao + i)->codigo)
    {
      return 1;
    }
  }
  return 0;
}

int verificarCodigoHospedeReserva(structHospede *hospede, structReserva *structReservaDados, int *quantidadeHospedes)
{
  for (int i = 0; i < (*quantidadeHospedes); ++i) {
    if ((hospede + i)->codigo == structReservaDados->codigoHospede)
    {
      return 1;
    }
  }
  return 0;
}