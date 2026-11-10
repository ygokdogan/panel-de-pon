# Panel de Pon · C Terminal Game

[Türkçe](README.md) | **English**

A terminal puzzle game written in C, inspired by the mechanics of Panel de Pon. Players swap cells, clear runs of matching symbols, and make room before the board reaches the top.

The game interface is in Turkish. No external libraries are required.

## Game mechanics

- **Configurable board:** Each dimension can be set from 1 to 20.
- **Five symbols:** `*`, `/`, `+`, `%`, and `O`. A dot (`.`) represents an empty cell.
- **Two starting modes:** Random initialization or manual input in control mode.
- **Match clearing:** Clear a run of at least three identical symbols extending right or down from the selected cell.
- **Gravity:** Symbols fall into empty spaces after a move.
- **Rising board:** A random row is added at the bottom after a valid swap.
- **Counters:** The number of swaps and total cleared symbols are displayed.

## Build and run

Open a **macOS / Linux** terminal with GCC or Clang installed, navigate to the project directory, and run:

```sh
cc -std=c11 -Wall -Wextra panel_de_pon.c -o panel-de-pon
./panel-de-pon
```

On Windows, use WSL. Native Windows builds require adjustments because the source uses `unistd.h` and `sleep()`.

## How to play

1. Choose `1` for game mode or `2` for control mode at startup.
2. Enter the board dimensions separated by a space, such as `8 6`.
3. Select an action from the menu and enter the requested coordinates.

| Menu | Action | Example input |
| --- | --- | --- |
| `1` | Swap two cells | `7,2 7,3` |
| `2` | Clear matching symbols | `7,1` |
| `0` | Quit | No coordinates needed |

**Coordinates use the `row,column` format and start at 1.** Do not include parentheses; separate two cell coordinates with a space. Rows are numbered from top to bottom and columns from left to right. Swaps are intended for two occupied cells that are horizontally or vertically adjacent.

Matches are not cleared automatically: select `2` from the menu. For example, given this row:

```text
    1 2 3 4 5 6
7   * * * + O %
```

Entering `7,1` clears the first three symbols. Matching scans only **right and down**, so select the leftmost or topmost cell of a run. If both directions contain a match of at least three symbols, the longer run is cleared; ties favor the horizontal run.

After a swap, a new row pushes the board upward. The game ends when a symbol remains in the top row. There is an approximately three-second delay between move displays.

### Control mode

Control mode lets you manually enter the initially occupied lower section of the board to try specific matches. Cells are requested from the bottom row upward, moving left to right within each row. These input prompts use **0-based indices**, while gameplay coordinates are **1-based**. Intermediate displays are not cleared in control mode; rows added after swaps are still random.

## Project structure

```text
.
├── panel_de_pon.c  # Game loop, board, and move handling
├── screenshots/   # Gameplay screenshots
├── .gitignore     # Local files and build artifacts
├── README.md      # Turkish documentation
└── README.en.md   # English documentation
```

## Technical notes and current limitations

The board is stored in a two-dimensional character array. Initial placement and new rows use `rand()`, seeded with `time(NULL)`. The game flow is in `main()`, board rendering in `printBoard()`, row insertion in `addRandomRow()`, and screen clearing in `clearScreen()`.

This version is a basic course project. Keep the following limitations in mind:

- Input validation does not robustly handle nonnumeric or incomplete input.
- The swap code may still execute after an adjacency or empty-cell check reports an error. Selecting the same cell twice is also allowed.
- Out-of-bounds coordinates during a clearing action may cause invalid memory access; keep coordinates within the board.
- Matches are not automatically detected across the board, and there is no chain-clearing system.

The source code's existing behavior has been preserved. This repository demonstrates array operations, terminal input, and basic game logic.
