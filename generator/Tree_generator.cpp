#pragma once

#include "Tree_generator.hpp"

char getRandomStartChar() {
    return 'a' + rand() % 26; // Gera um caractere aleatório de 'a' a 'z'
}


string Tree_generator::createTree(int depth, char startChar) {
    if (depth == 0) return std::string(1, startChar);

    std::string tree = "{";
    tree += startChar;

    int numChildren = rand() % 3; // Número aleatório de filhos (0 a 2)

    for (int i = 0; i < numChildren; ++i) {
        tree += createTree(depth - 1, getRandomStartChar());
    }

    tree += "}";
    return tree;
}


void Tree_generator::generateTree(int depth, int numTests){

    srand(static_cast<unsigned int>(time(0))); // Inicializa o gerador de números aleatórios


    // Escrevendo o JSON no arquivo
    std::ofstream file("tests/trees.json");
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo para escrita." << std::endl;
        return;
    }

    file << "[" << endl;

    for (int i = 0; i < numTests; i++)
    {

        file << "   {" << endl;
        file << "       \"ID\":"<< i+1 << "," << endl;
        file << "       \"t1\":\"" << createTree(depth, getRandomStartChar()) << "\", " << endl;
        file << "       \"t2\":\"" << createTree(depth, getRandomStartChar()) << "\"" << endl;
        file << "   }";

        if (i!= numTests - 1) file << "," << endl;
        
    }
    file <<endl << "]" << endl;

    file.close();

    std::cout << "Arquivo JSON criado com sucesso!" << std::endl;

}