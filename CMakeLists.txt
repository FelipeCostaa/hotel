cmake_minimum_required(VERSION 3.17)
project(hotel C)

set(CMAKE_C_STANDARD 11)

add_executable(hotel main.c hotel.c hotel.h acomodacao.c acomodacao.h categoriaAcomodacao.c categoriaAcomodacao.h fornecedor.c fornecedor.h hospede.c hospede.h operadorSistema.c operadorSistema.h produtosDisponiveis.c produtosDisponiveis.h horaData.c horaData.h reserva.c reserva.h transacoes.c transacoes.h vendas.c vendas.h feedback.c feedback.h exportar.c exportar.h)