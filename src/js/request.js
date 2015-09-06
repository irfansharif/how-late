// Finally, execute our API calls, which will then pass messages back to the watch to show stuff
function do_google_api() {
    use_access_token(function(access_token) {
        // Use access token to make request to Calendar API
        var req = new XMLHttpRequest();
        req.open("GET", "https://www.googleapis.com/calendar/v3/users/me/calendarList?access_token=" + access_token, true);
        req.onload = function(e) {
            if (req.readyState == 4 && req.status == 200) {
                // Get list of Calendars https://developers.google.com/google-apps/calendar/v3/reference/calendarList/list
                var result = JSON.parse(req.responseText);
                // Get Calendars https://developers.google.com/google-apps/calendar/v3/reference/calendarList#resource
                var calenders = result.items;
                if (!calendars || calendars.length === 0) {
                    return;
                }
                req = new XMLHttpRequest();
                req.open("GET", "https://www.googleapis.com/calendar/v3/calendars/" + 
                    calendars[0].id + 
                    "/events?maxResults=10&orderBy=startTime", true);
                req.onload = function(e) {
                    if (req.readyState == 4 && req.status == 200) {
                        // Get list of events https://developers.google.com/google-apps/calendar/v3/reference/events/list
                        result = JSON.parse(req.responseText);
                        // Get events https://developers.google.com/google-apps/calendar/v3/reference/events#resource
                        var events = result.items;
                        // Do stuff with events here
                    }
                };
                req.send();
            }
        };
        req.send();
    });
}