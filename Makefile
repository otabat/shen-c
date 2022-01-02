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
CFLAGS=-O3 -fno-optimize-sibling-calls -fsigned-char
LDFLAGS=-lgc

ifeq ($(OS),Windows_NT)
    $(error "Windows is not supported.")
else ifeq ($(shell uname -s),Darwin)
    OS_NAME=macos
    ARCH_NAME=$(shell uname -p)
	ARCHIVE_SUFFIX=.tar.gz
else ifeq ($(shell uname -s),Linux)
    OS_NAME=linux
    ARCH_NAME=$(shell uname -p)
	ARCHIVE_SUFFIX=.tar.gz
else
    $(error "The OS is not supported.")
endif

GIT_VERSION=$(shell git tag -l --contains HEAD)

ifeq ("$(GIT_VERSION)","")
	GIT_VERSION=$(shell git rev-parse --short HEAD)
endif

RELEASE_ROOT=release
RELEASE_ARCHIVE_DIR_NAME=shen-c-${GIT_VERSION}-${OS_NAME}-${ARCH_NAME}
RELEASE_ARCHIVE_DIR=${RELEASE_ROOT}/${RELEASE_ARCHIVE_DIR_NAME}
RELEASE_ARCHIVE_NAME=${RELEASE_ARCHIVE_DIR_NAME}${ARCHIVE_SUFFIX}

all: ${OBJ_ROOT} ${BIN_ROOT} ${TARGET}
${TARGET}: ${SRC_OBJS}
	${CC} ${LDFLAGS} -o $@ $^

${OBJ_ROOT}/%.o: $(SRC_ROOT)/%.c
	${CC} ${CFLAGS} -c -o $@ $<

${OBJ_ROOT}:
	mkdir -p ${OBJ_ROOT}

${BIN_ROOT}:
	mkdir -p ${BIN_ROOT}

repl: all
	${TARGET}

rrepl: all
	rlwrap -n ${TARGET}

gperf: all
	mkdir -p prof
	env CPUPROFILE=${PROFILE} ${TARGET}

gperf_signal: all
	rm ${PROFILE}
	mkdir -p prof
	env CPUPROFILE=${PROFILE} CPUPROFILESIGNAL=12 ${TARGET}

pprof: all
	pprof ${TARGET} ${PROFILE}

pprof_text: all
	pprof ${TARGET} ${PROFILE} --text > ${PROFILE_TEXT}

pprof_signal_text: all
	pprof ${TARGET} ${PROFILE_SIGNAL} --text > ${PROFILE_SIGNAL_TEXT}

pprof_pdf: all
	pprof ${TARGET} ${PROFILE} --pdf > ${PROFILE_PDF}

clean:
	rm -rf ${OBJ_ROOT}
	rm -rf ${BIN_ROOT}
	rm -rf ${RELEASE_ROOT}

release: clean all
	mkdir -p ${RELEASE_ARCHIVE_DIR}
	cp -r shen ${RELEASE_ARCHIVE_DIR}
	cp -r bin ${RELEASE_ARCHIVE_DIR}
	cp shen-c ${RELEASE_ARCHIVE_DIR}
	cd ${RELEASE_ROOT}; tar -czvf ${RELEASE_ARCHIVE_NAME} ${RELEASE_ARCHIVE_DIR_NAME}
	rm -rf ${RELEASE_ARCHIVE_DIR}

.PHONY: repl rrepl clean pprof pprof_text pprof_signal_text pprof_pdf release
