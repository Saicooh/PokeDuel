#ifndef funciones_h
#define funciones_h

void menu();

void validarOpcion(int *opcion);

void validarOpcionPokemon(int *opcion, int equipoRegistrado);

void validar(int *user_continue);

char *gets_csv_field(char *tmp, int k);

void escribirLentamente(char *texto, int saltosLinea);

int calcularEspaciosExtra(int largoCadena, int ancho);

void playSongType(int type, int loop, int numLiga, int stop);

#endif /* funciones_h */