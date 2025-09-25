GCC = gcc
BIBLIOTECAS = -lm

PROGRAMAS = mod_Lopez

mod_Lopez:
		$(GCC) $@.c -o $@
		
clear:
	$(RM) $(PROGRAMAS)
