//
// Created by isharif on 27/08/15.
//

#pragma once

#include <pebble.h>

typedef struct {
    char *course_title;
    char *class_location;
    char *class_type;
    time_t *start_time;
    time_t *end_time;
    int icon;
} EventCardData;