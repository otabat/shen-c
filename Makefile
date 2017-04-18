SRC_ROOT=src/c
BIN_ROOT=bin
OBJ_ROOT=obj
TEST_SRC_ROOT=test/c
SRCS=$(wildcard ${SRC_ROOT}/*.c)
SRC_OBJS=$(patsubst ${SRC_ROOT}/%.c, obj/%.o, $(SRCS))
TARGET=${BIN_ROOT}/shen-c

$(shell mkdir -p obj bin)

all: ${TARGET} 

${TARGET}: ${SRC_OBJS}
#	cc -g -O0 -std=c99 -fsanitize=address -lgc -o $@ $^
#	cc -g -O0 -std=c99 -Weverything -Wno-padded -Wno-reserved-id-macro -Wno-used-but-marked-unused -fsanitize=address -lgc -o $@ $^
#	cc -O2 -std=c99 -fno-optimize-sibling-calls -lgc -o $@ $^
	cc -O3 -std=c99 -fno-optimize-sibling-calls -lgc -o $@ $^
#	gcc-6 -O2 -std=c99 -fno-optimize-sibling-calls -Wall -L /usr/local/lib -lgc -o $@ $^

${OBJ_ROOT}/%.o: $(SRC_ROOT)/%.c
#	cc -g -O0 -std=c99 -fsanitize=address -fno-omit-frame-pointer -lasan -c -o $@ $<
#	cc -g -O0 -std=c99 -Weverything -Wno-padded -Wno-reserved-id-macro -Wno-used-but-marked-unused -fsanitize=address -fno-omit-frame-pointer -c -o $@ $<
#	cc -O2 -std=c99 -fno-optimize-sibling-calls -c -o $@ $<
	cc -O3 -std=c99 -fno-optimize-sibling-calls -c -o $@ $<
#	gcc-6 -O2 -std=c99 -fno-optimize-sibling-calls -Wall -I /usr/local/include/gc -c -o $@ $<

repl: ${TARGET}
	${TARGET}

clean:
	rm -R obj
	rm -R bin

.PHONY: repl clean
