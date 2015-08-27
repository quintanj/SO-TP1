#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	vector<int> quantums(argn[0]);
	for(int i = 0; i < argn[0]; i++){
		quantums[i] = argn[i+1];		//cargamos los quantums
	}
	queue<int> colaReady;
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	this->colaReady.push(pid);			//agregamos el elemento a la cola ready
}

void SchedRR::unblock(int pid) {
	//agregar a la cola
}

int SchedRR::tick(int cpu, const enum Motivo m) {

}
