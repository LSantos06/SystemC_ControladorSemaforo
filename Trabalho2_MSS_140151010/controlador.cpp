#include "controlador.h"

void controlador::temporizador(){
	while(true){
		switch (estado){
			case 0:
				// Realiza a mudanca de estado
				ativacao.write(!ativacao);
				wait(IC);
				break;

			case 1:
				// Realiza a mudanca de estado
				ativacao.write(!ativacao);
				wait(IL);
				break;

			case 2:
				// Realiza a mudanca de estado
				ativacao.write(!ativacao);
				wait(IC);
				break;

			case 3:
				// Realiza a mudanca de estado
				ativacao.write(!ativacao);
				wait(IL);
				break;

			default:
				break;
		}
	}
}

void controlador::atualiza_estado(){
	cout << "MERDA";
	// Apos o temporizador contar o tempo o estado eh mudado
	estado.write(proximo_estado);
}

// Implementacao com 2 metodos
#if NUM_SC_METHODS == 2

void controlador::logica_saida_e_proximo_estado(){
	switch (estado){
		case 0:
			// Saidas
			semaforo_autoestrada.write(2);
			semaforo_via.write(1);

			// Proximo Estado
			// Se tem carro na via, vai para S1
			// Senao continua em S0
			if(sensor_via)
				proximo_estado.write(1);
			else
				proximo_estado.write(0);

			break;

		case 1:
			// Saidas
			semaforo_autoestrada.write(0);
			semaforo_via.write(1);

			// Proximo Estado
			proximo_estado.write(2);
			break;

		case 2:
			// Saidas
			semaforo_autoestrada.write(1);
			semaforo_via.write(2);

			// Proximo Estado
			proximo_estado.write(3);
			break;

		case 3:
			// Saidas
			semaforo_autoestrada.write(1);
			semaforo_via.write(0);

			// Proximo Estado
			proximo_estado.write(0);
			break;

		default:
			// Saidas
			semaforo_autoestrada.write(0);
			semaforo_via.write(0);

			// Proximo Estado
			proximo_estado.write(0);
			break;
	}
}

// Implementacao com 3 metodos
#elif NUM_SC_METHODS == 3

void controlador::logica_saida(){
	switch (estado){
		case 0:
			semaforo_autoestrada.write(2);
			semaforo_via.write(1);
			break;

		case 1:
			semaforo_autoestrada.write(0);
			semaforo_via.write(1);
			break;

		case 2:
			semaforo_autoestrada.write(1);
			semaforo_via.write(2);
			break;

		case 3:
			semaforo_autoestrada.write(1);
			semaforo_via.write(0);
			break;

		default:
			semaforo_autoestrada.write(0);
			semaforo_via.write(0);
			break;
	}
}

void controlador::logica_proximo_estado(){
	switch (estado){
		case 0:
			// Se tem carro na via, vai para S1
			// Senao continua em S0
			if(sensor_via)
				proximo_estado.write(1);
			else
				proximo_estado.write(0);
			break;

		case 1:
			proximo_estado.write(2);
			break;

		case 2:
			proximo_estado.write(3);
			break;

		case 3:
			proximo_estado.write(0);
			break;

		default:
			proximo_estado.write(0);
			break;
	}
}

#endif
