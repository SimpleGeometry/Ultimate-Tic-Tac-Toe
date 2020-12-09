# CS 126 Final Project -- Ultimate TTT Game/AI

Hey, welcome to my Ultimate Tic Tac Toe project for my CS 126 class at UIUC! Feel free to take a look around.

This project involved building a backend and frontend for the game of Ultimate Tic Tac Toe, as well as an AI for the game. Everything is implemented in C++, including the frontend (using the Cinder library).

If you've never heard of Ultimate Tic Tac Toe before, check out [this link](https://mathwithbaddrawings.com/ultimate-tic-tac-toe-original-post/). The basic idea is that it's like regular Tic Tac Toe, but each square inside the board has its own smaller Tic Tac Toe board, which introduces enough complexity to make the game interesting, I think.

Take a look at my project proposal for a bit more background on why I decided to choose this for my project topic, and various other details (e.g. a development timeline).

UI design inspiration: http://bejofo.net/ttt and https://ultimate-t3.herokuapp.com/local-game.

## Running the application

Cinder setup (adapted from Jason's Campuswire post):
1. This project requires Cinder, which you can download [here](https://libcinder.org/download). Download v0.9.2 for your platform. Extract the downloaded item into a folder (we will refer to this folder as ~/Cinder). 
2. Build: Only need to do this once per machine (may take a bit). You can open the ~/Cinder folder in CLion and click the green build button, or build it by command line (https://www.libcinder.org/docs/guides/linux-notes/ubuntu.html for Ubuntu, may be similar for other OSes).
3. Go to ~/Cinder/my-projects (not sure if you need to make this folder yourself or it comes by default) and once you're inside, clone this repo.
4. Run CMake on this project (easiest if you have CLion or maybe some other IDE, when developing I used CLion and just clicked the run button, which auto-built the project).

I've only tested this on Ubuntu using CLion, unfortunately, so I can't 100% guarantee that it will work on other platforms. However, it probably should be fine on other platforms (or if there are any issues, they should be resolvable with some minor modifications). The only thing is that it might be a bit hard if you're not familiar with CMake and don't have CLion or a similar IDE (I'm not familiar either so I can't give much help, apologies :P).

In any case, I hope you find the game and AI interesting! I haven't optimized the AI very much, so it could definitely be better with some tuning of the heuristics and more optimized search, but I think I'm quite happy with where it currently is. Please message me if you have any questions or comments!
