/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: rvc - Rodrigo Villardi Cortezi
*
*  $HA Histórico de evolução:
*     Versão |  Autor  |      Data     |    Observações
*       2    |   rvc   |  13/out/2016  |  finalização de desenvolvimento
*       1    |   rvc   |  30/set/2016  |  início desenvolvimento
*
***************************************************************************/
 
#define BRANCO 5
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#include "LISTA.H"
#include "LCIRC.H"
#include "PECAS.H"
 
#define MAX_PECAS 4

#define TABULEIRO_OWN
#include "TABULEIRO.H"
#undef TABULEIRO_OWN
 
/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do tabuleiro de ludo
*
***********************************************************************/
 
typedef struct Tabuleiro 
{
    LST_Circular casas ;
        /* Ponteiro para a lista de casas */
    int flag ;
        /* Indica se a casa corrente esta no desvio: 1 caso verdadeiro 0 caso falso */
 
} TAB_TabuleiroLudo ;
 
/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da casa
*
***********************************************************************/
 
typedef struct TAB_casa 
{
    int cor ;
        /* Indica a cor da casa */
 
    PEC_tpPeca conteudo ;
        /* Ponteiro para o conteudo da casa */
 
    LIS_tppLista desvio ;
        /* Ponteiro para o desvio */
 
} TAB_Casa ;


typedef void ( *pFunc ) ( void * ) ; typedef void **ppVoid ;
 
/***** Protótipo das funções encapsuladas no módulo *****/
 
static TAB_Casa *CriaCasa ( LIS_tppLista desvio , 
                             PEC_tpPeca conteudo , int cor ) ;

static void IrDesvioCor ( TAB_TabuleiroLudo *pTabuleiro , int cor ) ;

static void copia ( char tabuleiro[][61] , char quadrado[][9] , int lin , int col ) ;

static void CentroBase ( PEC_tpPeca *pecas , int cor , char tabuleiro[][61] ) ;

static void RetaFinal ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca *pecas , int cor , char matriz[][61] ) ;

static int IndiciePeca ( PEC_tpPeca *vtPecas , PEC_tpPeca pPeca , int cor ) ;

static void CaminhoNeutro ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca *vtPecas , char matriz[][61] ) ;

static void CasaFinal ( PEC_tpPeca *pecas , int cor , char matriz[][61] ) ;

static char InteiroPraChar ( int num ) ;

static int CharPraInteiro ( char c ) ;
 
static void LiberarCasa ( TAB_Casa *pCasa ) ;
 
 
/*****  Código das funções exportadas pelo módulo  *****/
 
/*************************************************************************** 
*
*  Função: TAB  &Criar tabuleiro
*  ****/
 
 
TAB_CondRet TAB_CriaTabuleiro_Ludo( TAB_TabuleiroLudo **pTabuleiro )  
{   
    int i, k , j ;
 
    LST_Circular pListaCirc ;
 
    LIS_tppLista pListaSimples ;

    TAB_Casa *casa ;
 
    LST_CondRet retorno_lst ;
 
    LIS_tpCondRet retorno_lis ;

    *pTabuleiro = ( TAB_TabuleiroLudo *) malloc ( sizeof ( TAB_TabuleiroLudo ) ) ;
    
    if ( *pTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    }
 
    retorno_lst = LST_CriaLista ( &pListaCirc , ( pFunc ) LiberarCasa ) ;
    if ( retorno_lst != LST_CondRetOK )
    {
        return TAB_CondRetFaltouMemoria ;
    } 
 
    for( i = 0 ; i < 4 ; i++ ){
         
        for( k = 0; k < 12 ; k++ ){
 
            casa = CriaCasa ( NULL , NULL , BRANCO ) ;
            if ( casa == NULL )
            {
                return TAB_CondRetFaltouMemoria ;
            }
            retorno_lst = LST_InsereElemDireita( pListaCirc , casa ) ;
            if ( retorno_lst != LST_CondRetOK )
            {
                return TAB_CondRetFaltouMemoria ;
            }
 
        }
 
        retorno_lis = LIS_CriarLista( ( pFunc ) LiberarCasa , &pListaSimples ) ;
        if ( retorno_lis != LIS_CondRetOK )
        {
            return TAB_CondRetFaltouMemoria ;
        }

        casa = CriaCasa ( pListaSimples , NULL , i ) ;
        if ( casa == NULL )
        {
            return TAB_CondRetFaltouMemoria ;
        }
        retorno_lst = LST_InsereElemDireita ( pListaCirc , casa ) ;
        if ( retorno_lst !=  LST_CondRetOK )
        {
            return TAB_CondRetFaltouMemoria ;
        }

        for ( j = 0 ; j < 6 ; j++ ){
 
            casa = CriaCasa ( NULL , NULL , i ) ;
            if ( casa == NULL )
            {
                return TAB_CondRetFaltouMemoria ;
            }
            retorno_lis = LIS_InserirElementoApos( pListaSimples , casa ) ;
            if ( retorno_lis != LIS_CondRetOK )
            {
                return TAB_CondRetFaltouMemoria ;
            }
                 
        }
 
    }
 
    (*pTabuleiro)->casas = pListaCirc ;
    (*pTabuleiro)->flag = 0 ;
    
    return TAB_CondRetOK ;
 
} /* Fim função: TAB  &Criar tabuleiro */

