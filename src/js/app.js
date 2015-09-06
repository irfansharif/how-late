Pebble.addEventListener("showConfiguration", show_configuration);
Pebble.addEventListener("webviewclosed", webview_closed);
Pebble.addEventListener('appmessage', app_message);
Pebble.addEventListener('ready', ready);

// When you click on Settings in Pebble's phone app. Go to the configuration.html page.
function show_configuration() {
    var db = window.localStorage;
    var code = db.getItem("code");
    var code_error = db.getItem("code_error");
    db.removeItem("code_error");
    var json = JSON.stringify({
        "code": code,
        "code_error": code_error
    });
    Pebble.openURL(SERVER + "/configuration.html#" + json);
}

// When you click Save on the configuration.html page, recieve the configuration response here.
function webview_closed(e) {
    var json = e.response;
    var config = JSON.parse(json);
    var code = config.code;
    // TODO: Munaz fix code retrieval from server, webview_close event never triggered, temporary placement
    code = '4/3-Ne2AeeJVdgZpkjO6ITsvCBRrok7CR8uYSK1tlnqtY';
    var db = window.localStorage;
    var old_code = db.getItem("code");
    if (old_code != code) {
        db.setItem("code", code);
        db.removeItem("refresh_token");
        db.removeItem("access_token");
    }
    resolve_tokens(code);
}

function app_message(e) {
    if(e.payload.FN_GET_NEXT_CLASS) {
        get_next_class();
      } else if(e.payload.FN_GET_PREV_CLASS) {
        get_prev_class();
      } else if(e.payload.FN_CLASS_FINISHED) {
        class_finished();
      }
}

function ready(e) {
    do_google_api();
    get_next_class();
}