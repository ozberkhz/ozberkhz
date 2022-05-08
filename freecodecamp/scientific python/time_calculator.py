def add_time(start, duration, day_input = 0):
    
    weekday = { "Monday" : 0,
    "Tuesday" : 1,
    "Wednesday" : 2,
    "Thursday" : 3,
    "Friday" : 4,
    "Saturday" : 5,
    "Sunday" : 6 }
    
    duration = duration.split(":")
    start = start.split()
    start[0] = start[0].split(":")

    # calculating the total amount of hours and minutes in the system
    sum_of_hours = int(start[0][0]) + int(duration[0])
    sum_of_mins = int(start[0][1]) + int(duration[1])
    
    # adding the excess minutes to hours
    sum_of_hours += sum_of_mins // 60
    
    # for convenience, we think of pm as 12 hours and presuming we start from 0.00 and move forward 
    if start[1] == "PM":
        sum_of_hours += 12
    
    # since we start from 0.00 AM, every 24 hours a day passes
    days_passed = sum_of_hours // 24
    
    # calculating the digits that will be displayed
    clock_hour = sum_of_hours % 12
    if clock_hour == 0:
        clock_hour = 12
    clock_minute = sum_of_mins % 60
    
    # calculating the meridiem
    meridiem = " AM" if sum_of_hours % 24 < 12 else " PM"
    
    hour = str(clock_hour) + ":" + ("0" if clock_minute < 10 else "") + str(clock_minute) + meridiem
    days_later = ((" ({} days later)".format(days_passed)) if days_passed > 1 else "") + (" (next day)" if days_passed == 1 else "") 
    day = ""
    
    if day_input != 0:
        day_input = day_input[0].upper() + day_input[1:].lower()
        day += ", " + list(weekday.keys())[(weekday[day_input] + days_passed) % 7] #enumerating the days then cycling through the week
          
    return hour + day + days_later 

# print(add_time("8:16 PM", "10000:45", "tuesdaY"))

hour = input("Enter the hour: ")
minutes = input("Enter the amount of time that passed: ")
day = input("Enter the current day: ")

print()

print(add_time(hour, minutes, day))
