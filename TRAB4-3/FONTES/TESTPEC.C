/***************************************************************************
*  $MCI Módulo de implementação: TPEC Teste Pecas
*
*  Arquivo gerado:              TESTPEC.C
*  Letras identificadoras:      TPEC
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: dcr - Daniel Cunha Rios
*
*  $HA Histórico de evolução:
*     Versão |  Autor   |      Data     |    Observações
*       2    |   dcr    |  02/out/2016  | finalização desenvolvimento
*       1    |   dcr    |  30/set/2016  | início desenvolvimento	
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    <stdlib.h>
#include    "PECAS.h"

#include	   "TST_ESPC.H"
#include    "GENERICO.H"
#include    "LERPARM.H"

#define MAX_PECAS 16 //USADO PARA VETOR DE PECAS

/***********************************************************************
*
*  $FC Função: TDADO &Testar dado
*
*  $ED Descrição da função
*     Cria um dado ponto
*
*     Comandos disponíveis:
*
*     =criarpeca                         IndPeca Cor CondRetEsp
*     =destruirpeca                      IndPeca CondRetEsp
*     =obtercor                          IndPeca CondRetEsp
*     =obterfinal                        IndPeca CondRetEsp
*     =obterstatus                       IndPeca CondRetEsp
*	  =atualizapeca   					 IndPeca Final Status CondRetEsp
*
***********************************************************************/

static const char CRIAR_PECA_CMD          [ ] = "=criarpeca"     ;
static const char DESTRUIR_PECA_CMD       [ ] = "=destruirpeca"  ;
static const char OBTER_COR_CMD           [ ] = "=obtercor"      ;
static const char OBTER_FINAL_CMD         [ ] = "=obterfinal"    ;
static const char OBTER_STATUS_CMD        [ ] = "=obterstatus"   ;
static const char ATUALIZAR_PECA_CMD      [ ] = "=atualizapeca"  ;

/**********************************************************************
* 
*         Vetor de PECAS
*
***********************************************************************/

PEC_tpPeca vtPecas [MAX_PECAS];

/***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int numLidos      = -1 ;
	int indPeca		  = -1 ;
	int cor           = -1 ;
	int CondRetEsp    = -1 ;
	int CondRetObtido = -1 ;
	int final         = -1 ;
	char status            ;
	PEC_tpPeca *p          ;

	/* Testar Criar */

	if( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &indPeca, &cor ,&CondRetEsp);
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = PEC_CriaPeca ( vtPecas, indPeca, cor ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado") ;


	} /* fim ativa: Testar Criar */
	
	/* Testar Destruir */
	
	else if ( strcmp( ComandoTeste , DESTRUIR_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;

		if ( numLidos != 2 )
		{
			return TST_CondRetParm ;
		}

		CondRetObtido = PEC_DestroiPeca ( vtPecas[indPeca] ) ;
		p = NULL ;

		return TST_CompararInt (CondRetEsp, CondRetObtido, "Retorno errado") ;

	}  /* fim ativa: Testar */

		/* Testar Obter Cor */

         else if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_ObtemCor( vtPecas[indPeca], &cor ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Cor */

    /* Testar Obter Final */

         else if ( strcmp( ComandoTeste , OBTER_FINAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_ObtemFinal( vtPecas[indPeca], &final ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Final */

     /* Testar Obter Status */

         else if ( strcmp( ComandoTeste , OBTER_STATUS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_ObtemStatus( vtPecas[indPeca], &status ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Status */

		/* Testar Atualiza Peca */

         else if ( strcmp( ComandoTeste , ATUALIZAR_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iici", &indPeca, &final, &status, &CondRetEsp ) ;

            if (  numLidos != 4 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_AtualizaPeca( vtPecas[indPeca], final, status ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Atualiza Peca." ) ;

         } /* fim ativa: Testar Atualiza Peca */

    return TST_CondRetNaoConhec ;
			
}  /* Fim função: TPEC &Testar peça */

/********** Fim do módulo de implementação: TPEC Teste lista de símbolos **********/