CC = clang
CFLAGS = -g
TARGET = main
OBJS = main.o algos.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c algos.h
	$(CC) $(CFLAGS) -c main.c

algos.o: algos.c algos.h
	$(CC) $(CFLAGS) -c algos.c

clean:
	rm -f $(OBJS) $(TARGET)