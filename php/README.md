# ARDUINO CLIMATE CONTROL

## Control Codes

```
Code Arduino pin Action
999 -- Close all output pins

Servo
10-90 5 Control servo angle 0-90 deg.

Vents
190 6 Face vent
191 7 Face and feet vents
192 8 Feet vent
193 9 Feet and windows vents
194 10 Windows vents
195 -- All vents offs

Airflow
196 11 Circulate air inside
197 12 Circulate air from outside
AC
198 13 AC on
199 -- AC off

Fan
300 Fan Off. AC Off
325 A1 Fan speed 1 (min)
350 A2 Fan speed 2
375 A3 Fan speed 3
400 A4 Fan speed 4 (max)
```

## Control Dashboard

• Address: http://127.0.0.1 or http://localhost
• Web server must be running. Currently set to start automatically. If not, click on icon on desktop
• Open dashboard icon on desktop

## Troubleshooting

1. If the dashboard hangs or loading for long. Open command prompt and type TASKKILL /IM /F apache* <ENTER> TASKKILL /IM /F uwamp* <ENTER> then start the uWamp server again
1. If nothing is happening when you click dashboard buttons
1. Shutdown server (TASKKILL /IM /F apache* <ENTER> TASKKILL /IM /F uwamp* <ENTER>)
1. run putty.exe in C://uwamp/www, select SERIAL radio button, change to COM3 and click OPEN
1. You can test the serial by typing the codes above on the putty terminal that opens
1. Arduino source code is included if you need to reassign pins or add new functions

```

```
