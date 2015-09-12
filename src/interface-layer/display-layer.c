//
// Created by isharif on 07/09/15.
//

#include "display-layer.h"
#include "../objects/event_card_private.h"
#include "../objects/event_card_data.h"

void display_event(EventCardData *ecd) {
//    event_card->card_data = ecd;
    text_layer_set_text(event_card->course_title, ecd->course_title);
//    text_layer_set_text(event_card->end_time, (const char*) ecd->end_time);
//    text_layer_set_text(event_card->class_location, ecd->class_location);
//    text_layer_set_text(event_card->class_type, ecd->class_type);
//    text_layer_set_text(event_card->start_time, (const char*) ecd->start_time);
}