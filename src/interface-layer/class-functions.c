//
// Created by isharif on 06/09/15.
//
#include <pebble.h>
#include "class-functions.h"

void get_prev_class() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, FN_GET_PREV_CLASS, 1);
    app_message_outbox_send();
};

void get_next_class() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, FN_GET_NEXT_CLASS, 1);
    app_message_outbox_send();
};

void class_finished() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, FN_CLASS_FINISHED, 1);
    app_message_outbox_send();
};