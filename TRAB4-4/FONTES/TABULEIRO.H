#if ! defined( TABULEIRO_ )
#define TABULEIRO_

/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: lr - Lucas Rodrigues 
*
*  $HA Histórico de evolução:
*     Versão |  Autor  |      Data     |    Observações
*       2    |   lr    |  16/out/2016  | finalização de desenvolvimento
*       1    |   lr    |  28/set/2016  | início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa um tabuleiro de ludo.
*     O tabuleiro possui uma cabeça encapsulando o seu estado.
*     É possivel criar um tabuleiro, deletar um tabuleiro,
*     inserir peca em um tabuleiro, mover peca de um tabuleiro,
*     e gera valor aleatório representando o dado.
*
*     Observacao importante: O modulo do tabuleiro não se importa
*     com as regras do jogo de ludo, o modulo do jogo apenas chamará as 
*     funções do tabuleiro caso essas regras sejam previamente testadas, 
*     por exemplo: o jogo avaliará se o jogador poderá mover a peça para
*     uma casa X, caso ele puder ele chama o modulo tabuleiro.
*   
***************************************************************************/

#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
    #define TABULEIRO_EXT extern
#endif

#include "LCIRC.H"
#include "LISTA.H"
#include "PECAS.H"

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

   typedef enum {

          TAB_CondRetOK,
          /* Concluiu corretamente */   

          TAB_CondRetFaltouMemoria, 
          /* Faltou Memoria */

          TAB_CondRetPecaNaoExiste,
          /* Peça não criada */
         
          TAB_CondRetPecaMorta,
          /* Peça fora de jogo */

          TAB_CondRetNaoEncontrouPeca,
          /* Não encontrou */

          TAB_CondRetCorInvalida,
          /* Cor inválida */
          
          TAB_CondRetFimTabuleiro
          /* Chegou ao final do tabuleiro */
   
   } TAB_CondRet ;

/********** Estrutura Encapsulada Pelo Módulo ************************/

typedef struct Tabuleiro * TAB_tpLudo;

/***********************************************************************
*
*  $FC Função: TAB  &Cria Tabuleiro
*
*  $ED Descrição da função
*     Cria uma tabuleiro de ludo utilizando lista circular e lisa encadeada. 
*     Ele pode armazenar peças de qualquer tipo.
*
*  $EP Parâmetros
*     * pTabuleiro - ponteiro para tabuleiro a ser criado.
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente a criaçao do tabuleiro
*     TAB_CondRetFaltouMemoria - Se houve algum problema de memoria
*
***********************************************************************/

/* Assertivas de Entrada TAB_CriaTabuleiro_Ludo
*  Ter memoria suficiente para criacao da estrutura de tabuleiro
*  O tabuleiro passado como parâmetro faz sentido
*
*  Fim Assertivas de Entrada TAB_CriaTabuleiro_Ludo */

TAB_CondRet TAB_CriaTabuleiro_Ludo( TAB_tpLudo * pTabuleiro ) ; 

/* Assertivas de Saida TAB_CriaTabuleiro_Ludo
*  A memoria referente a estrutura do tabuleiro tem que ser alocada
*  A funcao retornara um TAB_CondRet
*
*  Fim Assertiva de Saida TAB_CriaTabuleiro_Ludo */


/***********************************************************************
*
*  $FC Função: TAB  &Gera Valor
*
*  $ED Descrição da função
*     Gera valor de 1 a 6 de um dado.
*
*  $EP Parâmetros
*      * pValor -  ponteiro para endereço onde será armazenado o valor
*                    o valor aleatório gerado pelo dado.
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se valor está dentro do padrão (Número de 1 a 6)    
*   
***********************************************************************/

/* Assertiva de Entrada TAB_LancaDado
*  Endereço passado como parâmetro deve fazer referência correta.
*
*  Fim Assertiva de Entrada TAB_LancaDado */

TAB_CondRet TAB_LancaDado ( int * pValor ) ;

/* Assertiva de Saida TAB_LancaDado
*  O valor gerado deverá ser corretamente armazenado em pValor.
*  A funcao retorna um TAB_CondRet.
*
*  Fim Assertiva de Saida TAB_LancaDado */

