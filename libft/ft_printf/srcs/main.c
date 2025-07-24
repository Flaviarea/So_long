#include <stdio.h>
#include "ft_printf.h"

int main()
{
	char *test_string = "amo Miki";
    ft_printf("Stampa array: %s", test_string);
}

/*
int count;
// return di printf è il numero di caratteri stampati 
    count = ft_printf("Hell%, world!\n");
    printf("Caratteri stampati: %d\n", count);

char *test = "no";
// nessun placeholder dopo %
printf("C'è solo questo %(s) e basta", test);
    return 0;
*/