# Компилятор и флаги
COMPILER = g++
CXXFLAGS = -I./src -I./crossPlatform -I./src/menu -I./crossPlatform/menu
LDFLAGS = -L./crossPlatform/so
LDLIBS = -l:affine.so -l:keygen.so -l:pleyfair.so -l:mathFunctions.so
RPATH = -Wl,-rpath,'$$ORIGIN/crossPlatform/so'

# Целевой исполняемый файл 
TARGET = CryptoSib

# Исходные файлы 
SOURCES = main.cpp \
         $(shell find src/menu -name '*.cpp') \
          $(shell find crossPlatform/menu -name '*.cpp')

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(SOURCES)
	$(COMPILER) $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $(RPATH) -o $@

# Чистка
clean:
	rm -f $(TARGET) *.o
	rm -f src/menu/*.o
	rm -f src/menu/chipers/*.o
	rm -f crossPlatform/menu/*.o
	rm -f crossPlatform/menu/crossChipers/*.o

# Полная чистка
distclean: clean

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Пересобрать и запустить
rerun: clean $(TARGET) run

# Отображение помощи
help:
	@echo "Доступные цели:"
	@echo "  make          - собрать $(TARGET)"
	@echo "  make clean    - удалить $(TARGET) и объектные файлы"
	@echo "  make run      - собрать и запустить"
	@echo "  make rerun    - пересобрать и запустить"
	@echo "  make help     - показать эту справку"

.PHONY: all clean distclean run rerun help