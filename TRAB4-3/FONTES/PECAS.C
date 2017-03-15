/***************************************************************************
*  $MCI Módulo de implementação: PEC Módulo Peças
*
*  Arquivo gerado:              PECAS.C
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: lr - Lucas Rodrigues
*
*  $HA Histórico de evolução:
*     Versão |  Autor   |      Data     |    Observações
*       2    |   lr     |  28/set/2016  | término desenvolvimento
*       1    |   lr     |  28/set/2016  | início desenvolvimento	
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "PECAS.H"
#define PECAS_OWN
#undef PECAS_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LST Descritor da lista
*
*
***********************************************************************/

typedef struct Peca {

	int cor ;
	    /* Cor definida entre 0 e 3 */

	int final;
	    /* Se a peça está na reta final do jogo (1) ou não (0) */

	char status ;
        /* Se a peça está dentro do jogo 'D' ou fora de jogo 'F' */

} PEC_Peca;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC  &Criar Peca
*  ****/

PEC_CondRet PEC_CriaPeca ( PEC_Peca ** pPeca, int ind, int cor ) 
{
	if ( cor < 0 || cor > 3 )
	{
		return PEC_CondRetCorInvalida ;
	}

	if(pPeca[ind]!=NULL)
	{
		return PEC_CondRetJaExiste;
	}

	pPeca[ind] = ( PEC_Peca * ) malloc ( sizeof ( PEC_Peca ) ) ;

	if ( pPeca[ind] == NULL ) 
	{
		return PEC_CondRetFaltaMemoria ;
	}

	

	pPeca[ind]->cor    = cor ;
	pPeca[ind]->final  = 0   ;
	pPeca[ind]->status = 'F' ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Criar Peca */

/***************************************************************************
*
*  Função: PEC  &Destroi Peca
*  ****/

PEC_CondRet PEC_DestroiPeca ( PEC_Peca * pPeca )
{
	if ( pPeca == NULL )
		return PEC_CondRetNaoExiste ;
	
	free( pPeca );

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Destroi Peca */


/***************************************************************************
*
*  Função: PEC  &Obtem cor
*  ****/

PEC_CondRet PEC_ObtemCor ( PEC_Peca * pPeca , int * cor )
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* cor    = pPeca->cor    ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem cor */


/***************************************************************************
*
*  Função: PEC  &Obtem final
*  ****/

PEC_CondRet PEC_ObtemFinal ( PEC_Peca * pPeca , int * final )
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* final  = pPeca->final  ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem final */


/***************************************************************************
*
*  Função: PEC  &Obtem status
*  ****/

PEC_CondRet PEC_ObtemStatus ( PEC_Peca * pPeca , char * status)
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* status = pPeca->status ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem status */


/***************************************************************************
*
*  Função: PEC  &Atualiza Peca
*  ****/

PEC_CondRet PEC_AtualizaPeca ( PEC_Peca * pPeca , int final, char status ) 
{

	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	if ( final < 0 || final > 1 )
	{
		return PEC_CondRetFinalErrado ;
	}

	if ( status == 'D' || status == 'F' )
	{
		pPeca->final = final ;
		pPeca->status = status ;
	}
	else
	{
		return PEC_CondRetStatusErrado ;
	}

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Atualiza Peca */

/********** Fim do módulo de implementação: PEC Módulo PECAS **********/
