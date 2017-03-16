/***************************************************************************
 *  $MCI Módulo de implementação: LST  Lista duplamente encadeada circular
 *
 *  Arquivo gerado:              LCIRC.c
 *  Letras identificadoras:      LST
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Histórico de evolução:
 *    Versão |  Autor  |      Data     |    Observações
 *      5    |   rvc   |  14/out/2016  |  finalização desenvolvimento
 *		4    |   rvc   |  14/out/2016  |  ajustes de desenvolvimento
 *      3    |   lr    |  25/set/2016  |  formalização do módulo
 *		2    |   rvc   |  24/set/2016  |  ajustes de desenvolvimento
 *	    1    |   dcr   |  17/set/2016  |  início desenvolvimento
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef _DEBUG
    #include    "GENERICO.H"
    #include    "CONTA.H"
    #include    "CESPDIN.H"
    #include    "TST_ESPC.H"
    #include    "INTRPCED.H"
    #include    "IdTiposEspaco.def"
#endif

#define LCIRC_OWN
#include "LCIRC.h"
#undef LCIRC_OWN


/***********************************************************************
 *
 *  $TC Tipo de dados: LST Elemento da lista
 *
 *
 ***********************************************************************/

typedef struct tagElemLista {
    
    void * valor ;
    /* Ponteiro para o valor contido no elemento */
    
    struct tagElemLista * ant ;
    /* Ponteiro para o elemento predecessor */
    
    struct tagElemLista * prox ;
    /* Ponteiro para o elemento sucessor */

    #ifdef _DEBUG

        int idTipo ;
            /* Id do tipo
            *
            *$ED Descrição
            *   Identintificador do tipo para um determinado elemento, caso haja
            *   alguma perda, com esta informação é possivel identificar se essa
            *   estrutura corresponde à um elemento ou não. */

        int tamValor ;
            /* Tamanho do elemento
            *
            *$ED Descrição
            *   Indica o tamanho do elemento carregado nesta estrutura para assim poder
            *   verificar integridade. */

        struct LST_tpCircular * pCabeca ;
            /* Ponteiro para cabeca
            *
            *$ED Descrição
            *   Todos os nós da lista devem apontar para a respectiva cabeça.
            *   Esse ponteiro corresponde a um identificador da lista para fins
            *   de verificação da integridade. */

    #endif
    
} LST_Elem ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LST Descritor da lista
 *
 *
 ***********************************************************************/

typedef struct LST_tpCircular {
    
    LST_Elem * pElemCorr ;
      /* Ponteiro para o elemento corrente */
    
    int numElem ;
 	  /* Numero de elementos da lista */
    
    void ( * ExcluirValor ) ( void * pValor ) ;
      /* Ponteiro para a função de destruição do valor contido em um elemento */

    #ifdef _DEBUG

        int tamValores ;
        /* Tamanho dos valores contidos na lista
            *
            *$ED Descrição
            *   Carrega o tamanho dos valores que estão armazenados na estrutura,
            *   para possível comparação com o possível elemento perdido */

    #endif

} LST_tppCircular ;


/*****  Dados encapsulados no módulo  *****/

      #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

      #endif


/***** Protótipo das funções encapsuladas no módulo *****/

static void LiberarElemento ( LST_tppCircular *pLista , LST_Elem  * pElem ) ;

static LST_Elem * CriaElemento ( LST_tppCircular * pLista , void * valor ) ;

static void LimparCabeca ( LST_tppCircular *pLista ) ;

#ifdef _DEBUG

   static LST_CondRet LST_VerificarElem( LST_Elem * pElem ) ;

#endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: LST  &Criar lista
 *  ****/

