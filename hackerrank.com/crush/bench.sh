g++ main.cpp -o crush -O2
time for i in {1..50}; do ./crush < input04.txt > /dev/null; done
g++ main.cpp -o crush -g -O2
valgrind --tool=callgrind --dump-instr=yes ./crush < input04.txt
