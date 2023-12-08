<!DOCTYPE html>
<html lang="en">
  <head>
    <script src="http://code.jquery.com/jquery-latest.min.js"></script>
    <meta charset="utf-8">
    <title>Piperpal</title>
  </head>
  <body>
    <div id="log"></div>	 
    <script>
	 $(document).ready(function(){
			 
			 setInterval(function(){
					 
					 if (navigator.geolocation) {
						 navigator.geolocation.getCurrentPosition(ajaxCall);         
					 } else{
						 $('#log').html("GPS is not available");
					 }
					 
					 function ajaxCall(position){
						 
						 var latitude = position.coords.latitude;
						 var longitude = position.coords.longitude;
						 var location = window.location.pathname.substr(1);
						 var queryString = window.location.search;
						 var urlParams = new URLSearchParams(queryString);
						 // alert(queryString+":("+latitude+","+longitude+")");
						 $.ajax({
							 url: "https://api.piperpal.com/pull.php", 
									 type: 'POST', //I want a type as POST
                                 data: {'glat' : latitude, 'glon' : longitude, 'location' : location, 'name' : urlParams.get('name'), 'service' : urlParams.get('service'), 'radius' : urlParams.get('radius') },
									 success: function(response) {
										 $('#log').html(response);
										 // alert(response);
								 }
						   });
				   }       
			   },15000);
		   

		 });
    </script>
	  <h2>Documentation</h2>
	  <h3>Location JavaScript API</h3>
	  <h4>Pull</h4>
	  <pre>
	    &lt;script type="text/javascript" src="https://api.piperpal.com/location/json.php?service=Books&glat=37.4375596&glon=-122.11922789999998"&gt;&lt;/script&gt;
	  </pre>
	  <h4>Push</h4>
	  <pre>
	    <span style="color: #ff0000">Example</span>
	    https://api.piperpal.com/location/push.php?name=<span style="color: #ff0000">Google</span>&location=<span style="color: #ff0000">http://www.google.com/</span>&service=<span style="color: #ff0000">Books</span>&glat=<span style="color: #ff0000">37.4375596</span>&glon=<span style="color: #ff0000">-122.11922789999998</span>&paid=<span style="color: #ff0000">50</span>
	  </pre>
	  <p>&copy; 2022 Aamot Software</p>
  </body>
</html>
