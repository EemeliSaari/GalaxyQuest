# Galaxy Quest

Simple game implemented with C++ and Qt. Game was done in the fall 2017 in a group of two as part of advanced programming course (TIE-02401) in Tampere University of Technology. 

Courses main theme was design by contract and our task was to implement code to work with courses code and interface they provided. Courses code covers the namespaces `Common` and `Course`.

Code has been commented using the doxygen format.

    Disclaimer: Courses code isn't provided in this repository so the game is not working as it is.

## About

Game is turn-based single player space themed game. Players purpose is to keep up the galactic economy by doing various missions to its habitats.

**Activities:**
- Rescue cargo ships
- Rescue people from various dangers they phase.

By doing these missions player gains points that are added to highscore at the end of the game.

**Movement:**

Player has the advanced quantum engine that they use for movement. Quantum engine increases the uncertainty each time move is initialised. Uncertainty marks a percentage chance that player may end up in a random location.

**Map:**

Map is generated using the `QuantumMap` class. Class is based in a simple algorithm that generates connections from `StarSystems` interface provided by course.

## Images

1. Start screen of the game

![start](/images/start.png)

2. Start of the game

![game start](/images/game_start.png)

3. Gameplay

![gameplay](/images/gameplay.png)

4. Highscore

![highscore](/images/highscore.png)
