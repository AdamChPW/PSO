.SILENT:
	start
	comp
	test
	gen_map

gen_map: gen_map/*.c
	cc -Wall -Wextra --pedantic gen_map/*.c -o bin/gen

gen:	gen_map
	bin/gen Test/mapa 7 7

comp: src/*.c
	gcc -Wall -Wextra --pedantic src/*.c -o bin/pso -lm

start:	comp
	bin/pso Test/mapa -c Test/config -p 5 -i 100 -n 5

test:	comp gen_map/*.c
	bin/gen Test/mapa_100x100 100 100
	bin/pso Test/mapa_100x100 -c Test/config -p 30 -i 100 -n 10 -d
	