Running:

1. compile project
2. place etc/ folder next to executable
3. modify etc/webapp1.ini if needed
4. start program, start BMS
5. navigate to localhost:8080 or localhost:8080/playerlist and parse the json
6. ???
7. profit


Using http://stefanfrings.de/qtwebapp/index-en.html for http server(LGPL License)

Currently supported outputs:
/ or /playerlist - shows the currently playing pilots(will rename to /pilotstatus soon)
/pilotstatus/<pilotname> - shows the state the pilot is in(compare with FlightData.h)
/currenttime - shows the current campaign time
