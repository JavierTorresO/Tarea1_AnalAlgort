CXX = g++
CXXFLAGS = -std=c++17 -O0 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
EXP_DIR = experiments
BUILD_DIR = build

COMMON_SRCS = $(SRC_DIR)/algoritmos/clasico.cpp \
              $(SRC_DIR)/algoritmos/strassen.cpp \
              $(SRC_DIR)/algoritmos/hibrido.cpp \
              $(SRC_DIR)/utils/matrix.cpp \
              $(SRC_DIR)/utils/generadores.cpp

TARGETS = $(BUILD_DIR)/exp_reales \
          $(BUILD_DIR)/exp_hibrido \
          $(BUILD_DIR)/exp_enteras \
          $(BUILD_DIR)/exp_dispersas \
          $(BUILD_DIR)/exp_estructuradas

all: dir_build $(TARGETS)

dir_build:
	mkdir -p $(BUILD_DIR)

# Reglas individuales para cada experimento
$(BUILD_DIR)/exp_reales: $(EXP_DIR)/exp_reales.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/exp_hibrido: $(EXP_DIR)/exp_hibrido.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/exp_enteras: $(EXP_DIR)/exp_enteras.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/exp_dispersas: $(EXP_DIR)/exp_dispersas.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/exp_estructuradas: $(EXP_DIR)/exp_estructuradas.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)/*