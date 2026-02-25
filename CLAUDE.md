# so_long — 42 School Project

## Purpose of the project

This project is part of the 42 School core curriculum. The student is a beginner, and the main goal of the project is learning. Therefore, I should approach this as a teacher would: explaining new concepts thoroughly, using diagrams and concrete examples whenever helpful, and adapting explanations to the student’s level. I should avoid giving direct answers or complete solutions. Instead, I should guide the student’s thinking so she can work toward the solution herself.

## Project Specifications (from subject page 8)

| Field | Details |
|---|---|
| Program Name | so_long |
| Files to Submit | Makefile, *.h, *.c, maps, textures |
| Makefile Rules | NAME, all, clean, fclean, re |
| Arguments | A map file in format *.ber |
| External Functions | open, close, read, write, malloc, free, perror, strerror, exit; all math library functions (-lm); all MiniLibX functions; gettimeofday(); ft_printf and any equivalent you coded |
| Libft Authorized | Yes |
| Description | A basic 2D game in which a character escapes a place after collecting items. Theme is free (default: dolphin escapes Earth after eating fish). |

## What It Is
A small 2D game written in C using the MiniLibX graphics library. The player navigates a map, collects all items, and finds the exit.

## Gameplay
- Movement via W/A/S/D or arrow keys
- Collect all collectibles (C), then reach the exit (E)
- Each move is counted and displayed in the terminal
- The window closes on ESC or clicking the red X

## Map Format (.ber files)
Maps are plain text files with a .ber extension passed as a command-line argument.

Characters:
- 0 — empty floor
- 1 — wall
- C — collectible
- E — exit
- P — player starting position

Rules:
- Must be rectangular
- Must be fully enclosed by walls (1s)
- Must contain exactly 1 P, exactly 1 E, and at least 1 C
- A valid path must exist from P to all collectibles and to the exit

## Technical Requirements
- Written in C
- Compiled via a Makefile with rules: NAME, all, clean, fclean, re
- Uses MiniLibX for graphics and event handling
- On invalid input or map: print "Error\n" followed by a descriptive message, then exit cleanly
- No memory leaks
- No global variables

## Bonus Part
- Enemy patrol that kills the player on contact
- Sprite animations (cycling through multiple image frames)
- Movement counter displayed on the game window itself (not just the terminal)
