INPUT_FILE0=students-27.txt
INPUT_FILE1=students-1000.txt
INPUT_FILE2=students-10000.txt
INPUT_FILE3=students-100000.txt

compile: test

test: test.c type_t.o dlist.o sort.o dlist.c
	gcc -Wall -g type_t.o dlist.o sort.o test.c -o test -lm
type_t.o: type_t.c type_t.h Makefile
	gcc -Wall -g type_t.c -c
dlist.o: dlist.c dlist.h
	gcc -Wall -g dlist.c -c
sort.o: sort.c sort.h Makefile
	#gcc -Wall -g -D_PERF_ sort.c -c
	gcc -Wall -g sort.c -c

run: insertion selection bubble quiick heap merge radix


insertion:
	$(eval V := 0)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V)
	
selection:
	$(eval V := 1)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V)

bubble:
	$(eval V := 2)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V)

quick:
	$(eval V := 3)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V)

heap:
	$(eval V := 4)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V)

merge:
	$(eval V := 5)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V)
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V)

radixLSD:
	$(eval V := 6)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V) 4
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE1)
	@./test $(INPUT_FILE1) $(V) 4
	@echo "\n##\n"
	@echo "INPUT FILE" $(INPUT_FILE2)
	@./test $(INPUT_FILE2) $(V) 4

radixMSD:
	$(eval V := 7)
	@echo "INPUT FILE" $(INPUT_FILE0)
	@./test $(INPUT_FILE0) $(V) 8
	@echo "\n##\n"
	#@echo "INPUT FILE" $(INPUT_FILE1)
	#@./test $(INPUT_FILE1) $(V) 4
	#@echo "\n##\n"
	#@echo "INPUT FILE" $(INPUT_FILE2)
	#@./test $(INPUT_FILE2) $(V) 4

clean:
	-rm *.o test
