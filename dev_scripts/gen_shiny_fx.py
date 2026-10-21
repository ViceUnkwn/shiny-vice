#!/usr/bin/env python3
"""Regenerates graphics/shiny_vice/shiny_fx.png (the Shiny Vice star icon + twinkle frames).

Run from the repo root:   python3 dev_scripts/gen_shiny_fx.py
Needs Pillow:             pip install pillow

Palette contract (must match include/shiny_vice_tint.h):
    0        transparent
    1..4     tintable ramp, recoloured at runtime from the Pokemon's shiny palette:
             1 = drop shadow, 2 = tip, 3 = base, 4 = light
    5        white core (never tinted)
    6..10    gold star icon (never tinted): outline, gold, light, highlight, shade

Sheet layout (16 px wide = 2 tiles per row; tile = (y / 8) * 2 + (x / 8)):
    tiles  0-3    star icon, 16x16 frame, 11x11 art centred on pixel (8, 8)
    tiles  4-6    small twinkle, 8x8 frames x3 (tile 7 unused)
    tiles  8..    medium twinkle, 16x16 frames x3   (8, 12, 16)
    tiles 20..    large twinkle,  16x16 frames x3   (20, 24, 28)
    tiles 32..    burst glint,    16x16 frames x3   (32, 36, 40)
Twinkle art is centred on pixel (3, 3) of an 8x8 frame and (7, 7) of a 16x16 frame so the
1 px drop shadow (+1, +1) always stays inside the frame.
"""
from PIL import Image

OUT = "graphics/shiny_vice/shiny_fx.png"

# Default (gold) palette. Entries 1..4 are overwritten at runtime by ShinyViceTint_Apply.
PALETTE = {
    0: (112, 160, 192),   # transparent key
    1: (96, 80, 16),
    2: (176, 144, 32),
    3: (248, 200, 48),
    4: (248, 224, 144),
    5: (248, 248, 248),
    6: (104, 56, 0),      # star outline
    7: (248, 192, 16),    # star gold
    8: (248, 240, 112),   # star light (upper-left edges)
    9: (248, 248, 216),   # star highlight
    10: (192, 128, 8),    # star shade (lower-right edges)
}

SHADOW, TIP, BASE, LIGHT, WHITE = 1, 2, 3, 4, 5
S_OUT, S_GOLD, S_LIGHT, S_HI, S_SHADE = 6, 7, 8, 9, 10


def twinkle(arm, wide=0, burst=0):
    """4-point twinkle as {(dx, dy): palette index}.

    arm   : arm length in pixels beyond the centre
    wide  : how many steps out from the centre the arms get 1 px of body either side
    burst : length of the short diagonal arms (0 = plain 4-point star)
    A 1 px drop shadow (+1, +1) is added under every pixel instead of a full outline, which
    keeps the arms thin but still readable on both pale and dark backgrounds.
    """
    p = {(0, 0): WHITE}
    for d in range(1, arm + 1):
        v = LIGHT if d == 1 else (TIP if d == arm and arm >= 3 else BASE)
        for dx, dy in ((d, 0), (-d, 0), (0, d), (0, -d)):
            p[(dx, dy)] = v
    for d in range(1, wide + 1):
        for s in (1, -1):
            for dx, dy in ((d, s), (-d, s), (s, d), (s, -d)):
                if (dx, dy) not in p:
                    p[(dx, dy)] = LIGHT if (abs(dx) == 1 and abs(dy) == 1) else BASE
    for d in range(1, burst + 1):
        for dx, dy in ((d, d), (-d, d), (d, -d), (-d, -d)):
            p[(dx, dy)] = LIGHT if d == 1 else (TIP if d == burst and burst >= 2 else BASE)
    out = dict(p)
    for (x, y) in p:
        if (x + 1, y + 1) not in p:
            out[(x + 1, y + 1)] = SHADOW
    return out


# 9x9 star body; the 1 px outline added around it makes the icon 11x11.
STAR_FILL = [
    "....#....",
    "...###...",
    "...###...",
    "#########",
    ".#######.",
    "..#####..",
    "..#####..",
    ".###.###.",
    ".##...##.",
]


def star_icon():
    h, w = len(STAR_FILL), len(STAR_FILL[0])
    fill = set()
    for y, row in enumerate(STAR_FILL):
        for x, c in enumerate(row):
            if c == "#":
                fill.add((x + 1, y + 1))
    px = {}
    for (x, y) in fill:
        v = S_GOLD
        if (x, y - 1) not in fill or (x - 1, y) not in fill:
            v = S_LIGHT                      # lit upper-left edges
        if (x, y + 1) not in fill or (x + 1, y) not in fill:
            v = S_SHADE                      # shaded lower-right edges
        px[(x, y)] = v
    for y in range(h + 2):
        for x in range(w + 2):
            if (x, y) not in fill and any(
                    n in fill for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1))):
                px[(x, y)] = S_OUT
    px[(3, 3)] = S_HI                        # one bright glint on the upper-left arm
    return px                                # 11x11, origin top-left


FRAMES = [
    # (tile, frame size, centre offset, pixels)
    (4, 8, 3, twinkle(1)),
    (5, 8, 3, twinkle(2)),
    (6, 8, 3, twinkle(3, wide=1)),
    (8, 16, 7, twinkle(3, wide=1)),
    (12, 16, 7, twinkle(4, wide=1)),
    (16, 16, 7, twinkle(5, wide=1)),
    (20, 16, 7, twinkle(4, wide=1)),
    (24, 16, 7, twinkle(6, wide=1)),
    (28, 16, 7, twinkle(7, wide=2)),
    (32, 16, 7, twinkle(3, burst=1)),
    (36, 16, 7, twinkle(5, wide=1, burst=2)),
    (40, 16, 7, twinkle(7, wide=1, burst=3)),
]


def main():
    width, height = 16, 22 * 8
    im = Image.new("P", (width, height), 0)
    flat = []
    for i in range(256):
        flat.extend(PALETTE.get(i, (0, 0, 0)))
    im.putpalette(flat)
    px = im.load()

    def put(tile, ox, oy, idx):
        x = (tile % 2) * 8 + ox
        y = (tile // 2) * 8 + oy
        if not (0 <= x < width and 0 <= y < height):
            raise ValueError("pixel outside sheet")
        px[x, y] = idx

    # star icon: 11x11 art placed so its centre pixel lands on (8, 8) of a 16x16 frame
    for (x, y), v in star_icon().items():
        put(0, x + 3, y + 3, v)

    for tile, size, centre, pixels in FRAMES:
        for (dx, dy), v in pixels.items():
            ox, oy = centre + dx, centre + dy
            if not (0 <= ox < size and 0 <= oy < size):
                raise ValueError(f"tile {tile}: pixel {(dx, dy)} leaves the {size}x{size} frame")
            put(tile, ox, oy, v)

    im.save(OUT, transparency=0)
    print(f"wrote {OUT} ({width}x{height})")


if __name__ == "__main__":
    main()
