<div id="result"></div>
<script>
if(typeof(EventSource) !== "undefined") {
    var source = new EventSource("https://www.piperpal.com/api/location/service/pull.php");
    source.onmessage = function(event) {
      document.getElementById("result").innerHTML += event.data + "<br>";
    };
} else {
    return "Sorry, your browser does not support server-sent events...";
}
</script>