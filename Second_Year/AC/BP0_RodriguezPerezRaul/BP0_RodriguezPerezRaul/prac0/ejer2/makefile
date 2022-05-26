###############################################################################

.ONESHELL:

###############################################################################

EXE = $(filter-out suma,$(basename $(SRC)))
LOG = $(filter-out suma.log,$(SUM:.cc=.log))
SRC = $(wildcard *.c *.cc)
SUM = $(wildcard suma*.cc)
SVG = $(SUM:.cc=.svg)

###############################################################################

  CFLAGS = -fopenmp -O3 -Wall
CXXFLAGS = $(CFLAGS)

###############################################################################

all: $(EXE)

clean:
	-rm -frv $(EJE) $(EXE) $(LOG) $(SVG) core* slurm-*.out *~

exe: $(EXE)

log: $(LOG)

svg: $(SVG)

###############################################################################

PLOT = set terminal svg enhanced; \
       set output '$@'; \
       set grid; \
       set xlabel 'size (double)'; \
       set ylabel 'time'; \
       set key bottom; \
       set logscale x 2; \
       set logscale y 10; \
       set xtics rotate; \
       set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1K' 1024, '2K' 2048, '4K' 4096, '8K' 8192, '16K' 16384, '32K' 32768, '64K' 65526, '128K' 131072, '256K' 262144, '512K' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864, '128M' 134217728, '256M' 268435456, '512M' 536870912); \
       set ytics ('1ns' 1, '10ns' 10, '100ns' 100, '1us' 1e3, '10us' 1e4, '100us' 1e5, '1ms' 1e6, '10ms' 1e7, '100ms' 1e8, '1s' 1e9, '10s' 1e10, '100s' 1e11)

suma-data : CFLAGS += -DDATA
suma-heap : CFLAGS += -DHEAP
suma-stack: CFLAGS += -DSTACK

%.log: %
	ulimit -s unlimited
	echo creando $@...
	for (( i=65536; i<=67108864; i*=2 )); do
		while [ "$$(squeue -h -j $$job)" ]; do sleep 1; done
		job=$$(sbatch -p ac -n1 --cpus-per-task=12 --hint=nomultithread --wrap "./$< $$i" | cut -d' ' -f4)
		while [ "$$(squeue -h -j $$job)" ]; do sleep 1; done
		echo -n "$$i "
		cat slurm-$$job.out
		rm -f slurm-$$job.out
	done | tee $@

%.svg: %.log
	gnuplot <<< "$(PLOT); plot '$<' u 1:2 w lp lc 1 pt 5"

suma.svg: $(LOG)
	gnuplot <<< "$(PLOT); plot 'suma-data.log' u 1:2 w lp lc 1 pt 5 title 'data', 'suma-heap.log' u 1:2 w lp lc 2 pt 7 title 'heap', 'suma-stack.log' u 1:2 w lp lc 3 pt 9 title 'stack'"

###############################################################################

.PHONY: all clean $(EJE) exe hostname log ssh svg
.PRECIOUS: $(LOG) $(SVG)

