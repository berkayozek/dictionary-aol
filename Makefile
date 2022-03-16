TARGET = Task2 Task3 Task4 Task5 Task6

all: $(TARGET)

$(TARGET):
	gcc $@.c -o $@ -pthread

clean:
	rm -f $(TARGET)
