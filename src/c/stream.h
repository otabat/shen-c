#ifndef SHEN_C_STREAM_H
#define SHEN_C_STREAM_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "exception.h"
#include "kl.h"
#include "number.h"

extern KLObject* std_input_stream_object;
extern KLObject* std_output_stream_object;
extern KLObject* std_error_stream_object;

void initialize_std_stream_objects (void);

char* kl_stream_to_string (KLObject* stream_object);

KLObject* read_kl_stream_byte (KLObject* stream_object);
void initialize_read_buffer (void);
int read_byte_with_buffer (FILE* file);
void unread_byte_with_buffer (char c);
void unread_bytes_with_buffer (char* lookahead_buffer);
KLObject* write_kl_stream_byte (KLObject* stream_object, KLObject* number_object);

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

inline char* stream_type_string_to_open_mode_string (char* stream_type_string)
{
  if (strcmp(stream_type_string, "in") == 0)
    return "r";

  if (strcmp(stream_type_string, "out") == 0)
    return "w";

  throw_kl_exception("Unknown stream type");

  return NULL;
}

inline KLStreamType stream_type_string_to_stream_type (char* stream_type_string)
{
  if (strcmp(stream_type_string, "in") == 0)
    return KL_STREAM_TYPE_IN;

  if (strcmp(stream_type_string, "out") == 0)
    return KL_STREAM_TYPE_OUT;

  throw_kl_exception("Unknown stream type");

  return 0;
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

inline KLObject* create_kl_stream (char* file_path, char* stream_type_string)
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
