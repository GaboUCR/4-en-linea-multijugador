# Directorio de compilación
BUILD_DIR := build

# Comando CMake
CMAKE := cmake

# Opciones de generador para CMake (puedes cambiarlo según tu preferencia)
GENERATOR := "MinGW Makefiles"

# Objetivo por defecto: construir el proyecto o ejecutar si ya existe
all:
	if not exist "$(BUILD_DIR)" ( \
		$(MAKE) build \
	) else ( \
		$(MAKE) run \
	)

# Generar documentación
doc: 
	cd .. && doxygen Doxyfile
	cd .. && start html/index.html

# Crear el directorio de compilación y ejecutar CMake
configure:
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -G $(GENERATOR) ..

# Compilar el proyecto
build: configure doc
	$(CMAKE) --build $(BUILD_DIR) --target all
	cd $(BUILD_DIR) && windeployqt.exe .

# Ejecutar el programa
run: doc
	cmd.exe /c "cd $(BUILD_DIR) && start CuatroEnLineaCliente.exe"

# Limpiar los archivos de compilación
clean:
	if exist $(BUILD_DIR) rd /S /Q $(BUILD_DIR)

# Marcar objetivos que no son archivos
.PHONY: all configure build run clean