/***********************************************************************
*
*  $FC Função: TAB  &Destroi tabuleiro
*
*  $ED Descrição da função
*     Destrói o tabuleiro criado.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro a destruir.    
*
*  $FV Valor retornado
*     TAB_CondRetOK - destruiu corretamente.
*
***********************************************************************/

/* Assertivas de entrada TAB_DestruirTabuleiro
*  Existir um tabuleiro ja criado
* 
*  Fim Assertivas de Entrada TAB_DestruirTabuleiro */

TAB_CondRet TAB_DestruirTabuleiro ( TAB_tpLudo pTabuleiro ) ;

/*  Assertiva de Saida TAB_DestruirTabuleiro
*   O tabuleiro deve ser destruido
*   Para todo pTabuleiro, pTabuleiro = NULL
*   A memoria deve ser liberada para todo pTabuleiro
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_DestruirTabuleiro */

/***********************************************************************
*
*  $FC Função: TAB  &Procura Peça
*
*  $ED Descrição da função
*     Procura uma determinada peça no tabuleiro.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro tabuleiro passado como referencia  
*     pPeca - ponteiro para peça a ser procuurada. 
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*     TAB_CondRetPecaNaoExiste - se peça procurada não existe.
*     TAB_CondRetPecaMorta - se peça está fora de jogo.
*     TAB_CondRetNaoEncontrouPeca - se a peça procurada não foi encontrada.
*
***********************************************************************/

/* Assertivas de entrada TAB_ProcuraPeca
*  Existir um tabuleiro ja criado.
*  Existir já uma peça criada.
*  Ponteiros do parâmetro devem fazer referência correta.
*
*  Fim Assertivas de Entrada TAB_ProcuraPeca */

TAB_CondRet TAB_ProcuraPeca ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) ;

/*  Assertiva de Saida TAB_ProcuraPeca
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_ProcuraPeca */

/***********************************************************************
*
*  $FC Função: TAB  &Obter Peça Casa
*
*  $ED Descrição da função
*     Obtem uma peça dentro de uma casa no tabuleiro.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     pPeca - ponteiro para lugar a ser aramzenado dados da Peça   
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*
***********************************************************************/

/* Assertivas de entrada TAB_ObterPecaCasa
*  Existir um tabuleiro ja criado.
*  Ponteiros do parâmetro devem fazer referência correta.
*
*  Fim Assertivas de Entrada TAB_ObterPecaCasa */

TAB_CondRet TAB_ObterPecaCasa ( TAB_tpLudo pTabuleiro, PEC_tpPeca *pPeca ) ;

/*  Assertiva de Saida TAB_ObterPecaCasa
*   O ponteiro pPeca deverá ser modificado.
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_ObterPecaCasa */

/***********************************************************************
*
*  $FC Função: TAB  &Avança Casa
*
*  $ED Descrição da função
*     Avança, dado um valor n, n casas no tabuleiro.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     cor - informação da cor da casa para qual será avançada. 
*     n - numero inteiro de casas a ser avançadas. 
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*     TAB_CondRetCorInvalida - caso a cor passada seja inválida.
*     TAB_CondRetFimTabuleiro - caso tenha chegado ao "fim" do tabuleiro.
*
***********************************************************************/

/* Assertivas de entrada TAB_AvancaCasa
*  Existir um tabuleiro ja criado.
*  A cor passada como parâmetro deverá ser válida (cor entre 0 e 3).
*
*  Fim Assertivas de Entrada TAB_AvancaCasa */

TAB_CondRet TAB_AvancaCasa ( TAB_tpLudo pTabuleiro , int cor , int n ) ;

/*  Assertiva de Saida TAB_AvancaCasa
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_AvancaCasa */

/***********************************************************************
*
*  $FC Função: TAB  &Retira Peça da Casa
*
*  $ED Descrição da função
*     Retira uma determinada peça passada como parâmetro de uma casa.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     pPeca - ponteiro para peça a ser retirada.
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*     TAB_CondRetPecaNaoExiste - se peça procurada não existe.
*     TAB_CondRetPecaMorta - se peça está fora de jogo.
*     TAB_CondRetNaoEncontrouPeca - se a peça procurada não foi encontrada.
*
***********************************************************************/

