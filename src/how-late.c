#include <pebble.h>
#include "click-config.h"
#include "app-message-handlers.h"

#define DELTA 13
#define KEY_TEMPERATURE 0

static int s_index = 0;

static Window *window;
static TextLayer *text_layer;
static GDrawCommandSequence *s_command_seq;
static Layer *s_canvas_layer;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if(tick_time->tm_min % 5 == 0) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, 0, 0);
    app_message_outbox_send();
  }
}

static void next_frame_handler(void *context) {
  layer_mark_dirty(s_canvas_layer); // Draw the next frame
  app_timer_register(DELTA, next_frame_handler, NULL); // Continue the sequence
}

static void update_proc(Layer *layer, GContext *ctx) {
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(s_command_seq, s_index);

  if (frame) {
    gdraw_command_frame_draw(ctx, s_command_seq, frame, GPoint(0, 30));
  }

  // Advance to the next frame, wrapping if necessary
  int num_frames = gdraw_command_sequence_get_num_frames(s_command_seq);
  s_index = s_index + 1;
  if (s_index == num_frames) {
    s_index = 0;
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_canvas_layer = layer_create(GRect(30, 30, bounds.size.w, bounds.size.h));
  layer_set_update_proc(s_canvas_layer, update_proc);
  layer_add_child(window_layer, s_canvas_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Waiting..");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  app_message_set_context(text_layer);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  app_timer_register(DELTA, next_frame_handler, NULL);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_background_color(window, GColorBlueMoon);

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  s_command_seq = gdraw_command_sequence_create_with_resource(RESOURCE_ID_CLOCK_SEQUENCE);
  
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
  layer_destroy(s_canvas_layer);
  gdraw_command_sequence_destroy(s_command_seq);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
