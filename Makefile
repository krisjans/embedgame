PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

BUILD = $(PROJECT_ROOT)/build

TARGET = $(BUILD)/embedgame

OBJS = $(BUILD)/embedgame.o $(BUILD)/platform_helpers.o

BUILD_MODE ?= debug

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else
	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

CFLAGS += -std=gnu++11

all:	$(TARGET)

$(TARGET):	$(BUILD) $(OBJS)
	$(CXX) -o $@ $(filter-out $<,$^)

$(BUILD)/%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

$(BUILD)/%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -fr $(TARGET) $(OBJS)
	rm -rf $(BUILD)
