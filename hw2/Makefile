main: main.o network.o user.o
	g++ main.o network.o user.o -o main

main.o: main.cpp user.h network.h
	g++ -c main.cpp

network.o: network.cpp network.h user.h
	g++ -c network.cpp

user.o: user.cpp user.h
	g++ -c user.cpp

clean:
	rm -f main.o network.o user.o main