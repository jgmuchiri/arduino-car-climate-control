
<script type=text/javascript src="static/js/jquery.min.js"></script>
<script type=text/javascript src="static/js/global.js"></script>
<script type=text/javascript src="static/js/clock.js"></script>
<script type=text/javascript src="static/js/bootstrap-slider.min.js"></script>
<script type=text/javascript>
    $(window).load(function() {
        setTimeout(function(){
                //$("#spinner").fadeOut(4000);
                $('#flash').fadeOut('fast');
            },7000);
    });
        // With JQuery
        $('#ex1').slider({
            formatter: function(value) {
                return 'Current value: ' + value;
            }
        });
    </script>
</body>
</html>