/* Assertivas de entrada TAB_RetiraPecaCasa
*  Existir um tabuleiro ja criado.
*  Existir uma peça já criada.
*
*  Fim Assertivas de Entrada TAB_RetiraPecaCasa */

TAB_CondRet TAB_RetiraPecaCasa ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) ;

/*  Assertiva de Saida TAB_RetiraPecaCasa
*   A peça deverá ser retirada caso esteja na casa.
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_RetiraPecaCasa */

/***********************************************************************
*
*  $FC Função: TAB  &Insere Peça da Casa
*
*  $ED Descrição da função
*     Insere uma determinada peça passada como parâmetro de uma casa.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     pPeca - ponteiro para peça a ser retirada.
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*     TAB_CondRetPecaNaoExiste - se peça procurada não existe.
*
***********************************************************************/

/* Assertivas de entrada TAB_InserePecaCasa
*  Existir um tabuleiro ja criado.
*  Existir uma peça já criada.
*
*  Fim Assertivas de Entrada TAB_InserePecaCasa */

TAB_CondRet TAB_InserePecaCasa ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) ;

/*  Assertiva de Saida TAB_InserePecaCasa
*   A peça deverá ser inserida caso tenha espaço na casa.
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_InserePecaCasa */

/***********************************************************************
*
*  $FC Função: TAB  &Ir Inicio Cor
*
*  $ED Descrição da função
*     Dado uma cor, vai ao inicio de seu percurso no tabuleiro.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     cor - valor correspondente a cor que se deseja ir ao inicio.
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*     TAB_CondRetCorInvalida - se a cor passada é inválida
*
***********************************************************************/

/* Assertivas de entrada TAB_IrInicioCor
*  Existir um tabuleiro ja criado.
*  A cor passada como parâmetro deverá ser válida (cor entre 0 e 3).
*
*  Fim Assertivas de Entrada TAB_IrInicioCor */

TAB_CondRet TAB_IrInicioCor ( TAB_tpLudo pTabuleiro , int cor ) ;

/*  Assertiva de Saida TAB_IrInicioCor
*   A função deverá ir ao inicio do percurso da cor.
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_IrInicioCor */

/***********************************************************************
*
*  $FC Função: TAB  &Eh Casa Final
*
*  $ED Descrição da função
*     Verifica dado um tabuleiro se chegou a casa final.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     n - ponteiro para armazenar resposta.
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*
***********************************************************************/

/* Assertivas de entrada TAB_EhCasaFinal
*  Existir um tabuleiro ja criado.
*  Ponteiro passado como parâmetro deverá fazer referência correta.
*
*  Fim Assertivas de Entrada TAB_EhCasaFinal */

TAB_CondRet TAB_EhCasaFinal ( TAB_tpLudo pTabuleiro , int * n ) ;

/*  Assertiva de Saida TAB_EhCasaFinal
*   Ponteiro n deverá ser preenchido corretamente (0->F, 1->V)
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_EhCasaFinal */

/***********************************************************************
*
*  $FC Função: TAB  &Exibe Tabuleiro
*
*  $ED Descrição da função
*     Exibe na tela o tabuleiro de Ludo.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro passado como referencia.
*     pPeca - ponteiro para peca.
*     num_jogadores - numero de jogadores 
*
*  $FV Valor retornado
*     TAB_CondRetOK - se peça procurada foi encontrada.
*
***********************************************************************/

/* Assertivas de entrada TAB_ExibeTabuleiro
*  Existir um tabuleiro ja criado.
*  Vetor de peças inicializado.
*  Numero de jogadores válido e coerete com a criação das peças. 
*
*  Fim Assertivas de Entrada TAB_ExibeTabuleiro */

TAB_CondRet TAB_ExibeTabuleiro ( TAB_tpLudo pTabuleiro , PEC_tpPeca *pPeca , int num_jogadores ) ;

/*  Assertiva de Saida TAB_ExibeTabuleiro
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_ExibeTabuleiro */

#undef TABULEIRO_EXT

/*********** Fim do módulo de definição: TAB Modulo Tabuleiro **********/

#else
#endif