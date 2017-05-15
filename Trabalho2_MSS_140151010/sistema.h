#include "controlador_tb.h"

SC_MODULE ( sistema ) {
	// Controlador
	controlador controlador_instance;
	// TestBench do Controlador
	controlador_tb controlador_tb_instance;
	// Arquivo de rastreamento
	sc_trace_file* trace_file;

	// "Fios" para conexao
	sc_signal  < bool > clk, sensor_via;
	sc_signal  < uint8_t > semaforo_autoestrada;
	sc_signal  < uint8_t > semaforo_via;
	sc_signal  < uint8_t > estado, proximo_estado;

	// Simulacao em si
	void simular(){
		// Cria arquivo de rastreamento
		trace_file = sc_create_vcd_trace_file("trace_file");

		// Seta a unidade do tempo de simulacao
		trace_file->set_time_unit(0.5, SC_NS);

		// Define sinais a serem rastreados
		sc_trace(trace_file, clk, "clk");
		sc_trace(trace_file, sensor_via, "sensor_via");
		sc_trace(trace_file, semaforo_autoestrada, "semaforo_autoestrada");
		sc_trace(trace_file, semaforo_via, "semaforo_via");
		sc_trace(trace_file, estado, "estado");
		sc_trace(trace_file, proximo_estado, "proximo_estado");

		sc_start();

		// Fecha o arquivo de rastreamento
		sc_close_vcd_trace_file(trace_file);
		cout << "Arquivo de rastreamento trace_file.vcd criado!" << endl;
	}

	SC_CTOR ( sistema ) : controlador_instance("controlador_instance"),
			controlador_tb_instance("controlador_tb_instance") {

		// Entradas do Controlador sao as saidas do Driver
		controlador_instance.clk(clk);
		controlador_tb_instance.driver_controlador->clk(clk);

		controlador_instance.sensor_via(sensor_via);
		controlador_tb_instance.driver_controlador->sensor_via(sensor_via);

		// Saidas do Controlador sao as entradas do Monitor
		controlador_instance.semaforo_autoestrada(semaforo_autoestrada);
		controlador_tb_instance.monitor_controlador->semaforo_autoestrada(semaforo_autoestrada);

		controlador_instance.semaforo_via(semaforo_via);
		controlador_tb_instance.monitor_controlador->semaforo_via(semaforo_via);

		controlador_instance.estado(estado);
		controlador_tb_instance.monitor_controlador->estado(estado);

		controlador_instance.proximo_estado(proximo_estado);
		controlador_tb_instance.monitor_controlador->proximo_estado(proximo_estado);
	}
};
