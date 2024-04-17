# Event Planner
 Program which simulates event organisation and participation

-The information about events is in a text file. Each Event has an organiser, a name,  a description, a location (latitude and longitude) and a date. The file is manually created and read when the application starts.

-Another file contains information about people. Each Person has a name, a location (latitude and longitude) and an organiser status. These are read when the application starts

-When the application is launched, a new window is created for each person, having as title the person's name. The person's location will also be shown. The window will show all events, sorted by date, with all their information, except the description. For organisers, the events organised by therm are shown with a green background.

-A checkbox will allow the persons to see only the events near them (at most 5 units away). The events' and persons' distance is calculated using Euclidean distance formula. Chceking the button will show only events near the person and unchecking will show all events.

-Organisers can add new events, by inputting the necessary information. The organiser is automatically set. The operation fails if there is another event with the same name and location.

-For a person who is not an organiser, when an event is selected in the list, its description will be shown. The person can indicate that he/she wants to attend the selected event by clicking a button "Going". This button will be disabled if the person has already indicated that he/she is going to the events. For an organiser, when an event is selected, two other controls will show its description and the list of persons going to the event.

-Another window will show the most popular events, by number of persons attending them. For each event, the event's name, description, location, date, time and number of persons attending will be shown.

-When a modificatoin is made by any person (organiser or not), everyone will see it automatically. The window with the popular events will also be updated automatically. For this feature the Observer design pattern is used.

-When the application finishes, all events are saved to the file, including the persons attending for each event.