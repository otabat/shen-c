#include "stream.h"

KLObject* in_symbol_object;
KLObject* out_symbol_object;

KLObject* std_input_stream_object;
KLObject* std_output_stream_object;
KLObject* std_error_stream_object;

size_t read_buffer_allocation_size = 100;
char* read_buffer;
size_t read_buffer_position = 0;

extern KLObject* get_in_symbol_object (void);
extern KLObject* get_out_symbol_object (void);

extern FILE* get_stream_file (Stream* stream);
extern void set_stream_file (Stream* stream, FILE* file);
extern KLStreamType get_stream_stream_type (Stream* stream);
extern void set_stream_stream_type (Stream* stream, KLStreamType stream_type);
extern Stream* create_stream (FILE* file, KLStreamType stream_type);

extern char* stream_type_to_stream_type_string (KLStreamType stream_type);

extern Stream* get_stream (KLObject* stream_object);
extern void set_stream (KLObject* stream_object, Stream* stream);
extern KLObject* create_kl_stream (char* file_path,
                                   KLObject* stream_type_symbol_object);
extern FILE* get_kl_stream_file (KLObject* stream_object);
extern void set_kl_stream_file (KLObject* stream_object, FILE* file);
extern KLStreamType get_kl_stream_stream_type (KLObject* stream_object);
extern void set_kl_stream_stream_type (KLObject* stream_object,
                                       KLStreamType stream_type);
extern KLObject* close_kl_stream (KLObject* stream_object);

extern void initialize_in_symbol_object (void);
extern void register_in_symbol_object (void);
extern void initialize_out_symbol_object (void);
extern void register_out_symbol_object (void);
extern void register_stream_symbol_objects (void);

extern KLObject* create_std_kl_stream (FILE* file,
                                       KLObject* stream_type_symbol_object);
extern void initialize_std_input_stream_object (void);
extern void initialize_std_output_stream_object (void);
extern void initialize_std_error_stream_object (void);
extern void initialize_std_stream_objects (void);
extern KLObject* get_std_input_stream_object (void);
extern KLObject* get_std_output_stream_object (void);
extern KLObject* get_std_error_stream_object (void);
extern void initialize_std_stream_objects (void);

extern bool is_kl_stream (KLObject* object);
extern bool is_kl_stream_equal (KLObject* left_object, KLObject* right_object);

extern char read_byte (FILE* file);
extern KLObject* read_kl_stream_byte (KLObject* stream_object);
extern char* get_read_buffer (void);
extern void set_read_buffer (char* buffer);
extern size_t get_read_buffer_allocation_size (void);
extern void set_read_buffer_allocation_size (size_t size);
extern void initialize_read_buffer (void);
extern int read_byte_with_buffer (FILE* file);
extern void unread_byte_with_buffer (char c);
extern void unread_bytes_with_buffer (char* lookahead_buffer);
extern char write_byte (FILE* file, char c);
extern KLObject* write_kl_stream_byte (KLObject* stream_object,
                                       KLObject* number_object);

extern char* read_file (FILE* file);
extern char* read_file_by_file_path (char* file_path);

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
