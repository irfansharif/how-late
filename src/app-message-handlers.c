#include <pebble.h>
#include "app-message-handlers.h"
#define KEY_TEMPERATURE 0

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  TextLayer *tl = (TextLayer*) context;
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  Tuple *t = dict_read_first(iterator);
  while(t != NULL) {
    static char s_buffer[64];
    switch (t->key) {
      case KEY_TEMPERATURE:
        APP_LOG(APP_LOG_LEVEL_INFO, "KEY_TEMPERATURE received with value %s", t->value->cstring);
        snprintf(s_buffer, sizeof(s_buffer), "Received '%s'", t->value->cstring);
        text_layer_set_text(tl, s_buffer);
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