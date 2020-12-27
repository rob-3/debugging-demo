# Running the Program
Simply run with `$ gcc main.c && ./a.out`

# Description
This program is a simple piece of software designed for managing a hotel. This
particular hotel has 17 rooms, each of which can hold one guest. The hotel and
guests are represented with the Hotel and Guest `struct`s. 

The program should print a summary of all occupied room numbers and the name of
the guest in those rooms. Then, it should prompt the user to select one of 4
options.

1. **Check in**: This option should prompt the user for guest details and a room
   number and then add a new guest to the given room. It can be assumed that a
   valid name and 10-digit phone number are given for the purposes of this
   program.
2. **Check out**: This option should prompt the user for a room number and then
   remove the guest in the given room.
3. **Guest info**: This option should prompt for a room number and then print
   the name and phone number of the guest in that room.
4. **Exit**: Save the current hotel data to `hotel.txt` and exit.

# Problems
1. The code does not compile.
2. When viewing certain phone numbers with option "Guest Info", the phone
   numbers are not displayed correctly. Furthermore, after exiting, these wrong
   phone numbers are stored instead of the correct ones.
3. The check out option doesn't seem to work at all. It should remove the person
   in the given room number from the hotel so they are not printed in the next
   prompt.
