_GUI = $(if $(NOGUI),,-D GUI)
CC = gcc
CFLAGS = -g -std=c99 -Wall -I ./include $(_GUI)
LDFLAGS = -lm -lSDL

.PHONY: clean doc

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

check-syntax: disc.o snow.o

read-file: read-file.o
	$(CC) $(CFLAGS) -o $@ $^

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o $@ $^

snow: disc.o snow.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	- rm -f *.o *.csv fact.txt read-file write-fact snow





doc: conf/doxygen.conf
	doxygen $<
	firefox doc/html/index.html




check-syntax-particle: particle.o event.o heap.o write-init.o read-init.o disc.o simulation.o clash-of-particles.o

particle: particle.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./particle
	
test-particle: particle.o test-particle.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./test-particle

event: particle.o event.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./event

heap: particle.o event.o heap.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./heap
	
test-heap-correctness: particle.o event.o heap.o write-init.o read-init.o simulation.o disc.o test-heap-correctness.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./test-heap-correctness

test-heap-complexity: particle.o event.o heap.o write-init.o read-init.o simulation.o disc.o test-heap-complexity.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./test-heap-complexity

write-init: particle.o event.o heap.o write-init.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./write-init

read-init: particle.o event.o heap.o read-init.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./read-init

simulation: particle.o event.o heap.o write-init.o read-init.o disc.o simulation.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./simulation
	
clash-of-particles: particle.o event.o heap.o write-init.o read-init.o disc.o simulation.o clash-of-particles.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./clash-of-particles

valgrind-clash: particle.o event.o heap.o write-init.o read-init.o disc.o simulation.o clash-of-particles.o
	 NOGUI=1 valgrind --leak-check=full $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./clash-of-particles
