#if ! defined( LCIRC_ )
#define LCIRC_
/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: LST Lista Duplamente Encadeada Circular
 *
 *  Arquivo gerado:              LCIRC.h
 *  Letras identificadoras:      LST
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o |  Autor  |      Data     |    Observa��es
 *       2    |   lr    |  25/set/2016  | t�rmino desenvolvimento
 *       1    |   lr    |  16/set/2016  | in�cio desenvolvimento
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo implementa listas duplamente encadeadas circulares
 *          gen�ricas.
 *     As listas possuem um apontador para o n� corrente da lista, para
 *          o proximo elemento � esquerda e � direita do corrente.
 *
 *     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
 *     Os ponteiros para os dados s�o copiados para elementos da lista.
 *     N�o � copiado o valor apontado por estes ponteiros.
 *
 *     A destrui��o do valor de um elemento a ser exclu�do � realizado
 *        por uma fun��o fornecida pelo usu�rio.
 *
 ***************************************************************************/

#if defined( LCIRC_OWN )
   #define LCIRC_EXT
#else
   #define LCIRC_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LST_tpCircular * LST_Circular ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LST Condi��es de retorno
 *
 *
 *  $ED Descri��o do tipo
 *     Condi��es de retorno das fun��es da lista duplamente encadeada
 *           circular.
 *
 ***********************************************************************/

typedef enum {
    
    LST_CondRetOK ,
    /* Concluiu corretamente */
    
    LST_CondRetNaoEncontrou ,
    /* N�o encontrou o valor procurado */
    
    LST_CondRetMemoriaCheia ,
    /* Faltou memoria para alocar elemento */
    
    LST_CondRetVazia ,
    /* N�o existe elementos na lista */

    LST_CondRetErroEstrutura
    /* A estrutura possui erros */
    
} LST_CondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: LST Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaTipoCabeca ,
               /* Modifica o tipo da cabe�a */

         DeturpaCorrenteNulo ,
               /* Anula ponteiro corrente */

         DeturpaCorrenteLixo ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoElem ,
               /* Modifica tipo elemento corrente */

         DeturpaCabecaNulo ,
               /* Anula ponteiro cabe�a */

         DeturpaPtAntNulo ,
               /* Anula ponteiro antecessor */

         DeturpaPtProxNulo ,
               /* Anula ponteiro sucessor */

         DeturpaPtCabecaLixo ,
               /* Faz ponteiro cabe�a apontar para lixo */

         DeturpaPtAntLixo ,
               /* Faz ponteiro antecessor apontar para lixo */

         DeturpaPtDirLixo ,
               /* Faz ponteiro sucessor apontar para lixo */

         DeturpaValor ,
               /* Atribui valor de tamanho 1 byte maior do que o alocado */

         DeturparEspacoCabeca ,
               /* Deturpa espa�o da cabeca */

         DeturparEspacoElemento
               /* Deturpa espa�o do elemento */

   } LST_tpModosDeturpacao ;

#endif

/***********************************************************************
 *
 *  $FC Fun��o: LST  &Criar lista
 *
 *  $ED Descri��o da fun��o
 *     Cria uma lista duplamente encadeada circular gen�rica.
 *     Os poss�veis tipos s�o desconhecidos a priori.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna o ponteiro para lista, neste
 *       momento ainda sem nenhum elemento (lista vazia).
 *     Este ponteiro ser� utilizado pelas fun��es que manipulem esta
 *        lista, atualizando o ponteiro do n� corrente, anterior e
 *        sucessor em cada inser��o ou remo��o.
 *
 *     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados
 *        errados, a fun��o retornar� LST_CondRetMemoriaCheia,
 *        apresentando uma mensagem de erro.
 *
 ***********************************************************************/

/* Assertivas de Entrada LST_CriaLista
 *  Ter memoria suficiente para criacao da estrutura da lista
 *  Os ponteiros recebidos como par�metros devem fazer refer�ncia correta
 *
 *  Fim Assertivas de Entrada TAB_CriaTabuleiro */

LST_CondRet LST_CriaLista ( LST_Circular * pLista,
                           void ( * ExcluirValor ) ( void *pValor ) );

/* Assertivas de Saida LST_CriaLista
 *  A memoria referente a estrutura da lista tem que ser alocada
 *  A funcao retornara um LST_CondRet
 *
 *  Fim Assertiva de Saida LST_CriaLista */

/***********************************************************************
 *
 *  $FC Fun��o: LST  &Remover elemento
 *
 *  $ED Descri��o da fun��o
 *     Remove o elemento procurado da lista dada.
 *     Se existir somente um elemento a lista tornou-se vazia.
 *
 *  $EP Par�metros
 *     pLista     - ponteiro para a lista.
 *   elemento - ponteiro para elemento que se deseja retirar da lista.
 *
 *  $FV Valor retornado
 *     LST_CondRetOK            - se removeu corretamente
 *     LST_CondRetNaoEncontrou  - se elemento n�o foi encontrado
 *     LST_CondRetVazia         - se n�o h� elemento na lista
 *
 ***********************************************************************/

