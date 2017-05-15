#include "controlador_tb.h"

#define NUM_CLKS 20

void driver::drive(){
	int contador;

	// Teste quando nao tem carros na via
	sensor_via = false;

	contador = 0;
	while (contador < NUM_CLKS/2){
		contador++;

		clk = 0;
		wait(1, SC_NS);
		clk = 1;
		wait(1, SC_NS);
	}

	// Teste quando tem carros na via
	sensor_via = true;

	contador = 0;
	while (contador < NUM_CLKS){
		contador++;

		clk = 0;
		wait(1, SC_NS);
		clk = 1;
		wait(1, SC_NS);
	}

	// Teste quando nao tem carros na via
	sensor_via = false;

	contador = 0;
	while (contador < NUM_CLKS/2){
		contador++;

		clk = 0;
		wait(1, SC_NS);
		clk = 1;
		wait(1, SC_NS);
	}

	// Teste quando tem carros na via
	sensor_via = true;

	contador = 0;
	while (contador < NUM_CLKS){
		contador++;

		clk = 0;
		wait(1, SC_NS);
		clk = 1;
		wait(1, SC_NS);
	}
}

// Funcoes para impressao das enumeracaoes
char const* getCor(uint8_t cor){
	switch(cor){
		case 0: return "Amarelo";
		case 1: return "Vermelho";
		case 2: return "Verde";
	}
	return "";
}

char const* getEstado(uint8_t estado){
	switch(estado){
		case 0: return "S0";
		case 1: return "S1";
		case 2: return "S2";
		case 3: return "S3";
	}
	return "";
}

void monitor::monitora(){
	cout << "Tempo " << sc_time_stamp() << ": " << endl;
	cout << "estado: " << getEstado(estado) << endl;
	cout << "proximo_estado: " << getEstado(proximo_estado) << endl;
	cout << "semaforo_autoestrada: " << getCor(semaforo_autoestrada) << endl;
	cout << "semaforo_via: " << getCor(semaforo_via) << endl << endl;
}
