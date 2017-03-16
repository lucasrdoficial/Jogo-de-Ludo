/***************************************************************************
 *  $MCI Módulo de implementação: JOGO  Módulo Jogo / Principal
 *
 *  Arquivo gerado:              JOGO.c
 *  Letras identificadoras:      JOGO
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Histórico de evolução:
 *     Versão |  Autores   |      Data     |    Observações
 *       2    | lr,dcr,rvc |  01/dez/2016  | término desenvolvimento
 *       1    | lr,dcr,rvc |  25/nov/2016  | início desenvolvimento
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PECAS.H"
#include "TABULEIRO.H"

#define MAX_JOGADORES 4
#define MAX_PECAS 	  4

/***********************************************************************
*
*  $TC Tipo de dados: JOGO Descritor dos dados dos jogadores
*
***********************************************************************/

typedef struct Jogador{

	char nome[81];
	/* Nome do Jogador */

	int cor;
	/* Cor do Jogador */

} JOGO_Jogador;

/***** Protótipo das funções encapsuladas no módulo *****/

static int JogarDado ( void );

static void DesenhaPlacar ( PEC_tpPeca * pPecas , JOGO_Jogador * vtJogadores, int num_jogadores );

static void ordenaRanking ( JOGO_Jogador *vtJogadores , int *qtdfim , int n ) ;

static int VerificaVencedor ( PEC_tpPeca * pPecas, int num_jogadores, JOGO_Jogador * vtJogadores );

static int ValidaMovimento ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca , int n ) ;

static void RealizaMovimento ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca , int n ) ;

static int ValidaInsercao ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) ;

static void InserePecaJogo ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) ;

static int ObtemOrdemJogador ( void ) ;

static void MostraMovimentosValidos ( int *mapa ) ;

static void ZeraMapa ( int *mapa ) ;

static int TemMovimento ( int *mapa ) ;

/*****  Código da função principal do módulo  *****/

