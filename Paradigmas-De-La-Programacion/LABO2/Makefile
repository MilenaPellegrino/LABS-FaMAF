
MAIN_CLASS = FeedReaderMain  # Archivo a ejecutar

# Rutas de nuestro proyecto 
SRC_DIR = src
OUT_DIR = out
LIB_DIR = lib
JAR_FILE = $(LIB_DIR)/json-20250517.jar

SOURCES = $(shell find $(SRC_DIR) -name "*.java")
CLASSPATH = $(OUT_DIR):$(JAR_FILE)

.PHONY: all run clean

all: $(SOURCES)
	mkdir -p $(OUT_DIR)
	javac -cp $(JAR_FILE) -d $(OUT_DIR) $(SOURCES)

run: all
	java -cp "$(CLASSPATH)" $(MAIN_CLASS) $(ARGS)

clean:
	rm -rf $(OUT_DIR)/*
	
