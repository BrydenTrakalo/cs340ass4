assign3bwt562: main.o dfs.o bfs.o best1.o puzzleGame.o
	g++ -o assign3bwt562 main.o dfs.o bfs.o best1.o best2.o best3.o puzzleGame.o

main.o: main.cpp dfs.o bfs.o best1.o puzzleGame.o
	g++ main.cpp -c 

dfs.o: dfs.cpp puzzleGame.o
	g++ dfs.cpp -c

bfs.o: bfs.cpp puzzleGame.o
	g++ bfs.cpp -c

best1.o: best1.cpp puzzleGame.o
	g++ best1.cpp -c

best2.o: best2.cpp puzzleGame.o
	g++ best2.cpp -c

best3.o: best3.cpp puzzleGame.o
	g++ best3.cpp -c

puzzleGame.o: puzzleGame.cpp
	g++ puzzleGame.cpp -c