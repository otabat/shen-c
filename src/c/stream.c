#include "stream.h"

static size_t read_buffer_allocation_size = 100;
static char* read_buffer;
static size_t read_buffer_position = 0;
static KLObject* std_input_stream_object;
static KLObject* std_output_stream_object;
static KLObject* std_error_stream_object;

FILE* get_stream_file (Stream* stream)
{
  return stream->file;
}

void set_stream_file (Stream* stream, FILE* file)
{
  stream->file = file;
}

KLStreamType get_stream_stream_type (Stream* stream)
{
  return stream->stream_type;
}

void set_stream_stream_type (Stream* stream, KLStreamType stream_type)
{
  stream->stream_type = stream_type;
}

Stream* create_stream (FILE* file, KLStreamType stream_type)
{
  Stream* stream = malloc(sizeof(Stream));

  set_stream_file(stream, file);
  set_stream_stream_type(stream, stream_type);

  return stream;
}

char* stream_type_string_to_open_mode_string (char* stream_type_string)
{
  if (strcmp(stream_type_string, "in") == 0)
    return "r";

  if (strcmp(stream_type_string, "out") == 0)
    return "w";

  throw_kl_exception("Unknown stream type");

  return NULL;
}

KLStreamType stream_type_string_to_stream_type (char* stream_type_string)
{
  if (strcmp(stream_type_string, "in") == 0)
    return KL_STREAM_TYPE_IN;

  if (strcmp(stream_type_string, "out") == 0)
    return KL_STREAM_TYPE_OUT;

  throw_kl_exception("Unknown stream type");

  return 0;
}

char* stream_type_to_stream_type_string (KLStreamType stream_type)
{
  if (stream_type == KL_STREAM_TYPE_IN)
    return "in";

  if (stream_type == KL_STREAM_TYPE_OUT)
    return "out";

  throw_kl_exception("Unknown stream type");

  return NULL;
}

KLObject* get_std_input_stream_object (void)
{
  return std_input_stream_object;
}

KLObject* get_std_output_stream_object (void)
{
  return std_output_stream_object;
}

KLObject* get_std_error_stream_object (void)
{
  return std_error_stream_object;
}

KLObject* create_std_kl_stream (FILE* file, char* stream_type_string)
{
  KLStreamType stream_type = stream_type_string_to_stream_type(stream_type_string);
  KLObject* stream_object = create_kl_object(KL_TYPE_STREAM);
  Stream* stream = create_stream(file, stream_type);

  set_stream(stream_object, stream);

  return stream_object;
}

static inline void initialize_std_input_stream_object (void)
{
  std_input_stream_object = create_std_kl_stream(stdin, "in");
}

static inline void initialize_std_output_stream_object (void)
{
  std_output_stream_object = create_std_kl_stream(stdout, "out");
}

static inline void initialize_std_error_stream_object (void)
{
  std_error_stream_object = create_std_kl_stream(stderr, "out");
}

void initialize_std_stream_objects (void)
{
  initialize_std_input_stream_object();
  initialize_std_output_stream_object();
  initialize_std_error_stream_object();
}

Stream* get_stream (KLObject* stream_object)
{
  return stream_object->value.stream;
}

void set_stream (KLObject* stream_object, Stream* stream)
{
  stream_object->value.stream = stream;
}

KLObject* create_kl_stream (char* file_path, char* stream_type_string)
{
  char* open_mode_string =
    stream_type_string_to_open_mode_string(stream_type_string);
  FILE* file = fopen(file_path, open_mode_string);

  if (is_null(file))
    throw_kl_exception("Failed to open stream");

  KLStreamType stream_type =
    stream_type_string_to_stream_type(stream_type_string);
  KLObject* stream_object = create_kl_object(KL_TYPE_STREAM);
  Stream* stream = create_stream(file, stream_type);

  set_stream(stream_object, stream);

  return stream_object;
}

FILE* get_kl_stream_file (KLObject* stream_object)
{
  return get_stream_file(get_stream(stream_object));
}

void set_kl_stream_file (KLObject* stream_object, FILE* file)
{
  set_stream_file(get_stream(stream_object), file);
}

