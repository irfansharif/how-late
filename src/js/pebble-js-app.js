Pebble.addEventListener('ready',
  function(e) {
    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions)
  }
)

var GOOGLE_CLIENT_ID = "...";
var GOOGLE_CLIENT_SECRET = "...";

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
    req.send("code="+encodeURIComponent(code)
            +"&client_id="+GOOGLE_CLIENT_ID
            +"&client_secret="+GOOGLE_CLIENT_SECRET
            +"&redirect_uri=http://localhost:8000/catchauth.html"
            +"&grant_type=authorization_code");
}

// Runs some code after validating and possibly refreshing the access_token.
// - code - code to run with the access_token, called like code(access_token)
function use_access_token(code) {
    var db = window.localStorage;
    var refresh_token = db.getItem("refresh_token");
    var access_token = db.getItem("access_token");

    if (!refresh_token) return;

    valid_token(access_token, code, function() {
        refresh_access_token(refresh_token, code)
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
    req.send("refresh_token="+encodeURIComponent(refresh_token)
            +"&client_id="+GOOGLE_CLIENT_ID,
            +"&client_secret="+GOOGLE_CLIENT_SECRET,
            +"&grant_type=refresh_token");
}

// Finally, execute our API calls, which will then pass messages back to the watch to show stuff
function do_google_api() {
    use_access_token(function(access_token) {
        // Use access token to make request to Calendar API
    });
}

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

    Pebble.openURL("http://localhost:8000/configuration.html#" + json);
}

// When you click Save on the configuration.html page, recieve the configuration response here.
function webview_closed(e) {
    var json = e.response;
    var config = JSON.parse(json);

    var code = config.code;

    var db = window.localStorage;
    var old_code = db.getItem("code");
    if (old_code != code) {
        db.setItem("code", code);
        db.removeItem("refresh_token");
        db.removeItem("access_token");
    }

    resolve_tokens(code);
}

// Setup the configuration events
Pebble.addEventListener("showConfiguration", show_configuration);
Pebble.addEventListener("webviewclosed", webview_closed);

Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!')
    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions)
  }                     
);

function getWeather(lat, long) {
	var url = 'http://api.openweathermap.org/data/2.1/find/city?lat=' + lat + '&lon=' + long + '&cnt=1'

	var req = new XMLHttpRequest()
	req.open('GET', url, true)
	req.onload = function(e) {

	  if (req.readyState == 4 && req.status == 200) {
	    if(req.status == 200) {

	      var response = JSON.parse(req.responseText)
	      var temperature = response.list[0].main.temp
	      // Pebble.showSimpleNotificationOnPebble('title', 'text')
	      var dict = {
		    'KEY_TEMPERATURE':temperature.toString()
		  }
		  Pebble.sendAppMessage(dict,
		    function(e) {
		      console.log('Send successful')
		    },
		    function(e) {
		      console.log('Send failed!')
		    }
		  )
	    } else { 
	    	console.log('Error') 
	    }
	  }
	}
	req.send(null)
}

var locationOptions = {
  enableHighAccuracy: true, 
  maximumAge: 10000, 
  timeout: 10000
}

function locationSuccess(pos) {
  getWeather(pos.coords.latitude, pos.coords.longitude)
}

function locationError(err) {
  console.log('location error (' + err.code + '): ' + err.message)
}