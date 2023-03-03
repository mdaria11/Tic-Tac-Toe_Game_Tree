This is a program that prints out all outcomes of a tic-tac-toe game and winning moves. It mainly has 3 features: the first feature prins out all the possible outcomes of a game; the second feature makes an and-or tree based on possible outcomes; the third feature makes a minimax tree.

To use the first feature, you'll need to write your game and next player to make a move in a file (eg. game.in) like this:

      O
      - O X
      O X X
      O X -

In this example, in the first line you specify the player that needs to move (in this case O), and then how the game looks from the moment you want to print all possible outcomes (- is for free spaces).
      
For the second feature, the input file has the same format as the first feature.

For the third feature, in the input file you need to specify the maximum level of the tree, the number of child-nodes the parent-node ( if the parent-node has 3 kids it should be (3) ) and for leaf nodes you need to specify their value like this [x].
An example of input file is:

      5
      (3)
      (2) (2) (3)
      (2) (1) (2) [7] (1) (1) (1)
      (2) (3) (1) (2) [6] (1) (2) [9]
      [5] [6] [7] [4] [5] [3] [6] [9] [5] [8] [9]

To execute the program follow this commands:

      ./minimax [-c1|-c2|-c3] [input file] [output file]
      
Use -c1 for the first feature, -c2 for the second one and -c3 for the third one. 
