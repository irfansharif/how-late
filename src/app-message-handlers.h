#include <pebble.h>

// Keys identify corresponding functions in pebble-js-app
#define FN_CLASS_FINISHED 00
#define FN_GET_NEXT_CLASS 01
#define FN_GET_PREV_CLASS 02

// Keys identify corresponding variables in EventCard struct
#define CLASS_INDEX 10
#define COURSE_TITLE 11
#define CLASS_LOCATION 12
#define CLASS_TYPE 13
#define START_TIME 14
#define END_TIME 15

void inbox_received_callback(DictionaryIterator *iterator, void *context);
void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);
