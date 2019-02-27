# Top level folders
OBJS_DIR = objs
UNITY_HOME_DIR = unity
MOCKS_HOME_DIR = mocks
TESTS_HOME_DIR = tests
PROD_HOME_DIR = src

# Helper Functions
get_src_from_dir = $(wildcard $1/*.c)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
get_dirs_from_dirspec = $(wildcard $1)
src_to = $(addprefix $(OBJS_DIR)/,$(subst .c,$1,$2))
src_to_o = $(call src_to,.o,$1)

# Unity
UNITY_SRC = $(call get_src_from_dir_list, $(UNITY_HOME_DIR))
UNITY_OBJS = $(call src_to_o,$(UNITY_SRC))

# Mocks
MOCKS_SRC_COMMON = $(MOCKS_HOME_DIR)/mocks.c
MOCKS_SRC_ARDUINO = $(MOCKS_HOME_DIR)/mocks_arduino.c
MOCKS_SRC_SHREG_DRIVER = $(MOCKS_HOME_DIR)/mocks_shreg_driver.c
MOCKS_SRC = \
	$(MOCKS_SRC_COMMON) \
	$(MOCKS_SRC_ARDUINO) \
	$(MOCKS_SRC_SHREG_DRIVER)

# Test Mocks
TEST_MOCKS_DIR = $(TESTS_HOME_DIR)/test_mocks
TEST_MOCKS_SRC = \
	$(call get_src_from_dir_list, $(TEST_MOCKS_DIR)) \
	$(MOCKS_SRC)
TEST_MOCKS_OBJS = \
	$(call src_to_o, $(TEST_MOCKS_SRC)) \
	$(UNITY_OBJS)
TEST_MOCKS_OUT = $(OBJS_DIR)/$(TEST_MOCKS_DIR).out

# Shift Registers Driver
SHREG_DRIVER_SRC = $(PROD_HOME_DIR)/shreg_driver.c

# Test Shift Registers Driver
TEST_SHREG_DRIVER_DIR = $(TESTS_HOME_DIR)/test_shreg_driver
TEST_SHREG_DRIVER_SRC = \
	$(call get_src_from_dir_list, $(TEST_SHREG_DRIVER_DIR)) \
	$(SHREG_DRIVER_SRC) \
	$(MOCKS_SRC_COMMON) \
	$(MOCKS_SRC_ARDUINO)
TEST_SHREG_DRIVER_OBJS = \
	$(call src_to_o,$(TEST_SHREG_DRIVER_SRC)) \
	$(UNITY_OBJS)
TEST_SHREG_DRIVER_OUT = $(OBJS_DIR)/$(TEST_SHREG_DRIVER_DIR).out

# Test Lights Manager
TEST_LIGHTS_MANAGER_DIR = $(TESTS_HOME_DIR)/test_lights_manager
TEST_LIGHTS_MANAGER_SRC = \
	$(call get_src_from_dir_list, $(TEST_LIGHTS_MANAGER_DIR))
TEST_LIGHTS_MANAGER_OBJS = \
	$(call src_to_o,$(TEST_LIGHTS_MANAGER_SRC)) \
	$(UNITY_OBJS)
TEST_LIGHTS_MANAGER_OUT = $(OBJS_DIR)/$(TEST_LIGHTS_MANAGER_DIR).out

# Include
TEST_INCLUDE_DIRS = $(UNITY_HOME_DIR) $(MOCKS_HOME_DIR) $(PROD_HOME_DIR)
TEST_INCLUDE_DIRS_EXPANDED = $(call get_dirs_from_dirspec, $(TEST_INCLUDE_DIRS))
TEST_INCLUDES += $(foreach dir, $(TEST_INCLUDE_DIRS_EXPANDED), -I$(dir))

# Compiler flags
CFLAGS += -Wall -Wshadow -Wswitch-default

# Targets
.PHONY: all
all: $(TEST_MOCKS_OUT) $(TEST_SHREG_DRIVER_OUT) $(TEST_LIGHTS_MANAGER_OUT)

.PHONY: test_mocks
test_mocks: $(TEST_MOCKS_OUT)
	./$(TEST_MOCKS_OUT)

.PHONY: test_shreg_driver
test_shreg_driver: $(TEST_SHREG_DRIVER_OUT)
	./$(TEST_SHREG_DRIVER_OUT)

.PHONY: test_lights_manager
test_lights_manager: $(TEST_LIGHTS_MANAGER_OUT)
	./$(TEST_LIGHTS_MANAGER_OUT)

# Recipes
$(TEST_MOCKS_OUT): $(TEST_MOCKS_OBJS)
	@echo Linking $@
	$(LINK.o) -o $@ $^

$(TEST_SHREG_DRIVER_OUT): \
	$(TEST_SHREG_DRIVER_OBJS)
	@echo Linking $@
	$(LINK.o) -o $@ $^

$(TEST_LIGHTS_MANAGER_OUT): \
	$(TEST_LIGHTS_MANAGER_OBJS)
	@echo Linking $@
	$(LINK.o) -o $@ $^

$(OBJS_DIR)/%.o: %.c
	@echo Compiling $(notdir $<)
	mkdir -p $(dir $@)
	$(COMPILE.c) -MMD -MP $(OUTPUT_OPTION) $(TEST_INCLUDES) $<

# Cleanup
.PHONY: clean
clean:
	rm -rf $(OBJS_DIR)

