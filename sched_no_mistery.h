#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <utility>
#include "basesched.h"
#include <iostream>

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);  
    
  private:
  
	std::vector<std::queue<int> > colaReady;		//hay una cola por cada quantum pasado por paŕametro. NOTA: si se pasa solo un paŕametro el vector tiene dos elem
	std::vector<int> quantumPorCola;				//me dice el quantum correspondiente a la cola	
	std::queue<std::pair<int, int> > colaBloqueados;//cola de tuplas con (pid, cola en la que entra cuando hace unblock)
	int quantumRestante;							//es lo que le resta ejecutar a la tarea antes de ser desalojada 
	int colaActual;									//me dice cual es la cola de la cual debo tomar tareas para ejecutar. INICIALIZAR EN 0
	
	
};

#endif


/*los paràmetros pasados al sched mistery son el quantum que les va a asignar a cada tarea.

Primero siempre corren un ciclo de clock cada tarea. luego empeizan a tener el quantum que está pasado por parámetro.

parece que hay una colaReady por parámetro pasado, es decir, cada cola tiene un qunatum asociado.

Al final se sigue ejecutando con el ultimo quantum pasado si es que la tarea no terminó la ejecución. osea queda en la ultima cola hasta que finaliza

cuando llega un tarea nueva en medio de la ejecución, solo corren las nuevas hasta alcanzar el quantum que tienen las tareas que ya venian ejecutando.
la primaras colas tienen priridad de ejecucion

La tarea que se bloquea se encola va a la cola anterior. 
*/
