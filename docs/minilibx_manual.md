# MiniLibX Function Manual

---

## 0. The Build System

Before writing a single line of game code, you need to understand how MiniLibX gets compiled and linked into your project. This section covers the Makefile flags, the role of each library, and what happens under the hood when you run `make`.

---

### The two stages of building

Building a C program always happens in two distinct stages:

**Stage 1 — Compiling:** each `.c` file is translated into a `.o` (object) file. No executable yet — just intermediate compiled units.

**Stage 2 — Linking:** all `.o` files (yours and from libraries) are combined into a single final executable.

Understanding this distinction is the key to understanding what every flag in your Makefile does.

```
Stage 1 — Compile:

  main.c    ──► gcc -c ──►  main.o
  game.c    ──► gcc -c ──►  game.o
  map.c     ──► gcc -c ──►  map.o

Stage 2 — Link:

  main.o  ┐
  game.o  ├──► gcc ──► so_long  (the final executable)
  map.o   ┘
  libmlx_Linux.a
  libX11.so
  ...
```

---

### The `-I`, `-L`, and `-l` flags

These three flags each deal with a different stage and a different kind of file.

#### `-I` — tell the compiler where to find header files (compile stage)

```makefile
$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
```

When the compiler sees `#include <mlx.h>`, it needs to physically find that file on disk. `-I` adds a directory to its search list.

- `-I/usr/include` → search `/usr/include`
- `-Imlx_linux` → search the `mlx_linux/` folder in your project

Note: no space between `-I` and the path is the common style, but both forms work.

#### `-L` — tell the linker where to find library files (link stage)

```makefile
$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
```

At link time, the linker needs to find compiled library files (`.a` or `.so`). `-L` adds a directory to its search list.

- `-Lmlx_linux` → look for libraries in the `mlx_linux/` folder
- `-L/usr/lib` → look in `/usr/lib`

#### `-l` — tell the linker which libraries to use (link stage)

This tells the linker which libraries to actually link against. It is a name, not a path.

- `-lmlx_Linux` → link `libmlx_Linux.a`
- `-lXext` → link `libXext.so`
- `-lX11` → link `libX11.so`
- `-lm` → link the math library (`libm`)
- `-lz` → link the compression library (`libz`)

The naming rule is always: **strip the `lib` prefix and the file extension**, so `libX11.so` becomes `-lX11`.

#### The full picture

```
#include <mlx.h>   ← compiler finds mlx.h via -I
      │
   compile
      │
   .o files
      │
    link        ← linker finds libmlx_Linux.a via -L, pulls it in via -l
      │
   so_long      (final executable)
```

`-I` is for the compiler finding *declarations* (header files).
`-L` and `-l` are for the linker finding *implementations* (compiled library code).

---

### Why does `-I` exist? Don't all headers live in the same place?

When you write `#include <stdio.h>`, you never need to specify where `stdio.h` lives. That is because the compiler has a built-in list of directories it searches automatically. On Linux this includes `/usr/include` and `/usr/local/include`. `stdio.h` lives in `/usr/include`, which is already on that default list.

`-I` becomes necessary when headers live somewhere **outside** the default search paths — which is exactly the case for your own `libft.h`, or for `mlx.h` which lives inside your project's `mlx_linux/` folder.

| Header | Location | On default search path? | Need `-I`? |
|---|---|---|---|
| `stdio.h` | `/usr/include` | Yes | No |
| `X11/Xlib.h` | `/usr/include` | Usually yes | Usually no |
| `libft.h` | your project folder | No | **Yes** |
| `mlx.h` | `mlx_linux/` folder | No | **Yes** |

---

### What do `-lX11`, `-lXext`, `-lm`, and `-lz` actually do?

You might expect to only need MiniLibX (`-lmlx_Linux`). But MiniLibX itself depends on other libraries, and the linker needs to know about the full chain explicitly.

#### `-lX11` — the core X Window System

