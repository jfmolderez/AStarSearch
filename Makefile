all : main
main : main.cpp
	g++ -std=c++17 -o main main.cpp
clean: 
	rm -f main