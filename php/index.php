<?php include('header.php'); ?>

    <div class="container-panel">
        <div class="header">
            <span class="header-title">Climate</span>

        </div>
        <div class="fan-speed">
            <a href="#" id="0" class="p-down"><img src="static/img/fan1.png" class="fan-down"/></i></a>

            <!--		<div class="fan-active fan-bar-one"></div>-->
            <div class="fan-active fan-bar-two"></div>
            <div class="fan-active fan-bar-three"></div>
            <div class="fan-active fan-bar-four"></div>
            <div class="fan-active fan-bar-five"></div>
            <img src="static/img/bar.png" class="fan-bar"/>
            <a href="#" id="0" class="p-up right"><img src="static/img/fan2.png" class="fan-up"/></i></a>
        </div>


        <div class="ac-ctrl ac-panel">
            <a href="#" id="196" class="in-air switches"><img src="static/img/in-air.png"></a>
            <a href="#" id="197" class="out-air switches"><img src="static/img/out-air.png"></a>

            <a href="#" id="198" class="ac switches"><img src="static/img/ac.png"/></a>
        </div>

        <div class="heating-panel">

            <a href="#" id="10" class="servoOnOff servoOn"><i class="fa fa-chevron-circle-down"></i></a>
            <!--a href="#" class="servoReset"><i class="fa fa-square-o"><span class="servo-pos"></span></i></a-->

            <input type="text" class="span2 servoSlider" value="" data-slider-min="10" data-slider-max="90"
                   data-slider-step="10" data-slider-value="10" data-slider-id="RC" id="R" data-slider-tooltip="hide"
                   data-slider-handle="square"/>

            <a href="#" id="90" class="servoOnOff servoOff" style="color:#D9534F"><i
                    class="fa fa-chevron-circle-up"></i></a>

        </div>


        <div id="clock"></div>

        <div class="switches-panel">
            <button id="190" class="btn btn-warning switches"><img src="static/img/face.png"/></button>
            <button id="191" class="btn btn-warning switches"><img src="static/img/face_feet.png"/></button>
            <button id="192" class="btn btn-warning switches"><img src="static/img/feet.png"/></button>
            <button id="193" class="btn btn-info switches"><img src="static/img/feet_windows.png"/></button>
            <button id="194" class="btn btn-info switches"><img src="static/img/windows.png"></button>
            &nbsp;
            &nbsp;
            <button id="999" class="btn btn-danger switches"><i class="glyphicon glyphicon-off"
                                                                style="font-size:76px"></i></button>
        </div>
    </div>
<?php include('footer.php'); ?>