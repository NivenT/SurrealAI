# SurrealAI
Game-playing AI using surreal numbers 

This project was inspired by the first volume [Winning Ways for your Mathematical Plays](https://www.amazon.com/Winning-Ways-Your-Mathematical-Plays/dp/1568811306). It uses surreal numbers to create an AI capable of playing a specific class of games. This is a proof of concept project, and will run slowly on large instances of games.

## Details
* The repo provides an abstract Game class, and lists the requirements for the games this project was made for. 

* In order to change which game you play, you have to edit the code in main.cpp

## Implemented Games
### [Nim](https://www.wikiwand.com/en/Nim)
There is a pile of stars. Players alternate turns removing (1, 2, or 3) stars from the pile. You win when you remove the last star.

<img src="https://github.com/NivenT/SurrealAI/blob/master/screenshots/capture.jpg" alt="Screenshot" width="400" height="300"/>

### [Notakto](http://www.counterwavegames.com/notakto/)
This is essentially, Tic-Tac-Toe, except both players use X. In the original Notakto, you lose if you make 3 X's in a row. In this one, you are not allowed to make 3 X's in a row and lose when you cannot make a move (i.e. all moves would lead to 3 X's in a row).

### GameSum
This represents the sum of two arbitrary games. Each turn, a player chooses which game to make a move in and then chooses which move to make. When a player can no longer make a move in either game, she loses.

<img src="https://github.com/NivenT/SurrealAI/blob/master/screenshots/capture2.jpg" alt="Screenshot" width="400" height="500"/>

^^^ Sum of Notakto and Nim
