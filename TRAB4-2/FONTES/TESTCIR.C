/***************************************************************************
*  $MCI Módulo de implementação: TLST Teste lista de símbolos
*
*  Arquivo gerado:              TESTCIR.c
*  Letras identificadoras:      TLST
*
*  Projeto: INF 1301 / Jogo de Ludo (Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: dcr - Daniel Cunha Rios
*
*  $HA Histórico de evolução:
*     Versão  |  Autor  |     Data     |   Observações
*       2     |   dcr   |  14/out/2016 |  finalização desenvolvimento
*       1     |   dcr   |  24/set/2016 |  início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "GENERICO.H"
#include    "CONTA.H"
#include    "CESPDIN.H"
#include    "LERPARM.H"
#include    "TST_ESPC.H"

#include    "LCIRC.H"


static const char RESET_LISTA_CMD                   [ ] = "=resetteste"              ;
static const char CRIAR_LISTAC_CMD                  [ ] = "=criarlistac"             ;
static const char REMOVE_ELEMENTO_CMD               [ ] = "=removeelemento"          ;
static const char DESTRUIR_LISTA_CMD                [ ] = "=destruirlista"           ;
static const char ESVAZIAR_LISTA_CMD                [ ] = "=esvaziarlista"           ;
static const char BUSCAR_ELEMENTO_CMD               [ ] = "=buscarelemento"          ;
static const char INSERIR_ELEMENTO_ESQ_CMD          [ ] = "=inserirelementoesq"      ;
static const char INSERIR_ELEMENTO_DIR_CMD          [ ] = "=inserirelementodir"      ;
static const char OBTER_VALOR_CMD                   [ ] = "=obtervalor"              ;
static const char AVANCAR_ELEMENTO_CORRENTE_CMD     [ ] = "=avancarelementocorrente" ;

/* Os comandos a seguir somente operam em modo _DEBUG */

const char VER_CABECA_CMD                           [ ] = "=verificarcabeca"  ;
const char VER_LISTA_CMD                            [ ] = "=verificarlista"   ;
const char VER_MEMORIA_CMD                          [ ] = "=verificarmemoria" ;
const char DETURPAR_CMD                             [ ] = "=deturpar"         ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define VT_LISTA   10

LST_Circular vtListas[ VT_LISTA ] ; typedef void ** ppVoid ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TDADO &Testar lista circular
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*       
*     =resetteste  // anula o vetor de listas. Provoca vazamento da memória
*     =criarlistac                       inxLista CondRetEsp
*     =removeelemento                    inxLista Elem CondRetEsp
*     =destruirlista                     inxLista CondRetEsp
*	  =esvaziarlista                     inxLista CondRetEsp
*     =buscarelemento                    inxLista Valor CondRetEsp
*     =inserirelementoesq                inxLista Valor CondRetEsp
*     =inserirelementodir                inxLista Valor CondRetEsp
*	  =obtervalor		                 inxLista Valor CondRetEsp
*	  =avancarelementocorrente		   	 inxLista Numero CondRetEsp
*
*     Estes comandos somente podem ser executados se o modulo tiver sido
*     compilado com _DEBUG ligado:
*
*     =verificarcabeca       inxLista
*     =verificararvore       inxLista
*     =verificarmemoria
*     =deturpar              inxLista < idCodigoDeturpa >
***********************************************************************/