Provides all the fundamental functions to talk to your display server: opening a display, creating windows, drawing pixels, handling events. Every `X`-prefixed function in MiniLibX (`XOpenDisplay`, `XCreateWindow`, `XFlush`) comes from here.

#### `-lXext` — X11 extensions

A library of optional add-ons built on top of X11. MiniLibX uses one specific extension from it: **XShm** (Shared Memory). XShm lets MiniLibX put images on screen much faster by sharing memory directly with the display server, instead of copying pixel data over a socket. The evidence is in MiniLibX's own internal header:

```c
#include <X11/extensions/XShm.h>
```

#### `-lm` — the math library

C separates math functions (`sqrt`, `sin`, `cos`, etc.) into their own library for historical reasons. X11 depends on it internally. You never call it directly in so_long, but the linker still needs to be told it exists.

#### `-lz` — zlib (compression)

A general-purpose compression library. X11 and its extensions use it internally when transferring image data. Like `-lm`, you never call it directly — it is a dependency of a dependency.

#### The dependency chain

```
your code
   └── MiniLibX  (libmlx_Linux.a)
          ├── X11     (windows, events, drawing)
          │     ├── lm    (math — internal dependency)
          │     └── lz    (compression — internal dependency)
          └── Xext    (shared memory fast image rendering)
```

---

### Why are these libraries in YOUR Makefile and not MiniLibX's?

MiniLibX's own Makefile only produces `libmlx_Linux.a`. At this stage, the compiler is just translating `.c` files into `.o` files and bundling them into an archive. **No linking happens** — so `-lX11` etc. don't need to be specified yet. The `.a` file is just a box of compiled object code waiting to be used.

Your project's Makefile is where the final executable is produced. Only here does the linker ask:

> "MiniLibX calls `XOpenDisplay`... where does that function actually live?"

And you answer: `-lX11`. Same for every other dependency down the chain.

Think of it like assembling furniture:

- MiniLibX's Makefile manufactures **one component** (a shelf unit) and boxes it up
- Your Makefile assembles **the whole room** — your pieces + the shelf unit + all the screws and brackets (`-lX11`, `-lXext`, `-lm`, `-lz`) that hold everything together

The shelf manufacturer doesn't need to know what room it will go in. But you, when assembling the room, need all the parts on hand.

---

### How to check if a library is installed locally

`ldconfig -p` lists every library the system knows about. Use it to verify a library is installed:

```bash
ldconfig -p | grep libX11
# → libX11.so.6 (libc6,x86-64) => /lib/x86_64-linux-gnu/libX11.so.6
```

If nothing comes back, the library is not installed. You can check all four MiniLibX dependencies at once:

```bash
ldconfig -p | grep -E "libX11|libXext|libm|libz"
```

---

### The MiniLibX configure script and `%%%%`

Inside `mlx_linux/Makefile.mk` you will find:

```makefile
## Please use configure script

INC = %%%%
```

`%%%%` is not special Makefile syntax. It is a **placeholder** — a sentinel string chosen because it is unlikely to appear naturally anywhere else — meant to be replaced by the `configure` binary before the Makefile is used.

After running `configure`, the resulting `Makefile.gen` shows what the placeholder becomes:

```makefile
INC = /usr/include
```

That value is then used in:

```makefile
CFLAGS = -O3 -I$(INC)
```

Which expands to `-I/usr/include` — telling the compiler to search `/usr/include` for header files such as `X11/Xlib.h`.

---

### The `IFLAGS` variable

In `Makefile.mk` you will also see `IFLAGS` used on line 45:

```makefile
$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
```

`IFLAGS` is referenced but **never defined anywhere** in the MiniLibX codebase. In Make, referencing an undefined variable simply produces an empty string. The line effectively becomes:

```makefile
$(CC) $(CFLAGS)  -c $< -o $@
```

It is a leftover placeholder from the original author, likely intended to let someone pass extra include flags from the command line (e.g. `make IFLAGS="-I/some/extra/path"`). For normal use it does nothing.

---

## 1. Initialization