LST_CondRet LST_CriaLista ( LST_tppCircular **pLista, void ( * ExcluirValor ) ( void *pValor ) )
{
    #ifdef _DEBUG
         CNT_CONTAR( "LST_CriaLista" ) ;
    #endif

    *pLista = ( LST_tppCircular *) malloc ( sizeof ( LST_tppCircular ) ) ;
    
    if ( *pLista == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_CriaLista_if0" ) ;
        #endif

        return LST_CondRetMemoriaCheia ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_CriaLista_pr0" ) ;
    #endif

    LimparCabeca ( *pLista ) ;
    (*pLista)->ExcluirValor = ExcluirValor ;
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_CriaLista_pr1" ) ;
    #endif

    #ifdef _DEBUG
       CED_MarcarEspacoAtivo(pLista);
       (*pLista)->tamValores = 0;
    #endif

    return 	LST_CondRetOK ;
    
} /* Fim função: LST  &Criar lista */

/***************************************************************************
 *
 *  Função: LST  &Remove Elemento
 *  ****/

LST_CondRet LST_RemoveElemento ( LST_tppCircular *pLista, void * elemento )
{
    LST_Elem * pElem    ;
    LST_CondRet retorno ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento" ) ;
         assert( pLista != NULL ) ;
    #endif

    if ( ( retorno = LST_BuscaElemento ( pLista , elemento ) ) != LST_CondRetOK )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento_if0" ) ;
        #endif
        return retorno ;
    }
    #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento_pr0" ) ;
    #endif
    pElem = pLista->pElemCorr ;
    
    if ( pElem->ant != pElem )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento_if1" ) ;
        #endif
        pElem->ant->prox = pElem->prox ;
        pElem->prox->ant = pElem->ant  ;
        pLista->pElemCorr   = pElem->ant  ;
    }
    else
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento_else" ) ;
        #endif
        pLista->pElemCorr = NULL ;
    }
    #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento_pr1" ) ;
         pLista->tamValores -= CED_ObterTamanhoValor( pElem ) ;
    #endif
    LiberarElemento( pLista , pElem ) ;
    #ifdef _DEBUG
         CNT_CONTAR( "LST_RemoveElemento_pr2" ) ;
    #endif
    return LST_CondRetOK ;
    
} /* Fim função: LST  &Remove Elemento */

/***************************************************************************
 *
 *  Função: LST  &Destruir lista
 *  ****/

LST_CondRet LST_DestruirLista ( LST_tppCircular *pLista )
{

    #ifdef _DEBUG
         CNT_CONTAR( "LST_DestruirLista" ) ;
         assert( pLista != NULL ) ;
    #endif

    LST_EsvaziarLista( pLista ) ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_DestruirListapr0" ) ;
    #endif

    return LST_CondRetOK;
    
} /* Fim função: LST  &Destruir lista */

/***************************************************************************
 *
 *  Função: LST  &Esvaziar lista
 *  ****/

LST_CondRet LST_EsvaziarLista( LST_tppCircular *pLista )
{
    
    LST_Elem * pElem ;
    LST_Elem * pProx ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_EsvaziarLista" ) ;
         assert( pLista != NULL ) ;
    #endif
    
    if( pLista->pElemCorr == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_EsvaziarLista_if0" ) ;
        #endif
        return LST_CondRetVazia ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_EsvaziarLista_pr0" ) ;
    #endif
    pElem = pLista->pElemCorr ;
    
    do
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_EsvaziarLista_while0" ) ;
        #endif
        pProx = pElem->prox ;
        LiberarElemento( pLista , pElem ) ;
        pElem = pProx ;
        
    } while ( pElem != pLista->pElemCorr ) ;
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_EsvaziarLista_pr1" ) ;
    #endif
    
    LimparCabeca( pLista ) ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_EsvaziarLista_pr2" ) ;
         pLista->tamValores = 0 ;
    #endif

    return LST_CondRetOK;
    
} /* Fim função: LST  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LST  &Procurar elemento na lista
 *  ****/

LST_CondRet LST_BuscaElemento ( LST_tppCircular *pLista , void * valor )
{
    LST_Elem * pElem ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_BuscaElemento" ) ;
         assert( pLista != NULL ) ;
    #endif
    
    if ( pLista->pElemCorr == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_BuscaElemento_if0" ) ;
        #endif
        return LST_CondRetVazia;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_BuscaElemento_pr0" ) ;
    #endif
    pElem = pLista->pElemCorr ;
    
    do
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_BuscaElemento_while0" ) ;
        #endif
        if ( pElem->valor == valor )
        {
            #ifdef _DEBUG
                CNT_CONTAR( "LST_BuscaElemento_if1" ) ;
            #endif
            pLista->pElemCorr = pElem ;
            return LST_CondRetOK ;
        }
        #ifdef _DEBUG
         CNT_CONTAR( "LST_BuscaElemento_while_fim" ) ;
        #endif
        pElem = pElem->prox ;
        
    } while ( pElem != pLista->pElemCorr ) ;
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_BuscaElemento_pr1" ) ;
    #endif

    return LST_CondRetNaoEncontrou;
    
} /* Fim função: LST  &Procurar elemento na lista */

