#include <stdio.h>

/*
 * Compile: gcc rule110.c -o rule110
 * Exec: ./rule110
 */

/* 
 * pré-processamento
 * 
 * onde houver BOARD_CAP, coloque 100
 */
#define BOARD_CAP 100

/* 
 * array
 *
 * modificador de tipo de armazenamento: static
 * tipo:  int
 * nome:  board
 * nº:    100 posições
 */
static int board[BOARD_CAP];

int main(int argc, char *argv[])
{
  /* 
   * Coloque o valor 1, na penúltima posição do array.
   * Como o array tem 100 posições, BOARD_CAP == 100,
   * o valor 1 estará na posição 98.
   */
  board[BOARD_CAP - 2] = 1;

  /* Começe da posição 0 e vá até 98, onde o valor é igual a 1 */
  for (size_t i = 0; i < BOARD_CAP - 2; ++i) {

  /* Começe da posição 0 e vá até 100 */
    for (size_t j = 0; j < BOARD_CAP; ++j) {
    /* 
     * Printa um espaço e um asterísco, conforme a a passagem do for
     *
     * fputc -> exibe 1 caracter de tamanho unsigned char
     */
      fputc(" *"[board[j]], stdout); 
    }
    fputc('\n', stdout); /* Pula linha */

    /* 
     * Desloca para esquerda (multiplica por 2 elevado a 1), o primeiro valor dentro do array 
     *
     *      board[0] * 2^1
     *
     *
     * O operador OR, representado por |, é usado para ligar o bit mais significativo
     * Então, pega-se o valor multiplicado e aplica a tabela verdade do OR:
     *
     *
     *      Operador Bit a Bit
     *
     *           OR
     *
     *       p  q   p | q
     *       0  0     1
     *       0  1     1
     *       1  0     1
     *       1  1     0
     *
     * Note o exemplo abaixo:
     *         128 | 3;        // 128 em binário, complemento de 2
     *
     *         1000 0000
     *       | 0000 0011
     *         ---------
     *         1000 0011
     */
    int pattern = (board[0] << 1) | board[1]; 

    /* 
     * j
     *
     * tipo:  size_t (Segundo esse artigo o tipo serve para representar tamanhos em bytes de objetos)
     * nome:  j
     * nº:    1
     *
     * A variável "j" vai de 1 até o complemento do array menos 1,
     * como o array "BOARD_CAP" vale 100, 
     * "j" vai de 1 até 99
     *
     *
     * "pattern" sofre um deslocamento de um bit para a esquerda:
     *      pattern << 1 -> pattern * 2^1
     * o que significa que o valor contido em "pattern", está sendo dobrado.
     *
     *
     * Operador Bit a Bit
     *
     *      AND
     *
     *  p  q   p & q
     *  0  0     0
     *  0  1     0
     *  1  0     0
     *  1  1     1
     *
     * Usado para desligar a paridade do bit (o bit mais significaivo)
     *
     * Ex:
     *    int A = 65;
     *
     *    a & 7;       // 7 em binário, complemento de 2
     *
     *    1000 0001
     *  & 0000 0111
     *    ---------
     *    0000 0001
     *
     *
     * Em seguida, a variável "j", que começa com o valor 1,
     * é utilizada para acessar os elementos dentro do array,
     * a partir da posição 3 (array começa no 0).
     *
     *    ex primeira iteração:
     *        board[j + 1]; -> board[1 + 1]; -> board[2];
     *
     *
     * Operador Bit a Bit
     *
     *      OR
     *
     *  p  q   p | q
     *  0  0     1
     *  0  1     1
     *  1  0     1
     *  1  1     0
     *
     * Usado para ligar a paridade do bit (o bit mais significaivo)
     *
     * Ex:
     *    128 | 3;        // 128 em binário, complemento de 2
     *
     *    1000 0000
     *  | 0000 0011
     *    ---------
     *    1000 0011
     *
     *
     * Já em o array "board" na posição "j" ( board[j] ),
     * recebe a variável "pattern" deslocada 110 bits apara a direita:
     *      110 >> pattern -> 2^110 * pattern
     *
     * Em seguida, um and é aplicado a este código.
     */
    for (size_t j = 1; j < BOARD_CAP - 1; ++j) {
      pattern = ( (pattern << 1) & 7 ) | board[j + 1];
      board[j] = (110 >> pattern) & 1;
    }

  }
  return 0;
}

/*
 * REFERÊNCIAS
 *
 * [Quando usar size_t?](https://pt.stackoverflow.com/questions/59369/quando-usar-size-t)
 */
