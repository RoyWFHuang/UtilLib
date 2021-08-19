ifeq ($(UTIL_LIB_NAME),)
	UTIL_LIB_NAME = libmethod.a
endif

LIB_METHOD = src/lib_method.c src/xor_list.c
UTIL_LIB_FILE = $(LIB_METHOD)


INCLUDE_DIR = \
-I./inc \
-I./h

XOR_LSIT_TEST = xor_list_test.c

all:
	$(CC) -c $(UTIL_LIB_FILE) $(CFLAG) $(INCLUDE_DIR)
	ar -r $(UTIL_LIB_NAME) *.o
	mv $(UTIL_LIB_NAME) ./lib/
	rm -rf *.o

xor_test: all
	@echo "============================"
	@$(CC) $(XOR_LSIT_TEST) $(INCLUDE_DIR) -lmethod -L./lib/ -o xor_test
	@./xor_test
	@rm xor_test
debug:
	$(CC) -c $(UTIL_LIB_FILE) $(CFLAG) $(INCLUDE_DIR) $(DEBUG_FLAG)
	ar -r ./lib/$(UTIL_LIB_NAME) *.o
	rm -rf *.o

clean:
	rm -rf *.o $(UTIL_LIB_NAME)

distclean: clean

