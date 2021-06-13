//
// Created by felipe on 27/01/2021.
//

#ifndef HOTEL_FORNECEDOR_H
#define HOTEL_FORNECEDOR_H

#endif //HOTEL_FORNECEDOR_H

// constantes
#define CHAR_P 32
#define CHAR_M 64
#define CHAR_G 128

typedef struct structFornecedores
{
    int codigo;
    char nomeFantasia[CHAR_G];
    char razaoSocial[CHAR_G];
    char inscricaoEstadual[CHAR_P];
    char cnpj[CHAR_P];
    structEndereco endereco;
    char telefone[CHAR_P];
    char email[CHAR_G];
} structFornecedores;

int verificarCodigoFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores);

void cadastrarFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores);

void gerarArqFornecedor(structFornecedores *fornecedorDados, int quantidadeFornecedores, FILE *arqQtdFornecedores,
                        FILE *arqDadosFornecedores);

void exibeFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores);

void listarFornecedores(structFornecedores *fornecedores, int *quantidadeFornecedores);

void atualizaFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores,
                        FILE *arqDadosFornecedores);

void deletarFornecedor(structFornecedores *fornecedores, structFornecedores *fornecedoresDados, int *quantidadeFornecedores,
                       FILE *arqQtdFornecedores, FILE *arqDadosFornecedores);
