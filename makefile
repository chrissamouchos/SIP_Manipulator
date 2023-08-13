# paths
INCLUDE_PATH = ./include
SRC_PATH = ./src
OBJS_PATH = ./bin
PROF = gmon.out

INPUT = ./input/res.txt

#Define the compiler
CC = gcc

# Compile options. -I<dir> guides the compiler to look there for "include" files
CFLAGS = -I$(INCLUDE_PATH) -pg

#Define the dependencies
DEP = 	main.c \
		Utils.c

#Create the .o file with the needed functions
OBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(DEP))

#UNLEASH THE FUll POWER OF VALGRIND!!!
FULLVAL = --leak-check=full -v

# The executable programm
EXEC = assessment

build : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

#Run the programm
run: $(EXEC)
	./$(EXEC) -i $(INPUT)

#Determine full valgrind
fvalgrind: $(EXEC)
	valgrind $(FULLVAL) ./$(EXEC) -i $(INPUT)

#Determine simple valgrind
svalgrind: $(EXEC)
	valgrind ./$(EXEC) -i $(INPUT)

#Profile executed code for input1, then show analysis
profiling:
	{ \
	gprof $(EXEC) gmon.out > analysis.txt;\
	cat analysis.txt;\
	rm -f gmon.out;\
	}

#Clean workspace
clean:
	rm -f $(OBJS) $(EXEC) $(PROF)
