// Retrieves the refresh_token and access_token.
// - code - the authorization code from Google.
function resolve_tokens(code) {
    var req = new XMLHttpRequest();
    req.open("POST", "https://accounts.google.com/o/oauth2/token", true);
    req.onload = function(e) {
        var db = window.localStorage;
        if (req.readyState == 4 && req.status == 200) {
            var result = JSON.parse(req.responseText);
            if (result.refresh_token && result.access_token) {
                db.setItem("refresh_token", result.refresh_token);
                db.setItem("access_token", result.access_token);
                return;
            }
        }
        db.removeItem("code");
        db.setItem("code_error", "Unable to verify the your Google authentication.");
    };
    req.send("code="+encodeURIComponent(code) +
            "&client_id="+GOOGLE_CLIENT_ID +
            "&client_secret="+GOOGLE_CLIENT_SECRET +
            "&redirect_uri=" + SERVER + "/catchauth.html" +
            "&grant_type=authorization_code");
}

// Runs some code after validating and possibly refreshing the access_token.
// - code - code to run with the access_token, called like code(access_token)
function use_access_token(code) {
    var db = window.localStorage;
    var refresh_token = db.getItem("refresh_token");
    var access_token = db.getItem("access_token");
    if (!refresh_token) {
        Pebble.showSimpleNotificationOnPebble('Setup', 'Configure your calendar through settings on your phone');
        code('dummy token');
        return;
    }
    valid_token(access_token, code, function() {
        refresh_access_token(refresh_token, code);
    });
}

// Validates the access token.
// - access_token - the access_token to validate
// - good - the code to run when the access_token is good, run like good(access_token)
// - bad - the code to run when the access_token is expired, run like bad()
function valid_token(access_token, good, bad) {
    var req = new XMLHttpRequest();
    req.open("https://www.googleapis.com/oauth2/v1/tokeninfo?access_token=" + access_token, true);
    req.onload = function(e) {
        if (req.readyState == 4 && req.status == 200) {
            var result = JSON.parse(req.responseText);
            if (result.audience != GOOGLE_CLIENT_ID) {
                var db = window.localStorage;
                db.removeItem("code");
                db.removeItem("access_token");
                db.removeItem("refresh_token");
                db.setItem("code_error", "There was an error validating your Google Authentication. Please re-authorize access to your account.");
                return;
            }
            good(access_token);
        }
        bad();
    };
    req.send(null);
}

// Refresh a stale access_token.
// - refresh_token - the refresh_token to use to retreive a new access_token
// - code - code to run with the new access_token, run like code(access_token)
function refresh_access_token(refresh_token, code) {
    var req = new XMLHttpRequest();
    req.open("POST", "https://accounts.google.com/o/oauth2/token", true);
    req.onload = function(e) {
        if (req.readyState == 4 && req.status == 200) {
            var result = JSON.parse(req.responseText);
            if (result.access_token) {
                var db = window.localStorage;
                db.setItem("access_token", result.access_token);
                code(result.access_token);
            }
        }
    };
    req.send("refresh_token="+encodeURIComponent(refresh_token) +
            "&client_id="+GOOGLE_CLIENT_ID, +
            "&client_secret="+GOOGLE_CLIENT_SECRET, +
            "&grant_type=refresh_token");
}