KLStreamType get_kl_stream_stream_type (KLObject* stream_object)
{
  return get_stream_stream_type(get_stream(stream_object));
}

void set_kl_stream_stream_type (KLObject* stream_object, KLStreamType stream_type)
{
  set_stream_stream_type(get_stream(stream_object), stream_type);
}

KLObject* close_kl_stream (KLObject* stream_object)
{
  int stream_status = fclose(get_kl_stream_file(stream_object));

  if (stream_status != 0)
    throw_kl_exception("Failed to close stream");

  return get_empty_kl_list();
}

bool is_kl_stream (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_STREAM;
}

bool is_kl_stream_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

char* kl_stream_to_string (KLObject* stream_object)
{
  if (stream_object == get_std_input_stream_object())
    return "#<Stream {stinput} in>";
  else if (stream_object == get_std_output_stream_object())
    return "#<Stream {stoutput} out>";
  else if (stream_object == get_std_error_stream_object())
    return "#<Stream {sterror} out>";

  Stream* stream = get_stream(stream_object);
  char* stream_type_string =
    stream_type_to_stream_type_string(get_stream_stream_type(stream));
  char string[1];
  char* object_string;
  int object_string_length = snprintf(string, 1,
                                      "#<Stream {0x%016" PRIxPTR "} %s>",
                                      (uintptr_t)stream_object,
                                      stream_type_string);

  object_string = malloc((size_t)object_string_length + 1);
  sprintf(object_string, "#<Stream {0x%016" PRIxPTR "} %s>",
          (uintptr_t)stream_object, stream_type_string);

  return object_string;
}

char read_byte (FILE* file)
{
  char c = (char)getc(file);

  if (c == EOF) {
    if (ferror(file) != 0)
      throw_kl_exception("Failed to read a byte from stream");

    return  -1;
  }

  return c;
}

KLObject* read_kl_stream_byte (KLObject* stream_object)
{
  if (!is_kl_stream(stream_object))
    throw_kl_exception("Parameter should be a stream object");
  
  return create_kl_number_l(read_byte(get_kl_stream_file(stream_object)));
}

static inline char* get_read_buffer (void)
{
  return read_buffer;
}

static inline void set_read_buffer (char* buffer)
{
  read_buffer = buffer;
}

static inline size_t get_read_buffer_allocation_size (void)
{
  return read_buffer_allocation_size;
}

static inline void set_read_buffer_allocation_size (size_t size)
{
  read_buffer_allocation_size = size;
}

void initialize_read_buffer (void)
{
  read_buffer = malloc(get_read_buffer_allocation_size());
  read_buffer[get_read_buffer_allocation_size() - 1] = '\0';
}

int read_byte_with_buffer (FILE* file)
{
  return ((read_buffer_position > 0) ?
          read_buffer[--read_buffer_position] : getc(file));
}

void unread_byte_with_buffer (char c)
{
  if (read_buffer_position >= get_read_buffer_allocation_size() - 1) {
    size_t new_read_buffer_allocation_size =
      get_read_buffer_allocation_size() * 2;
    char* new_read_buffer = malloc(new_read_buffer_allocation_size);

    strcpy(new_read_buffer, get_read_buffer());
    set_read_buffer(new_read_buffer);
    set_read_buffer_allocation_size(new_read_buffer_allocation_size);
  }

  read_buffer[read_buffer_position++] = c;
}

void unread_bytes_with_buffer (char* lookahead_buffer)
{
  size_t lookahead_buffer_size = strlen(lookahead_buffer);
        
  for (long i = (long)lookahead_buffer_size - 1; i >= 0; --i)
    unread_byte_with_buffer(lookahead_buffer[i]);
}

char write_byte (FILE* file, char c)
{
  if (putc(c, file) != c)
    throw_kl_exception("Failed to write a byte to stream");

  return c;
}

KLObject* write_kl_stream_byte (KLObject* stream_object, KLObject* number_object)
{
  if (!is_kl_stream(stream_object))
    throw_kl_exception("Parameter is not a stream object");

  if (!is_kl_number(number_object))
    throw_kl_exception("Parameter is not a number object");

  char c = (char)get_kl_number_number_l(number_object); 

  return create_kl_number_l(write_byte(get_kl_stream_file(stream_object), c));
}