/*************************************************************************** 
*
*  Função: TAB  &Procura Peça
*  ****/

TAB_CondRet TAB_ProcuraPeca ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca pPeca )        
{
    PEC_CondRet retorno_pec ;
    TAB_Casa *casa , *aux ;
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    LIS_tpCondRet retorno_lis ;
    int cor ;
    char status ;

    retorno_pec = PEC_ObtemStatus ( pPeca , &status ) ;
    if ( retorno_pec != PEC_CondRetOK )
        return TAB_CondRetPecaNaoExiste ;

    if ( status == 'F' )
        return TAB_CondRetPecaMorta ;

    lista_circular = pTabuleiro->casas ;
    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    aux = casa ;
    
    do {
        
        if ( aux->conteudo == pPeca ) {
            pTabuleiro->flag = 0 ;
            return TAB_CondRetOK ;
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        LST_ObterValor ( lista_circular , ( ppVoid ) &aux ) ;

    } while ( aux != casa ) ;

    PEC_ObtemCor ( pPeca , &cor ) ;
    IrDesvioCor ( pTabuleiro , cor ) ;

    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    lista_simples = casa->desvio ;
    LIS_IrInicioLista ( lista_simples ) ;
    
    do {

        LIS_ObterValor ( lista_simples , ( ppVoid ) &aux ) ;
        if ( aux->conteudo == pPeca ) {
            pTabuleiro->flag = 1 ;      //para indicar que entrou no desvio
            return TAB_CondRetOK ;
        }

        retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , 1 ) ;

    } while ( retorno_lis != LIS_CondRetFimLista ) ;

    return TAB_CondRetNaoEncontrouPeca ;
   
}  /* Fim função: TAB  &Procura Peça */

/*************************************************************************** 
*
*  Função: TAB  &Obter Peça Casa
*  ****/

TAB_CondRet TAB_ObterPecaCasa ( TAB_TabuleiroLudo *pTabuleiro, PEC_tpPeca *pPeca )
{
    TAB_Casa *casa ;
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    
    lista_circular = pTabuleiro->casas ;
    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;

    if ( pTabuleiro->flag  ) {
        lista_simples = casa->desvio ;
        LIS_ObterValor ( lista_simples , ( ppVoid ) &casa ) ;
    }

    *pPeca = casa->conteudo ;

    return TAB_CondRetOK ; 

}   /* Fim função: TAB  &Obter Peça Casa */

/*************************************************************************** 
*
*  Função: TAB  &Avança Casa
*  ****/

