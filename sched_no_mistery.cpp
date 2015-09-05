#include <vector>
#include <queue>
#include <utility>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {  
	int cantQuantums = argn.size();
	colaReady.resize(cantQuantums);		//creo el vector de colaReady, una cola por quantum asignado. Siempre el primero es de quantum 1
	quantumPorCola.resize(cantQuantums);	//vector de quantums

	//cargo los valores de los quantums pasados por parámetro
	//al vector quantumPorCola
	for(unsigned int i = 0; i < argn.size(); i++){
			quantumPorCola[i] = (argn[i] == 0)? -1 : argn[i]; //si le pasan parámetro 0 le pongo 1 como quantum a esa cola
		}

	colaActual = 0;			//empieza a ehecutar las tareas de la cola 0
}

void SchedNoMistery::load(int pid) {  
	
	colaReady[0].push(pid);			//cada vez que llega una tarea, llega a la primera cola
}

void SchedNoMistery::unblock(int pid) { 
	int colaNum;
	pair<int, int> pidCola = colaBloqueados.front();	//tomo primera tupla de la cola de (task,cola)
	colaBloqueados.pop();								//la quito de colaBloqueados
	while((pidCola.first) != pid){				//si no coincide el pid sigo en el loop
		colaBloqueados.push(pidCola);			//no es la tarea que busco, la encolo de vuelta
		pidCola = colaBloqueados.front();		//pongo la que sigue
		colaBloqueados.pop();					//la saco de la cola
		}
	//la tarea a desbloquear ya no está en colaBloqueados
	//tengo la tarea y la cola a donde se va a encolar
	colaNum = pidCola.second;		
	colaReady[colaNum].push(pid);		
	//pone la tarea pid en la cola anterior a la que estaba ejecutando cuando se bloqueó
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {  
	int nextPid = IDLE_TASK;
	
		switch (m) {
    	case TICK:{
    	
			int colaSiguiente = colaActual + (((unsigned int)colaActual == colaReady.size() -1)? 0 : 1);
		//si estoy en la ultima cola, la cola siguiente va a ser la misma
     	//Si la tarea era IDLE_TASK y no hay ninguna tarea en la cola, sigue ejecutando IDLE_TASK 
    		if (current_pid(cpu) == IDLE_TASK){
				
		//busco la colaReady que tenga una tarea, el orden de prioridad es de la primera a la ultima
				for(unsigned int i = 0; i < colaReady.size(); i++){
				
					if (!colaReady[i].empty()){
						quantumRestante = quantumPorCola[i];	//le asigno la cantidad correcta de quantum
						nextPid = colaReady[i].front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
						colaReady[i].pop();						//y se quita de la cola
						colaActual = i;						
						break;
					}else{
						if ((unsigned int) i == colaReady.size() -1) nextPid = IDLE_TASK;		//si no hay tareas en ninguna cola sigue IDLE_TASK
						}
				}
    		}else{
			//no era la IDLE_TASK, se resta uno al quantum restante
				if(quantumRestante < 0) nextPid = current_pid(cpu);		//me llegó un parámetro con quantum 0, sigue esa tarea hasta que temrina
       			quantumRestante--;
       			if (quantumRestante == 0){
				//se quedó sin tiempo
				//pongo la tarea actual en la cola siguiente. (si era la ultima cola se queda ahí)
       				colaReady[colaSiguiente].push(current_pid(cpu));	
				//busco la colaReady que tenga una tarea, el orden de prioridad es de la primera a la ultima
					for(unsigned int i = 0; i < colaReady.size(); i++){
					
						if (!colaReady[i].empty()){
							quantumRestante = quantumPorCola[i];	//le asigno la cantidad correcta de quantum
							nextPid = colaReady[i].front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
							colaReady[i].pop();						//y se quita de la cola
							colaActual = i;
							break;
						}
					}
       			}else{
       				//le queda tiempo, sigue ejecutando la misma
       				nextPid = current_pid(cpu);
       			}
       		}
       		
       		break;
       	}
       	case BLOCK:{
				
			int colaAnterior = colaActual - ((colaActual == 0)? 0 : 1);
		//si el proceso que se bloqueó estaba en la primera cola, sigue en esa cola
		
			pair<int, int> blockedTask (current_pid(cpu), colaAnterior); 
		//armo la tupla, (tarea bloqueada, cola a la que se va a agregar cuando se desbloquee)
			colaBloqueados.push(blockedTask);
		//pongo la tarea en la cola tareas bloqueadas. 
		//ahora busco la siguiente tarea a ejecutar
			for(unsigned int i = 0; i < colaReady.size(); i++){
					
						if (!colaReady[i].empty()){
							quantumRestante = quantumPorCola[i];	//le asigno la cantidad correcta de quantum
							nextPid = colaReady[i].front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
							colaReady[i].pop();						//y se quita de la cola
							colaActual = i;						
							break;
						}else{
							if ((unsigned int)i == colaReady.size() - 1) nextPid = IDLE_TASK;		//si no hay tareas en ninguna cola sigue IDLE_TASK
							}
					}
			break;
		}
		case EXIT:
		
			for(unsigned int i = 0; i < colaReady.size(); i++){
					
						if (!colaReady[i].empty()){
							quantumRestante = quantumPorCola[i];	//le asigno la cantidad correcta de quantum
							nextPid = colaReady[i].front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
							colaReady[i].pop();						//y se quita de la cola
							colaActual = i;						
							break;
						}else{
							if ((unsigned int)i == colaReady.size() - 1) nextPid = IDLE_TASK;		//si no hay tareas en ninguna cola sigue IDLE_TASK
							}
					}
			break;
			
	
	}
	return nextPid;
}

	
