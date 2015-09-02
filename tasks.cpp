#include "tasks.h"
#include <stdlib.h>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params){
	int n = params[0];
	int bmin = params[1];
	int bmax = params[2];
	// Valor para hacer modulo sobre la salida de rand() 
	// teniendo en cuenta el offset por 1
	int cant = bmax - bmin + 1; //el offset tiene que ser esta cantidad
	int cant_ciclos;
	srand(1);
	for (int i=0; i < n; i++){
		cant_ciclos = bmin + (rand() % cant);
		uso_IO(pid, cant_ciclos);
	}
}

void TaskBatch(int pid, vector<int> params){ //params: total_cpu y cant_bloqueos
	int total_cpu = params[0];
	int cant_bloqueos = params[1];

	//genero valores en donde ocurriran los bloqueos [0, total_cpu-1]
	vector<bool> momentos(total_cpu);
	int contador = 0;
	while(contador < cant_bloqueos){
		int aux = rand() % total_cpu;
		if(!momentos[aux]){
			momentos[aux] = true;
			contador++;
		}
	}

	for(int i = 0; i < total_cpu; i++){
		if(momentos[i]){
			uso_IO(pid, 1);
		}else{
			uso_CPU(pid, 1);
		}
	}
}

void Task7(int pid, vector<int> params){
	if (pid == 0){
		uso_CPU(pid, 8	);
		uso_IO(pid, 1);
		uso_CPU(pid, 10);
		
		//~ uso_IO(pid, 5);
		uso_CPU(pid, 10);
	//~ 
		uso_IO(pid, 5);
		//~ uso_CPU(pid, 8);
		
		//~ uso_IO(pid, 8);
		uso_CPU(pid, 30);
		
	}else{
		uso_CPU(pid, 42);
		//~ uso_IO(pid, 3);
		//~ uso_CPU(pid, 10);
		//~ uso_IO(pid, 5); 
		//~ uso_CPU(pid, 20);		
		}
}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
	register_task(Task7, -1);
}

