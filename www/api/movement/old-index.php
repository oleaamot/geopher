<html>
<body style="background: #ffffff;" onload="updateGeo();">
    <script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=true"></script>
    <!--script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"--><!--/script-->
    <script>
	function success(position) {
	var s = document.querySelector('#status');
	
	if (s.className == 'success') {
		// not sure why we're hitting this twice in FF, I think it's to do with a cached result coming back    
		return;
	}
	
        s.innerHTML = '<input type=hidden class="input_form_custom" name=glat value=' + position.coords.latitude + ' /><input type=hidden class="input_form_custom" name=glon value=' + position.coords.longitude + ' />';
	s.className = 'success';

	var q = document.querySelector('#status_publisher');
	
	if (q.className == 'success') {
		// not sure why we're hitting this twice in FF, I think it's to do with a cached result coming back    
		return;
	}
	
        q.innerHTML = '<img src="img/Latitude_Icon.png" title="Latitude of Location-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glat size=16 value=' + position.coords.latitude + ' /><br /><img src="img/Longitude_Icon.png" title="Longitude of Location-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glon size=16 value=' + position.coords.longitude + ' />';

        // '<input type=text name=glat size=16 value=' + position.coords.latitude + ' /><input type=text name=glon size=16 value=' + position.coords.longitude + ' />';
	q.className = 'success';

	var r = document.querySelector('#status_lns');
	
	if (r.className == 'success') {
		// not sure why we're hitting this twice in FF, I think it's to do with a cached result coming back    
		return;
	}
	
        r.innerHTML =  '<img src="https://piperpal.com/img/Latitude_Icon.png" title="Latitude of Location-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glat size=16 value=' + position.coords.latitude + ' /><br /><img src="https://piperpal.com/img/Longitude_Icon.png" title="Longitude of Location-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glon size=16 value=' + position.coords.longitude + ' />';

//'<input type=hidden class="input_form_custom" name=glat value=' + position.coords.latitude + ' /><input type=hidden class="input_form_custom" name=glon value=' + position.coords.longitude + ' />';
	r.className = 'success';

	var mapcanvas = document.createElement('div');
	mapcanvas.id = 'mapcanvas';
	mapcanvas.style.height = '400px';
	mapcanvas.style.width = '640px';
	
	document.querySelector('article').appendChild(mapcanvas);
	
	var latlng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
	var myOptions = {
	zoom: 15,
	center: latlng,
	mapTypeControl: false,
	navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL},
	mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	var map = new google.maps.Map(document.getElementById("mapcanvas"), myOptions);
	
	var marker = new google.maps.Marker({
		position: latlng, 
				map: map, 
				title:"You are here! (at least within a "+position.coords.accuracy+" meter radius)"
				});

        var locations = [
         ['Banja Luka', 44.766666699999990000, 17.183333299999960000, 4],
    ['Tuzla', 44.532841000000000000, 18.670499999999947000, 5],
    ['Zenica', 44.203439200000000000, 17.907743200000027000, 3],
    ['Sarajevo', 43.850000000000000000, 18.250000000000000000, 2],
    ['Mostar', 43.333333300000000000, 17.799999999999954000, 1]
];

var infowindow = new google.maps.InfoWindow();

var marker, i;
for (i = 0; i < locations.length; i++) {
    marker = new google.maps.Marker({
      position: new google.maps.LatLng(locations[i][1], locations[i][2]),
      map: map
				    });

google.maps.event.addListener(marker, 'click', (function (marker, i) {
    return function () {
	infowindow.setContent(locations[i][0]);
	infowindow.open(map, marker);
    }
						})(marker, i));
}
}

function error(msg) {
	// var s = document.querySelector('#status');
	// s.innerHTML = typeof msg == 'string' ? msg : "failed";
	// s.className = 'fail';
	
	// console.log(arguments);
}

if (navigator.geolocation) {
	navigator.geolocation.getCurrentPosition(success, error);
} else {
	error('not supported');
}
window.location.href = 'https://api.piperpal.com/location/json.php?service='<?php echo $_GET['service']; ?>&glat=' + position.coords.latitude + '&glon=' + position.coords.longitude;

print window.location.href;
</script>
</body>
</html>
