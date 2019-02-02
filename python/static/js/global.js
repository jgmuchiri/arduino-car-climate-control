function setColor(val) {
    var r = (parseInt(val));
    var g = (255 - parseInt(val));
    var b = (255 - parseInt(val) + 30);
    return "rgb(" + r + "," + g + "," + b + ")";
}
function headTime() {
    var monthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
    var dayNames = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]

// Create a newDate() object
    var newDate = new Date();
// Extract the current date from Date object
    newDate.setDate(newDate.getDate());
// Output the day, date, month and year
    $('#Date').html(dayNames[newDate.getDay()] + ", " + newDate.getDate() + ' ' + monthNames[newDate.getMonth()] + ' ' + newDate.getFullYear());

    setInterval(function () {
        // Create a newDate() object and extract the seconds of the current time on the visitor's
        var seconds = new Date().getSeconds();
        // Add a leading zero to seconds value
        $("#sec").html(( seconds < 10 ? "0" : "" ) + seconds);
    }, 1000);

    setInterval(function () {
        // Create a newDate() object and extract the minutes of the current time on the visitor's
        var minutes = new Date().getMinutes();
        // Add a leading zero to the minutes value
        $("#min").html(( minutes < 10 ? "0" : "" ) + minutes);
    }, 1000);

    setInterval(function () {
        // Create a newDate() object and extract the hours of the current time on the visitor's
        var hours = new Date().getHours();
        // Add a leading zero to the hours value
        $("#hours").html(( hours < 10 ? "0" : "" ) + hours);
    }, 1000);

}
function setFanSpeed(speed) {
    //fan control speeds
    //300- stop, 325-speed 1, 350-speed 2, 375-speed 3, 400-speed 4
    $.ajax({
        url: '/controls',
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
    var sp2 = $('.fan-bar-two')
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
    //Header
    headTime();
    //FAN CONTROL
    var fanSpeed = 300; //get this from db

    var fanUpBtn = $('.p-up');
    var fanDownBtn = $('.p-down');

    //assign initial fan values
    fanUpBtn.attr('id', fanSpeed);
    fanDownBtn.attr('id', fanSpeed);

    //initialize fan
    setFanSpeed(fanSpeed);
    setFanIndicator(fanSpeed);

    //increase fan speed
    $(fanUpBtn).click(function () {
        //increment speed
        var speed = $(this).attr('id');
        if (speed >= 400) {
            fanSpeed == 400;
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
            fanSpeed == 300;
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
    //initial speed. get from database from last state

    //control servo up
    var servoPos = $('.servo-pos').text(10);

    //increase airflow
    $('.servoUp').mousedown(function () {
        var svUp = $(this).attr('id');
        var nSvUp = 10;
        if (svUp >= 10) {
            nSvUp = parseInt(svUp) + 2;
        }
        if (nSvUp > 90) {//prevent from going over 90 deg
            nSvUp = 90;
        }

        $(this).attr('id', nSvUp);
        $('.servoDown').attr('id', nSvUp);

        servoPos.css('color', setColor(svUp));

        $.ajax({
            url: '/controls',
            data: {'value': svUp},
            type: 'POST',
            success: function (response) {
                console.log(response);
                servoPos.text(svUp);
                $('.progress-hot .progress-bar').css('width', parseInt(svUp));
                $('.progress-cold .progress-bar').css('width', parseInt(svUp) - parseInt(10));
            },
            error: function (error) {
                //console.log(error);
            }
        });
    });
    //minimize airflow
    $('.servoDown').click(function () {
        var svUp = $(this).attr('id');
        var nSvUp = 10;
        if (svUp > 10) {
            nSvUp = parseInt(svUp) - 2;
        }
        if (nSvUp > 90) {
            nSvUp = 90;
        }

        $(this).attr('id', nSvUp);
        $('.servoUp').attr('id', nSvUp);
        servoPos.css('color', setColor(svUp));

        $.ajax({
            url: '/controls',
            data: {'value': svUp},
            type: 'POST',
            success: function (response) {
                servoPos.text(svUp);

            },
            error: function (error) {
                //console.log(error);
            }
        });
    });

    //CLOSE VALVE
    $('.servoReset').click(function () {

        $('.servoUp').attr('id', 10);
        $('.servoDown').attr('id', 10);
        servoPos.text(10);
        $.ajax({
            url: '/controls',
            data: {'value': 1},
            type: 'POST',
            success: function (response) {

            },
            error: function (error) {
                //console.log(error);
            }
        });
    });

    //SWITCHES
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
            url: '/switches',
            data: {'switcher': switcher},
            type: 'POST',
            success: function (response) {
                console.log(response);
            }
        });
    });
});