### `mlx_init`
```c
void *mlx_init();
```
Must be called **first**, before anything else. Connects your program to the display server and returns a pointer you'll pass to almost every other function.

```c
void *mlx = mlx_init();
if (!mlx)
    return (1); // failed to connect
```

---

## 2. Window Management

### `mlx_new_window`
```c
void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);
```
Opens a new window on screen.

```c
void *win = mlx_new_window(mlx, 800, 600, "so_long");
```

### `mlx_clear_window`
```c
int mlx_clear_window(void *mlx_ptr, void *win_ptr);
```
Fills the entire window with black. Useful when redrawing a frame.

```c
mlx_clear_window(mlx, win);
```

### `mlx_destroy_window`
```c
int mlx_destroy_window(void *mlx_ptr, void *win_ptr);
```
Closes and frees a window.

```c
mlx_destroy_window(mlx, win);
```

### `mlx_destroy_display`
```c
int mlx_destroy_display(void *mlx_ptr);
```
Closes the X11 connection. Call this last, after destroying all windows and images.

Then call `free(mlx)` yourself — `mlx_destroy_display` does NOT free the pointer. This is because `mlx_init` internally calls `malloc` to allocate a `t_xvar` struct and returns it to you. `mlx_destroy_display` only closes the display connection inside that struct; the struct itself is your responsibility to free.

```c
mlx_destroy_display(mlx);
free(mlx);
```

---

## 3. Drawing Directly to a Window

### `mlx_pixel_put`
```c
int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
```
Draws a single pixel. Origin `(0, 0)` is **top-left**. Color format is `0x00RRGGBB`.

> **Warning:** this is slow — it sends one pixel at a time to the display. For games, use images instead (see section 4).

```c
mlx_pixel_put(mlx, win, 100, 200, 0x00FF0000); // red pixel at (100, 200)
```

### `mlx_string_put`
```c
int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *str);
```
Draws text directly onto the window.

```c
mlx_string_put(mlx, win, 10, 10, 0x00FFFFFF, "Moves: 42");
```

### `mlx_set_font`
```c
void mlx_set_font(void *mlx_ptr, void *win_ptr, char *name);
```
Changes the font used by `mlx_string_put`. Uses X11 font names.

```c
mlx_set_font(mlx, win, "fixed");
```

---

## 4. Images

### What is a pixel?

Your screen is a grid of tiny coloured squares called **pixels**. A 1920×1080 screen has 1920 columns and 1080 rows — that's 2,073,600 pixels total. Every image you see is just pixels with carefully chosen colours.

In MiniLibX, colours are expressed as integers in the format `0x00RRGGBB`:
- `RR` = how much red (00 to FF)
- `GG` = how much green
- `BB` = how much blue

```
0x00FF0000 = pure red
0x0000FF00 = pure green
0x000000FF = pure blue
0x00FFFFFF = white
0x00000000 = black
```

### What is a sprite?

A **sprite** is a small 2D image used to visually represent one game object. In so_long, each tile on your map is a sprite: the player, the wall, the floor, the collectible, the exit — each one is a separate image file containing pixel colour data.

A sprite is nothing more than a rectangle of pixels. A 64×64 sprite is a grid of 64×64 = 4,096 pixels, each with a colour.

### Why use an image buffer instead of mlx_pixel_put?

`mlx_pixel_put` sends one pixel at a time to the X display server. Under the hood, your program and the X server communicate through a socket (a communication channel). Every call to `mlx_pixel_put` sends a separate message across that socket:

```
mlx_pixel_put approach — one message per pixel:

your program ──► [pixel 1 colour] ──► X server
your program ──► [pixel 2 colour] ──► X server
your program ──► [pixel 3 colour] ──► X server
... × 4096 for a 64×64 tile ...
```

For a 64×64 tile that is 4,096 messages. For a full 800×600 screen that is 480,000 messages per frame. This is extremely slow.

An **image buffer** is a plain array of integers sitting in your program's RAM. Each slot stores the colour of one pixel. Writing to it is just writing to memory — instant, no communication with anyone.

