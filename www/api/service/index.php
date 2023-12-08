<!DOCTYPE html>
<html lang="en">
  <head>
    <script src="http://code.jquery.com/jquery-latest.min.js"></script>
    <meta charset="utf-8">
    <title>Piperpal</title>
   </head>
   <body>
    <div id="log"></div>
     <script type="text/javascript" src="http://api.piperpal.com/service/json.php?glat=37.4375596&glon=-122.11922789999998"></script>
     <script type="text/javascript" src="http://api.piperpal.com/location/json.php?service=<?php echo $_GET['service']; ?>&name=<?php echo $_GET['name']; ?>&glat=37.4375596&glon=-122.11922789999998"></script>
    <script>      
    $(document).ready(function(){      
       function pullTags(){
	 if (navigator.geolocation) {
	   navigator.geolocation.getCurrentPosition(ajaxCall);         
	 } else{
	   $('#log').html("GPS is not available");
	 }
	 function ajaxCall(position){
	   var latitude = position.coords.latitude;
	   var longitude = position.coords.longitude;
	   var service = <?php echo $_GET['service']; ?>;
	   var name = <?php echo $_GET['name']; ?>;
	   $.ajax({
	     url: "http://piperpal.com/api/location/pull.php", 
		 type: 'GET', //I want a type as POST
		 data: {'glat' : latitude, 'glon' : longitude, 'service' : service, 'name' : name },
		 success: function(response) {
		 document.write (response);
	       }
	     });
	 }       
       }
       pullTags();
       // setInterval(pullTags,1800000) 
     });
     </script>
     <form method="GET" action="index.php">
     <input type="text" name="name" />
     <select name="service">
     <script language="JavaScript">
     var srv = JSON.parse(services);
       for (i=0; i < srv.services.length; i++) {
         document.write(srv.services[i].distance + "<option value='" + srv.services[i].service + "'>" + " " + srv.services[i].service + "</option>\n");
       }
     </script>
     </select>
     <input type="submit" value="Locate" />
     </form>
     <script language="JavaScript">
     var loc = JSON.parse(locations);
       for (i=0; i < loc.locations.length; i++) {
         document.write("<h3>" + loc.locations[i].name + "</h3><p><a href='" + loc.locations[i].location + "'>" + loc.locations[i].location + "</a><br />" + loc.locations[i].distance + "<br />" + loc.locations[i].service + "</p>\n");
       }
     </script>
    <p>Check out <a href="berkeley.html">Berkeley</a>, <a href="oslo.html">Oslo</a> and <a href="http://piperpal.com/">Piperpal</a>.</p>
  </body>
</html>
