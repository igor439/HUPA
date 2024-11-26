# Define o compilador
CXX = g++

# Define os arquivos-fonte
SRC = main.cpp Paciente.cpp Medico.cpp Especialidade.cpp Sala.cpp Controller.cpp ElementoPaginaFolha.cpp Pagina.cpp ElementoPagina.cpp

# Define o nome do programa
TARGET = programa

# Define as opções de compilação
CXXFLAGS = -Wall -g -std=c++17

# Regra padrão para compilar o programa
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Regra para limpar arquivos compilados
clean:
	del /Q $(TARGET).exe