```
Image buffer approach — write directly to RAM, one message for everything:

your program writes colours directly into RAM array
                  (no messages sent, instant)
                       │
mlx_put_image_to_window sends the whole array at once ──► X server
```

This is the recommended approach for any game.

### `mlx_new_image`
```c
void *mlx_new_image(void *mlx_ptr, int width, int height);
```
Creates a blank image in memory.

```c
void *img = mlx_new_image(mlx, 64, 64);
```

### `mlx_get_data_addr`
```c
char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
```
Returns a pointer to the raw pixel data of an image so you can write to it directly. You also get metadata needed to navigate the buffer.

- `bits_per_pixel`: how many bits one pixel takes (usually 32)
- `size_line`: how many **bytes** one row of pixels takes
- `endian`: byte order (0 = little, 1 = big)

```c
int bpp, line_len, endian;
char *pixels = mlx_get_data_addr(img, &bpp, &line_len, &endian);

// Write a red pixel at (x, y):
int offset = (y * line_len) + (x * (bpp / 8));
*(unsigned int *)(pixels + offset) = 0x00FF0000;
```

### `mlx_xpm_file_to_image`, `mlx_xpm_to_image`, `mlx_put_image_to_window`

These three functions are closely related and almost always used together. Here is how they fit together:

**`mlx_xpm_file_to_image` and `mlx_xpm_to_image` load a sprite into memory.**
**`mlx_put_image_to_window` draws that sprite onto the screen.**

Think of it in two steps:

```
Step 1 — Load:   XPM file on disk  ──►  mlx image object in memory
Step 2 — Draw:   mlx image in memory ──►  visible on screen
```

You always need both steps. Loading an image does not display it. Displaying requires something to have been loaded first.

### What does "loading a file into memory" mean?

Your computer has two kinds of storage that are important here:

- **Disk** — permanent storage. Files live here when the computer is off. Slow to access.
- **RAM** — temporary storage. Your program lives here while it is running. Very fast to access.

When your program runs, it can only work with data that is in RAM. A file sitting on disk is invisible to it until it is explicitly read and copied into RAM. This is what "loading" means.

When you call `mlx_xpm_file_to_image`, here is what happens step by step:

```
DISK                                      RAM
─────────────────────────────────────────────────────────
player.xpm                1. OS reads the file
(text describing pixels)  ──────────────────►  raw bytes of the file
                                               │
                                          2. MiniLibX parses
                                             the XPM format
                                               │
                                               ▼
                                          3. malloc() allocates
                                             a pixel colour array
                                               │
                                               ▼
                                          [0xFF0000, 0x000000, ...]
                                           one int per pixel
                                               │
                                          4. returns pointer ──► void *sprite
```

After this call, `sprite` is a pointer to a block of RAM containing the colour of every pixel in the image. The original file on disk is no longer involved — everything the game needs is now in memory.

"The image is loaded" simply means: its pixel data exists in RAM and can be used instantly.

### How can XPM data already live in your code?

XPM is unusual among image formats: it is actually valid C syntax. An XPM file looks like this:

```c
static char *my_sprite[] = {
    "4 4 2 1",        // 4 wide, 4 tall, 2 colours, 1 char per pixel
    "  c #FFFFFF",    // space = white
    "X c #000000",    // X     = black
    "XXXX",
    "X  X",
    "X  X",
    "XXXX"
};
```

This is a `char **` — an array of strings. You can copy this directly into a `.c` file, compile it, and pass the `my_sprite` pointer to `mlx_xpm_to_image`. The image data is baked into your program binary — no external file needed.

This is useful for tiny images (like a cursor) that you don't want to ship as separate files. For so_long you will almost always use `mlx_xpm_file_to_image` instead, since your sprites live in `.xpm` files.

The difference between the two load functions is only **where the XPM data comes from**:

| Function | Source |
|---|---|
| `mlx_xpm_file_to_image` | A `.xpm` file on disk (path as string) |
| `mlx_xpm_to_image` | A `char **` array already compiled into your program |

