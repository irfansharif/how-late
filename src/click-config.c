#include <pebble.h>
#include "click-config.h"

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
//  Temporary placement, TODO Remove after Munaz completes event parser
  class_finished();
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  get_prev_class();
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  get_next_class();
}