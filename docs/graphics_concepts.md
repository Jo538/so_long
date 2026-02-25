# Graphics Programming — Lecture Notes
### Concepts for the so_long project (42 School)

---

## Table of Contents

1. [The Screen is a Grid of Pixels](#1-the-screen-is-a-grid-of-pixels)
2. [Colors are Numbers — RGB and Hexadecimal](#2-colors-are-numbers--rgb-and-hexadecimal)
3. [Windows in Graphical Programs](#3-windows-in-graphical-programs)
4. [The Event Loop — The Heartbeat of Any GUI Program](#4-the-event-loop--the-heartbeat-of-any-gui-program)
5. [Drawing Pixels vs. Loading Image Files](#5-drawing-pixels-vs-loading-image-files)
6. [How a File Becomes an Image in RAM](#6-how-a-file-becomes-an-image-in-ram)
7. [Image File Formats — PNG vs. XPM](#7-image-file-formats--png-vs-xpm)
8. [Transparency and the Alpha Channel](#8-transparency-and-the-alpha-channel)
9. [Tiles and Tile-Based Games](#9-tiles-and-tile-based-games)
10. [What "Rendering" Means](#10-what-rendering-means)
11. [Screen Coordinates and the Array Indexing Gotcha](#11-screen-coordinates-and-the-array-indexing-gotcha)
12. [What is a Graphics Library?](#12-what-is-a-graphics-library)
13. [X11 and the Unix Display System](#13-x11-and-the-unix-display-system)
14. [MiniLibX — The Library Used in so_long](#14-minilibx--the-library-used-in-so_long)
15. [Textures and Collectibles — Terminology](#15-textures-and-collectibles--terminology)
16. [The .ber File Format](#16-the-ber-file-format)
17. [Putting It All Together — What so_long Does](#17-putting-it-all-together--what-so_long-does)

---

## 1. The Screen is a Grid of Pixels

Every screen — laptop, monitor, phone — is a rectangular grid of tiny dots called **pixels** (short for *picture elements*). Each pixel can display exactly one color at a time. That is the only thing a screen can do: show a color at each dot.

```
A small 8×4 screen (massively simplified):

+--+--+--+--+--+--+--+--+
|  |  |  |  |  |  |  |  |   row 0
+--+--+--+--+--+--+--+--+
|  |  |  |  |  |  |  |  |   row 1
+--+--+--+--+--+--+--+--+
|  |  |  |  |  |  |  |  |   row 2
+--+--+--+--+--+--+--+--+
|  |  |  |  |  |  |  |  |   row 3
+--+--+--+--+--+--+--+--+
col0 col1 col2 col3 ...
```

A real 1920×1080 screen has 1920 × 1080 = **2,073,600 pixels**. Your program's job is to tell each of those pixels what color to show.

**Key takeaway:** Everything you see on a screen — text, icons, game sprites, windows — is ultimately just a grid of colored dots. There is no magic.

---

## 2. Colors are Numbers — RGB and Hexadecimal

### RGB

Computers represent colors using three numbers: **Red, Green, Blue** (RGB). Each value ranges from 0 (none of that color) to 255 (maximum of that color). Mixing them produces any color.

```
Color        R     G     B      Result
─────────────────────────────────────────
Red        255     0     0      pure red
Green        0   255     0      pure green
Blue         0     0   255      pure blue
White      255   255   255      all channels full
Black        0     0     0      all channels off
Yellow     255   255     0      red + green mixed
Orange     255   128     0      red + half green
Grey       128   128   128      equal low amounts
```

Why 0–255? Because one color channel is stored in **8 bits** (1 byte), and 8 bits can hold 256 different values (0 through 255).

### Hexadecimal

Hexadecimal is simply **base 16** counting. Normal decimal counting uses 10 digits (0–9). Hexadecimal uses 16 digits: 0–9 and then A=10, B=11, C=12, D=13, E=14, F=15.

```
Decimal:  0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17 ...
Hex:      0  1  2  3  4  5  6  7  8  9   A   B   C   D   E   F  10  11 ...
```

The reason hex is used for colors is elegant: one byte (0–255) fits **exactly** into two hex digits.

```
Decimal 255 → Hex FF
  F = 15
  F = 15
  (15 × 16) + 15 = 240 + 15 = 255  ✓

Decimal 0   → Hex 00
Decimal 128 → Hex 80   (8 × 16 + 0 = 128)
Decimal 16  → Hex 10   (1 × 16 + 0 = 16)
```

### RGB in Hex: #RRGGBB

Each color channel gets two hex digits. A full color is written as `#RRGGBB`:

```
#FF0000  →  R=FF(255)  G=00(0)   B=00(0)   =  pure red
#00FF00  →  R=00(0)    G=FF(255) B=00(0)   =  pure green
#0000FF  →  R=00(0)    G=00(0)   B=FF(255) =  pure blue
#FFFF00  →  R=FF(255)  G=FF(255) B=00(0)   =  yellow
#FFFFFF  →  R=FF(255)  G=FF(255) B=FF(255) =  white
#000000  →  R=00(0)    G=00(0)   B=00(0)   =  black
```

### Colors as a Single Integer in C

In C code, colors are packed into one 32-bit integer. The prefix `0x` means hexadecimal.

```
0xFF0000  ← pure red   (in C code)
0x00FF00  ← pure green
0xFFFFFF  ← white

The 32 bits are laid out as:
┌──────────┬──────────┬──────────┬──────────┐
│  alpha   │   red    │  green   │   blue   │
│ 00000000 │ 11111111 │ 00000000 │ 00000000 │
└──────────┴──────────┴──────────┴──────────┘
= 0x00FF0000 = pure red
```

The leftmost byte is the **alpha** channel (transparency) — covered in section 8.

---

## 3. Windows in Graphical Programs

When a program opens a **window**, the operating system gives it a rectangular region of the screen to draw on. The OS handles the border, title bar, and close/minimise buttons. Your program is responsible for filling every pixel inside that rectangle.

```
┌─────────────────────────────────┐
│  ./so_long              _ □ ×   │  ← title bar: managed by the OS
├─────────────────────────────────┤
│                                 │
│                                 │
│     YOUR PROGRAM DRAWS HERE     │  ← this is your canvas
│                                 │
│                                 │
└─────────────────────────────────┘
```

The canvas is just a big block of memory — the pixel data buffer. You write color values into it, and the OS copies it onto the physical screen.

---

## 4. The Event Loop — The Heartbeat of Any GUI Program

This is one of the most important concepts in graphics programming.

A command-line program runs from top to bottom and exits. A graphical program is different: it **stays alive indefinitely**, waiting for events (key presses, mouse clicks, window close requests), and reacting to them.

This is called the **event loop**:

```
Program starts
      │
      ▼
Initialise (open window, load images, draw map)
      │
      ▼
┌──────────────────────────────────────────┐
│               EVENT LOOP                 │
│                                          │
│   Did something happen?                  │
│                                          │
│   ┌──────────────────────────────────┐   │
│   │  Key W pressed?  → move up       │   │
│   │  Key A pressed?  → move left     │   │
│   │  Key S pressed?  → move down     │   │
│   │  Key D pressed?  → move right    │   │
│   │  ESC pressed?    → quit          │   │
│   │  Window X clicked? → quit        │   │
│   │  Nothing yet?    → keep waiting  │   │
│   └──────────────────────────────────┘   │
│                ↑ repeat forever          │
└──────────────────────────────────────────┘
      │
      ▼  (only exits when quit event occurs)
Free all memory, exit cleanly
```

### Hooks

You do not write the loop yourself in MiniLibX. Instead, you **register hooks** — you tell MiniLibX: *"when this event happens, call this function."* Then you hand over control by calling `mlx_loop()`, which never returns until the program ends.

```
Think of it like leaving instructions with a receptionist:
  "If someone presses W, call move_up()."
  "If someone presses ESC, call quit_game()."
  "If the window is closed, call quit_game()."
Then you go sit down — the receptionist (MiniLibX) handles everything.
```

---

## 5. Drawing Pixels vs. Loading Image Files

There are two ways to put a visual on screen.

### Option A — Draw pixel by pixel (manual)

You write code that sets the color of every single pixel yourself.

```
Pseudocode for a 4×4 red square:

for y from 0 to 3:
    for x from 0 to 3:
        set_pixel(x, y, 0xFF0000)   ← set every pixel to red
```

This works but has serious problems:
- A 64×64 tile has **4,096 pixels** — imagine writing code to set each one
- Getting a recognisable shape (a dog, a fish, a wall texture) this way requires extreme skill
- Any visual change means rewriting code
- Artists cannot contribute because the visuals live inside the code

### Option B — Load an image file

An image file is created once (in a graphics editor, by you or an artist) and saved to disk. Your program loads it at startup and stamps it on the window wherever needed.

```
wall.xpm on disk
      │
      │  mlx_xpm_file_to_image()   ← one function call
      ▼
Image object in RAM (a block of pixel color data)
      │
      │  mlx_put_image_to_window(window, image, x, y)   ← stamp it
      ▼
Appears on screen at position (x, y)
```

For so_long, you **always** use option B. Load your textures once at startup, then stamp them wherever the map needs them. The same wall image gets stamped dozens of times across the map without loading it again.

---

## 6. How a File Becomes an Image in RAM

This process feels like magic until you trace each step. It is not magic.

### Step 1 — What is actually on disk?

An image file is a sequence of bytes. The file format is a set of rules for how those bytes encode pixel colors. XPM is the simplest — it is plain text.

A minimal XPM file looks like this:

```
/* XPM */
static char *wall_tile[] = {
"4 4 3 1",           ← width=4, height=4, 3 colors, 1 char per pixel
". c #8B4513",       ← '.' means brown
"# c #000000",       ← '#' means black
"o c None",          ← 'o' means transparent
"####",              ← row 0: all black
"#..#",              ← row 1: black, brown, brown, black
"#..#",              ← row 2: same
"####"               ← row 3: all black
};
```

This is literally a text file. You could write one by hand in a text editor.

### Step 2 — What does mlx_xpm_file_to_image() do?

The library reads and parses the file step by step:

```
1. Read the header line "4 4 3 1"
   → now knows: width=4, height=4, 3 colors defined

2. Read the color lines:
   → builds a lookup table: '.' → 0x8B4513, '#' → 0x000000

3. Call malloc to allocate memory:
   → needs width × height × 4 bytes = 4 × 4 × 4 = 64 bytes

4. Walk through the pixel rows character by character:
   → '# # # #' → write 0x000000, 0x000000, 0x000000, 0x000000
   → '# . . #' → write 0x000000, 0x8B4513, 0x8B4513, 0x000000
   → etc.

5. Return a pointer to that memory block
```

The resulting block of memory (the "image") is simply a flat array of color integers:

```
Memory layout for a 4×4 image:

Index:   [0]        [1]        [2]        [3]        ← row 0
       0x000000   0x000000   0x000000   0x000000

Index:   [4]        [5]        [6]        [7]        ← row 1
       0x000000   0x8B4513   0x8B4513   0x000000

Index:   [8]        [9]        [10]       [11]       ← row 2
       0x000000   0x8B4513   0x8B4513   0x000000

Index:  [12]       [13]       [14]       [15]        ← row 3
       0x000000   0x000000   0x000000   0x000000

Formula: pixel at (x, y) → array index [y * width + x]

Example: pixel at (1, 1) → index [1 * 4 + 1] = index [5] = 0x8B4513 (brown) ✓
```

### Step 3 — What does mlx_put_image_to_window() do?

It tells X11: *"Copy this block of memory to the screen, placing the top-left corner at position (x, y)."* X11 does the hardware-level work of lighting up the correct pixels on the physical display.

```
Your RAM                              Physical screen
┌────────────────────┐                ┌──────────────────────┐
│  pixel color data  │  ── copy ──►   │  pixels light up at  │
│  [0x000000, ...]   │                │  the right position  │
└────────────────────┘                └──────────────────────┘
```

---

## 7. Image File Formats — PNG vs. XPM

Both formats store the same thing — pixel color data — but encode it differently.

```
Format   Full Name            Encoding          Human readable?  Transparency
──────────────────────────────────────────────────────────────────────────────
XPM      X PixMap             Plain text        YES              Limited (on/off)
PNG      Portable Network     Binary compressed NO               Full (0–255)
         Graphics
```

### XPM — Why it exists

XPM was designed for the X Window System (Linux/Unix). Because it is plain text, it can be directly `#include`-d into C source files and compiled into the program. No file loading needed at runtime. This is unusual and not common in other ecosystems.

Example XPM (shown in section 6 above) — you can literally read it with your eyes.

### PNG — The modern standard

PNG compresses pixel data, resulting in much smaller file sizes for complex images. The data is binary, not human-readable. It supports a full alpha (transparency) channel. It is the standard format for web images and modern games.

### Which to use for so_long?

**XPM** is the safe choice. The base MiniLibX has built-in support for XPM via `mlx_xpm_file_to_image()`. PNG requires an additional extension. Most 42 students use XPM to avoid the setup complexity.

---

## 8. Transparency and the Alpha Channel

Recall the 32-bit color integer layout:

```
┌──────────┬──────────┬──────────┬──────────┐
│  alpha   │   red    │  green   │   blue   │
│  8 bits  │  8 bits  │  8 bits  │  8 bits  │
└──────────┴──────────┴──────────┴──────────┘
```

The **alpha channel** controls how opaque or transparent a pixel is:

```
Alpha = 255  → fully opaque   (you see only this pixel, nothing behind it)
Alpha = 128  → half transparent (this pixel blended 50/50 with what's behind it)
Alpha = 0    → fully invisible (the pixel beneath shows through completely)
```

### Why this matters for sprites

Game characters and objects are rarely perfect rectangles. Without transparency, a non-rectangular sprite looks like this:

```
Without transparency:             With transparency:

██████████████                    · · · · · · · ·
██████████████                    · · 🐾🐾🐾 · ·
████  🐕  ████   ← ugly black    · ·  🐕  · · ·
████  🐕  ████     box spoils it  · · 🐾🐾🐾 · ·
██████████████                    · · · · · · · ·
```

### XPM transparency

XPM supports one color being designated as transparent using the keyword `None`:

```
"o c None",   ← any pixel drawn with 'o' will be transparent
```

This is binary: a pixel is either fully transparent or fully opaque. No blending.

### PNG transparency

PNG stores an alpha value per pixel (0–255), enabling smooth edges and gradients. This is full alpha transparency and produces much cleaner-looking sprites.

---

## 9. Tiles and Tile-Based Games

### What is a tile?

A **tile** is a fixed-size image used as a building block to construct a larger world. The name comes from bathroom tiles — small identical pieces arranged to cover a large area.

```
Individual tile images (64×64 pixels each):

[  wall  ]   [  floor  ]   [ collectible ]   [  player  ]   [  exit  ]
```

Key properties:
- **Fixed size** — all tiles are the same dimensions (e.g. 64×64 pixels)
- **Reusable** — you load one wall image once, then stamp it hundreds of times
- **Grid-aligned** — always placed at exact multiples of the tile size

### The tile map

Your `.ber` file is a **tile map** — a grid where each cell specifies which tile to draw there.

```
Map file (so_long .ber):           Rendered on screen (64px tiles):

1 1 1 1 1                          ██ ██ ██ ██ ██
1 0 C 0 1         render►          ██ ·· 🐟 ·· ██
1 P 0 E 1                          ██ 🐶 ·· 🚪 ██
1 1 1 1 1                          ██ ██ ██ ██ ██
```

### How tile position maps to screen position

Since each tile is `TILE_SIZE` pixels wide and tall, the formula for where to draw each tile is:

```
screen_x = col * TILE_SIZE
screen_y = row * TILE_SIZE

Example with TILE_SIZE = 64:

Tile at row=0, col=0  →  screen (x=0,   y=0)
Tile at row=0, col=1  →  screen (x=64,  y=0)
Tile at row=1, col=0  →  screen (x=0,   y=64)
Tile at row=2, col=3  →  screen (x=192, y=128)
```

This means rendering the entire map is just two nested loops — one over rows, one over columns — stamping the right tile image at each position.

---

## 10. What "Rendering" Means

**Rendering** is the process of converting data (numbers, coordinates, colors) into a visible image.

```
YOUR DATA                              SCREEN

map array:                             ┌──────────────────┐
  [1][1][1][1][1]                      │ ██ ██ ██ ██ ██   │
  [1][0][C][0][1]   ── render ──►     │ ██ ·· 🐟 ·· ██   │
  [1][P][0][E][1]                      │ ██ 🐶 ·· 🚪 ██   │
  [1][1][1][1][1]                      │ ██ ██ ██ ██ ██   │
                                       └──────────────────┘
```

**To render a frame** means to draw everything once — the complete current state of the game — onto the screen.

In so_long, you typically render the whole map from scratch on each move. This means:
1. Clear the window (or redraw every tile, overwriting whatever was there)
2. Loop through every cell of the map array
3. Stamp the appropriate tile image at the correct screen position
4. If the player moved, stamp the player image at the new position

The term "rendering" comes from 3D graphics and filmmaking, where producing a single frame can require heavy computation. In 2D tile-based games it is simpler, but the word is the same.

---

## 11. Screen Coordinates and the Array Indexing Gotcha

### The screen coordinate system

Screens use a coordinate system where the **origin (0,0) is the top-left corner**. This is different from school maths where the origin is at the bottom-left.

```
(0,0) ──────────────────► x increases (left → right)
  │
  │
  │   y increases (top → bottom)
  │
  ▼

For a 640×480 window:
  Top-left corner:     (0,   0)
  Top-right corner:    (639, 0)
  Bottom-left corner:  (0,   479)
  Bottom-right corner: (639, 479)
```

### Why columns = horizontal = x

Think of the grid like a spreadsheet. Columns run **vertically** on the page, but they label the **horizontal** position — how far left or right you are.

```
         col 0   col 1   col 2   col 3   col 4
          │       │       │       │       │
row 0 ─── 1       1       1       1       1
row 1 ─── 1       0       0       0       1
row 2 ─── 1       0      [P]      0       1
row 3 ─── 1       1       1       1       1
```

The player P is at column 2, row 2:
- Column 2 = 2 steps to the right = **horizontal position** = **x = 2**
- Row 2 = 2 steps down = **vertical position** = **y = 2**

So: column = x (horizontal), row = y (vertical).

### The order gotcha — the most common source of bugs

The real trap is that the two most common ways to reference a cell are written in **opposite order**:

```
Context              Order written        Example for column 3, row 2
─────────────────────────────────────────────────────────────────────
Screen/MiniLibX      (x, y)               put_image(window, img, 3, 2)
                     horizontal first

C 2D array           [row][col]           map[2][3]
                     vertical first
```

They refer to the same pixel, but the indices are written in reverse order:

```
  Screen function:   put_image(win, img, x=3, y=2)
  Array access:      map[y=2][x=3]

  Same cell.  Different notation order.
```

If you accidentally write `map[x][y]` instead of `map[y][x]`, your map will render mirrored or scrambled. This is an extremely common bug. The rule to remember:

```
RULE:  when indexing a 2D array in C, always write [row][col] = [y][x]
       when calling screen functions, always write (x, y) = (col, row)
```

---

## 12. What is a Graphics Library?

### Standard C library (libc)

The standard C library provides tools for working with data in memory and the operating system:
- `malloc` / `free` — allocate and release memory
- `open` / `read` / `write` — read and write files
- `printf` — print text to the terminal
- `exit` — terminate the program

It has **no concept of a screen**. It cannot open windows, draw images, or receive mouse events.

### A graphics library

A graphics library is an additional layer that knows how to:
- Talk to the **display server** (the software that controls the screen)
- Create and manage **windows**
- Transfer pixel color data from RAM onto the screen
- Receive **keyboard and mouse events** from the OS

```
YOUR PROGRAM (C code)
        │
        │  calls
        ▼
GRAPHICS LIBRARY (MiniLibX)
        │
        │  talks to
        ▼
DISPLAY SERVER (X11 on Linux)
        │
        │  controls
        ▼
SCREEN HARDWARE
```

Without a graphics library, opening a window in raw C would require dozens of lines of low-level system code. MiniLibX reduces that to 2 lines.

### Comparison

| Standard libc                     | MiniLibX                                  |
|-----------------------------------|-------------------------------------------|
| `printf` — print text to terminal | `mlx_put_image_to_window` — draw on screen|
| `malloc` — allocate memory        | `mlx_new_image` — allocate image buffer   |
| `open` / `read` — read a file     | `mlx_xpm_file_to_image` — load an image   |
| Works everywhere (no display needed) | Requires a running display server      |

---

## 13. X11 and the Unix Display System

### What is Unix?

Unix is a family of operating systems. Linux is a Unix-like system. macOS is also Unix-based. These systems share design principles and many tools, though they differ in implementation.

### What is X11?

X11 (the X Window System, version 11) is the display system standard on Linux. It is the software layer responsible for:
- Owning and managing the physical screen
- Deciding which program gets to draw in which region
- Routing keyboard and mouse events to the correct window

X11 uses a **client–server model**, even when everything runs on the same physical machine:

```
                     X SERVER
              (owns the physical screen,
               runs in the background)
            ┌────────────────────────────┐
            │                            │
     ┌──────▼──────┐  ┌───────────┐  ┌──▼──────┐
     │   Terminal  │  │  Browser  │  │ so_long │
     │  (X client) │  │ (X client)│  │(X client│
     └─────────────┘  └───────────┘  └─────────┘

Each program is an X client — it asks the X server to show things on screen.
```

### Why MiniLibX hides X11

Directly using X11 in C is verbose and complex. Opening a basic window requires ~50 lines of X11 boilerplate. MiniLibX wraps those 50 lines into one function call: `mlx_new_window()`.

You do not need to understand X11 in depth to use MiniLibX. But knowing it exists explains why MiniLibX programs only work when a display is available (i.e., you need a graphical desktop environment, not just a terminal).

---

## 14. MiniLibX — The Library Used in so_long

MiniLibX is a small graphics library created by 42 School. It is specifically designed for students — simple enough to learn quickly, but powerful enough to build real graphical programs.

### Core functions

| What you want to do              | MiniLibX function                    |
|----------------------------------|--------------------------------------|
| Initialise the library           | `mlx_init()`                         |
| Open a window                    | `mlx_new_window(mlx, w, h, title)`   |
| Load an XPM image from file      | `mlx_xpm_file_to_image(mlx, path, &w, &h)` |
| Draw an image to the window      | `mlx_put_image_to_window(mlx, win, img, x, y)` |
| React to key presses             | `mlx_key_hook(win, func, param)`     |
| React to window close / ESC      | `mlx_hook(win, event, mask, func, param)` |
| Start the event loop             | `mlx_loop(mlx)`                      |
| Destroy an image (free it)       | `mlx_destroy_image(mlx, img)`        |
| Destroy a window                 | `mlx_destroy_window(mlx, win)`       |

### Typical program structure

```
1. mlx_init()                        → initialise connection to display
2. mlx_new_window()                  → open the window
3. mlx_xpm_file_to_image() × N      → load all texture files
4. [parse map, set up game state]
5. [draw the initial map using mlx_put_image_to_window()]
6. mlx_key_hook() / mlx_hook()       → register event callbacks
7. mlx_loop()                        → hand over control, never returns
                                       (until the program exits)
```

---

## 15. Textures and Collectibles — Terminology

### Texture

**Texture** is a standard graphics programming term — not specific to so_long or 42.

In 3D graphics, a texture is an image that gets "mapped" (applied) onto the surface of a 3D shape to give it visual detail (e.g. a brick pattern on a cube). In 2D tile-based games, the word is borrowed and used to mean the image for a tile. "Texture" and "tile image" are essentially synonymous in this context.

```
3D use (origin of the word):         2D use (so_long context):

   ┌──────┐                          wall_texture.xpm
  /      /│  ← brick texture         = the image you stamp
 /      / │    applied to a cube       wherever map[y][x] == '1'
└──────┘  │
│      │  /
└──────┘
```

### Collectible

**Collectible** is a general game design term for any item the player picks up. Examples:
- Coins in Mario → collectibles
- Rings in Sonic → collectibles
- Fish in so_long → collectibles

The term is not specific to 42 or so_long.

---

## 16. The .ber File Format

The `.ber` extension is **not a standard format**. It is a plain text file with a custom extension chosen by 42 for this project. If you opened a `.ber` file in a text editor you would see exactly this:

```
11111111111
10C00000001
100110001E1
1P0000000C1
11111111111
```

Your program treats it like any text file:
1. Check the argument ends in `.ber` (if not, print an error and exit)
2. Open it with `open()`
3. Read it character by character with `read()`
4. Parse the characters into a 2D array in memory
5. Validate the map rules (see section 17)

The `.ber` extension is purely a label. It carries no special meaning to the operating system.

### Map validation rules

A valid `.ber` map must satisfy all of these:

| Rule | Detail |
|------|--------|
| Rectangular | All rows must have the same length |
| Enclosed by walls | Every cell on the border must be `1` |
| Exactly 1 player | One and only one `P` |
| Exactly 1 exit | One and only one `E` |
| At least 1 collectible | One or more `C` |
| Valid characters only | Only `0`, `1`, `C`, `E`, `P` |
| Valid path exists | A path must exist from `P` to all `C`s and to `E` |

If any rule is violated: print `"Error\n"` followed by a descriptive message, then exit cleanly.

---

## 17. Putting It All Together — What so_long Does

Here is the complete picture of the program flow, using every concept from these notes:

```
./so_long map.ber
      │
      ▼
┌─────────────────────────────────────────┐
│               STARTUP                   │
│                                         │
│  1. Check argument count and extension  │
│  2. Open and read the .ber file         │
│  3. Parse characters into a 2D array    │
│  4. Validate all map rules              │
│  5. mlx_init()                          │
│  6. mlx_new_window()                    │
│  7. Load all textures (XPM files)       │
│  8. Render initial map                  │
│     → loop over [row][col]              │
│     → for each cell, stamp the right    │
│       texture at (col*SIZE, row*SIZE)   │
│  9. Register key hooks                  │
│  10. mlx_loop()  ← hand over control   │
└────────────────────────┬────────────────┘
                         │
               ┌─────────▼──────────┐
               │     EVENT LOOP     │
               │                    │
               │  Key W/A/S/D?      │
               │  → compute new     │
               │    player position │
               │  → check for wall  │
               │  → check for C     │
               │    (remove it)     │
               │  → check for E     │
               │    (win if all C   │
               │     collected)     │
               │  → redraw map      │
               │  → print move count│
               │                    │
               │  ESC / window X?   │
               │  → free all memory │
               │  → exit            │
               └────────────────────┘
```

### The rendering step expanded

```
For each row y from 0 to map_height - 1:
  For each col x from 0 to map_width - 1:

    screen_x = x * TILE_SIZE
    screen_y = y * TILE_SIZE

    if map[y][x] == '1':  put wall texture  at (screen_x, screen_y)
    if map[y][x] == '0':  put floor texture at (screen_x, screen_y)
    if map[y][x] == 'C':  put floor texture, then collectible texture
    if map[y][x] == 'E':  put floor texture, then exit texture
    if map[y][x] == 'P':  put floor texture, then player texture
```

Note: floor is drawn first under collectibles/player/exit because those tiles have transparent backgrounds — the floor must show through.

---

*These notes cover all concepts introduced in the initial study session. Refer back to any section as needed when building the project.*
