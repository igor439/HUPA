# Projeto Hospital

Este projeto simula um sistema hospitalar onde você pode gerar dados aleatórios de pacientes, médicos e salas, e exportá-los para arquivos CSV e em Seguida gera um realorio confome especificado no trabalho para a disciplina de EAD II.

## Requisitos

Para rodar este projeto, você precisará de um compilador C++ e ferramentas de build. Abaixo estão as instruções para configurar e executar o código no ambiente Windows com o MinGW.

### Ferramentas necessárias

- [MinGW](http://www.mingw.org/) ou [MSYS2](https://www.msys2.org/) para compilar código C++.
- `mingw32-make` (ou `make` no MSYS2).
- Editor de texto ou IDE para editar e visualizar os arquivos.

## Passos para rodar o código

### 1. Instalando o MinGW

Se você ainda não tem o MinGW instalado, siga as etapas abaixo:

1. **Baixe o MinGW**: 
   - Acesse [MinGW](http://www.mingw.org/).
   - Faça o download e instale o MinGW. Durante a instalação, escolha a opção para adicionar o MinGW ao PATH.

2. **Verifique a instalação**:
   - Abra o prompt de comando (CMD) e digite:
     ```
     g++ --version
     ```
   - Isso deve mostrar a versão do `g++` instalado. Se aparecer um erro, o MinGW pode não estar instalado corretamente.

### 2. Configuração do projeto

1. **Baixe o código fonte**: 
   - Faça o download ou clone o repositório do código em seu computador.

2. **Estrutura do projeto**:
   - O código fonte está localizado na pasta `src`.
   - As dependências de arquivos, como `Paciente.cpp`, `Medico.cpp`, `Sala.cpp`, `Controller.cpp`, etc., estão na pasta `src`.

3. **Abra o terminal (ou CMD) no diretório do projeto**:
   - Navegue até a pasta onde os arquivos de código-fonte estão localizados:
     ```
     cd C:\Users\IgorSoares\Desktop\EAD II\Projeto_Hospital\src
     ```

### 3. Compilando o código

1. **Compile o código**:
   - No terminal, execute o comando para compilar os arquivos C++:
     ```
     g++ -Wall -g main.cpp Paciente.cpp Medico.cpp Especialidade.cpp Sala.cpp Controller.cpp ElementoPaginaFolha.cpp Pagina.cpp ElementoPagina.cpp -o programa
     ```

   - Este comando irá gerar um executável chamado `programa` (ou `programa.exe` no Windows).

### 4. Executando o programa

1. **Execute o programa**:
   - Após a compilação, execute o programa com o comando:
     ```
     ./programa
     ```
   - Ou, no Windows, você pode rodar diretamente:
     ```
     programa.exe
     ```

2. O programa irá gerar os dados e exportá-los para arquivos CSV. Você pode abrir esses arquivos em um editor de texto ou em uma planilha (como Excel) para visualizar os dados gerados.

### 5. Estrutura dos arquivos CSV

- O programa gera dois arquivos CSV:
  1. **Pacientes.csv**: Contém os dados dos pacientes gerados, como nome, idade, sintomas, medicamentos, especialidade e prioridade.
  2. **Medicos.csv**: Contém os dados dos médicos, com seu ID, nome e especialidade.
  3. **Salas.csv**: Contém o número de salas alocadas para cada especialidade.

## Como modificar o código

1. **Gerar mais ou menos pacientes, médicos ou salas**:
   - No código-fonte, altere os parâmetros que definem a quantidade de pacientes, médicos ou salas.
   - Por exemplo, na função `exportarPacientesCSV`, você pode mudar o número de pacientes passando um número diferente como argumento.

2. **Alterar especialidades ou sintomas**:
   - No código, a lista de especialidades e sintomas pode ser alterada conforme necessário, modificando as variáveis `sintomasPorEspecialidade` e `especialidades`.

### 6. Contribuindo

Se desejar contribuir para o projeto, siga as etapas abaixo:

1. Faça um fork do repositório.
2. Crie uma nova branch (`git checkout -b minha-contribuicao`).
3. Faça as modificações necessárias e adicione os arquivos modificados (`git add .`).
4. Faça um commit das suas alterações (`git commit -m "Minha contribuição"`).
5. Envie a branch para o repositório remoto (`git push origin minha-contribuicao`).
6. Abra um pull request para revisão.

## Licença

Este projeto é licenciado sob a MIT License - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

