#include <pebble.h>
#include "click-config.h"
#include "app-message-handlers.h"
#include "objects/event_card_private.h"
#include "interface-layer/display-layer.h"

static Window *window;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if(mktime(tick_time) > *cached_time) {
//     Trigger FN_CLASS_FINISHED, TODO: Uncomment after Munaz finishes updating event parser
//    class_finished();
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  event_card->course_title = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  event_card->start_time = text_layer_create((GRect) { .origin = { 0, 52 }, .size = { bounds.size.w, 20 } });
  event_card->end_time = text_layer_create((GRect) { .origin = { 0, 32 }, .size = { bounds.size.w, 20 } });
  event_card->class_location = text_layer_create((GRect) { .origin = { 0, 12 }, .size = { bounds.size.w, 20 } });
  event_card->class_type = text_layer_create((GRect) { .origin = { 0, 92 }, .size = { bounds.size.w, 20 } });


  text_layer_set_text(event_card->course_title, "Waiting..");
  text_layer_set_text_alignment(event_card->course_title, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(event_card->course_title));


  text_layer_set_text(event_card->start_time, "Waiting..");
  text_layer_set_text_alignment(event_card->start_time, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(event_card->start_time));


  text_layer_set_text(event_card->end_time, "Waiting..");
  text_layer_set_text_alignment(event_card->end_time, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(event_card->end_time));


  text_layer_set_text(event_card->class_location, "Waiting..");
  text_layer_set_text_alignment(event_card->class_location, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(event_card->class_location));


  text_layer_set_text(event_card->class_type, "Waiting..");
  text_layer_set_text_alignment(event_card->class_type, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(event_card->class_type));

  app_message_set_context(event_card);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void window_unload(Window *window) {
  text_layer_destroy(event_card->course_title);
  text_layer_destroy(event_card->start_time);
  text_layer_destroy(event_card->end_time);
  text_layer_destroy(event_card->class_location);
  text_layer_destroy(event_card->class_type);
}

static void init(void) {
  event_card = malloc(sizeof (EventCard));
  memset(event_card, 0, sizeof(EventCard));

//  memset(&eventCards, 0, sizeof(EventCardData) * 10);

  window = window_create();
  window_set_background_color(window, GColorDarkCandyAppleRed);

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  free(event_card);
  free(ecd);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
