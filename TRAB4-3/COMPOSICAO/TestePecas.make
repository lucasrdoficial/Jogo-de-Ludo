##################################################
###
### Diretivas de MAKE para o construto: TestePecas
### Gerado a partir de: TestePecas.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TestePecas


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
   $(Fobj)\testpec.obj   $(Fobj)\pecas.obj \
   Construto

### Limpar arquivos

limpa :
   CompileBanner /c$(NOME)
   CompileBanner /c$(NOME) >$(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testpec.obj :  {$(Pc)}\testpec.c \
    {$(Ph)}generico.h           {$(Ph)}lerparm.h            {$(Ph)}pecas.h              \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\pecas.obj :  {$(Pc)}\pecas.c \
    {$(Ph)}pecas.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testpec.obj   $(Fobj)\pecas.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TestePecas
###
##################################################