`mlx_put_image_to_window` does not care how the image was created — it works the same whether the image came from `mlx_xpm_file_to_image`, `mlx_xpm_to_image`, or `mlx_new_image`.

```c
// Full load-then-draw example:
int    w, h;
void  *wall  = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &w, &h);
void  *floor = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &w, &h);

mlx_put_image_to_window(mlx, win, wall,  0,  0);   // draw wall at top-left
mlx_put_image_to_window(mlx, win, floor, 64, 0);   // draw floor next to it
```

---

### `mlx_put_image_to_window`
```c
int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
```
Renders an image onto the window at position `(x, y)`. The image must have been created first by one of the load functions above (or `mlx_new_image`).

```c
mlx_put_image_to_window(mlx, win, sprite, 0, 0);
```

### `mlx_xpm_file_to_image`
```c
void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
```
Loads an XPM file from disk into an image. Fills in `width` and `height` for you.

```c
int w, h;
void *sprite = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &w, &h);
```

### `mlx_xpm_to_image`
```c
void *mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, int *width, int *height);
```
Same as above but loads from an XPM already in memory (as a `char **` array), instead of from a file.

### `mlx_destroy_image`
```c
int mlx_destroy_image(void *mlx_ptr, void *img_ptr);
```
Frees an image. Call this for every image you loaded when cleaning up.

```c
mlx_destroy_image(mlx, sprite);
```

### `mlx_get_color_value`
```c
int mlx_get_color_value(void *mlx_ptr, int color);
```
Converts a `0x00RRGGBB` color to the format your screen actually expects (depends on color depth). Rarely needed in practice.

---

## 5. Events and Hooks

### What is an event?

MiniLibX is **event-driven**. When `mlx_loop` runs, your program stops doing anything on its own and just sits waiting:

```
while (true)
    wait for something to happen...
```

An **event** is "something happened" — a key was pressed, the mouse moved, the window needs redrawing, etc.

### What is a hook?

A **hook** is a function you write and *register* in advance, saying:

> "When event X happens, call *my* function."

MiniLibX then calls your function automatically at the right moment. You never call it yourself.

Think of it like leaving your phone number with a restaurant:
- You don't sit on hold listening
- You register your number ("call me when my table is ready")
- They call you when the event happens

Every hook registration follows the same pattern:
```c
mlx_???_hook(target, your_function, data_to_pass_in);
```

### The `void *param` pattern

Every hook lets you pass one pointer (`param`) when registering. MiniLibX passes it back to your function when it calls it. This is how you give your callback access to your game data without using global variables:

```c
// Register: pass your game struct as param
mlx_key_hook(win, on_keypress, &game);

// Callback: cast param back to your type
int    on_keypress(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    game->moves++;
    return (0);
}
```

### `mlx_hook`
```c
int mlx_hook(void *win_ptr, int event, int mask, int (*func)(), void *param);
```
The most powerful and general hook. Lets you catch **any** X11 event by specifying its event code.

Key event codes you'll use in so_long:

| Event | Code | Triggered when |
|---|---|---|
| `KeyPress` | 2 | A key is pressed |
| `KeyRelease` | 3 | A key is released |
| `DestroyNotify` | 17 | The window X is clicked |

### What is a mask? What does `1L<<0` mean?

The `mask` parameter tells X11 which category of events your window wants to receive. It is a **bitmask** — an integer where each individual bit represents one event category as a yes/no flag.

`1L` is the number `1` written as a `long` integer. `<<` is the left-shift operator — it moves bits to the left. So:

```
1L<<0  =  00000001  =  1   (KeyPressMask    — listen for key presses)
1L<<1  =  00000010  =  2   (KeyReleaseMask  — listen for key releases)
1L<<2  =  00000100  =  4   (ButtonPressMask — listen for mouse clicks)
```

You can combine them with `|` to listen to multiple event types at once:

```c
1L<<0 | 1L<<1   // listen for both key presses AND key releases
```

Think of it as a checklist where each bit is one checkbox.