/***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{

		int numLidos      = -1 ;
		int inxLista      = -1 ;
		int CondRetEsp    = -1 ;
		int CondRetObtido = -1 ;
		int num           = -1 ;
    int i                  ;
    char StringDado    [10];
    char * pDado           ;

    #ifdef _DEBUG
        int  IntEsperado   = -1 ;
    #endif

	/* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

		
	/* Testar Criar Lista Circular */

         else if ( strcmp( ComandoTeste , CRIAR_LISTAC_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,&inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2  ) || ( ! ValidarInxLista ( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            }
            
            CondRetObtido = LST_CriaLista( &vtListas [ inxLista ], NULL ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Criar Lista Circular." ) ;

         } /* fim ativa: Testar Criar Lista Circular */
            

	/* Testar Remover Elemento */

         else if ( strcmp( ComandoTeste , REMOVE_ELEMENTO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,&inxLista, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            }    

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRetObtido = LST_RemoveElemento( vtListas[ inxLista ], StringDado ) ;

            if ( CondRetObtido != LST_CondRetOK )
            {
               free( pDado ) ;
            } /* if */
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Remover Elemento." ) ;

         } /* fim ativa: Testar Remover Elemento */

           
	/* Testar Destruir Lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,&inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LST_DestruirLista( vtListas[ inxLista ] ) ;
			vtListas [ inxLista ] = NULL ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Destruir Lista." ) ;

         } /* fim ativa: Testar Destruir Lista */

            
	/* Testar Esvaziar Lista */ 		
        
                 else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
                 {
        
                    numLidos = LER_LerParametros( "ii" ,&inxLista, &CondRetEsp ) ;
        
                    if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
                    {
                       return TST_CondRetParm ;
                    }
        
                    CondRetObtido = LST_EsvaziarLista( vtListas[ inxLista ] ) ;
        			
                    return TST_CompararInt( CondRetEsp , CondRetObtido ,
                             "Condicao de retorno errada ao Esvaziar Lista." ) ;
        
                 } /* fim ativa: Testar Esvaziar Lista */    

                    
	/* Testar Buscar Elemento */	
    
             else if ( strcmp( ComandoTeste , BUSCAR_ELEMENTO_CMD ) == 0 )
             {
    
                numLidos = LER_LerParametros( "isi" ,&inxLista, StringDado, &CondRetEsp ) ;
    
                if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
                {
                   return TST_CondRetParm ;
                }
    
               pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
                if ( pDado == NULL )
                {
                  return TST_CondRetMemoria ;
                } /* if */

                CondRetObtido = LST_BuscaElemento( vtListas[ inxLista ], StringDado ) ;

                if ( CondRetObtido != LST_CondRetOK )
                {
                   free( pDado ) ;
                } /* if */
    			
                return TST_CompararInt( CondRetEsp , CondRetObtido ,
                         "Condicao de retorno errada ao Buscar Elemento." ) ;
    
             } /* fim ativa: Testar Buscar Elemento */  

                
	/* Testar Inserir Elemento a Esquerda */
  
           else if ( strcmp( ComandoTeste , INSERIR_ELEMENTO_ESQ_CMD ) == 0 )
           {
  
              numLidos = LER_LerParametros( "isi" ,&inxLista, StringDado, &CondRetEsp ) ;
  
              if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
              {
                 return TST_CondRetParm ;
              }

              pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            
              if ( pDado == NULL )
              {
                 return TST_CondRetMemoria ;
              } /* if */

              CondRetObtido = LST_InsereElemEsquerda( vtListas[ inxLista ], StringDado ) ;

              if ( CondRetObtido != LST_CondRetOK )
              {
                 free( pDado ) ;
              } /* if */
  			
              return TST_CompararInt( CondRetEsp , CondRetObtido ,
                       "Condicao de retorno errada ao Inserir Elemento a Esquerda." ) ;
  
           } /* fim ativa: Testar Inserir Elemento a Esquerda */  

              
	/* Testar Inserir Elemento a Direita */

         else if ( strcmp( ComandoTeste , INSERIR_ELEMENTO_DIR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,&inxLista, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            }

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            
            if ( pDado == NULL )
            {
              return TST_CondRetMemoria ;
            } /* if */

            CondRetObtido = LST_InsereElemDireita( vtListas[ inxLista ], StringDado ) ;

            if ( CondRetObtido != LST_CondRetOK )
            {
              free( pDado ) ;
            } /* if */
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Inserir Elemento a Direita." ) ;

         } /* fim ativa: Testar Inserir Elemento a Direita */

           
	/* Testar Obter Valor */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,&inxLista, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            }

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRetObtido = LST_ObterValor( vtListas[ inxLista ], (ppVoid) &StringDado ) ;

            if ( CondRetObtido != LST_CondRetOK )
            {
               free( pDado ) ;
            } /* if */
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Obter Valor." ) ;

         } /* fim ativa: Testar Obter Valor */

	/* Testar Avançar Elemento Corrente */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEMENTO_CORRENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,&inxLista, &num, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LST_AvancarElementoCorrente( vtListas[ inxLista ], num ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Avançar Elemento Corrente." ) ;

         } /* fim ativa: Testar Avançar Elemento Corrente */

    /* Testar verificador de cabeça */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_CABECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;
            if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
              return TST_CondRetParm ;
            } 

            return LST_VerificarCabeca( vtListas[ inxLista ] ) ;

         } /* fim ativa: Testar verificador de cabeça */
      #endif

    /* Testar verificador de lista */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;
            if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            }

            return TST_CompararInt( CondRetEsp ,
                             LST_VerificarLista( vtListas[ inxLista ] ) ,
                             "Retorno incorreto ao verificar lista." ) ;

         } /* fim ativa: Testar verificador de lista */
      #endif

      /* Deturpar uma lista */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , DETURPAR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &IntEsperado ) ;

            if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } 

            LST_Deturpar( vtListas[ inxLista ] , IntEsperado ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Deturpar uma lista */
      #endif

      /* Verificar vazamento de memória */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_MEMORIA_CMD ) == 0 )
         {

            CED_ExibirTodosEspacos( CED_ExibirTodos ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Verificar vazamento de memória */
      #endif
            
      return TST_CondRetNaoConhec ;

	} /* Fim função: TLISC &Testar lista circular */

      /*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= VT_LISTA ))  /* Verifica se está dentro do vetor */        
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != NULL )	/* nao seria NULL no lugar de 0? */         
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == NULL )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/
