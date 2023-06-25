# Directorio de compilación
BUILD_DIR := build

# Comando CMake
CMAKE := cmake

# Opciones de generador para CMake (puedes cambiarlo según tu preferencia)
GENERATOR := "MinGW Makefiles"
BUILD_DIR := build
# Objetivo por defecto: construir el proyecto
all: build doc

doc: 
	cd .. && doxygen Doxyfile
	cd .. && start html/index.html

# Crear el directorio de compilación y ejecutar CMake
configure:
	mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -G $(GENERATOR) ..

# Compilar el proyecto
build: configure
	$(CMAKE) --build $(BUILD_DIR) --target all

	cd $(BUILD_DIR) && windeployqt.exe .
	start cmd /c "cd $(BUILD_DIR) && CuatroEnLineaCliente.exe"
	start cmd /c "cd $(BUILD_DIR) && CuatroEnLineaCliente.exe"

# Limpiar los archivos de compilación
clean:
	rm -rf $(BUILD_DIR)

# Marcar objetivos que no son archivos
.PHONY: all configure build clean