In practice on Linux with MiniLibX, this mask is often ignored internally — the conventional values to use are `1L<<0` for key events and `0` for `DestroyNotify`. You will see these values in every so_long project.

#### Complete example

Here is a full program using `mlx_hook` that opens a window, prints which key was pressed to the terminal, and closes cleanly on ESC or the red X button.

```c
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

// This struct holds everything the callbacks need access to.
typedef struct s_data
{
    void    *mlx;
    void    *win;
}   t_data;

// Called every time a key is pressed.
// keycode identifies which key. param is whatever we passed at registration.
int on_keypress(int keycode, void *param)
{
    t_data  *data;

    data = (t_data *)param;
    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307) // ESC key
    {
        mlx_destroy_window(data->mlx, data->win);
        mlx_loop_end(data->mlx);
    }
    return (0);
}

// Called when the user clicks the red X button on the window.
// No keycode here — the signature is just (void *param).
int on_close(void *param)
{
    t_data  *data;

    data = (t_data *)param;
    printf("Window closed.\n");
    mlx_destroy_window(data->mlx, data->win);
    mlx_loop_end(data->mlx);
    return (0);
}

int main(void)
{
    t_data  data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 400, 300, "hook example");

    // event 2  = KeyPress,      mask 1L<<0 = KeyPressMask
    mlx_hook(data.win, 2, 1L<<0, on_keypress, &data);

    // event 17 = DestroyNotify, mask 0 (no mask needed for this event)
    mlx_hook(data.win, 17, 0, on_close, &data);

    mlx_loop(data.mlx);

    mlx_destroy_display(data.mlx);
    free(data.mlx);
    return (0);
}
```

**What happens when you run this:**
1. A 400×300 window titled "hook example" appears
2. Every time you press a key, the terminal prints its keycode, e.g.:
   ```
   Key pressed: 119
   Key pressed: 97
   Key pressed: 65307
   ```
3. On ESC or clicking the red X, the window closes and the program exits cleanly

**Why `&data` and not just `data`?**
`mlx_hook` stores your param as a `void *` — a pointer. Passing `&data` gives it the address of your struct so the callback can reach the real values inside it. If you passed `data` directly (a copy), changes inside the callback would be lost.

### `mlx_key_hook`
```c
int mlx_key_hook(void *win_ptr, int (*func)(), void *param);
```
Shortcut for hooking key presses only. Equivalent to `mlx_hook` with event `2`.
Callback signature: `func(int keycode, void *param)`

```c
int on_keypress(int keycode, void *param)
{
    if (keycode == 119) // 'w' key
        move_player_up(param);
    return (0);
}

mlx_key_hook(win, on_keypress, game);
```

### `mlx_mouse_hook`
```c
int mlx_mouse_hook(void *win_ptr, int (*func)(), void *param);
```
Registers a callback for mouse button clicks.
Callback signature: `func(int button, int x, int y, void *param)`

```c
int on_click(int button, int x, int y, void *param)
{
    if (button == 1) // left click
        ft_printf("clicked at %d, %d\n", x, y);
    return (0);
}

mlx_mouse_hook(win, on_click, NULL);
```

### `mlx_expose_hook`
```c
int mlx_expose_hook(void *win_ptr, int (*func)(), void *param);
```
Called when the window needs to be redrawn (e.g. after being uncovered by another window).
Callback signature: `func(void *param)`

### `mlx_loop_hook`
```c
int mlx_loop_hook(void *mlx_ptr, int (*func)(), void *param);
```
Registers a function called **on every iteration** of the event loop, even when no event occurs. Useful for animations.
Callback signature: `func(void *param)`

```c
int every_frame(void *param)
{
    // this runs as fast as the loop can go
    update_animation(param);
    redraw(param);
    return (0);
}

mlx_loop_hook(mlx, every_frame, game);
```

### `mlx_loop`
```c
int mlx_loop(void *mlx_ptr);
```
Starts the event loop. **This call never returns.** It continuously listens for events and calls your registered hooks.

```c
mlx_loop(mlx); // everything after this line is unreachable
```

