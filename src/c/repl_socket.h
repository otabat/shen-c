#ifndef SHEN_C_REPL_SOCKET_H
#define SHEN_C_REPL_SOCKET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>

#include "exception.h"
#include "kl.h"
#include "stream.h"

extern int repl_socket_file_descriptor;

typedef struct sockaddr SOCKET_ADDRESS;
typedef struct sockaddr_in SOCKET_ADDRESS_IN;
typedef struct sockaddr_storage SOCKET_ADDRESS_STORAGE;
typedef struct in_addr IN_ADDRESS;
typedef struct addrinfo ADDRESS_INFO;
typedef struct sigaction SIGNAL_ACTION;

void start_repl_server (char* host_name, char* port, int max_connection_queue_number);

inline int get_repl_socket_file_descriptor (void)
{
  return repl_socket_file_descriptor;
}

inline void set_repl_socket_file_descriptor (int socket_file_descriptor)
{
  repl_socket_file_descriptor = socket_file_descriptor;
}

inline void initialize_repl_socket_file_descriptor (int socket_file_descriptor)
{
  set_repl_socket_file_descriptor(socket_file_descriptor);
}

inline void initialize_repl_socket_std_input_stream_object (void)
{
  FILE* file = fdopen(get_repl_socket_file_descriptor(), "r");

  if (is_null(file))
    throw_kl_exception("Failed to open stream of input REPL file descriptor");

  std_input_stream_object = create_std_kl_stream(file, get_in_symbol_object());
}

inline void initialize_repl_socket_std_output_stream_object (void)
{
  FILE* file = fdopen(get_repl_socket_file_descriptor(), "w");

  if (is_null(file))
    throw_kl_exception("Failed to open stream of output REPL file descriptor");

  std_output_stream_object = create_std_kl_stream(file, get_out_symbol_object());
}

inline void initialize_repl_socket_std_error_stream_object (void)
{
  FILE* file = fdopen(get_repl_socket_file_descriptor(), "w");

  if (is_null(file))
    throw_kl_exception("Failed to open stream of error REPL file descriptor");

  std_error_stream_object = create_std_kl_stream(file, get_out_symbol_object());
}

inline void initialize_repl_socket_std_stream_objects (void)
{
  initialize_repl_socket_std_input_stream_object();
  initialize_repl_socket_std_output_stream_object();
  initialize_repl_socket_std_error_stream_object();
}

#endif
