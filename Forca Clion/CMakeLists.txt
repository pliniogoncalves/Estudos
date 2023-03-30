cmake_minimum_required(VERSION 3.25)
project(Forca_Clion)

set(CMAKE_CXX_STANDARD 11)

add_executable(Forca_Clion forca.cpp forca.cpp imprime_cabecalho.cpp ler_arquivo.cpp sorteia_palavra.cpp imprime_erros.cpp imprime_palavra.cpp chuta.cpp nao_acertou.cpp nao_enforcou.cpp resultado.cpp letra_existe.cpp adciona_palavra.cpp salva_arquivo.cpp)
