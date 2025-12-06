# compiler C++ e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# nome final exe
EXECUTABLE = bin/tp3.out

# adicionar novos arquivos
SOURCES = src/main.cpp \
		  src/endereco.cpp \
		  src/indicePalavras.cpp \
		  src/logradouro.cpp \
		  src/consulta.cpp

# gera os nomes dos arquivos de objeto (.o) a partir da lista SOURCES
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

# compila tudo
all: $(EXECUTABLE)

# criar o executável a partir dos arquivos de objeto
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# compilar um arquivo .cpp em um .o
obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# limpar os arquivos compilados
clean:
	rm -rf obj bin

# Phony targets
.PHONY: all clean