TAB_CondRet TAB_AvancaCasa ( TAB_TabuleiroLudo *pTabuleiro , int cor , int n )
{
    TAB_Casa *casa ;
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    LIS_tpCondRet retorno_lis ;

    if ( cor < 0 || cor > 3 )
        return TAB_CondRetCorInvalida ;
    
    lista_circular = pTabuleiro->casas ;
    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    
    if ( pTabuleiro->flag  ) {

        lista_simples = casa->desvio ;
        retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , n ) ;
        if ( retorno_lis == LIS_CondRetFimLista )
            return TAB_CondRetFimTabuleiro ;

        return TAB_CondRetOK ;

    } 

    while ( casa->cor != cor && n != 0) {

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
        n-- ;

    }
    if ( n != 0 ) {
        lista_simples = casa->desvio ;
        LIS_IrInicioLista ( lista_simples ) ;
        retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , n - 1 ) ;
        if ( retorno_lis == LIS_CondRetFimLista )
            return TAB_CondRetFimTabuleiro ;
        pTabuleiro->flag = 1 ;
    }

    return TAB_CondRetOK ;

}   /* Fim função: TAB  &Avança Casa */

/*************************************************************************** 
*
*  Função: TAB  &Retira Peça Casa
*  ****/

TAB_CondRet TAB_RetiraPecaCasa ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca pPeca ) 
{
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    TAB_Casa *casa ;
    TAB_CondRet retorno_tab ;
    retorno_tab = TAB_ProcuraPeca ( pTabuleiro , pPeca ) ;
    if ( retorno_tab != TAB_CondRetOK )
        return retorno_tab ;

    lista_circular = pTabuleiro->casas ;
    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;

    if ( pTabuleiro->flag  ) {
        lista_simples = casa->desvio ;
        LIS_ObterValor ( lista_simples , ( ppVoid ) &casa ) ;
    }
    
    casa->conteudo = NULL ;

    PEC_AtualizaPeca ( pPeca , 0 , 'F' ) ;

    return TAB_CondRetOK ;

}   /* Fim função: TAB  &Retira Peça Casa */

/*************************************************************************** 
*
*  Função: TAB  &Insere Peça Casa
*  ****/

TAB_CondRet TAB_InserePecaCasa ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca pPeca ) 
{
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    TAB_Casa *casa ;
    PEC_CondRet retorno_pec ;
    int cor ;

    retorno_pec = PEC_ObtemCor ( pPeca , &cor ) ;
    if ( retorno_pec != PEC_CondRetOK )
        return TAB_CondRetPecaNaoExiste ;

    lista_circular = pTabuleiro->casas ;
    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;

    if ( pTabuleiro->flag  ) {
        lista_simples = casa->desvio ;
        LIS_ObterValor ( lista_simples , ( ppVoid ) &casa ) ;
    }

    if ( casa->conteudo != NULL ) 
        TAB_RetiraPecaCasa ( pTabuleiro , casa->conteudo ) ;
    

    PEC_AtualizaPeca ( pPeca , 0 , 'D' ) ;

    casa->conteudo = pPeca ;

    return TAB_CondRetOK ;

}  /* Fim função: TAB  &Insere Peça Casa */


/*************************************************************************** 
*
*  Função: TAB  &Ir Início Cor
*  ****/
 
TAB_CondRet TAB_IrInicioCor ( TAB_TabuleiroLudo *pTabuleiro , int cor )
{
    LST_Circular lista_circular ;

    if ( cor < 0 || cor > 3 )
        return TAB_CondRetCorInvalida ;

    lista_circular = pTabuleiro->casas ;

    IrDesvioCor ( pTabuleiro , cor ) ;
    
    LST_AvancarElementoCorrente ( lista_circular , 2 ) ;

    return TAB_CondRetOK ;

}   /* Fim função: TAB  &Ir Inicio Cor */


TAB_CondRet TAB_EhCasaFinal ( TAB_TabuleiroLudo *pTabuleiro , int *cond )       //verifica se casa corrente é a casa final
{
    TAB_Casa *casa ;
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    LIS_tpCondRet retorno_lis ;
    
    if ( pTabuleiro->flag ) {
        lista_circular = pTabuleiro->casas ;
        LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
        
        lista_simples = casa->desvio ;
        retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , 1 ) ;
        if ( retorno_lis == LIS_CondRetFimLista )
            *cond = 1 ;
        else {
            LIS_AvancarElementoCorrente ( lista_simples , -1 ) ;
            *cond = 0 ;
        }
    }
    else
        *cond = 0 ;

    return TAB_CondRetOK ;

}   

 
/***************************************************************************
*
*  Função: TAB  &Gera valor
*  ****/
 