int main (void)
{
	const char * cores[MAX_PECAS] = { "VERMELHO" , "AZUL" , "VERDE" , "AMARELO" } ;
	const char * ordem[MAX_JOGADORES] = { "PRIMEIRO" , "SEGUNDO" , "TERCEIRO" , "ULTIMO" } ;
	int i , k , ind ;
	int dado     	;
	int opcao    	;
	int cond     	;	
	int cor = 0  	;
	int resposta 	;
	int num_jogadores = 0;
	char status ;
	char digito ;

	int valid_mapa[MAX_PECAS] ;

	JOGO_Jogador vtJogadores[MAX_JOGADORES] ; 

	PEC_tpPeca vtPecas[ MAX_JOGADORES * MAX_PECAS ] = { NULL , NULL , NULL , NULL ,
														NULL , NULL , NULL , NULL ,
														NULL , NULL , NULL , NULL ,
														NULL , NULL , NULL , NULL } ;
	PEC_tpPeca peca ;
	TAB_tpLudo  pTabuleiro  ;

	PEC_CondRet PecasRetorno     ;
	TAB_CondRet TabuleiroRetorno ;

	printf("\n\n\n");
	printf("\t\t    /$$$$$                                           /$$                 /$$                       /$$           \n") ;
	printf("\t\t   |__  $$                                          | $$                | $$                      | $$           \n") ;
	printf("\t\t      | $$  /$$$$$$   /$$$$$$   /$$$$$$         /$$$$$$$  /$$$$$$       | $$       /$$   /$$  /$$$$$$$  /$$$$$$  \n") ;
	printf("\t\t      | $$ /$$__  $$ /$$__  $$ /$$__  $$       /$$__  $$ /$$__  $$      | $$      | $$  | $$ /$$__  $$ /$$__  $$ \n") ;
	printf("\t\t /$$  | $$| $$  | $$| $$  | $$| $$  | $$      | $$  | $$| $$$$$$$$      | $$      | $$  | $$| $$  | $$| $$  | $$ \n") ;
	printf("\t\t| $$  | $$| $$  | $$| $$  | $$| $$  | $$      | $$  | $$| $$_____/      | $$      | $$  | $$| $$  | $$| $$  | $$ \n") ;
	printf("\t\t|  $$$$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$/      |  $$$$$$$|  $$$$$$$      | $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$/ \n") ;
	printf("\t\t|_______/  |______/ |_____  $$|_______/       |_______/ |_______/       |________/ |______/  |_______/ |______/  \n") ;
	printf("\t\t                     /$$   |$$                                                                                   \n") ;
	printf("\t\t                    |  $$$$$$/                                                                                   \n") ;
	printf("\t\t                    |_______/                                                                                    \n") ;

	printf("\n\n----------------------------------------------------------------------------------------------------------------------------------");
	printf("\n\n\t"); printf("Seja bem vindo a aplicacao do Jogo de Ludo que foi desenvolvido pela equipe de desenvolvimento LRDCRC. Essa aplicacao foi\n");
    printf("desenvolvida na universidade PUC-RIO em 2016.2 na disciplina INF1301. Antes de iniciarmos a partida, vamos definir os possiveis jogadores\n");
    printf("e as suas respectivas cores...\n\n\n");
    
    resposta = 1 ;
    for ( i = 0 ; resposta == 1 && i < MAX_JOGADORES ; i++ ) 
    {
    	printf ( "DIGITE O NOME DO '%s' JOGADOR: " , ordem[i] ); 
    	scanf(" %80[^\n]", vtJogadores[i].nome); 
    	vtJogadores[i].cor = 0;
    	printf("A COR DA SUA PECA SERA ------ "); printf( "%s " , cores[i] ) ; printf("------"); printf("\n\n");

    	for ( cor = MAX_PECAS * i ; cor < ( MAX_PECAS * i ) + MAX_PECAS ; cor++ ) 
    	{
    		PecasRetorno = PEC_CriaPeca (vtPecas, cor, i) ; 
    		switch ( PecasRetorno ) 
    		{
				case PEC_CondRetOK :
					break ;
				case PEC_CondRetFaltaMemoria : {
					printf("\n\n\tMEMORIA INSUFICIENTE PARA CRIAR PECAS !!\n\n");
					exit(1) ;
				}
				case PEC_CondRetJaExiste : {
					printf("\n\n\tPECA JA FOI CRIADA !!\n\n");
					exit(1);
				}
				case PEC_CondRetCorInvalida : {
					printf("\n\n\tCOR INVALIDA AO CRIAR A PECA !!\n\n");
					exit(1);
				}
				default : {
					printf("\n\n\tERRO INESPERADO !!\n\n");
				}
			}			
			
    	}

    	if ( i >= 1 && i <= 2) {
    		printf(".-----------------------------------.\n");
    		printf("| 1. Caso tenha mais jogadores.     |\n");
    		printf("| 2.Caso 'NAO' tenha mais jogadores.|\n");
    		printf(".-----------------------------------.\n");
    		printf("AGORA DIGITE SUA RESPOSTA: "); scanf("%d", &resposta); printf("\n");
    		while ( resposta != 1 && resposta != 2  ) {
    			printf("\tNUMERO INVALIDO!! \n\n");
    			printf("DIGITE SUA RESPOSTA: "); scanf("%d", &resposta); printf("\n");
    		}
    	}

    	num_jogadores++ ;
    }
    
    printf("\n***************************************************************************************************************************************\n\n");
    printf("\t\t\t\t\t\t\tPRIMEIRO PASSO CONCLUIDO !\n\n"); 
    printf("\n\tAgora para podermos iniciar a partida, o jogador devera estar ciente das regras do jogo que estao sendo representadas\n");
    printf("na especificacao de requisitos do Software... TENHAM UM OTIMO JOGO !!!"); printf("\n\n");

    TabuleiroRetorno = TAB_CriaTabuleiro_Ludo( &pTabuleiro ) ;
	
	if ( TabuleiroRetorno != TAB_CondRetOK )
	{
		printf("\n\n\tMEMORIA INSUFICIENTE PARA CRIAR TABULEIRO !!\n\n"); 
	}

	printf("**********************************************************     INICIO DO JOGO     ******************************************************\n\n");
	TAB_ExibeTabuleiro ( pTabuleiro , vtPecas , num_jogadores ) ;
	printf("\n\n\n\t\t\t\t\t\t\tDIGITE A LETRA - D - PARA JOGAR O DADO . . .\n\n");
	cond = 0 ;
	while ( !cond ) {
		for ( i = 0 ; i < num_jogadores && cond != 1 ; i++ ) 
		{
			printf( "JOGADOR : %s\n" , vtJogadores[i].nome ) ;
			scanf ( " %c" , &digito ) ;
			while ( digito != 'd' && digito != 'D' ) {
				printf("\n\n\tDIGITE A LETRA - D - PARA JOGAR O DADO . . .\n\n");
				scanf ( " %c" , &digito ) ;
			}
			dado = JogarDado() ;

			ZeraMapa ( valid_mapa ) ;
			for ( k = 0 ; k < MAX_PECAS ; k++ ) {
				ind = (MAX_PECAS * i) + k ;
				if ( ( dado == 6 && ValidaInsercao ( pTabuleiro , vtPecas[ind] ) ) || ValidaMovimento ( pTabuleiro , vtPecas[ind] , dado ) ) 
				{
					valid_mapa[k] = 1 ;
				}
			}
			if ( TemMovimento ( valid_mapa ) ) {
				MostraMovimentosValidos ( valid_mapa ) ;
				opcao = ObtemOrdemJogador() ;
				while ( valid_mapa[opcao] != 1 ) 
				{
					printf("\n\n\tESSA PECA NAO PODE SER MOVIMENTADA !!\n\n");
					opcao = ObtemOrdemJogador() ;
				}

				peca = vtPecas[ (MAX_PECAS * i) + opcao ] ;
				PEC_ObtemStatus ( peca , &status ) ;
				if ( status == 'F' )
					InserePecaJogo ( pTabuleiro , peca ) ;
				else
					RealizaMovimento ( pTabuleiro , peca , dado ) ;

				cond = VerificaVencedor ( vtPecas , i , vtJogadores ) ; 
			}

			TAB_ExibeTabuleiro ( pTabuleiro , vtPecas , num_jogadores ) ;
				
		} 
	}

	DesenhaPlacar( vtPecas, vtJogadores , num_jogadores );

    for (i = 0 ; i < MAX_PECAS * num_jogadores ; i++ ) 
    {
    	PecasRetorno = PEC_DestroiPeca ( vtPecas[i] );
    	switch ( PecasRetorno ) 
			{
				case PEC_CondRetOK :
					break ;
				case PEC_CondRetNaoExiste : {
					printf("\n\n\tPECA NAO EXISTE !!\n\n");
					exit(1);
				}
				default :
					printf("\n\n\tERRO INESPERADO !!\n\n");
					exit(1);
			}
    }

    TabuleiroRetorno = TAB_DestruirTabuleiro ( pTabuleiro ) ; 

	printf("\n\n");
	printf("\t\t__/\\\\\\\\\\\\\\\\\\_________________________________________\n"); 
	printf("\t\t _\\/\\\\///////////___________________________________________\n"); 
	printf("\t\t  _\\/\\\\______________/\\\\___________________________________\n"); 
	printf("\t\t   _\\/\\\\\\\\\\\\_____\\///_____/\\\\\\__/\\\\\\_______________\n"); 
	printf("\t\t    _\\/\\\\///////_______/\\\\__/\\\\\\///\\\\\\///\\\\__________\n"); 
	printf("\t\t     _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); 
	printf("\t\t      _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); 
	printf("\t\t       _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); 
	printf("\t\t        _\\///______________\\///_ _\\///____\\////_____\\////________\n"); 
	printf("\n\n");

	return 0;

}    /* Fim função: MAIN */

/****************  Código das funções encapsuladas no módulo  **********************/

static int JogarDado ( void )
{
	int valor;
	TAB_CondRet TabuleiroRetorno;
	TabuleiroRetorno = TAB_LancaDado ( &valor ) ;
	
	printf("\t\t\t+------+    \n");   
	printf("\t\t\t|`.    | `. \n");  
	printf("\t\t\t|  `+--+---+\n"); 
	printf("\t\t\t|   |  |   |\n");
	printf("\t\t\t+---+--+.  |\n");  
	printf("\t\t\t `. |    `.|\n");
	printf("\t\t\t   `+------+\n");
	printf("\n");
	printf("************  AO JOGAR O DADO VOCE OBTEVE O NUMERO: %d *************\n\n", valor);
	return valor;
}

static void DesenhaPlacar ( PEC_tpPeca * pPecas , JOGO_Jogador * vtJogadores , int num_jogadores )
{
	int i, k, final ;
	int qtdfim[] = { 0 , 0 , 0 , 0 };
	PEC_CondRet PecasRetorno ;

	for(i = 0 ; i < num_jogadores ; i++)
	{
		for( k = 4 * i ; k < (4 * i) + 4 ; k++ )
		{
			PecasRetorno = PEC_ObtemFinal ( pPecas[k] , &final );
			switch ( PecasRetorno ) 
			{
				case PEC_CondRetOK :
					break ;

				case PEC_CondRetNaoExiste : {
					printf("\n\n\tPECA NAO EXISTE !!\n\n");
					exit(1) ;
				}
				default : {
					printf("\n\n\tERRO INESPERADO !!\n\n");
					exit(1) ;
				}
			}
			
			if ( final == 1 )
				qtdfim[i]++ ;
		}
	}
	
	ordenaRanking ( vtJogadores , qtdfim , num_jogadores ) ;

	for ( i = 0 ; i < num_jogadores ; i++ )
	{
		printf("JOGADOR: %s OBTEVE %d PONTOS !!\n", vtJogadores[i].nome ,qtdfim[i] );
	}
	printf("\n");
}



static int VerificaVencedor ( PEC_tpPeca * pPecas, int cor, JOGO_Jogador * vtJogadores )
{
	int i , final ;
	PEC_CondRet PecasRetorno ;
	for ( i = cor * MAX_PECAS ; i < (cor * MAX_PECAS) + MAX_PECAS ; i++ ) {
		PecasRetorno = PEC_ObtemFinal ( pPecas[i] , &final ) ;
		if ( final != 1 )
			return 0 ;
	}

	printf("\n\n");
	printf("\t\t.----------------------------------------------.\n");
    printf("\t\t|                                              |\n");
    printf("\t\t|     PARABENS !!! TEMOS UM VENCEDOR . . .     |\n");
    printf("\t\t|                                              |\n");
    printf("\t\t.----------------------------------------------.\n");
    printf("\n\n");
	printf("O JOGADOR %s E O VENCEDOR DO JOGO!!!\n\n", vtJogadores[cor].nome ); 

	return 1 ;
}



static void ordenaRanking ( JOGO_Jogador * vtJogadores , int *qtdfim , int n ) {		//ordenação descrescente 

	int fim , i ;
	int menor , aux ;

	JOGO_Jogador jogador_aux ;
	
	for ( fim = n - 1 ; fim > 0 ; fim-- ) {
		menor = 0 ;
		for ( i = 1 ; i <= fim ; i++ )
			if ( qtdfim[i] < qtdfim[menor] )
				menor = i ;
		
		aux = qtdfim[fim] ;
		qtdfim[fim] = qtdfim[menor] ;
		qtdfim[menor] = aux ; 

		jogador_aux = vtJogadores[fim] ;
		vtJogadores[fim] = vtJogadores[menor] ;
		vtJogadores[menor] = jogador_aux ;

	}

}		

static int ValidaMovimento ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca , int n )
{
	int cor , cor2 ;
	int final ;
	PEC_tpPeca conteudo ;
	TAB_CondRet TabuleiroRetorno ;
	PEC_CondRet PecasRetorno ;

	if ( n <= 0 || n > 6 )
		return 0 ;

	PecasRetorno = PEC_ObtemFinal ( pPeca , &final ) ;
	if ( PecasRetorno != PEC_CondRetOK ) {
		printf("\n\n\tPECA NAO EXISTE !!\n\n");
		exit(1) ;
	}

	if ( final == 1 )
		return 0 ;

	TabuleiroRetorno = TAB_ProcuraPeca ( pTabuleiro ,  pPeca ) ;
	switch ( TabuleiroRetorno ) {

		case TAB_CondRetOK : 
			break ;
		
		case TAB_CondRetNaoEncontrouPeca : {
			printf("\n\n\tPECA NAO ENCONTRADA !!\n\n");
			exit(1) ;
		}
		case TAB_CondRetPecaMorta : {
			return 0 ;
		}
		default : {
			printf("\n\n\tERRO INESPERADO !!\n\n");
			exit(1) ;
		}

	}

	PEC_ObtemCor ( pPeca , &cor ) ;

	TabuleiroRetorno = TAB_AvancaCasa ( pTabuleiro , cor , n ) ;
	if ( TabuleiroRetorno == TAB_CondRetFimTabuleiro )
		return 0 ;

	TAB_ObterPecaCasa ( pTabuleiro , &conteudo ) ;
	if ( conteudo != NULL ) {
		PEC_ObtemCor ( conteudo , &cor2 ) ;
		if ( cor == cor2 )
			return 0 ;
	}

	return 1 ;
}

static void RealizaMovimento ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca , int n )
{
	PEC_tpPeca conteudo ;
	TAB_CondRet TabuleiroRetorno ;
	int valid , cond , cor ;

	valid = ValidaMovimento ( pTabuleiro , pPeca , n ) ;
	if ( !valid ) {
		printf("\n\n\tMOVIMENTO INVALIDO !!\n\n");
		exit(1) ;
	}

	TabuleiroRetorno = TAB_RetiraPecaCasa ( pTabuleiro , pPeca ) ; 

	PEC_ObtemCor ( pPeca , &cor ) ;
	TAB_AvancaCasa ( pTabuleiro , cor , n ) ;

	TAB_EhCasaFinal ( pTabuleiro , &cond ) ;
	if ( cond )
		PEC_AtualizaPeca ( pPeca , 1 , 'D' ) ;

	else {
		TAB_ObterPecaCasa ( pTabuleiro , &conteudo ) ;

		if ( conteudo != NULL )
			PEC_AtualizaPeca ( conteudo , 0 , 'F' ) ;

		TAB_InserePecaCasa ( pTabuleiro , pPeca ) ;
	}




}

static int ValidaInsercao ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) 
{
	int cor , cor2 ;
	char status ;
	PEC_tpPeca conteudo ;
	PEC_CondRet PecasRetorno ;
	TAB_CondRet TabuleiroRetorno ;

	PecasRetorno = PEC_ObtemStatus ( pPeca , &status ) ;
	if ( PecasRetorno != PEC_CondRetOK ) {
		printf("\n\n\tPECA NAO EXISTE !!\n\n");
		exit(1) ;
	}
	if ( status == 'D' )
		return 0 ;

	PEC_ObtemCor ( pPeca , &cor ) ; 

	TabuleiroRetorno = TAB_IrInicioCor ( pTabuleiro , cor ) ;
	if ( TabuleiroRetorno != TAB_CondRetOK ) {
		printf("\n\n\tCOR INVALIDA !!\n\n");
		exit(1) ;
	}

	TAB_ObterPecaCasa ( pTabuleiro , &conteudo ) ;
	if ( conteudo != NULL ) {
		PEC_ObtemCor ( conteudo , &cor2 ) ;
		if ( cor == cor2 )
			return 0 ;
	}

	return 1 ;
} 

