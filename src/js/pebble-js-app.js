Pebble.addEventListener('ready',
  function(e) {
    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions)
  }
)

function getWeather(lat, long) {
	var url = 'http://api.openweathermap.org/data/2.1/find/city?lat=' + lat + '&lon=' + long + '&cnt=1'

	var req = new XMLHttpRequest()
	req.open('GET', url, true)
	req.onload = function(e) {

	  if (req.readyState == 4 && req.status == 200) {
	    if(req.status == 200) {

	      var response = JSON.parse(req.responseText)
	      console.log(JSON.stringify(response, null, 2))
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