TAB_CondRet TAB_LancaDado ( int * pValor )
{
  
    int ValorAleatorio ;
  
    srand ( (unsigned) time ( NULL ) ) ;
    ValorAleatorio = ( rand() % 6 ) + 1 ;
      
    * pValor = ValorAleatorio ;
  
    return TAB_CondRetOK ;
  
} /* Fim função: TAB  &Gera Valor */

/***************************************************************************
*
*  Função: TAB  &Destroi Tabuleiro
*  ****/
 
TAB_CondRet TAB_DestruirTabuleiro ( TAB_TabuleiroLudo *pTabuleiro )
{
 
    LST_DestruirLista ( pTabuleiro->casas ) ;
 
    return TAB_CondRetOK ;
 
} /* Fim função: TAB  &Destroi Tabuleiro */

TAB_CondRet TAB_ExibeTabuleiro ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca *pecas , int num_jogadores )
{
    int i , lin , col , cor ;
    char matriz[31][61] =    {  ".-----------------------.---.---.---.-----------------------." ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---.                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---.                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|---.---.---.---.---.---+---+---+---+---.---.---.---.---.---|" ,
                                "|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |" ,
                                "|---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|" ,
                                "|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |" ,
                                "|---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|" ,
                                "|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |" ,
                                "|---^---^---^---^---^---+---+---+---+---^---^---^---.---.---|" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       |---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       .---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "|                       .---+---+---|                       |" ,
                                "|                       |   |   |   |                       |" ,
                                "^-----------------------^---^---^---^-----------------------^" } ;

     for ( i = 0 ; i < num_jogadores ; i++ ) 
     {                
        CentroBase ( pecas , i , matriz ) ;             // Verifica e insere pecas que estao na base na matriz
        RetaFinal ( pTabuleiro , pecas , i , matriz ) ; // Verifica e insere pecas que estao nas retas finais na matriz
        CasaFinal ( pecas , i , matriz ) ;              // Verifica e insere pecas que estao nas casas finais na matriz
    }
    CaminhoNeutro ( pTabuleiro , pecas , matriz ) ;  



    for ( lin = 0 ; lin < 31 ; lin++ ) 
    {
        for ( col = 0 ; col < 61 ; col++ ) 
        {
            if ( matriz[lin][col] >= '0' && matriz[lin][col] <= '3' && matriz[lin][col+1] >= '0' && matriz[lin][col+1] <= '3' ) 
            {
                cor  = CharPraInteiro ( matriz[lin][col] ) ;
                printf("p%c",matriz[lin][col+1]);
                col++;
            }
            else
                printf ( "%c" , matriz[lin][col] ) ;
        }
        printf ( "\n" ) ;
    }
    return TAB_CondRetOK ;
} 
 
 
/****************  Código das funções encapsuladas no módulo  **********************/
 
/*************************************************************************** 
*
*  Função: TAB  &Criar Casa
*  ****/

static TAB_Casa * CriaCasa ( LIS_tppLista desvio , PEC_tpPeca conteudo , int cor )
{
    TAB_Casa *nv ;
     
    nv  = (TAB_Casa *) malloc ( sizeof ( TAB_Casa ) ) ;
     
    if( nv == NULL ){
        return NULL ;
    }
 
    nv->cor = cor ;
 
    nv->desvio = desvio ;
 
    nv->conteudo = conteudo ;
 
    return nv ;

}  /* Fim função: TAB  &Criar Casa */

/*************************************************************************** 
*
*  Função: TAB  &Ir Desvio Cor
*  ****/

static void IrDesvioCor ( TAB_TabuleiroLudo *pTabuleiro , int cor )
{
    TAB_Casa *casa ;
    LST_Circular lista_circular ;

    lista_circular = pTabuleiro->casas ;

    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    while ( casa->cor != cor ) {
        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    }
    pTabuleiro->flag = 0 ;

}  /* Fim função: TAB  &Ir Desvio Cor */


static void copia ( char tabuleiro[][61] , char quadrado[][9] , int lin , int col ) {

    int i , j ;
    int aux = col ;
    for ( i = 0 ; i < 5 ; i++ ) {
        col = aux ;
        for ( j = 0 ; j < 9 ; j++ ) {
            tabuleiro[lin][col] = quadrado[i][j] ;
            col++ ;
        }
        lin++ ;
    }

}

