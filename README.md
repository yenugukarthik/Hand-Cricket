# Hand-Cricket
game code in C that simulates a cricket match with a "super over" scenario.
Initialization: Initializes various components such as switches, displays, and keys.


Functions:
random(): Generates a pseudo-random number based on a linear congruential generator algorithm.
switches(): Reads the values from switches and determines which switch is activated.
write_digit(), write_pixel(), write_char(), etc.: Functions to write characters, pixels, and digits on the VGA display.
clear_display(), clear_screen(), clear_image(): Functions to clear the display or specific areas of it.
write_string(): Writes a string of characters onto the VGA display.
head() and tail(): Functions to draw the head and tail of a coin flip on the display.
write_seg(): Writes the score on a segment display.


Main Function:
Initializes the display and prompts the user to choose heads or tails.
Simulates a coin toss by flipping a virtual coin (drawing heads or tails on the display).
Determines the outcome of the toss (win or lose) and sets the parameters for the next phase.
Displays the outcome of the toss and prompts the user to continue.
Generates a target score randomly for the user to chase.
Displays instructions for batting.
Allows the user to select a switch and press the button to simulate each delivery.
Updates the score based on the user's choice and displays the outcome.
Determines the final result of the match and displays it along with the scores.