/***************************************************************************
 *
 *  Função: LST  &Inserir elemento à esquerda
 *  ****/

LST_CondRet LST_InsereElemEsquerda ( LST_tppCircular * pLista, void * valor )
{
    LST_Elem *pElem ;
    LST_Elem *p     ;
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemEsquerda" ) ;
         assert( pLista != NULL ) ;
    #endif

    pElem = CriaElemento( pLista ,  valor ) ;
    
    if ( pElem == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemEsquerda_if0" ) ;
        #endif
        return LST_CondRetMemoriaCheia ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemEsquerda_pr0" ) ;
    #endif
    p = pLista->pElemCorr ;

    #ifdef _DEBUG
        pElem->pCabeca      = pLista  ;
        pElem->idTipo       = CED_ObterTipoEspaco(pElem);
        pElem->tamValor     = CED_ObterTamanhoValor(pElem);
        pLista->tamValores += pElem->tamValor;
    #endif

    if ( p == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemEsquerda_if1" ) ;
        #endif
        pElem->ant = pElem->prox = pElem ;
    }
    
    else
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemEsquerda_else" ) ;
        #endif
        p->ant->prox = pElem  ;
        pElem->ant   = p->ant ;
        pElem->prox  = p      ;
        p->ant       = pElem  ;
    }
    
    #ifdef _DEBUG
     CNT_CONTAR( "LST_InsereElemEsquerda_pr1" ) ;
    #endif
    pLista->pElemCorr = pElem ;
    pLista->numElem++ ;
    
    #ifdef _DEBUG
     CNT_CONTAR( "LST_InsereElemEsquerda_pr2" ) ;
    #endif

    return LST_CondRetOK ;
    
} /* Fim função: LST  &Inserir elemento à esquerda */

/***************************************************************************
 *
 *  Função: LST  &Inserir elemento à direita
 *  ****/

