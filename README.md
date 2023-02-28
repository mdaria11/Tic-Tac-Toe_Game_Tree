This is a program that prints out all outcomes of a tic-tac-toe game and winning moves. It mainly has 3 features: the first feature prins out all the possible outcomes of a game; the second feature makes an and-or tree based on possible outcomes; the third feature makes a minimax tree.

To use the first feature (-c1), you'll need to write your game and next player to make a move in a file (eg. game.in) like this:

      O
      - O X
      O X X
      O X -

In this example, in the first line you specify the player that needs to move (in this case O), and then how the game looks from the moment you want to print all possible outcomes (- is for free spaces).


To execute the program follow this commands:

      make build
      ./minimax -c1 [input file] [output file]
      
