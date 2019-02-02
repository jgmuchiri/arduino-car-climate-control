function setColor(val) {
    var r = (parseInt(val));
    var g = (255 - parseInt(val));
    var b = (255 - parseInt(val) + 30);
    return "rgb(" + r + "," + g + "," + b + ")";
}


function setFanSpeed(speed) {
    //fan control speeds
    //300- stop, 325-speed 1, 350-speed 2, 375-speed 3, 400-speed 4
    $.ajax({
        url: 'control.php?value='+speed,
        data: {'value': speed},
        type: 'POST',
        success: function (response) {
            console.log(response);

        },
        error: function (error) {
            //console.log(error);
        }
    });
}
function setFanIndicator(speed) {
    var sp1 = $('.fan-bar-one');
    var sp2 = $('.fan-bar-two');
    var sp3 = $('.fan-bar-three');
    var sp4 = $('.fan-bar-four');
    var sp5 = $('.fan-bar-five');

    switch (speed) {
        case 300://1
        sp1.show();
        sp2.hide();
        sp3.hide();
        sp4.hide();
        sp5.hide();
        break;
        case 325://2
        sp1.show();
        sp2.show();
        sp3.hide();
        sp4.hide();
        sp5.hide();
        break;
        case 350://3
        sp1.show();
        sp2.show();
        sp3.show();
        sp4.hide();
        sp5.hide();
        break;
        case 375: //4
        sp1.show();
        sp2.show();
        sp3.show();
        sp4.show();
        sp5.hide();
        break;
        case 400: //5
        sp1.show();
        sp2.show();
        sp3.show();
        sp4.show();
        sp5.show();
        break;

    }
}

$('.document').ready(function () {

    $('#clock').tzineClock();
    setFanSpeed(fanSpeed);
    setFanIndicator(fanSpeed);
    //FAN CONTROL
    var fanSpeed = 300; //POST this from db

    var fanUpBtn = $('.p-up');
    var fanDownBtn = $('.p-down');

    //assign initial fan values
    fanUpBtn.attr('id', fanSpeed);
    fanDownBtn.attr('id', fanSpeed);


    //increase fan speed
    $(fanUpBtn).click(function () {
        //increment speed
        var speed = $(this).attr('id');
        if (speed >= 400) {
            fanSpeed = 400;
        } else {
            fanSpeed = parseInt(speed) + 25;
        }

        fanUpBtn.attr('id', fanSpeed);

        //set new values
        fanUpBtn.attr('id', fanSpeed);
        fanDownBtn.attr('id', fanSpeed);

        //set new fan speed
        setFanSpeed(fanSpeed);
        //set indicator
        setFanIndicator(fanSpeed);
    });

    //decrease fan speed
    $(fanDownBtn).click(function () {
        $('.fan-bar-two').show();
        //increment speed
        var speed = $(this).attr('id');
        if (speed <= 300) {
            fanSpeed = 300;
        } else {
            fanSpeed = parseInt(speed) - 25;
        }


        fanUpBtn.attr('id', fanSpeed);

        //set new values
        fanUpBtn.attr('id', fanSpeed);
        fanDownBtn.attr('id', fanSpeed);

        //set new fan speed
        setFanSpeed(fanSpeed);
        //set indicator
        setFanIndicator(fanSpeed);
    });
    //initial speed. POST from database from last state

    //control servo up
    var servoPos = $('.servo-pos').text(10);

    $('.servoOnOff').click(function(){
     var value = $(this).attr('id');

     $.ajax({
        url: 'control.php?value='+value,
        data: {'value': value},
        type: 'POST',
        success: function (response) {
            console.log(response);
        },
        error: function (error) {
            console.log(error);
        }
    });
 });

    var r = $('#R').slider().on('slideStop',function(event) {
        var value = $(this).attr('value');
        $.ajax({
            url: 'control.php?value='+value,
            data: {'value': value},
            type: 'POST',
            success: function (response) {

            },
            error: function (error) {
                console.log(error);
            }
        });
    }).data('slider');




    //CLOSE VALVE
    $('.servoReset').click(function () {

        $('.servoUp').attr('id', 10);
        $('.servoDown').attr('id', 10);
        servoPos.text(10);
        $.ajax({
            url: 'control.php?value='+value,
            data: {'value': 1},
            type: 'POST',
            success: function (response) {

            },
            error: function (error) {
                //console.log(error);
            }
        });
    });

    //switches
    //190-194:vents 196:in-circulation 197: out-circulation
    $('.switches').click(function () {
        var switcher = $(this).attr('id');
        //change the state to 'next is off'
        if (switcher == 198) {
            $(this).attr('id', 199);
        }

        //change the state to 'next is on'
        if (switcher == 199) {
            $(this).attr('id', 198);
        }

        $.ajax({
            url: 'control.php?value='+switcher,
            data: {'value': switcher},
            type: 'POST',
            success: function (response) {
                console.log(response);
            }
        });
    });
});

