#ifndef SHEN_C_STREAM_H
#define SHEN_C_STREAM_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "exception.h"
#include "kl.h"
#include "number.h"

FILE* get_stream_file (Stream* stream);
void set_stream_file (Stream* stream, FILE* file);
KLStreamType get_stream_stream_type (Stream* stream);
void set_stream_stream_type (Stream* stream, KLStreamType stream_type);
Stream* create_stream (FILE* file, KLStreamType stream_type);

char* stream_type_string_to_open_mode_string (char* stream_type_string);
KLStreamType stream_type_string_to_stream_type (char* stream_type_string);
char* stream_type_to_stream_type_string (KLStreamType stream_type);
KLObject* get_std_input_stream_object (void);
KLObject* get_std_output_stream_object (void);
KLObject* get_std_error_stream_object (void);
KLObject* create_std_kl_stream (FILE* file, char* stream_type_string);
void initialize_std_stream_objects (void);

Stream* get_stream (KLObject* stream_object);
void set_stream (KLObject* stream_object, Stream* stream);
KLObject* create_kl_stream (char* file_path, char* stream_type_string);
FILE* get_kl_stream_file (KLObject* stream_object);
void set_kl_stream_file (KLObject* stream_object, FILE* file);
KLStreamType get_kl_stream_stream_type (KLObject* stream_object);
void set_kl_stream_stream_type (KLObject* stream_object, KLStreamType stream_type);
KLObject* close_kl_stream (KLObject* stream_object);
bool is_kl_stream (KLObject* object);
bool is_kl_stream_equal (KLObject* left_object, KLObject* right_object);
char* kl_stream_to_string (KLObject* stream_object);

char read_byte (FILE* file);
KLObject* read_kl_stream_byte (KLObject* stream_object);
void initialize_read_buffer (void);
int read_byte_with_buffer (FILE* file);
void unread_byte_with_buffer (char c);
void unread_bytes_with_buffer (char* lookahead_buffer);
char write_byte (FILE* file, char c);
KLObject* write_kl_stream_byte (KLObject* stream_object, KLObject* number_object);

#endif
