social_network: social_network.o network.o user.o post.o
	g++ social_network.o network.o user.o post.o -o social_network

social_network.o: social_network.cpp network.h user.h
	g++ -c social_network.cpp

network.o: network.cpp network.h user.h
	g++ -c network.cpp

user.o: user.cpp user.h
	g++ -c user.cpp

post.o: post.cpp post.h
	g++ -c post.cpp

clean:
	rm -f social_network *.o