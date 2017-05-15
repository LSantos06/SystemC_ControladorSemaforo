#include "sistema.h"

int sc_main (int arc, char * argv[]){
	// Sistema que eh o modulo de mais alto nivel que instancia o Controlador e seu TestBench, interconectando-os
	sistema sistema_instance("sistema_instance");

	sistema_instance.simular();

	return 0;
}
