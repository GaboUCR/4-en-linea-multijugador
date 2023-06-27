CC = g++

SRCS = server.cpp channel.cpp DatabaseManager.cpp -lsqlite3
EXEC = programa

.PHONY: all clean

all: run

compile: $(OBJS)
	$(CC) $(SRCS) $(OBJS) -o $(EXEC) 

run: compile
	./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)
