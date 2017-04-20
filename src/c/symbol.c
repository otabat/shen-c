#include "symbol.h"

unsigned long auto_increment_symbol_id = 0;
char* auto_increment_symbol_prefix = "G__";

extern char* get_symbol (KLObject* symbol_object);
extern void set_symbol (KLObject* symbol_object, char* symbol);
extern KLObject* create_kl_symbol (char* symbol);
extern bool is_kl_symbol (KLObject* object);
extern bool is_symbol_equal (char* left_symbol, char* right_symbol);
extern bool is_kl_symbol_equal (KLObject* left_object, KLObject* right_object);

extern unsigned long get_auto_increment_symbol_id (void);
inline unsigned long pre_increment_auto_increment_symbol_id (void);
inline char* get_auto_increment_symbol_prefix (void);
inline char* create_auto_increment_symbol (void);
extern KLObject* create_auto_increment_kl_symbol (void);

extern KLObject* kl_string_to_kl_symbol (KLObject* string_object);
extern KLObject* kl_string_to_kl_symbol_or_kl_boolean (KLObject* string_object);
