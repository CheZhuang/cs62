#output: main.cpp class1.cpp class2.cpp
#	g++ main.cpp class1.cpp class2.cpp -o output


# main.o: main.cpp
# 	g++ -c main.cpp -o main.o
# class1.o: class1.cpp
# 	g++ -c class1.cpp -o class1.o
# class2.o: class2.cpp
# 	g++ -c class2.cpp -o class2.o
# clean:
# 	rm *.o output
# output: main.o class1.o class2.o
# 	g++ main.o class1.o class2.o -o output

# output: main.o class1.o class2.o
# 	g++ $^ -o $@
# main.o: main.cpp
# 	g++ -c $< -o $@
# class1.o: class1.cpp
# 	g++ -c $< -o $@
# class2.o: class2.cpp
# 	g++ -c $< -o $@
# clean:
# 	rm *.o output

# output: main.o class1.o class2.o
# 	g++ $^ -o $@
# %.o: %.cpp
# 	g++ -c $< -o $@
# clean:
# 	rm *.o output

COMP=g++
FLAGS=-Wall -std=c++11
output: main.o class1.o class2.o
	$(COMP) $(FLAGS) $^ -o $@
%.o: %.cpp
	$(COMP) $(FLAGS) -c $< -o $@
clean:
	rm *.o output