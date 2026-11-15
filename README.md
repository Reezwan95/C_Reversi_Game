# Reversi (Othello) in C, against a computer opponent

A console Reversi (Othello) game where you play against a computer AI. The program:

- draws the board;
- checks that every move follows the rules (a move must flip at least one line of the opponent's pieces);
- flips captured pieces in all eight directions;
- handles turns where a player has no legal move;
- keeps score and announces the winner.

## Files

| File | Purpose |
|---|---|
| `reversi.c` | Game loop, move validation, flipping logic, the computer's move choice, scoring |
| `reversi.h` | Function declarations and constants |
| `liblab8part2.h`, `liblab8part2.a` | Course-provided helper library the game links against |

## Build and play

```bash
gcc reversi.c liblab8part2.a -o reversi
./reversi
```

The provided static library must match your platform.

Written in C for a first-year programming course at the University of Toronto.

---
Reezwan-Us Sami · [Portfolio](https://reezwan95.github.io)
