OBJS_DIR = objs
UNITY_HOME_DIR = unity
MOCKS_HOME_DIR = mocks
TESTS_HOME_DIR = tests

TEST_MOCKS = $(TESTS_HOME_DIR)/test_mocks
TEST_MOCKS_OUT = $(OBJS_DIR)/$(TEST_MOCKS).out

TEST_INCLUDE_DIRS = $(UNITY_HOME_DIR) $(MOCKS_HOME_DIR)

#Helper Functions
get_src_from_dir = $(wildcard $1/*.c)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
get_dirs_from_dirspec = $(wildcard $1)
src_to = $(addprefix $(OBJS_DIR)/,$(subst .c,$1,$2))
src_to_o = $(call src_to,.o,$1)

UNITY_SRC = $(call get_src_from_dir_list, $(UNITY_HOME_DIR))
UNITY_OBJS = $(call src_to_o,$(UNITY_SRC))

MOCKS_SRC = $(call get_src_from_dir_list, $(MOCKS_HOME_DIR))
MOCKS_OBJS = $(call src_to_o,$(MOCKS_SRC))

TEST_MOCKS_SRC = $(call get_src_from_dir_list, $(TEST_MOCKS))
TEST_MOCKS_OBJS = $(call src_to_o,$(TEST_MOCKS_SRC))

TEST_INCLUDES_DIRS_EXPANDED = $(call get_dirs_from_dirspec, $(TEST_INCLUDE_DIRS))
TEST_INCLUDES += $(foreach dir, $(TEST_INCLUDES_DIRS_EXPANDED), -I$(dir))

.PHONY: all
all: $(TEST_MOCKS_OUT)

.PHONY: test_mocks
test_mocks: $(TEST_MOCKS_OUT)
	./$(TEST_MOCKS_OUT)

$(TEST_MOCKS_OUT): $(UNITY_OBJS) $(MOCKS_OBJS) $(TEST_MOCKS_OBJS)
	@echo Linking $@
	$(LINK.o) -o $@ $^

$(OBJS_DIR)/%.o: %.c
	@echo Compiling $(notdir $<)
	mkdir -p $(dir $@)
	$(COMPILE.c) -MMD -MP $(OUTPUT_OPTION) $(TEST_INCLUDES) $<

.PHONY: clean
clean:
	rm -rf $(OBJS_DIR)