/* Assertivas de Entrada LST_RemoveElemento
 *  Existir uma lista ja criada
 *  Existir a posi��o que se deseja acessar
 *  Existir um elemento na posi��o acessada.
 *
 *  Fim Assertiva de Entrada TAB_RetiraPeca */

LST_CondRet LST_RemoveElemento ( LST_Circular pLista, void * elemento  ) ;

/* Assertiva de Saida LST_RemoveElemento
 *  Retirou o elemento desejado
 *  A posi��o onde o elemento foi retirado existe
 *  A funcao retornara um LST_CondRet
 *
 *  Fim Assertiva de Saida LST_RemoveElemento */
/***********************************************************************
 *
 *  $FC Fun��o: LST  &Destruir Lista
 *
 *  $ED Descri��o da fun��o
 *     Destr�i a lista fornecida.
 *
 *  $EP Par�metros
 *     pLista     - ponteiro para a lista na qual deve ser destruida.
 *
 *  $FV Valor retornado
 *     LST_CondRetOK      - destruiu lista sem problemas.
 *
 ***********************************************************************/

/* Assertivas de entrada LST_DestruirLista
 *  Existir uma lista ja criada
 *
 *  Fim Assertivas de Entrada LST_DestruirLista */

LST_CondRet LST_DestruirLista ( LST_Circular pLista ) ;

/*  Assertiva de Saida LST_DestruirLista
 *   A lista deve ser destruida
 *   A memoria deve ser liberada
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_DestruirLista */
/***********************************************************************
 *
 *  $FC Fun��o: LST  &Esvaziar lista
 *
 *  $ED Descri��o da fun��o
 *     Elimina todos os elementos, sem contudo eliminar a lista
 *
 *  $EP Par�metros
 *     pLista - ponteiro para a lista a ser esvaziada
 *
 *  $FV Valor retornado
 *     LST_CondRetOK      - esvaziou lista sem problemas.
 *
 ***********************************************************************/

/* Assertivas de entrada LST_EsvaziarLista
 *  Existir uma lista ja criada
 *
 *  Fim Assertivas de Entrada LST_EsvaziarLista */

LST_CondRet LST_EsvaziarLista ( LST_Circular pLista ) ;

/*  Assertiva de Saida LST_EsvaziarLista
 *   A lista deve ser esvaziada
 *   A lista n�o poder� conter elementos
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_EsvaziarLista */

/***********************************************************************
 *
 *  $FC Fun��o: LST  &Procurar elemento na lista
 *
 *  $ED Descri��o da fun��o
 *     Procura o elemento desejado e o deixa na posi��o corrente.
 *
 *  $EP Par�metros
 *     pLista     - ponteiro para a lista onde procura
 *     *valor   - ponteiro pra o endere�o do elemento desejado
 *
 *  $FV Valor retornado
 *     LST_CondRetOK              - se encontrou o elemento.
 *     LST_CondRetNaoEncontrou    - se o elemento n�o foi encontrado.
 *     LST_CondRetVazia           - se a lista est� vazia
 *
 ***********************************************************************/

/* Assertivas de entrada LST_BuscaElemento
 *  Existir uma lista ja criada
 *  Ponteiro para valor conter o endere�o correto
 *
 *  Fim Assertivas de Entrada LST_BuscaElemento */

LST_CondRet LST_BuscaElemento ( LST_Circular pLista , void * valor ) ;

/*  Assertiva de Saida LST_BuscaElemento
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_BuscaElemento */

/***********************************************************************
 *
 *  $FC Fun��o: LST  &Inserir elemento � esquerda
 *
 *  $ED Descri��o da fun��o
 *     Insere novo elemento antes do elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Par�metros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     *valor - ponteiro para o valor do novo elemento
 *              Pode ser NULL
 *
 *  $FV Valor retornado
 *     LST_CondRetOK           - se a inser��o ocorreu perfeitmente.
 *   LST_CondRetMemoriaCheia - se n�o possui mem�ria suficiente para
 *                                  inserir
 *
 ***********************************************************************/

/* Assertivas de entrada LST_InsereElemEsquerda
 *  Existir uma lista ja criada
 *  Ponteiro para valor conter o endere�o correto
 *
 *  Fim Assertivas de Entrada LST_InsereElemEsquerda */

LST_CondRet LST_InsereElemEsquerda ( LST_Circular pLista , void * valor  ) ;

/*  Assertiva de Saida LST_InsereElemEsquerda
 *   O elemento dever� ser inserido na lista
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_InsereElemEsquerda */

