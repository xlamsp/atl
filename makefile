UNITY_HOME_DIR = unity

OBJS_DIR = objs

#Helper Functions
get_src_from_dir = $(wildcard $1/*.c)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
src_to = $(addprefix $(OBJS_DIR)/,$(subst .c,$1,$2))
src_to_o = $(call src_to,.o,$1)

UNITY_SRC = $(call get_src_from_dir_list, $(UNITY_HOME_DIR))
UNITY_OBJS = $(call src_to_o,$(UNITY_SRC))

.PHONY: all
all: $(UNITY_OBJS)

$(OBJS_DIR)/%.o: %.c
	@echo Compiling $(notdir $<)
	mkdir -p $(dir $@)
	$(COMPILE.c) -MMD -MP  $(OUTPUT_OPTION) $<

.PHONY: clean
clean:
	rm -rf $(OBJS_DIR)