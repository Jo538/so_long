*This project has been created as part of the 42 curriculum by jchartie.*

# so_long

## Description

**so_long** is a small 2D top-down game built in C using the MiniLibX graphical library. The player controls a dog navigating through a tile-based map, collecting all the bread scattered around before reaching the exit. The game enforces map validation, flood-fill path checking, and smooth window management — all while displaying the move count in the shell after every step.

The project covers core concepts of computer graphics programming: window management, event handling, sprite rendering with XPM textures, and basic game logic in C.

**Map tiles:**
| Character | Meaning |
|-----------|---------|
| `0` | Empty space |
| `1` | Wall |
| `C` | Collectible |
| `E` | Exit |
| `P` | Player starting position |

**Controls:**
| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `S` / `↓` | Move down |
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `ESC` | Quit |

## Instructions

### Requirements

- GCC or compatible C compiler
- MiniLibX (Linux version included at `libs/mlx_linux`)
- X11 and Xext development libraries (Linux)

On Debian/Ubuntu:
```bash
sudo apt-get install libxext-dev libx11-dev
```

### Compilation

```bash
make
```

This compiles all libraries (`libft`, `libftprintf`, MiniLibX) and the main executable.

Other Makefile targets:

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Full recompile
make test     # Run the test suite
```

### Running the game

```bash
./so_long <path/to/map.ber>
```

**Map requirements:**
- Extension must be `.ber`
- Must be rectangular and fully enclosed by walls (`1`)
- Must contain exactly 1 exit (`E`), 1 player start (`P`), and at least 1 collectible (`C`)
- Must have a valid path from `P` to all collectibles and to `E`

**Example:**
```
1111111111111
1001000000C1
1000011111001
1P0011E000001
1111111111111
```

If the map is invalid, the program exits cleanly and prints an error message to the standard error.

## Resources

### References

- [MiniLibX documentation (42 school)](https://harm-smits.github.io/42docs/libs/minilibx)
- [X11 programming guide](https://tronche.com/gui/x/xlib/)
- Flood fill algorithm: standard BFS/DFS reference implementations

### AI usage

Claude Code (claude-sonnet-4-6) was used during this project for the following tasks:
- Writing this README.md
- Helping structure the map validation logic and flood-fill approach
- Generating the test suite scaffold and suggesting edge cases to cover
