var offset = -1;
var dict;

function get_next_class() {
    if(offset + 1 > CLASS_ARRAY.length - 1) {
        dict = {
            'CLASS_INDEX': -1
        };
    } else {
        offset = offset + 1;
        dict = CLASS_ARRAY[offset];
        dict.CLASS_INDEX = offset + 1;
    }
    Pebble.sendAppMessage(dict);
}

function get_prev_class() {
    if(offset - 1 < 0) {
        dict = {
            'CLASS_INDEX': -1
        };
    } else {
        offset = offset - 1;
        dict = CLASS_ARRAY[offset];
        dict.CLASS_INDEX = offset + 1;
    }
    Pebble.sendAppMessage(dict);
}

function update_class_cache(finished_class) {
    do_google_api();
    //TODO: Remove following and parameter after Munaz finishes event parser
    setTimeout(function() {
        CLASS_ARRAY.push(finished_class);
    }, 5000);
}

function class_finished() {
    var finished_class = CLASS_ARRAY.shift();
    offset = -1;
    update_class_cache(finished_class);
    get_next_class();
}