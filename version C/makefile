# ############################################################
# 
# Makefile for "skel" with pre-compiled headers
# 
# Args :
#  - DEBUG = enable/disable debugging options during compilation
#    Value = 0/1
#    Default = 0
# 
# ############################################################


# ############################################################
#
# Constants defintions
#
# ############################################################

NAME = rc4
NASM = C:\NASM\nasm.exe
CC	= cl
LINK = link
DEL	= @del

# Set defaut values for parameters
!IFNDEF DEBUG
DEBUG = 0
!ENDIF

# ############################################################
#
# Directories and file pathes definition
#
# ############################################################

O = obj
O_ASM = obj_asm
E = exe
S = sources
H = headers
I = includes
T = tests
EXE = $(E)\$(NAME).exe

# ############################################################
#
# Files definitions
#
# ############################################################

OBJS = $(O)\*.obj
OBJS_ASM = $(O_ASM)\*.obj

# ############################################################
#
# Definition of compilation parameters
#
# ############################################################

CFLAGS = /c /nologo /W3 /I"$(H)" /Fd"$(E)\$(NAME).pdb" /Fp"$O\stdafx.pch" /TC 
!IF "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) /ZI
!ELSE
CFLAGS = $(CFLAGS) /O1 /Os
!ENDIF

LFLAGS = /nologo
!IF "$(DEBUG)" == "1"
LFLAGS = $(LFLAGS) /debug
!ENDIF

NFLAGS = -f win32

# ############################################################
#
# Inferences rules
#
# ############################################################

all:$(EXE)
$(O)\stdafx._obj_:$(H)\stdafx.h
	$(CC) /Yc $(CFLAGS) $(S)\stdafx._c_ /Fo$@
{$(S)}.c{$(O)}.obj:
	$(CC) /Yu"stdafx.h" $(CFLAGS) $< /Fo$(O)\\
{$(S)}.asm{$(O_ASM)}.obj:
	$(NASM) $(NFLAGS) $<
	move $(S)\\*.obj $(O_ASM)


# ############################################################
#
# Link
#
# ############################################################

$(EXE): $(O)\stdafx._obj_ $(OBJS) $(OBJS_ASM)
 	$(LINK) $(LFLAGS) $** /OUT:"$(EXE)"

# ############################################################
#
# Clean
#
# ############################################################

clean:
	$(DEL) /Q $(O)\* $(O_ASM)\* $(E)\* $(T)\ciphered.txt  $(T)\deciphered_invalid.txt $(T)\deciphered_valid.txt
