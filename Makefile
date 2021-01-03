export SHEN_C_HOME=${CURDIR}
SRC_ROOT=src/c
BIN_ROOT=bin
OBJ_ROOT=obj
TEST_SRC_ROOT=test/c
PROFILE_ROOT=prof

SRCS=$(wildcard ${SRC_ROOT}/*.c)
SRC_OBJS=$(patsubst ${SRC_ROOT}/%.c, obj/%.o, $(SRCS))
TARGET=${BIN_ROOT}/shen-c
PROFILE=${PROFILE_ROOT}/shen-c.prof
PROFILE_TEXT=${PROFILE_ROOT}/shen-c.prof.txt
PROFILE_PDF=${PROFILE_ROOT}/shen-c.prof.pdf
PROFILE_SIGNAL=${PROFILE_ROOT}/shen-c.prof.0
PROFILE_SIGNAL_TEXT=${PROFILE_ROOT}/shen-c.prof.0.txt

CC=clang
CFLAGS?=-O3 -fno-optimize-sibling-calls
LDFLAGS=-lgc

SHEN_VERSION=22.3

$(shell mkdir -p obj bin)

all: ${TARGET} shen/src/kl/repl.kl shen/src/kl/init.kl

${TARGET}: ${SRC_OBJS}
	${CC} $(CFLAGS) $(LDFLAGS) -o $@ $^
#	cc -g -O0 -std=c99 -fsanitize=address -lgc -o $@ $^
#	cc -g -O0 -std=c99 -lgc -lprofiler -Wl,-no_pie -o $@ $^
#	cc -g -O0 -std=c99 -lgc -o $@ $^
#	cc -O2 -std=c99 -lgc -o $@ $^
#	cc -g -O3 -std=c99 -lgc -lprofiler -Wl,-no_pie -o $@ $^
#	gcc-6 -g -O3 -std=c99 -L /usr/local/lib -lgc -lprofiler -Wl,-no_pie -o $@ $^
#	gcc-6 -O3 -std=c99 -L /usr/local/lib -lgc -o $@ $^

${OBJ_ROOT}/%.o: $(SRC_ROOT)/%.c
	${CC} $(CFLAGS) -c -o $@ $<
#	cc -g -O0 -std=c99 -Weverything -Wno-static-in-inline -Wno-padded -Wno-reserved-id-macro -Wno-used-but-marked-unused -fsanitize=address -fno-omit-frame-pointer -c -o $@ $<
#	cc -g -O0 -std=c99 -c -o $@ $<
#	cc -O2 -std=c99 -fno-optimize-sibling-calls -c -o $@ $<
#	gcc-6 -g -O3 -std=c99 -fno-optimize-sibling-calls -Wall -I /usr/local/include/gc -c -o $@ $<
#	gcc-6 -O3 -std=c99 -fno-optimize-sibling-calls -Wall -I /usr/local/include/gc -c -o $@ $<

repl: ${TARGET}
	${TARGET}

rrepl: ${TARGET}
	rlwrap -n ${TARGET}

gperf: ${TARGET}
	mkdir -p prof
	env CPUPROFILE=${PROFILE} ${TARGET}

gperf_signal: ${TARGET}
	rm ${PROFILE}
	mkdir -p prof
	env CPUPROFILE=${PROFILE} CPUPROFILESIGNAL=12 ${TARGET}

pprof:
	pprof ${TARGET} ${PROFILE}

pprof_text:
	pprof ${TARGET} ${PROFILE} --text > ${PROFILE_TEXT}

pprof_signal_text:
	pprof ${TARGET} ${PROFILE_SIGNAL} --text > ${PROFILE_SIGNAL_TEXT}

pprof_pdf:
	pprof ${TARGET} ${PROFILE} --pdf > ${PROFILE_PDF}

clean:
	rm -rf obj
	rm -rf bin
	rm -rf shen

shen-dist/ShenOSKernel-$(SHEN_VERSION).tar.gz:
	mkdir -p shen-dist
	(cd shen-dist; wget https://github.com/Shen-Language/shen-sources/releases/download/shen-$(SHEN_VERSION)/ShenOSKernel-$(SHEN_VERSION).tar.gz)
	touch $@

shen/src/kl/repl.kl: shen/src/kl
	echo '(shen.initialise)(set shen.*porters* "Tatsuya Tsuda")(set shen.*language* "C")(set shen.*implementation* "shen-c")' > $@
	echo '(defun shen.x.launcher.done () nil)' >> $@

shen/src/kl: shen-dist/ShenOSKernel-$(SHEN_VERSION).tar.gz
	tar xzf $<
	mkdir -p shen/src/kl
	mkdir -p shen/src/shen
	mkdir -p shen/tests
	mv ShenOSKernel-$(SHEN_VERSION)/klambda/* shen/src/kl/
	mv ShenOSKernel-$(SHEN_VERSION)/sources/* shen/src/shen/
	mv ShenOSKernel-$(SHEN_VERSION)/tests/* shen/tests/
	rm -R ShenOSKernel-$(SHEN_VERSION)

test:
	fail_cnt=0
	pass_cnt=0
	for f in shen/tests/*.shen; do \
		echo -n $$(basename "$$f") " ";  \
	    if ./$(TARGET) script "$$f"; then \
		  ((pass_cnt=pass_cnt+1)); \
		  printf "\033[0;32m✔\033[0m\n"; \
		else \
		  ((fail_cnt=fail_cnt+1)); \
		  printf "\033[1;31mX\033[0m\n"; \
		  fi; done; echo "Passed $${pass_cnt}  Failed: $${fail_cnt}"

.PHONY: repl rrepl clean pprof pprof_text pprof_signal_text pprof_pdf test
