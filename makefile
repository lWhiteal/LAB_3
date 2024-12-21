# Компилятор
CC = gcc

# Флаги компилятора
CFLAGS = -Wall -Wextra -Werror

# Имя исполняемого файла
TARGET = lab

# Исходные файлы
SRCS = main.c doubly_linked_list.c

# Объектные файлы
OBJS = $(SRCS:.c=.o)

# Зависимости
DEPS = doubly_linked_list.h

# Рецепт по умолчанию
all: $(TARGET)

# Рецепт для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Рецепт для сборки объектных файлов
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Рецепт для очистки
clean:
	rm -f $(OBJS) $(TARGET)

# Рецепт для полной очистки
distclean: clean
	rm -f *~

# Рецепт для удаления всех файлов, созданных make
mrproper: distclean
	rm -f $(DEPS)