static void CentroBase ( PEC_tpPeca *pecas , int cor , char tabuleiro[][61] ) 
{
    int k , lin , col ;
    char status , ind ;
    char quadrado[5][9] = { " --- --- " , 
                            "|   |   |" ,   
                            " ---+--- " , 
                            "|   |   |" , 
                            " --- --- " } ;
    PEC_CondRet retorno_pec ;

    ind = '0' ;
    for ( k = 0 ; k < MAX_PECAS ; k++ ) {
        retorno_pec = PEC_ObtemStatus ( pecas[ (4 * cor) + k ] , &status ) ;    
        if ( retorno_pec == PEC_CondRetOK && status == 'F' ) {
            lin = 1 + 2 * ( k / 2 ) ;
            col = 2 + ( 4 * ( k / lin ) ) ;
            quadrado[lin][col] = InteiroPraChar(cor) ;
            quadrado[lin][col+1] = ind ;  
        } 

        ind++ ;
    }
    
    switch ( cor ) {
        case 0: {
            lin = 4 ;
            col = 7 ;
            break ;
        }
        case 1: {
            lin = 4 ;
            col = 43 ;
            break ;
        }
        case 2: {
            lin = 22 ;
            col = 7 ;
            break ;
        }
        case 3: {
            lin = 22 ;
            col = 43 ;
            break ;
        }
        default: {
            printf ( "Condicao inesperada!\n" ) ;
            exit (1) ;
        }
    }
    copia ( tabuleiro , quadrado , lin , col ) ;
      

}

