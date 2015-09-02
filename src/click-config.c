#include <pebble.h>
#include "click-config.h"
#include "app-message-handlers.h"

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) {

}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, FN_GET_NEXT_CLASS, 1);
  app_message_outbox_send();
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, FN_GET_PREV_CLASS, 1);
  app_message_outbox_send();
}