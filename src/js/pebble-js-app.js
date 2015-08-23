Pebble.addEventListener('ready',
  function(e) {
    // Request current position
    // navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
	  var dict = {
	    'KEY_DATA':'Hello from PebbleKit JS!'
	  }

	  Pebble.sendAppMessage(dict,
	    function(e) {
	      console.log('Send successful.');
	    },
	    function(e) {
	      console.log('Send failed!');
	    }
	  )
  }
)


// var locationOptions = {
//   enableHighAccuracy: true, 
//   maximumAge: 10000, 
//   timeout: 10000
// };

// function locationSuccess(pos) {
//   console.log('lat= ' + pos.coords.latitude)
//   console.log('lon= ' + pos.coords.longitude)
//   sendReq(pos.coords.latitude, pos.coords.longitude)
// }

// function locationError(err) {
//   console.log('location error (' + err.code + '): ' + err.message);
// }

// function sendReq(lat, long) {
// 	var req = new XMLHttpRequest();
// 	req.open('GET', 'http://api.openweathermap.org/data/2.1/find/city?lat=' + lat + '&lon=' + long + '&cnt=1', true);
// 	req.onload = function(e) {
// 	  if (req.readyState == 4 && req.status == 200) {
// 	    if(req.status == 200) {
// 	      var response = JSON.parse(req.responseText);
// 	      var temperature = response.list[0].main.temp;
// 	      var icon = response.list[0].main.icon;
// 	      Pebble.showSimpleNotificationOnPebble('title', 'text');
// 	      Pebble.sendAppMessage({ 'icon':icon, 'temperature':temperature + '\u00B0C'});
// 	    } else { console.log('Error'); }
// 	  }
// 	}
// 	req.send(null);
// }