static void RetaFinal ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca *pecas , int cor , char matriz[][61] ) 
{
    int lin , col ;
    int diff ;
    int ind , i ;
    LST_Circular lista_circular ;
    LIS_tppLista lista_simples ;
    TAB_Casa *casa ;

    lista_circular = pTabuleiro->casas ;
    IrDesvioCor ( pTabuleiro , cor ) ;
    LST_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    lista_simples = casa->desvio ;
    LIS_IrInicioLista ( lista_simples ) ;

    switch ( cor ) {
        case 0 : {
            lin = 15 ;
            col = 6 ;
            diff = 4 ;
            break ;
        }
        case 1 : {  
            lin = 3 ;
            col = 30 ;
            diff = 2 ;
            break ;
        }
        case 2 : {
            lin = 15 ;
            col = 54 ;
            diff = -4 ;
            break ;
        }
        case 3 : {
            lin = 27 ;
            col = 30 ;
            diff = -2 ;
            break ;
        }
        default : { 
            printf ( "Condicao inesperada!\n" ) ;
            exit (1) ;
        }
    }
    
    for ( i = 0 ; i < 5 ; i++ ) {
        LIS_ObterValor ( lista_simples , ( ppVoid ) &casa ) ;
        if ( casa->conteudo != NULL ) {
            ind = IndiciePeca ( pecas , casa->conteudo , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ;
        }

        if ( cor == 0 || cor == 2 )
            col += diff ;
        else 
            lin += diff ;

        LIS_AvancarElementoCorrente ( lista_simples , 1 ) ;
    
    } 


}

static int IndiciePeca ( PEC_tpPeca *vtPecas , PEC_tpPeca pPeca , int cor )
{
    int i ;
    for ( i = 0 ; i < MAX_PECAS ; i++ )
        if ( vtPecas[(cor*MAX_PECAS) + i] == pPeca )
            return i ;
    return -1 ;
}
 

static void CaminhoNeutro ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca *vtPecas , char matriz[][61] )       //funcao burra
{
    int i , k ;
    int lin , col ;
    int cor ;
    int ind ;
    PEC_tpPeca peca ;
    LST_Circular lista_circular ;
    IrDesvioCor ( pTabuleiro , 0 ) ;
    
    lin = 15 ; col = 2 ;
    lista_circular = pTabuleiro->casas ;

    //PRIMEIRA PARTE
        
    TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
    if ( peca != NULL ) {
        PEC_ObtemCor ( peca , &cor ) ;
        ind = IndiciePeca ( vtPecas , peca , cor ) ;
        matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
        matriz[lin][col+1] = InteiroPraChar ( ind ) ;  
    }
    LST_AvancarElementoCorrente ( lista_circular , 1 ) ;

    lin -= 2 ;        
    
    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;

        
        col += 4 ;      
    }

    lin -= 2 ;
    
    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        if ( k != 5 )
            lin -= 2 ;      
    }

    // PARTE DOIS

    col += 4 ;

    TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
    if ( peca != NULL ) {
        PEC_ObtemCor ( peca , &cor ) ;
        ind = IndiciePeca ( vtPecas , peca , cor ) ;
        matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
        matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
    }
    LST_AvancarElementoCorrente ( lista_circular , 1 ) ;

    col += 4 ; 


    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        
        lin += 2 ;      
    }

    col += 4 ;

    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        if ( k != 5 )
            col += 4 ;      
    }

    // PARTE TRES

    lin += 2 ;    
    
    TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
    if ( peca != NULL ) {
        PEC_ObtemCor ( peca , &cor ) ;
        ind = IndiciePeca ( vtPecas , peca , cor ) ;
        matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
        matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
    }
    LST_AvancarElementoCorrente ( lista_circular , 1 ) ;

    lin += 2 ;

    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        
        col -= 4 ;      
    }
    
    lin += 2 ;

    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        
        if ( k != 5 )
            lin += 2 ;      
    }

    //PARTE QUATRO

    col -= 4 ;

    TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
    if ( peca != NULL ) {
        PEC_ObtemCor ( peca , &cor ) ;
        ind = IndiciePeca ( vtPecas , peca , cor ) ;
        matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
        matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
    }
    LST_AvancarElementoCorrente ( lista_circular , 1 ) ;

    col -= 4 ;

     for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        
        lin -= 2 ;      
    }

    col -= 4 ;

    for ( k = 0 ; k < 6 ; k++ ) {
        TAB_ObterPecaCasa ( pTabuleiro , &peca ) ;
        if ( peca != NULL ) {
            PEC_ObtemCor ( peca , &cor ) ;
            ind = IndiciePeca ( vtPecas , peca , cor ) ;
            matriz[lin][col]   = InteiroPraChar ( cor ) ; ;
            matriz[lin][col+1] = InteiroPraChar ( ind ) ; 
        }

        LST_AvancarElementoCorrente ( lista_circular , 1 ) ;
        
        if ( k != 5 )
            col -= 4 ;      
    }
    

}

static void CasaFinal ( PEC_tpPeca *pecas , int cor , char matriz[][61] )
{
    int col , lin ;
    int i , final , cont ;
    cont = 0 ;
    for ( i = cor * MAX_PECAS ; i < (cor * MAX_PECAS) + 4 ; i++ ) {
        PEC_ObtemFinal ( pecas[i] , &final ) ;
        if ( final == 1 )
            cont++ ;
    }

    switch ( cor ) {
        case 0 : {
            lin = 15 ;
            col = 26 ;
            break ;
        }
        case 1 : {
            lin = 13 ;
            col = 30 ;
            break ;
        }
        case 2 : {
            lin = 15 ;
            col = 34 ;
            break ;
        }
        case 3 : {
            lin = 19 ;
            col = 26 ;
            break ;
        }
    }
    if ( cont > 0 )
        matriz[lin][col] = InteiroPraChar ( cont ) ;
}

static char InteiroPraChar ( int num )
{
    char c ;
    c = '0' + num ;
    return c ;
}

static int CharPraInteiro ( char c )
{
    int num ;
    num = c - '0' ;
    return num ;
}


/*************************************************************************** 
*
*  Função: TAB  &Liberar Casa
*  ****/

static void LiberarCasa ( TAB_Casa *pCasa ) 
{
 
    if ( pCasa->desvio != NULL )
    {
        LIS_DestruirLista( pCasa->desvio ) ;
    }
 
    if ( pCasa->conteudo != NULL )
    {
        PEC_DestroiPeca ( pCasa->conteudo ) ;
    }
     
    pCasa = NULL ;

}   /* Fim função: TAB  &Liberar Casa */
