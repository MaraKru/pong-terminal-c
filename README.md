# Terminal Pong Game in C

## A classic Pong arcade game implementation using ncurses for terminal-based multiplayer action

### Project Overview

This classic Pong arcade game was developed as a collaborative academic project. The game features real-time terminal graphics, two-player controls, and competitive scoring - all rendered in ASCII art using the ncurses library.


### My Contribution

* Graphics rendering (draw): implemented the terminal visualization system using ncurses, creating the court borders, rackets, ball, and score display in ASCII art
* Score management (do_score): developed the scoring logic with win conditions and score display formatting
* Physics Assistance: collaborated on the ball physics implementation (step), helping debug collision responses and movement logic


### Quick Start

*Prerequisites*
* GCC compiler
* ncurses library
* Linux/macOS terminal or WSL (Windows)

```bash
gcc -o pong pong.c -lncurses
./pong
```


### Technical Stack

C - NCurses - Terminal Graphics - Real-time input


### Features

- Two-player local multiplayer
- Real-time terminal graphics with ASCII art
- Live score display
- Realistic ball physics with angle-based bounces


### Game Controls

| Player | Move up | Move down |
|--------|---------|-----------|
| Left   | A key   | Z key     |
| Right  | K key   | M key     |


### Technical Implementation

**Core Mechanics**

1. Real-time game loop
2. Collision Detection
3. Ball Physics
4. Score Management


### Key Functions

```bash
int collision();  // detect ball collisions
int step();       // update ball position
void draw();      // render game state
void polling();   // main game loop
```


### My Engineering Insights

This was my first group project in C. At that time, I was relatively new to the language, so my portion of work took a lot of time and effort. The key lesson I learned was about collaborating with someone significantly more experienced. 
I discovered that taking initiative in work isn't embarrassing or wrong, even when you're obviously a beginner. That's exactly how skills are developed. My team lead took on one of the most complex parts — the ball physics. While we discussed the implementation together and I tried my best to assist, the bounce mechanics implementation was a true revelation for me in terms of mathematical modeling in games.