LST_CondRet LST_InsereElemDireita ( LST_tppCircular *pLista , void * valor )
{
    LST_Elem *pElem ;
    LST_Elem * p ;
    pElem = CriaElemento ( pLista , valor ) ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita" ) ;
         assert( pLista != NULL ) ;
    #endif

    if ( pElem == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita_if0" ) ;
        #endif
        return LST_CondRetMemoriaCheia ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita_pr0" ) ;
    #endif
    p = pLista->pElemCorr ;

    #ifdef _DEBUG
        pElem->pCabeca      = pLista  ;
        pElem->idTipo       = CED_ObterTipoEspaco(pElem);
        pElem->tamValor     = CED_ObterTamanhoValor(pElem);
        pLista->tamValores += pElem->tamValor;
    #endif
    
    if ( p == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita_if1" ) ;
        #endif
        pElem->ant = pElem->prox = pElem ;
    }
    
    else
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita_else" ) ;
        #endif
        p->prox->ant = pElem   ;
        pElem->ant   = p       ;
        pElem->prox  = p->prox ;
        p->prox      = pElem   ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita_pr1" ) ;
    #endif
    pLista->pElemCorr = pElem ;
    pLista->numElem++ ;
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_InsereElemDireita_pr2" ) ;
    #endif

    return LST_CondRetOK ;
    
} /* Fim função: LST  &Inserir elemento à direita */

/***************************************************************************
 *
 *  Função: LST  &Obter valor
 *  ****/

LST_CondRet LST_ObterValor ( LST_tppCircular *pLista , void ** valor )
{
    #ifdef _DEBUG
         CNT_CONTAR( "LST_ObterValor" ) ;
         assert( pLista != NULL ) ;
    #endif

    if( pLista->pElemCorr == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_ObterValor_if0" ) ;
        #endif
        return LST_CondRetVazia ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_ObterValor_pr0" ) ;
    #endif
    *valor = pLista->pElemCorr->valor ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_ObterValor_pr1" ) ;
    #endif

    return LST_CondRetOK ;
    
}

/* Fim função: LST  &Obter valor */

/***************************************************************************
 *
 *  Função: LST  &Avançar Elemento Corrente
 *  ****/

LST_CondRet LST_AvancarElementoCorrente ( LST_tppCircular *pLista , int num )
{
    LST_Elem *pElem ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente" ) ;
         assert( pLista != NULL ) ;
    #endif
    
    if( pLista->pElemCorr == NULL )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente_if0" ) ;
        #endif
        return LST_CondRetVazia ;
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente_pr0" ) ;
    #endif
    pElem = pLista->pElemCorr ;

    if ( num > 0 )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente_if1" ) ;
        #endif
        while( num )
        {
            #ifdef _DEBUG
             CNT_CONTAR( "LST_AvancarElementoCorrente_while0" ) ;
            #endif
            pElem = pElem->prox ;
            num-- ;
        }
    }
    else if ( num < 0 )
    {
        #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente_if2" ) ;
        #endif
        while( num )
        {
            #ifdef _DEBUG
             CNT_CONTAR( "LST_AvancarElementoCorrente_while1" ) ;
            #endif
            pElem = pElem->ant ;
            num++ ;
        }
    }
    
    #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente_pr1" ) ;
    #endif

    pLista->pElemCorr = pElem ;

    #ifdef _DEBUG
         CNT_CONTAR( "LST_AvancarElementoCorrente_pr2" ) ;
    #endif

    return LST_CondRetOK ;
    
}

/* Fim função: LST  &Avançar Elemento Corrente */

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LST  &Verificar uma lista circular duplamente encadeada
*  ****/

LST_CondRet LST_VerificarLista ( LST_tppCircular * pLista )
{
    LST_tppCircular * ppLista = NULL ;

    CNT_CONTAR( "LST_VerificarLista" ) ;

    if ( LST_VerificarCabeca ( pLista ) != LST_CondRetOK )
    {
        CNT_CONTAR( "LST_VerificarLista_if0" ) ;
        return LST_CondRetErroEstrutura ;
    }

    CNT_CONTAR( "LST_VerificarLista_pr0" ) ;
    CED_MarcarEspacoAtivo( pLista ) ;

    ppLista =  pLista ;
    CNT_CONTAR( "LST_VerificarLista_pr1" ) ;

    return LST_VerificarElem ( ppLista->pElemCorr ) ;

} /* Fim função: LST  &Verificar uma lista circular duplamente encadeada */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LST  &Verificar cabeca da lista
*  ****/

LST_CondRet LST_VerificarCabeca ( LST_tppCircular * pLista )
{
    LST_tppCircular * ppLista = NULL ;

    CNT_CONTAR( "LST_VerificarCabeca" ) ;

    /* Verifica o tipo do espaço */

    if ( pLista == NULL )
    {
        CNT_CONTAR( "LST_VerificarCabeca_if0" ) ;
        TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
        return LST_CondRetErroEstrutura ;
    }
    
    CNT_CONTAR( "LST_VerificarCabeca_pr0" ) ;

    if ( ! CED_VerificarEspaco ( pLista, NULL ) )
    {
        CNT_CONTAR( "LST_VerificarCabeca_if1" ) ;
        TST_NotificarFalha( "Controle de espaço acusou erro." ) ;
        return LST_CondRetErroEstrutura ;
    }

    CNT_CONTAR( "LST_VerificarCabeca_pr1" ) ;

    if ( (TST_CompararInt ( LST_TipoEspacoCabeca , CED_ObterTipoEspaco ( pLista ) ,
        "Tipo de espaco de dados não é elemento da lista.")) != TST_CondRetOK )
    {
        CNT_CONTAR( "LST_VerificarCabeca_if2" ) ;
        return LST_CondRetErroEstrutura ;
    }

    CNT_CONTAR( "LST_VerificarCabeca_pr2" ) ;

    ppLista = (LST_tppCircular * ) pLista ;

    /* Verifica elemento corrente */

    if ( ppLista->pElemCorr != NULL )
    {
        CNT_CONTAR( "LST_VerificarCabeca_if3" ) ;
        if ( TST_CompararPonteiro( pLista , ppLista->pElemCorr->pCabeca , "Nó corrente não aponta para cabeça.") != TST_CondRetOK )
        {
            CNT_CONTAR( "LST_VerificarCabeca_if4" ) ;
            return LST_CondRetErroEstrutura ;
        }
    }

    CNT_CONTAR(" LST_VerificarCabeca_pr3 ") ;

    return LST_CondRetOK ;
} /* Fim função: LST  &Verificar cabeca da lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LST  &Verificar um elemento
*  ****/

   LST_CondRet LST_VerificarElem( LST_Elem * pElem )
   {

      LST_Elem * ppElem = NULL ;

      CNT_CONTAR( "LST_VerificarElem" ) ;

      /* Verificar se é nó estrutural */

         if ( pElem == NULL )
         {
            CNT_CONTAR( "LST_VerificarElem_if0" ) ;
            TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
            return LST_CondRetErroEstrutura ;

         } 

         CNT_CONTAR( "LST_VerificarElem_pr0" ) ;

         if ( ! CED_VerificarEspaco( pElem , NULL ))
         {
            CNT_CONTAR( "LST_VerificarElem_if1" ) ;
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LST_CondRetErroEstrutura ;
         } 

         CNT_CONTAR( "LST_VerificarElem_pr1" ) ;

         if ( (TST_CompararInt ( LST_TipoEspacoElem , CED_ObterTipoEspaco( pElem ) ,
              "Tipo do espaço de dados não é elemento da lista." )) != TST_CondRetOK )
         {
            CNT_CONTAR( "LST_VerificarElem_if2" ) ;
            return LST_CondRetErroEstrutura ;
         } /* if */

         CNT_CONTAR( "LST_VerificarElem_pr2" ) ;

         ppElem = ( LST_Elem * )( pElem ) ;

      /* Verificar elemento à esquerda */

         if ( ppElem->ant != NULL )
         {
            CNT_CONTAR( "LST_VerificarElem_if3" ) ;
            if ( TST_CompararPonteiro( ppElem , ppElem->ant->pCabeca ,
                 "Ponteiro para cabeça não está certo." ) != TST_CondRetOK )
            {
                CNT_CONTAR( "LST_VerificarElem_if4" ) ;
                return LST_CondRetErroEstrutura ;
            } 

         } /* if */

         CNT_CONTAR( "LST_VerificarElem_pr3" ) ;

      /* Verificar filho à direita */

         if ( ppElem->prox != NULL )
         {
            CNT_CONTAR( "LST_VerificarElem_if5" ) ;
            if ( TST_CompararPonteiro( ppElem , ppElem->prox->pCabeca ,
                 "Ponteiro para cabeça não está certo." ) != TST_CondRetOK )
            {
                CNT_CONTAR( "LST_VerificarElem_if6" ) ;
               return LST_CondRetErroEstrutura ;
            } 

         } /* if */

         CNT_CONTAR( "LST_VerificarElem_pr4" ) ;

      return LST_CondRetOK ;

   } /* Fim função: LST  &Verificar elemento da lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LST  &Deturpar lista
*  ****/

void LST_Deturpar( LST_tppCircular * pLista , LST_tpModosDeturpacao ModoDeturpar )
{
    LST_tppCircular * ppLista = NULL ;

      if ( pLista == NULL )
      {
        return ;
      } 

      ppLista = ( LST_tppCircular * )( pLista ) ;

      switch ( ModoDeturpar ) 
      {

      /* Modifica o tipo da cabeça */

         case DeturpaTipoCabeca :
         {

            CED_DefinirTipoEspaco( ppLista , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } 

      /* Anula ponteiro corrente */

         case DeturpaCorrenteNulo :
         {

            ppLista->pElemCorr = NULL ;

            break ;

         } /* fim ativa: Anula ponteiro corrente */

      /* Faz corrente apontar para lixo */

         case DeturpaCorrenteLixo :
         {

            ppLista->pElemCorr = ( LST_Elem * )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz corrente apontar para lixo */

      /* Deturpar espaço cabeca */

         case DeturparEspacoCabeca :
         {

            memcpy( (( char * )( ppLista )) - 10 , "????" , 4 ) ;

            break ;

         } /* fim ativa: Deturpar espaço cabeca */

      /* Deturpa elemento */

         default :

         if ( ppLista->pElemCorr != NULL )
         {

            switch ( ModoDeturpar ) 
            {

            /* Modifica tipo elemento corrente */

               case DeturpaTipoElem :
               {

                  CED_DefinirTipoEspaco( ppLista->pElemCorr , CED_ID_TIPO_VALOR_NULO ) ;

                  break ;

               } /* fim ativa: Modifica tipo elemento corrente */

            /* Anula ponteiro cabeça */

               case DeturpaCabecaNulo :
               {

                  ppLista->pElemCorr->pCabeca = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro cabeça */

            /* Anula ponteiro antecessor */

               case DeturpaPtAntNulo :
               {

                  ppLista->pElemCorr->ant = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro antecessor */

            /* Anula ponteiro sucessor */

               case DeturpaPtProxNulo :
               {

                  ppLista->pElemCorr->prox = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro sucessor */

            /* Faz ponteiro cabeça apontar para lixo */

               case DeturpaPtCabecaLixo :
               {

                  ppLista->pElemCorr->pCabeca = ( LST_tppCircular * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro cabeça apontar para lixo */

            /* Faz ponteiro antecessor apontar para lixo */

               case DeturpaPtAntLixo :
               {

                  ppLista->pElemCorr->ant = ( LST_Elem * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro antecessor apontar para lixo */

            /* Faz ponteiro sucessor apontar para lixo */

               case DeturpaPtDirLixo :
               {

                  ppLista->pElemCorr->prox = ( LST_Elem * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro sucessor apontar para lixo */

            /* Atribui valor fora do domínio do espaço */

               case DeturpaValor :
               {

                  memcpy( &( ppLista->pElemCorr->valor ) , "<<<<<" , 5 ) ;

                  break ;

               } /* fim ativa: Atribui valor fora do domínio do espaço */

            /* Deturpar espaço elemento */

               case DeturparEspacoElemento :
               {

                  memcpy( (( char * )( ppLista->pElemCorr )) - 50 , "????????" , 8 ) ;

                  break ;

               } /* fim ativa: Deturpar espaço elemento */

            } /* fim seleciona: Deturpa elemento */

            break ;

         } /* fim ativa: Deturpa elemento */

      } /* fim seleciona: Elemento &Deturpar lista */

   } /* Fim função: LST  &Deturpar lista */

#endif

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: LST  -Liberar elemento da lista
 *
 *  $ED Descrição da função
 *     Elimina os espaços apontados pelo valor do elemento e o
 *     próprio elemento.
 *
 ***********************************************************************/

void LiberarElemento ( LST_tppCircular *pLista , LST_Elem  * pElem )
{

    #ifdef _DEBUG
        CNT_CONTAR( "LiberarElemento" ) ;
        if (pLista == NULL)
        {
            CNT_CONTAR( "LiberarElemento_EXCECAO" ) ;
            pLista = pElem->pCabeca ;
        }
    #endif
    
    if ( ( pLista->ExcluirValor != NULL ) && ( pElem->valor != NULL )    )
    {
        #ifdef _DEBUG
           CNT_CONTAR( "LiberarElemento_if0" ) ;
        #endif
        pLista->ExcluirValor( pElem->valor ) ;

    } /* if */
    
    #ifdef _DEBUG
        CNT_CONTAR( "LiberarElemento_pr0" ) ;
    #endif
	pElem->valor = NULL ;
    pLista->numElem-- ;
    
} /* Fim função: LST  -Liberar elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LST  -Cria elemento da lista
 *
 *  $ED Descrição da função
 *     Cria elemento da lista e inicializa os valores contidos nele.
 *
 ***********************************************************************/

LST_Elem * CriaElemento ( LST_tppCircular * pLista , void * valor )
{
    LST_Elem * pElem ;

    #ifdef _DEBUG
        CNT_CONTAR( "CriaElemento" ) ;
    #endif
    
    pElem = ( LST_Elem * ) malloc ( sizeof ( LST_Elem ) ) ;
    if ( pElem == NULL )
    {
        #ifdef _DEBUG
            CNT_CONTAR( "CriaElemento_if0" ) ;
        #endif
        return NULL ;
    }

    #ifdef _DEBUG
        CNT_CONTAR( "CriaElemento_pr0" ) ;
    #endif
    
    #ifdef _DEBUG
        CED_MarcarEspacoAtivo( pElem ) ;
        pElem->pCabeca = pLista ;
    #else
        pLista = NULL ;
    #endif

    pElem->valor = valor ;
    pElem->prox  = NULL  ;
    pElem->ant   = NULL  ;

    #ifdef _DEBUG
        CNT_CONTAR( "CriaElemento_pr1" ) ;
    #endif
    
    return pElem ;
    
} /* Fim função: LST  &Cria elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LST  -Limpar a cabeça da lista
 *
 ***********************************************************************/

void LimparCabeca ( LST_tppCircular *pLista )
{
    #ifdef _DEBUG
        CNT_CONTAR( "LimparCabeca" ) ;
    #endif
    pLista->pElemCorr = NULL ;
    pLista->numElem  = 0    ;
    
} /* Fim função: LST  -Limpar a cabeça da lista */
