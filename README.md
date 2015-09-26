# MapMaker
Part of a larger ongoing personal project. Creates a randomized 2D grid of different terrain types based on neighbor lists.

Some notes:
  - A different map is generated each time the program is run.
  - Each terrain type has a list of valid terrain neighbors. Generation is based off of these lists and their intersections.
  - The program also reads in item & unit database files with which it creates units and places them on the map.
  - The map is displayed as a grid of numbers in the console window, with the number representing its terrain type; units are represented by the first two letters of their name.
  - The project is, to the best of my knowledge, compliant with C++98 standard
