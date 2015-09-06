export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5 ejercicio6 ejercicio7 ejercicio8

all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h



ejercicio1: simusched
	./simusched ej1/lote1.tsk 1 0 0 SchedFCFS | ./graphsched.py > ej1/lote1.png
	./simusched ej1/lote2.tsk 1 0 0 SchedFCFS | ./graphsched.py > ej1/lote2.png

ejercicio2: simusched
	./simusched ej2/rolando.tsk 1 4 0 SchedFCFS | ./graphsched.py > ej2/uncore.png
	./simusched ej2/rolando.tsk 2 4 0 SchedFCFS | ./graphsched.py > ej2/doscores.png

ejercicio3: simusched
	./simusched ej3/batch.tsk 1 0 0 SchedFCFS | ./graphsched.py > ej3/salida.png
	./simusched ej3/lot.tsk 3 0 0 SchedFCFS | ./graphsched.py > ej3/salida2.png

ejercicio4: simusched 
	./simusched ej4/lote.tsk 2 0 0 SchedRR 3 2 | ./graphsched.py > ej4/test.png

ejercicio5: simusched
	./simusched ej5/ej5.tsk 1 2 0 SchedRR 2 | ./graphsched.py > ej5/ej5RR1202.png
	./simusched ej5/ej5.tsk 1 2 0 SchedRR 10 | ./graphsched.py > ej5/ej5RR12010.png
	./simusched ej5/ej5.tsk 1 2 0 SchedRR 50 | ./graphsched.py > ej5/ej5RR12050.png

ejercicio6: simusched

ejercicio7: simusched
	./simusched ej7/1lote.tsk 1 0 0 SchedMistery 2 3 5 2 0 2 | ./graphsched.py > ej7/taskCpuMistery.png
	./simusched ej7/2lote.tsk 1 0 0 SchedMistery 2 3 5 2 | ./graphsched.py > ej7/todojuntomistery.png

ejercicio8: simusched
	./simusched ej8/lotej8.tsk 3 0 0 SchedRR2 3 3 3 | ./graphsched.py > ej8/rr2.png


clean:
	rm -f $(OBJS) $(MAIN)

new: clean all