static void InserePecaJogo ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca )
{
	int cor , valid ;
	char status ;
	TAB_CondRet TabuleiroRetorno ;
	PEC_CondRet PecasRetorno ;

	valid = ValidaInsercao ( pTabuleiro , pPeca ) ;
	if ( !valid ) {
		printf("\n\n\tINSERCAO INVALIDA !!\n\n");
		exit(1) ;
	}

	PecasRetorno = PEC_ObtemStatus ( pPeca , &status ) ;
	if ( PecasRetorno != PEC_CondRetOK ) {
		printf("\n\n\tPECA NAO EXISTE !!\n\n");
		exit(1) ;
	}

	if ( status == 'D' ) {
		printf("\n\n\tPECA JA INSERIDA !!\n\n");
		exit(1) ;
	}


	PecasRetorno = PEC_ObtemCor ( pPeca , &cor ) ;

	TabuleiroRetorno = TAB_IrInicioCor ( pTabuleiro , cor ) ;
	if ( TabuleiroRetorno != TAB_CondRetOK ) {
		printf("\n\n\tCOR INVALIDA !!\n\n");
		exit(1) ;
	}

	TAB_InserePecaCasa ( pTabuleiro , pPeca ) ;

}

static int ObtemOrdemJogador ( void )
{
	int num ;
	printf ( "DIGITE O NUMERO DA PECA QUE DESEJA MOVIMENTAR : " ) ;
	scanf ( "%d" , &num ) ; 
	while ( num < 0 || num > 3 ) {
		printf("\n\n\tNUMERO INVALIDO !!\n\n");
		printf ( "DIGITE O NUMERO DA PECA QUE DESEJA MOVIMENTAR : " ) ;
		scanf ( "%d" , &num ) ; 
	}
	printf("\n\n");
	return num ;
}

static void MostraMovimentosValidos ( int *mapa )
{
	int i ; 
	printf("PECAS QUE PODEM SER MOVIDAS : ");
	for ( i = 0 ; i < MAX_PECAS ; i++ )
	{
		if ( mapa[i] == 1 )
			printf( "P%d " , i ) ;
	}
	printf("\n") ;
}

static void ZeraMapa ( int *mapa )
{
	int i ; 
	for ( i = 0 ; i < MAX_PECAS ; i++ )
		mapa[i] = 0 ;
}

static int TemMovimento ( int *mapa )
{
	int i ;
	for ( i = 0 ; i < MAX_PECAS ; i++ )
		if ( mapa[i] == 1 )
			return 1 ;
	return 0 ;
}


/************* Fim do módulo de implementação: JOGO Módulo jogo / Principal ****************/
