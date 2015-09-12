//
// Created by isharif on 07/09/15.
//

#include "display-layer.h"
#include "../objects/event_card_private.h"
#include "../objects/event_card_data.h"

static char course_tl_buffer[64];
static char class_loc_buffer[64];
static char class_typ_buffer[64];
static char start_tm_buffer[64];
static char end_tm_buffer[64];

void display_event( EventCard *ec, EventCardData *ecd) {
    snprintf(course_tl_buffer, sizeof(course_tl_buffer), "%s", ecd->course_title);
    text_layer_set_text(ec->course_title, course_tl_buffer);

    snprintf(class_loc_buffer, sizeof(class_loc_buffer), "%s", ecd->class_location);
    text_layer_set_text(ec->class_location, class_loc_buffer);

    snprintf(class_typ_buffer, sizeof(class_typ_buffer), "%s", ecd->class_type);
    text_layer_set_text(ec->class_type, class_typ_buffer);

    snprintf(start_tm_buffer, sizeof(start_tm_buffer), "%s", (const char*) ecd->start_time);
    text_layer_set_text(ec->start_time, start_tm_buffer);

    snprintf(end_tm_buffer, sizeof(end_tm_buffer), "%s", (const char*) ecd->end_time);
    text_layer_set_text(ec->end_time, end_tm_buffer);
}