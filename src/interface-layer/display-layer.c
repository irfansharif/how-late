//
// Created by isharif on 07/09/15.
//

#include "display-layer.h"
#include "../objects/event_card_private.h"
#include "../objects/event_card_data.h"

static char course_tl_buffer[64];

void display_event( EventCard *ec, EventCardData *ecd) {
//    event_card->card_data = ecd;

    snprintf(course_tl_buffer, sizeof(course_tl_buffer), "'%s'", ecd->course_title);
    text_layer_set_text(ec->course_title, course_tl_buffer);
//    text_layer_set_text(event_card->end_time, (const char*) ecd->end_time);
//    text_layer_set_text(event_card->class_location, ecd->class_location);
//    text_layer_set_text(event_card->class_type, ecd->class_type);
//    text_layer_set_text(event_card->start_time, (const char*) ecd->start_time);
}