/***********************************************************************
 *
 *  $FC Fun��o: LST  &Inserir elemento � direita
 *
 *  $ED Descri��o da fun��o
 *     Insere novo elemento ap�s o elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Par�metros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     *valor - ponteiro para o valor do novo elemento
 *              Pode ser NULL
 *
 *  $FV Valor retornado
 *     LST_CondRetOK           - se a inser��o ocorreu perfeitmente.
 *   LST_CondRetMemoriaCheia - se n�o possui mem�ria suficiente para
 *                                  inserir
 *
 ***********************************************************************/

/* Assertivas de entrada LST_InsereElemDireita
 *  Existir uma lista ja criada
 *  Ponteiro para valor conter o endere�o correto
 *
 *  Fim Assertivas de Entrada LST_InsereElemDireita */

LST_CondRet LST_InsereElemDireita ( LST_Circular pLista , void * valor ) ;

/*  Assertiva de Saida LST_InsereElemDireita
 *   O elemento dever� ser inserido na lista
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_InsereElemDireita */

/***********************************************************************
 *
 *  $FC Fun��o: LST  &Obter valor
 *
 *  $ED Descri��o da fun��o
 *     Obtem o valor contido no elemento corrente da lista.
 *
 *  $EP Par�metros
 *     pLista   - ponteiro para a lista de onde se quer o valor
 *     * valor - ponteiro para armazenar o valor desejado
 *
 *  $FV Valor retornado
 *     LST_CondRetOK    - se o elemento corrente existe
 *     LST_CondRetVazia - se a lista estiver vazia
 *
 ***********************************************************************/

/* Assertivas de entrada LST_ObterValor
 *  Existir uma lista ja criada
 *  Ponteiro para valor conter o endere�o correto
 *
 *  Fim Assertivas de Entrada LST_ObterValor */

LST_CondRet LST_ObterValor ( LST_Circular pLista , void ** valor ) ;

/*  Assertiva de Saida LST_ObterValor
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_ObterValor */

/***********************************************************************
 *
 *  $FC Fun��o: LIS  &Avan�ar elemento
 *
 *  $ED Descri��o da fun��o
 *     Avan�a o elemento corrente 'num' elementos na lista.
 *     Se 'num' for positivo avan�a em dire��o ao final.
 *     Se 'num' for negativo avan�a em dire��o ao in�cio.
 *     Se 'num' for zero n�o avan�a nenhuma elemento.
 *
 *  $EP Par�metros
 *     pLista  - ponteiro para a lista a ser manipulada
 *     num    - o n�mero de elementos a andar
 *
 *  $FV Valor retornado
 *     LST_CondRetOK      - se 'num' elementos tiverem sido andados
 *     LST_CondRetVazia   - se a lista est� vazia
 *
 ***********************************************************************/

/* Assertivas de entrada LST_AvancarElementoCorrente
 *  Existir uma lista ja criada
 *  Numero de elementos a andar dever� ser do tipo int.
 *
 *  Fim Assertivas de Entrada LST_AvancarElementoCorrente */

LST_CondRet LST_AvancarElementoCorrente ( LST_Circular pLista , int num ) ;

/*  Assertiva de Saida LST_AvancarElementoCorrente
 *   O elemento dever� ter sido movimentado 0 ou mais vezes.
 *   A funcao retorna um LST_CondRet
 *
 *   Fim Assertiva de Saida LST_AvancarElementoCorrente */

/***********************************************************************
*
*  $FC Fun��o: LST  &Verificar uma lista circular duplamente encadeada
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica completamente uma determinada lista circular duplamente encadeada.
*     Tamb�m marca todos os espa�os por ela ocupados.
*
***********************************************************************/

#ifdef _DEBUG

LST_CondRet LST_VerificarLista ( LST_Circular pLista ) ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LST  &Verificar cabe�a da lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade de um n� cabe�a da lista.
*
*  $EP Par�metros
*     $P pLista - ponteiro para um espa�o que deveria ser uma cabe�a
*                      de lista.
*
*  $FV Valor retornado
*     Condi��o de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LST_CondRet LST_VerificarCabeca( LST_Circular pLista ) ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LST  &Deturpar lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Corrompe elementos espec�ficos da estrutura da lista.
*     Essa fun��o destina-se a preparar os cen�rios de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*     Esta fun��o n�o tem prote��o contra erros de uso, consequentemente
*     poder� levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Par�metros
*     $P pLista       - lista a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpa��o
*                       LST_tpModosDeturpacao identifica os modos de
*                       deturpa��o conhecidos
*
***********************************************************************/

#ifdef _DEBUG

void LST_Deturpar( LST_Circular pLista , LST_tpModosDeturpacao ModoDeturpar ) ;

#endif

#undef LCIRC_EXT

/****** Fim do m�dulo de defini��o: LCIRC M�dulo Lista Circular ******/

#else
#endif
