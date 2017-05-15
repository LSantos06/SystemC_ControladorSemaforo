#include <systemc.h>

// Pode assumir os valores 2 ou 3, define o numero de SC_METHODs utilizados
#define NUM_SC_METHODS 2

// Intervalos gerados pelo temporizador
// IL, o estado vai durar IL ciclos de clock
#define IL 4
// IC, o estado vai durar IC ciclos de clock
#define IC 2

// Enumeracao das cores dos semaforos
enum cor_t{
	Amarelo, Vermelho, Verde
};

// Enumeracao dos estados
enum estado_t {
	S0, // semaforo_autoestrada = Verde,     semaforo_via = Vermelho, duracao = IL
		   // Se sensor_via = false ao fim de IL, continua em S0
		   // Se sensor_via = true  ao fim de IL, vai para S1

	S1, // semaforo_autoestrada = Amarelo,   semaforo_via = Vermelho, duracao = IC

	S2, // semaforo_autoestrada = Vermelho,  semaforo_via = Verde,    duracao = IL

	S3  // semaforo_autoestrada  = Vermelho, semaforo_via = Amarelo,  duracao = IC

  //S0 ...
};

SC_MODULE ( controlador ){
	// Entradas
	sc_in  < bool > clk, sensor_via;

	// Saidas
	sc_out < uint8_t > semaforo_autoestrada;
	sc_out < uint8_t > semaforo_via;
	sc_out < uint8_t > estado, proximo_estado;

	// Temporizador
	sc_signal < bool > ativacao;
	void temporizador();

	// Metodos que definem o funcionamento do controlador
	void atualiza_estado();

	// Implementacao com 2 metodos
	#if NUM_SC_METHODS == 2

	void logica_saida_e_proximo_estado();

	// Implementacao com 3 metodos
	#elif NUM_SC_METHODS == 3

	void logica_saida();

	void logica_proximo_estado();

	#endif

	SC_CTOR(controlador) {
		SC_CTHREAD(temporizador, clk.pos());

		SC_METHOD(atualiza_estado);
		sensitive << ativacao;

		// Implementacao com 2 metodos
		#if NUM_SC_METHODS == 2

		SC_METHOD(logica_saida_e_proximo_estado);
		sensitive << estado << sensor_via;

		// Implementacao com 3 metodos
		#elif NUM_SC_METHODS == 3

		SC_METHOD(logica_saida);
		sensitive << estado << sensor_via;

		SC_METHOD(logica_proximo_estado);
		sensitive << estado << sensor_via;

		#endif
	}
};
