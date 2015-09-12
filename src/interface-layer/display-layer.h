#include <pebble.h>
#include "../objects/event_card_private.h"

static TextLayer *text_layer;
static EventCard *event_card;

void display_event( EventCard *ec, EventCardData *ecd);