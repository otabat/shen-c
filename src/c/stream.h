#ifndef SHEN_C_STREAM_H
#define SHEN_C_STREAM_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "exception.h"
#include "kl.h"
#include "number.h"
#include "symbol.h"

extern KLObject* in_symbol_object;
extern KLObject* out_symbol_object;

extern KLObject* std_input_stream_object;
extern KLObject* std_output_stream_object;
extern KLObject* std_error_stream_object;

void register_stream_symbol_objects (void);

void initialize_std_stream_objects (void);

char* kl_stream_to_string (KLObject* stream_object);

KLObject* read_kl_stream_byte (KLObject* stream_object);
void initialize_read_buffer (void);
int read_byte_with_buffer (FILE* file);
void unread_byte_with_buffer (char c);
void unread_bytes_with_buffer (char* lookahead_buffer);
KLObject* write_kl_stream_byte (KLObject* stream_object, KLObject* number_object);

inline KLObject* get_in_symbol_object (void)
{
  return in_symbol_object;
}

inline KLObject* get_out_symbol_object (void)
{
  return out_symbol_object;
}

inline FILE* get_stream_file (Stream* stream)
{
  return stream->file;
}

inline void set_stream_file (Stream* stream, FILE* file)
{
  stream->file = file;
}

inline KLStreamType get_stream_stream_type (Stream* stream)
{
  return stream->stream_type;
}

inline void set_stream_stream_type (Stream* stream, KLStreamType stream_type)
{
  stream->stream_type = stream_type;
}

inline Stream* create_stream (FILE* file, KLStreamType stream_type)
{
  Stream* stream = malloc(sizeof(Stream));

  set_stream_file(stream, file);
  set_stream_stream_type(stream, stream_type);

  return stream;
}

inline char* stream_type_to_stream_type_string (KLStreamType stream_type)
{
  if (stream_type == KL_STREAM_TYPE_IN)
    return "in";

  if (stream_type == KL_STREAM_TYPE_OUT)
    return "out";

  throw_kl_exception("Unknown stream type");

  return NULL;
}

inline KLObject* get_std_input_stream_object (void)
{
  return std_input_stream_object;
}

inline KLObject* get_std_output_stream_object (void)
{
  return std_output_stream_object;
}

inline KLObject* get_std_error_stream_object (void)
{
  return std_error_stream_object;
}

inline Stream* get_stream (KLObject* stream_object)
{
  return stream_object->value.stream;
}

inline void set_stream (KLObject* stream_object, Stream* stream)
{
  stream_object->value.stream = stream;
}

inline KLObject* create_kl_stream (char* file_path,
                                   KLObject* stream_type_symbol_object)
{
  char* open_mode_string;
  KLStreamType stream_type;

  if (stream_type_symbol_object == get_in_symbol_object()) {
    open_mode_string = "r";
    stream_type = KL_STREAM_TYPE_IN;
  } else if (stream_type_symbol_object == get_out_symbol_object()) {
    open_mode_string = "w";
    stream_type = KL_STREAM_TYPE_OUT;
  } else
    throw_kl_exception("Unknown stream type");

  FILE* file = fopen(file_path, open_mode_string);

  if (is_null(file))
    throw_kl_exception("Failed to open stream");

  KLObject* stream_object = create_kl_object(KL_TYPE_STREAM);
  Stream* stream = create_stream(file, stream_type);

  set_stream(stream_object, stream);

  return stream_object;
}

inline FILE* get_kl_stream_file (KLObject* stream_object)
{
  return get_stream_file(get_stream(stream_object));
}

inline void set_kl_stream_file (KLObject* stream_object, FILE* file)
{
  set_stream_file(get_stream(stream_object), file);
}

inline KLStreamType get_kl_stream_stream_type (KLObject* stream_object)
{
  return get_stream_stream_type(get_stream(stream_object));
}

inline void set_kl_stream_stream_type (KLObject* stream_object,
                                       KLStreamType stream_type)
{
  set_stream_stream_type(get_stream(stream_object), stream_type);
}

inline KLObject* close_kl_stream (KLObject* stream_object)
{
  int stream_status = fclose(get_kl_stream_file(stream_object));

  if (stream_status != 0)
    throw_kl_exception("Failed to close stream");

  return get_empty_kl_list();
}

inline bool is_kl_stream (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_STREAM;
}

inline bool is_kl_stream_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}


#endif
