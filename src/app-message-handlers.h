#include <pebble.h>
#include "interface-layer/keys.h"
#include "objects/event_card_data.h"

EventCardData eventCards[10];
EventCardData *ecd;

time_t *cached_time;
int cache_end_time;

void inbox_received_callback(DictionaryIterator *iterator, void *context);
void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);