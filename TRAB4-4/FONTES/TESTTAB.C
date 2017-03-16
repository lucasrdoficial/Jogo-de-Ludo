/***************************************************************************
*  $MCI Modulo de implementação: TTAB Teste tabuleiro
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: dcr - Daniel Cunha Rios 
*
*  $HA Histórico de evolução:
*     Versão |  Autor   |      Data     |    Observações
*       2    |   dcr    |  13/set/2016  | finalização desenvolvimento
*       1    |   dcr    |  30/set/2016  | início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include	"TABULEIRO.H"

#include    "PECAS.H"
#include	"TST_ESPC.H"
#include	"GENERICO.H"
#include	"LERPARM.H"


static const char CRIAR_TAB_LUDO_CMD          [ ] = "=criartab"        ;
static const char PROCURA_PECA_CMD            [ ] = "=procurapeca"     ;
static const char OBTER_PECA_CASA_CMD         [ ] = "=obterpecacasa"   ;
static const char AVANCA_CASA_CMD             [ ] = "=avancacasa"      ;
static const char RETIRA_PECA_CASA_CMD        [ ] = "=retirapecacasa"  ;
static const char INSERE_PECA_CASA_CMD        [ ] = "=inserepecacasa"  ;
static const char IR_INICIO_COR_CMD           [ ] = "=iriniciocor"     ;
static const char LANCAR_DADO_CMD             [ ] = "=lancardado"      ;
static const char DESTRUIR_TAB_CMD            [ ] = "=destruirtab"     ;
static const char EH_CASA_FINAL_CMD           [ ] = "=ehcasafinal"     ;
static const char EXIBE_TABULEIRO_CMD         [ ] = "exibetabuleiro"   ;

#define MAX_PECAS 15 //USADO PARA VETOR DE PECAS

#define MAX_TABULEIRO 10 //USADO PARA VETOR DE PECAS

/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Criar um tabuleiro
*
*     Comandos disponíveis:
*
*     =criartab                        Tab CondRetEsp
*     =procurapeca                     Tab IndPeca QtdMov CondRetEsp
*     =obterpecacasa                   Tab IndPeca CondRetEsp
*	  =avancacasa   				   CondRetEsp
*	  =retirapecacasa
*	  =inserepecacasa   			   Tab CondRetEsp
*	  =iriniciocor   				   Tab CondRetEsp
*	  =lancardado   				   CondRetEsp
*	  =destruirtab   				   Tab CondRetEsp
*     =ehcasafinal                     Tab IndPeca CondRetEsp
*     =exibetabuleiro                  Tab IndPeca qtdmov CondRetEsp
*
***********************************************************************/

TAB_tpLudo vtTabuleiro[MAX_TABULEIRO]; //DECLARACAO DO VETOR DE TABULEIRO

PEC_tpPeca vtPecas[MAX_PECAS]; //DECLARAÇAO DO VETOR DE PECAS

typedef void * pVoid ;

/***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int tab           =-1 ;
	int ret           =-1 ;
	int qtdMov        =-1 ;
	int CondRetEsp    =-1 ;
	int CondRetObtido =-1 ;
	int numLidos      =-1 ;
	int indPeca       =-1 ;
	int cor           =-1 ;
	int valor             ;
	int i                 ;
	int n                 ;

	for(i=0;i<16;i++)
	{
		ret = PEC_CriaPeca ( vtPecas, i, i/4 ) ;
		if ( ret != PEC_CondRetOK )
			break;
	}

	PEC_AtualizaPeca ( vtPecas[7] , 0 , 'D' ) ;

	/* Testar Criar Tabuleiro */

	if( strcmp( ComandoTeste , CRIAR_TAB_LUDO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &tab, &CondRetEsp) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_CriaTabuleiro_Ludo ( &vtTabuleiro [tab] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao criar tabuleiro") ;


	} /* fim ativa: Criar Tabuleiro */


	/* Testar Ṕrocurar Peça */

	else if( strcmp( ComandoTeste , PROCURA_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &tab, &indPeca, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_ProcuraPeca ( vtTabuleiro [tab], vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao procurar peça") ;


	} /* fim ativa: Procurar Peça */


	/* Testar Obter peça casa */

	else if( strcmp( ComandoTeste , OBTER_PECA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &tab, &indPeca, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_ObterPecaCasa ( vtTabuleiro [tab], (pVoid) vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Obter peça casa") ;


	} /* fim ativa: Obter peça casa */

	/* Testar Eh Casa Final */

	else if( strcmp( ComandoTeste , EH_CASA_FINAL_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &tab, &CondRetEsp ) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_EhCasaFinal ( vtTabuleiro [tab], &n ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao verificar Eh Casa Final") ;


	} /* fim ativa: Eh Casa Final */


	/* Testar Exibe Tabuleiro */

	else if( strcmp( ComandoTeste , EXIBE_TABULEIRO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iiii", &tab, &indPeca, &qtdMov, &CondRetEsp ) ;
		if( numLidos != 4 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_ExibeTabuleiro ( vtTabuleiro [tab], (pVoid) vtPecas [indPeca] , qtdMov ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Exibir Tabuleiro") ;


	} /* fim ativa: Exibe Tabuleiro */


	/* Testar Avança casa */

	else if( strcmp( ComandoTeste , AVANCA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iiii", &tab, &cor, &qtdMov, &CondRetEsp ) ;
		if( numLidos != 4 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_AvancaCasa ( vtTabuleiro [tab], cor, qtdMov ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Avançar casa") ;


	} /* fim ativa: Avança casa */


	/* Testar Retira peça casa */

	else if( strcmp( ComandoTeste , RETIRA_PECA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &tab, &indPeca, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_RetiraPecaCasa ( vtTabuleiro [tab], vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Retirar peça casa") ;


	} /* fim ativa: Retirar peça casa */


	/* Testar Insere peça casa */

	else if( strcmp( ComandoTeste , INSERE_PECA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &tab, &indPeca, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_InserePecaCasa ( vtTabuleiro [tab], vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Inserir peça casa") ;


	} /* fim ativa: Insere peça casa */


	/* Testar Ir Inicio Cor */

	else if( strcmp( ComandoTeste , IR_INICIO_COR_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &tab, &cor, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_IrInicioCor ( vtTabuleiro [tab], cor ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Inserir peça casa") ;


	} /* fim ativa: Ir Inicio Cor */


	/* Testar Lançar o dado */

	else if( strcmp( ComandoTeste , LANCAR_DADO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
		if( numLidos != 1 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_LancaDado ( &valor ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Lançar o dado") ;


	} /* fim ativa: Lançar o dado */


	/* Testar Destruir tabuleiro */

	else if( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &tab, &CondRetEsp ) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_DestruirTabuleiro ( vtTabuleiro [tab] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Destruir tabuleiro") ;


	} /* fim ativa: Destruir tabuleiro */

    return TST_CondRetNaoConhec ;

}  /* Fim função: TTAB &Testar tabuleiro */

/********** Fim do módulo de implementação: TTAB Teste lista de símbolos **********/