##################################################
###
### Diretivas de MAKE para o construto: JOGO
### Gerado a partir de: Jogo.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = JOGO


### Nomes de paths

Pinc                 = .
Ptab                 = .
Pdef                 = .
Ph                   = .
Pobj                 = .
Perr                 = .
PDEFAULT             = .
Pc                   = .

### Nomes de diretórios para geração

Finc                 = .
Ftab                 = .
Fdef                 = .
Fh                   = .
Fobj                 = .
Ferr                 = .
FDEFAULT             = .
Fc                   = .

### Macros da plataforma


O       =
OD      = /Zi /Od
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\lista.obj   $(Fobj)\lcirc.obj   $(Fobj)\pecas.obj \
   $(Fobj)\tabuleiro.obj   $(Fobj)\jogo.obj \
   Construto

### Limpar arquivos

limpa :
   CompileBanner /c$(NOME)
   CompileBanner /c$(NOME) >$(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lcirc.obj :  {$(Pc)}\lcirc.c \
    {$(Ph)}cespdin.h            {$(Ph)}conta.h              {$(Ph)}generico.h           \
    {$(Pdef)}idtiposespaco.def    {$(Ph)}intrpced.h           {$(Ph)}lcirc.h              \
    {$(Pdef)}tiposespacoslcirc.def {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\pecas.obj :  {$(Pc)}\pecas.c \
    {$(Ph)}pecas.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\tabuleiro.obj :  {$(Pc)}\tabuleiro.c \
    {$(Ph)}lcirc.h              {$(Ph)}lista.h              {$(Ph)}pecas.h              \
    {$(Ph)}tabuleiro.h         
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\jogo.obj :  {$(Pc)}\jogo.c \
    {$(Ph)}lcirc.h              {$(Ph)}lista.h              {$(Ph)}pecas.h              \
    {$(Ph)}tabuleiro.h         
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\lista.obj   $(Fobj)\lcirc.obj   $(Fobj)\pecas.obj \
   $(Fobj)\tabuleiro.obj   $(Fobj)\jogo.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: JOGO
###
##################################################

