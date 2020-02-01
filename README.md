This program creates a database where the data is "date event" format.
(Ex. 2017-01-02 "Today is New Year"). 
In the "date", the year, month and day are necessarily separated by a hyphen, and the values themselves can be represented arbitrarily within the allowed values. 
0 <= year <= 9999, 1 <= month <= 12, 1 <= day <= 31.
(Year '190' can be written as '190', and as '0190', similar to month and day).
An event is data that comes after a date and a mandatory space, enclosed in quotation marks.
Internal spaces and non-standard characters inside the event are allowed.

When you start the program, you must enter the following command:

 - "ADD" command- 
add data to the Database, after this command, add a date and event separated by a space.
The data must be entered according to the rules written above, otherwise the record will not be added.
The date can be repeated, the event can be repeated, if an existing "date event" pair is added to the Database, this pair is ignored.

 - "Find","Del" commands 
A query after these commands on the Database can be made with additional conditions for the date and for the event.
(Example (date < 2017-01-02 OR date != 2020-1-1) AND (event != "holiiday" AND event != "New Year") 
When requesting certain data, the "Find" and "Del" commands display how much data they found or deleted respectively.
If you do not enter anything after the commands, "Find" will display all events, and "Dell" will delete all events.

