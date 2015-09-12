#include <pebble.h>
#include "app-message-handlers.h"
#include "interface-layer/display-layer.h"
#include "objects/event_card_private.h"

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  EventCard *ec = (EventCard*) context;
  TextLayer *course_tl = ec->course_title;
  TextLayer *class_loc = ec->class_location;
  TextLayer *class_typ = ec->class_type;
  TextLayer *start_tm = ec->start_time;
  TextLayer *end_tm = ec->end_time;

  ecd = malloc(sizeof(EventCardData));
  memset(ecd, 0, sizeof(EventCardData));
  int class_index_num = -1;

  Tuple *t = dict_read_first(iterator);
  while(t != NULL) {
    switch (t->key) {
      case CLASS_INDEX:
        class_index_num = t->value->int32;
        if( t->value->int32 == -1 ) {
          // trigger bounce animation here
        } else if (t->value->int32 == CURRENT_CLASS_INDEX)
          cache_end_time = 1;
        else
          cache_end_time = 0;
        break;
      case COURSE_TITLE:
        ecd->course_title = t->value->cstring;
        break;
      case CLASS_LOCATION:
        ecd->class_location = t->value->cstring;
        break;
      case CLASS_TYPE:
        ecd->class_type = t->value->cstring;
        break;
      case START_TIME:
        ecd->start_time = (time_t*) t->value;
        break;
      case END_TIME:
        ecd->end_time = (time_t*) t->value;
        if(cache_end_time) {
          *cached_time = (time_t) t->value;
        }
        break;
    }
    t = dict_read_next(iterator);
  }


  if(class_index_num != -1 ) {
//    eventCards[class_index_num] = *ecd;
    display_event(ec, ecd);
  }
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
 
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  
}