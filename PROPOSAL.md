#Final Project Proposal

##Project Overview
The project I would like to do for the final project is an implementation of 
Ultimate Tic Tac Toe 
(rules [here](https://mathwithbaddrawings.com/ultimate-tic-tac-toe-original-post/)),
together with an AI for the game. As stated in the requirements,
this project will include the backend as well as the frontend, with the goal of
the frontend component being to have a clean and minimalistic UI for playing
the game and interacting with options/menus. The game will have options for
human vs. human, human vs. AI, and AI vs. AI.

##Background Knowledge
I've been pretty interested in various forms of game AI, and I've studied a bit
on the various techniques that are typical for implementing a classical/non-ML
AI on 2-player perfect-information games like Ultimate TTT. Some of the things
I've looked at a bit are 
[Pascal Pons's perfect Connect 4 AI](http://blog.gamesolver.org/)
and the [Chessprogramming Wiki](https://www.chessprogramming.org/Main_Page). I
also tried to implement a good tree-search-based AI for the Mine-opoly competition,
but I didn't have enough time to make it better than a simple heuristic-based
AI, so I'm hoping I will get a chance to explore this more extensively here.

##Preliminary Timeline
Week 1: Implementation of the game's backend, state tracking, etc.

Week 2: Frontend implementation, AI interfacing with rest of backend (no complex 
logic or internal structure for AI yet, just feeding in random moves), and menus
and backend for different modes of play.

Week 3: Implementation of tree-search AI.

##Stretch Goals
The base project involves the following:
* Backend:
    * Game implementation
    * AI
    * Support for selecting different modes of play (human vs. human, human vs. AI, etc.)
* Frontend:
    * Displaying the game/processing moves inputted by the player(s)
    * Menu for selecting modes of play

Possible extensions include:
* Improved AI (can always make it better, faster, more optimized, etc.)
* Game engine visualization (showing which moves the engine/AI thinks is the best), 
similar to lichess.org's [analysis board](https://lichess.org/analysis).