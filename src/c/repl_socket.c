#include "repl_socket.h"

static int max_receive_data_size = 100;
int repl_socket_file_descriptor;

extern int get_repl_socket_file_descriptor (void);
extern void set_repl_socket_file_descriptor (int socket_file_descriptor);
extern void initialize_repl_socket_file_descriptor (int socket_file_descriptor);
extern void initialize_repl_socket_std_input_stream_object (void);
extern void initialize_repl_socket_std_output_stream_object (void);
extern void initialize_repl_socket_std_error_stream_object (void);
extern void initialize_repl_socket_std_stream_objects (void);

static inline void sigchld_handler(int s)
{
	int old_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = old_errno;
}

void start_repl_server (char* host_name, char* port, int max_connection_queue_number)
{
  ADDRESS_INFO socket_info;
  ADDRESS_INFO* head_host_info;

  memset(&socket_info, 0, sizeof(socket_info));
  socket_info.ai_family = AF_INET;
  socket_info.ai_socktype = SOCK_STREAM;
  socket_info.ai_flags = AI_PASSIVE;

  int get_address_info_result =
    getaddrinfo(host_name, port, &socket_info, &head_host_info);

  if (get_address_info_result != 0) {
    fprintf(stderr, "Error in getaddrinfo: %s\n",
            gai_strerror(get_address_info_result));
    exit(EXIT_FAILURE);
  }

  ADDRESS_INFO* host_info = head_host_info;
  int socket_file_descriptor;
  int socket_optiona_value = 1;

  while (is_not_null(host_info)) {
    socket_file_descriptor = socket(host_info->ai_family, host_info->ai_socktype,
                                    host_info->ai_protocol);

    if (socket_file_descriptor == -1) {
      perror("Failed to create a socket: ");
      host_info = host_info->ai_next;

      continue;
    }

    if (setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR,
                   &socket_optiona_value, sizeof(int)) == -1) {
      perror("Error in setsockopt");
      host_info = host_info->ai_next;

      continue;
    }

    if (bind(socket_file_descriptor, host_info->ai_addr,
             host_info->ai_addrlen) == -1) {
      close(socket_file_descriptor);
      perror("Failed to bind: ");
      exit(EXIT_FAILURE);
    }

    break;
  }

  freeaddrinfo(head_host_info);

  if (is_null(host_info)) {
    fprintf(stderr, "Failed to bind");
    exit(EXIT_FAILURE);
  }

  if (listen(socket_file_descriptor, max_connection_queue_number) == -1) {
    perror("Failed to listen: ");
    exit(EXIT_FAILURE);
  }

  SIGNAL_ACTION signal_action;

  signal_action.sa_handler = sigchld_handler;
  sigemptyset(&signal_action.sa_mask);
  signal_action.sa_flags = SA_RESTART;
  printf("Server waiting for client connections\n");

  int new_socket_file_descriptor;
	SOCKET_ADDRESS_STORAGE client_address;
	socklen_t socket_size;
  char buffer[INET_ADDRSTRLEN];

  socket_size = sizeof(client_address);
  new_socket_file_descriptor =
    accept(socket_file_descriptor, (SOCKET_ADDRESS*)&client_address,
           &socket_size);
  
  if (new_socket_file_descriptor == -1)
    perror("Failed to accept client");
  
  SOCKET_ADDRESS* socket_address = (SOCKET_ADDRESS*)&client_address;
  IN_ADDRESS* in_address = &(((SOCKET_ADDRESS_IN*)socket_address)->sin_addr);
  
  inet_ntop(client_address.ss_family, in_address, buffer, INET_ADDRSTRLEN);
  printf("Client connected: %s\n", buffer);
  close(socket_file_descriptor);
  initialize_repl_socket_file_descriptor(new_socket_file_descriptor);
}
