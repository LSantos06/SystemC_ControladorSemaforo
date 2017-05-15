#include "controlador.h"

SC_MODULE ( driver ) {
	// Saidas do driver sao as entradas do Controlador
	sc_out  < bool > clk, sensor_via;

	// Descricao do funcionamento do Driver
	void drive();

	SC_CTOR ( driver ) {
		SC_THREAD (drive);
	}
};

SC_MODULE ( monitor ) {
	// Entradas do monitor sao as saidas do Controlador
	sc_in < uint8_t > semaforo_autoestrada;
	sc_in < uint8_t > semaforo_via;
	sc_in < uint8_t > estado, proximo_estado;

	// Descricao do funcionamento do Monitor
	void monitora();

	SC_CTOR ( monitor ) {
		SC_METHOD (monitora);
		sensitive << semaforo_autoestrada << semaforo_via;
	}

};

SC_MODULE ( controlador_tb ) {
	// Instanciacao do driver e do monitor
	driver *driver_controlador;
	monitor *monitor_controlador;

	SC_CTOR ( controlador_tb ) {
		driver_controlador = new driver("driver_controlador");
		monitor_controlador = new monitor("monitor_controlador");
	}
};
