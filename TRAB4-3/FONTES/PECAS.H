#if ! defined ( PEC_ )
#define PEC_

/***************************************************************************
*
*  $MCD Módulo de definição: PEC Módulo de Peça
*
*  Arquivo gerado:              PECAS.H  
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: lr -> Lucas Rodrigues
*
*  $HA Histórico de evolução:
*     Versão |  Autor  |      Data     |    Observações
*       2    |   lr    |  28/set/2016  | término desenvolvimento
*       1    |   lr    |  28/set/2016  | início desenvolvimento
*
*  $ED Descrição do módulo
*     Cria, dado um indice no vetor, uma Peça.
*     Destroi, dado um indice no vetor, uma Peça.
*     Obtem, dado um indice no vetor, informações sobre a Peça.
*     Atualiza status e final, dado um indice no vetor, de uma Peça.
*
*     OBS IMPORTANTE: As 4 primeiras posições do vetor de peças destinam-se
*                     a cor vermelha, as próximas 4 destinam-se a cor azul,
*                     e analogamente para a cor verde e amarelo.
*
**************************************************************************/

/*****************IMPORTANTE*********************
*
*  AS CORES DA PEÇA SÃO CLASSIFICADAS COMO:
*
*       0 - VERMELHO
*       1 - AZUL
*       2 - VERDE
*       3 - AMARELO
*
*************************************************/

#if defined( PEC_OWN )
#define PEC_EXT
#else
   #define PEC_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct Peca * PEC_tpPeca; 

/***********************************************************************
*
*  $TC Tipo de dados: PEC condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peça
*
***********************************************************************/

typedef enum {

	PEC_CondRetOK ,
		/* Ocorreu tudo certo */

	PEC_CondRetFaltaMemoria , 
		/* Faltou memória na alocação */

	PEC_CondRetStatusErrado ,
		/* Status Errado */

	PEC_CondRetFinalErrado ,
		/* Final Errado */						

	PEC_CondRetCorInvalida ,
		/* Cor inválida */

	PEC_CondRetJaExiste ,
		/* Peca ja existe */

	PEC_CondRetNaoExiste
		/* Peca nao existe */
	

} PEC_CondRet;

/***********************************************************************
*
*  $FC Função: PEC &Criar PEC
*
*  $ED Descrição da função
*     Cria uma peça, dado um indice, no vetor.
*
*  $EP Parametros
*  * pPeça - ponteiro para peça a ser criada
*    ind   - indice da peça no vetor
* 	 cor   - cor da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetFaltaMemoria - se faltou memoria
*     PEC_CondRetJaExiste - Se peca ja existe
*     PEC_CondRetCorInvalida - se a cor passada não for entre 0 e 3
*
***********************************************************************/

/* Assertivas de Entrada PEC_CriaPeca
*  Existir mémoria para criacao da peça
*  A peça nao pode existir para que seja criada (pPeca[ind] = NULL)
*  A cor dada (int) tem que ser entre 0 e 3
*  Para todo pPeca[indice], pPeca = NULL.
*
*  Fim Assertiva de Entrada PEC_CriaPeca */

PEC_CondRet PEC_CriaPeca ( PEC_tpPeca * pPeca, int ind, int cor ) ;

/* Assertivas de Saida PEC_CriaPeca
*  A memoria referente a estrutura da peca tem que ser alocada
*  Para todo pPeca[ind] criado, pPeca[ind] != NULL
*  Para todo pPeca criado, pPeca->cor entre 0 e 3
*  A funcao retornara um PEC_CondRet
*
*  Fim Assertiva de Saida PEC_CriaPeca */

/***********************************************************************
*
*  $FC função: PEC &Destruir peça
*
*  $ED Descrição da função
*     Destroi uma peça dado um indice, dentro do vetor.
*
*  $EP Parametros
*   *pPeca  -  peca a ser destruida.
*     ind   -  indice no vetor
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_DestroiPeca
*  Existir peça ja criada (para todo pPeca , pPeca != NULL)
*
*  Fim Assertiva de Entrada PEC_DestroiPeca */

PEC_CondRet PEC_DestroiPeca ( PEC_tpPeca pPeca ) ;
 
/* Assertiva de Saida PEC_DestroiPeca
*  A peca deve ser destruida (para todo pPeca , pPeca = NULL)
*  A memoria alocada para peca deve ser liberada 
*  A funcao retorna um PEC_CondRet
*
*  Fim Assertiva de Saida PEC_DestroiPeca */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem cor
*
*  $ED Descrição da função
*     Dada uma peça no vetor, informa sua cor.
*
*  $EP Parametros
*   pPeca - peça que procura saber a cor
*  * cor - ponteiro passado para receber a cor
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemCor
*  Deve existir uma cor valida na peca (para todo pPeca, pPeca->cor entre 0 e 3)
*
*  Fim Assertiva de Entrada PEC_ObtemCor */

PEC_CondRet PEC_ObtemCor ( PEC_tpPeca pPeca , int * cor ) ;

/*  Assertiva de Saida PEC_ObtemCor
*   Deverá ser retornado uma cor válida (inteiro entre 0 e 3)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemCor */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem final
*
*  $ED Descrição da função
*     Dada uma peça no vetor, informa se está na casa final.
*
*  $EP Parametros
*   pPeca - peça que procura saber o final
*  * final - ponteiro passado para receber o final
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemFinal
*  Deve existir um valor final valido na peca
*
*  Fim Assertiva de Entrada PEC_ObtemFinal */

PEC_CondRet PEC_ObtemFinal ( PEC_tpPeca pPeca , int * final ) ;

/*  Assertiva de Saida PEC_ObtemFinal
*   Deverá ser retornado um final válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemFinal */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem status
*
*  $ED Descrição da função
*     Dada uma peça no vetor, informa seu status.
*
*  $EP Parametros
*   pPeca - peça que procura saber o status
*  * status - ponteiro passado para receber o status
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemStatus
*  Deve existir um status valido na peca
*
*  Fim Assertiva de Entrada PEC_ObtemStatus */

PEC_CondRet PEC_ObtemStatus ( PEC_tpPeca pPeca , char * status ) ;

/*  Assertiva de Saida PEC_ObtemStatus
*   Deverá ser retornado um status válido (caracter 'D' ou 'F')
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemStatus */

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza peça
*
*  $ED Descrição da função
*     Dado uma peça, atualiza o status e a condição final da peça.
*
*  $EP Parametros
*   pPeca - peça que procura saber a cor
*   final - atualizar se peça está no estágio final
*   status - atualizar se se peça está em jogo
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetStatusErrado - se status dado está errado
*     PEC_CondRetFinalErrado - se final dado está errado
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_AtualizaPeca
*  Deve existir um status valido na peca
*  Deve existir um valor final valido na peca
*  A peça deve existi antes de chamar a função.
*
*  Fim Assertiva de Entrada PEC_AtualizaPeca */

PEC_CondRet PEC_AtualizaPeca ( PEC_tpPeca pPeca , int final, char status ) ;

/*  Assertiva de Saida PEC_AtualizaPeca
*   Deverá ser atualizado um status válido (caracter 'D' ou 'F')
*   Deverá ser atualizado um final válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_AtualizaPeca */

#undef PEC_EXT

/********** Fim do módulo de definição: PEC Módulo Peças **********/
 
#else
#endif