### Why do hook registrations come before `mlx_loop`?

This is a common source of confusion. You might expect to write your hooks *inside* the loop, but that is not how it works.

The hook registration functions (`mlx_key_hook`, `mlx_hook`, etc.) **do not start any listening**. They only store your function pointer inside MiniLibX's internal data — like writing a contact into an address book. Nothing happens yet. No events are received. No functions are called.

When `mlx_loop` starts, it reads that address book and knows which functions to call when events arrive. The loop is what actually watches for events. The hooks just tell it what to do when they arrive.

```
Before mlx_loop — setup phase:

  mlx_hook(win, 2, ..., on_keypress, ...)   ← writes "on_keypress" into address book
  mlx_hook(win, 17, ..., on_close, ...)     ← writes "on_close" into address book

  mlx_loop(mlx) starts ─────────────────────────────────────────────────►
                   │                    │                    │
          [key pressed]        [X button clicked]     [each tick]
          reads address book   reads address book
          calls on_keypress()  calls on_close()
```

Think of it like setting up voicemail before leaving home. You record your message (register hooks) while things are quiet. Then you leave (call `mlx_loop`). Calls come in later, and the machine already knows what to do.

### `mlx_loop_end`
```c
int mlx_loop_end(void *mlx_ptr);
```
Signals the event loop to stop. Call this from inside a hook to exit cleanly instead of using `exit()`.

```c
int handle_keypress(int keycode, void *mlx)
{
    if (keycode == 65307)
        mlx_loop_end(mlx);
    return (0);
}
```

---

## 6. Mouse Utilities

### `mlx_mouse_get_pos`
```c
int mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
```
Fills `x` and `y` with the current mouse cursor position.

```c
int x, y;
mlx_mouse_get_pos(mlx, win, &x, &y);
```

### `mlx_mouse_move`
```c
int mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
```
Moves the cursor to `(x, y)`.

### `mlx_mouse_hide` / `mlx_mouse_show`
```c
int mlx_mouse_hide(void *mlx_ptr, void *win_ptr);
int mlx_mouse_show(void *mlx_ptr, void *win_ptr);
```
Hides or shows the cursor inside the window.

---

## 7. Miscellaneous

### `mlx_get_screen_size`
```c
int mlx_get_screen_size(void *mlx_ptr, int *width, int *height);
```
Fills in the screen's resolution.

```c
int sw, sh;
mlx_get_screen_size(mlx, &sw, &sh);
```

### `mlx_do_key_autorepeatoff` / `mlx_do_key_autorepeaton`
```c
int mlx_do_key_autorepeatoff(void *mlx_ptr);
int mlx_do_key_autorepeaton(void *mlx_ptr);
```
By default, holding a key fires repeated KeyPress events. `autorepeatoff` disables this so you get exactly one event per physical press.

### `mlx_do_sync`
```c
int mlx_do_sync(void *mlx_ptr);
```
Forces all pending drawing operations to flush to the screen immediately.

---

## The full event flow

```
main()
  │
  ├── mlx_init()           → get mlx pointer
  ├── mlx_new_window()     → get window
  ├── mlx_key_hook()       → register: "call on_keypress when key pressed"
  ├── mlx_hook(win, 17...) → register: "call on_close when X is clicked"
  ├── mlx_loop_hook()      → register: "call every_frame constantly"
  └── mlx_loop()           → hand control to MiniLibX — never returns
                                  │
                         [key pressed] → calls on_keypress()
                         [X clicked]  → calls on_close()
                         [each tick]  → calls every_frame()
```

---

## Typical so_long skeleton

```c
int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");

    // load sprites
    int w, h;
    void *player = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &w, &h);

    // register hooks
    mlx_hook(win, 2, 1L<<0, handle_keypress, game);
    mlx_hook(win, 17, 0, handle_close, game);

    // draw initial frame
    mlx_put_image_to_window(mlx, win, player, 100, 100);

    // start loop — never returns
    mlx_loop(mlx);
}
```
