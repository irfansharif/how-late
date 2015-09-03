#include <pebble.h>
#include "app-message-handlers.h"
#define CURRENT_CLASS_INDEX 1

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  TextLayer *tl = (TextLayer*) context;
  Tuple *t = dict_read_first(iterator);
  while(t != NULL) {
    static char s_buffer[64];
    switch (t->key) {
      case CLASS_INDEX:
        if( t->value->int32 == -1 ) {
          // trigger bounce animation here
          return;
        } else if (t->value->int32 == CURRENT_CLASS_INDEX) {
          // cache END_TIME
        }
        break;
      case COURSE_TITLE:
        snprintf(s_buffer, sizeof(s_buffer), "Received '%s'", t->value->cstring);
        text_layer_set_text(tl, s_buffer);
        break;
      case CLASS_LOCATION:
        break;
      case CLASS_TYPE:
        break;
      case START_TIME:
        break;
      case END_TIME:
        break;
    }
    t = dict_read_next(iterator);
  }
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
 
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  
}