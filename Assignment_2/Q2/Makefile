all: execute_python
execute_python: compile_c run_c
	python3 graph.py
compile_c:
	gcc -o Q2 Ques2.c
run_c:
	./Q2  custom_execution_times.txt
clean:
	rm -f Q2 custom_execution_times.txt