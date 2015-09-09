//
// Created by isharif on 27/08/15.
//
#pragma once

#include <pebble.h>
#include "event_card_data.h"

typedef struct {
    TextLayer *course_title;
    TextLayer *class_location;
    TextLayer *class_type;
    TextLayer *start_time;
    TextLayer *end_time;
    TextLayer *pagenation_layer;
    Layer *image_layer;
    Layer *horizontal_ruler_layer;
    Animation *animation;
    EventCardData *card_data;
} EventCard;
