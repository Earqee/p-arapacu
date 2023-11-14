# Compressão de Huffman

Este software consiste em uma implementação em C do algoritmo de compressão Huffman. O algoritmo de Huffman é um método popular para compressão de dados sem perdas, utilizado em diversas aplicações, incluindo compactação de arquivos. Esta implementação em C busca ser extremamente eficiente e eficaz para que seja usada como base no desenvolvimento de outras aplicações que manipulem dados compactados ou criptografados.

## Estrutura do Projeto

O projeto está organizado em vários módulos, cada um responsável por uma parte específica do algoritmo. Aqui estão os principais componentes:

### Estruturas Básicas

- **Bit Manipulation (`bit.h`):** Define uma estrutura `BIT_MANIP` para manipulação de bits e operações relacionadas.

- **Hash Table (`hash.h`):** Implementa uma tabela de dispersão (`HASH`) para contagem de frequências dos caracteres no arquivo.

- **Heap (`heap.h`):** Define uma estrutura de heap (`HEAP`) utilizada na construção da árvore de Huffman. A utilização de uma heap como fila de prioridade é ótima em relação a uma fila comum, pois permite acesso eficiente ao elemento de maior prioridade (neste caso, menor frequência) e a inserção e remoção de elementos com complexidade O(log n), onde n é o número de elementos na heap.

- **Lista Encadeada (`list.h`):** Implementa uma lista encadeada (`LIST`) usada para diversas finalidades, incluindo armazenar códigos de compressão.

### Árvore de Huffman

- **Árvore Binária (`tree.h`):** Define a estrutura da árvore de Huffman (`BINARY_TREE`) e os nós da árvore (`TREE_NODE`).

- **Dados de Huffman (`huff_data.h`):** Contém a definição e operações relacionadas aos dados de Huffman (`HUFF_DATA`), que incluem caracteres e suas frequências.

### Compressão e Descompressão

- **Compressão (`compress.h`):** Implementa funções para contar frequências, construir a árvore de Huffman, gerar códigos de compressão e realizar a compressão efetiva do arquivo.

- **Descompressão (`decompress.h`):** Contém as funções necessárias para extrair informações do cabeçalho do arquivo comprimido e realizar a descompressão.

### Utilitários

- **Utilitários (`utility.h`):** Fornece funções utilitárias, como leitura do arquivo de entrada e caminhadas pela árvore de Huffman.

## Como Usar

1. **Compilação:**
   ```bash
   gcc -o huffman main.c
   ```

2. **Compressão:**
   ```bash
   ./huffman -c arquivo.txt
   ```

3. **Descompressão:**
   ```bash
   ./huffman -d comprimido.bin
   ```

## Destaques

- **Eficiência de Compressão:** O algoritmo de Huffman é conhecido por sua eficiência na compressão de dados, especialmente em cenários onde certos caracteres são mais frequentes do que outros.

- **Organização Modular:** O código é organizado em módulos separados, facilitando a compreensão, manutenção e reutilização de componentes individuais.

- **Implementação em C:** A implementação em C oferece desempenho eficiente e portabilidade.

- **Uso Eficiente de Heap:** A utilização de uma heap como fila de prioridade na construção da árvore de Huffman contribui para a eficiência do algoritmo, permitindo operações de inserção e remoção com complexidade O(log n), otimizando o acesso aos elementos de maior prioridade.

- **Comentários Descritivos:** O código contém comentários descritivos para auxiliar na compreensão de cada função e trecho.

Este projeto fornece uma implementação sólida e organizada do algoritmo de compressão Huffman em C. Sinta-se à vontade para explorar, contribuir ou utilizar conforme necessário!


## Agradecimentos

Este projeto foi desenvolvido e revisado pelos discentes de Engenharia de Computação Thiago José, Hugo Tallys, Valério Nogueira e José Augusto, com revisão final pelo Prof. Dr. Márcio Ribeiro.

