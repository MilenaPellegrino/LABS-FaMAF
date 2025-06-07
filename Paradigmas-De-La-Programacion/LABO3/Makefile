MAIN_CLASS=FeedReaderMain

# Comment this line to run with default java
JAVA_PATH=/usr/lib/jvm/java-11-openjdk-amd64/bin/
JAVAC=javac
JAVA=java
LIB_DIR=lib
BUILD_DIR=build

# Directory where spark is installed
SPARK_FOLDER=/usr/local/spark-3.5.1-bin-hadoop3

# Extra libraries to include, replace with your own .jars
CLASSPATH=$(OUT_DIR):$(LIB_DIR)/json-20231013.jar:$(SPARK_FOLDER)/jars/*

SOURCES=$(shell find src -name "*.java")

all: build

build:
	mkdir -p $(BUILD_DIR)
	$(JAVA_PATH)$(JAVAC) -cp "$(CLASSPATH)" -d $(BUILD_DIR) $(SOURCES)

run:
	$(JAVA_PATH)$(JAVA) -cp "$(CLASSPATH):$(BUILD_DIR)" FeedReaderMain

run_entity:
	$(JAVA_PATH)$(JAVA) -cp "$(CLASSPATH):$(BUILD_DIR)" FeedReaderMain "-ne"


clean:
	rm -rf $(OUT_DIR) $(BUILD_DIR)
