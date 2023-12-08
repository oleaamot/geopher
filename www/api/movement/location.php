<!DOCTYPE html>
<html>
  <head>
    <title>Location Location Location</title>

    <script type="text/javascript" charset="utf-8">

   var watchID = null;
   var glat = pos.coords.latitude;
   var glon = pos.coords.longitude;

function Location() {
    // Determine support for geolocation
    if (navigator.geolocation){
        var timeoutVal = 10 * 1000 * 1000;
        navigator.geolocation.getCurrentPosition(
            displayPosition,
            displayError,
            { enableHighAccuracy: true, timeout: timeoutVal, maximumAge: 0 }
        );
    }
    else{
        alert('It seems like Geolocation, which is required for this page, is not enabled in your browser. Please use a browser which supports it.');
    }
}

// Success callback function
function displayPosition(pos){
    var glat = pos.coords.latitude;
    var glon = pos.coords.longitude;
    var thediv = document.getElementById("location");

    thediv.innerHTML = "<form method='POST' action='https://www.piperpal.com/'><table><tr><th>Name</th><td><input type='text' name='name' value='" + name + "' /></td></tr><tr><th>Link</th><td><input type='text' name='link' value='" + link + "' /></td></tr><tr><th>GLat</th><td><input type='text' name='glat' value='" + glat + "' /></td></tr><tr><th>GLon</th><td><input type='text' name='glon' value='" + glon + "' /></td></tr><tr><th>GRad</th><td><input type='text' name='grad' value='" + grad + "' /></td></tr><tr><td colspan='2'><input type='submit' value='Vote' /></td></tr></table></form>\n";

}

// Error callback function
function displayError(error) {
    var errors = {
      1: 'Permission denied',
      2: 'Position unavailable',
      3: 'Request timeout'
    };
    var thediv = document.getElementById("errormsg");
    thediv.innerHTML = "<p>Location Error: " + errors[error.code] + "</p>";
}

Location();

function f() {
  // Update every 1 ms seconds
  var options = {enableHighAccuracy: true,timeout: 5000,maximumAge: 0,desiredAccuracy: 0, frequency: 1 };
  watchID = navigator.geolocation.watchPosition(onSuccess, onError, options);
}

// onSuccess Geolocation
//
function onSuccess(position) {
  var xmlhttp;
  if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
    xmlhttp=new XMLHttpRequest();
  }else{// code for IE6, IE5
    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }       
        var str = 'glat='  + position.coords.latitude + '&' + 'glon=' + position.coords.longitude + '&' + 'service=Restaurant';
        var url = "http://api.piperpal.com/location/json.php";
        var params = str;
        xmlhttp.open("GET", url+"?"+params, true);
        document.writeln(xmlhttp.responseText);        
        window.location.href=xmlhttp.responseText;
        window.location.href= url + '?' + str;
        // document.writeln(str);
        document.body.innerHTML += xmlhttp.responseText;
        xmlhttp.send();
        //document.writeln("send");
        //document.writeln(str);
}

// clear the watch that was started earlier
// 
function clearWatch() {
  if (watchID != null) {
    navigator.geolocation.clearWatch(watchID);
    watchID = null;
  }
}

// onError Callback receives a PositionError object
//
function onError(error) {
  alert('code: '    + error.code    + '\n' +
	'message: ' + error.message + '\n');
}

    </script>
  </head>
  <body onload="Location();">
    <p id="geolocation">Watching geolocation...</p>
    <button onclick="Location();"> Watch</button>     
    <script type='text/javascript'>link = 'https://api.piperpal.com/location/location.php'; name = '<?php echo $_GET['name']; ?>'; glat = pos.coords.latitude; glon = pos.coords.longitude;</script>
    <script src='https://api.piperpal.com/location/location.js' type='text/javascript'></script>
    <div id='location'></div>
    <script type="text/javascript" src="https://api.piperpal.com/location/json.php?service=Books&glat=60&glon=10"></script>
    <script language="JavaScript">
      Location();
      document.write("glat=" + pos.coords.latitude + "<br />\n");
      document.write("glon=" + pos.coords.longitude + "<br />\n");
      var obj = JSON.parse(locations);
      for (i=0; i < obj.locations.length; i++) {
          document.write(obj.locations[i].name + " " + obj.locations[i].distance + "<br />\n");
      }
    </script>                                                              
  </body>
</html>
