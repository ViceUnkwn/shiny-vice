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
    tiles  0-3    unused (the star lives in shiny_star.png, a 32x32 sheet of its own)
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
    6: (66, 37, 47),      # star outline      (from graphics/shiny_vice/star_source.png)
    7: (240, 221, 17),    # star gold
    8: (240, 237, 103),   # star pale glint
    9: (255, 255, 255),   # star white rim
    10: (199, 105, 4),    # star orange shade
}

SHADOW, TIP, BASE, LIGHT, WHITE = 1, 2, 3, 4, 5
S_OUT, S_GOLD, S_LIGHT, S_WHITE_STAR, S_SHADE = 6, 7, 8, 9, 10


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


STAR_SRC = "graphics/shiny_vice/star_source.png"   # the supplied artwork (13 frames, 32x32)
STAR_OUT = "graphics/shiny_vice/shiny_star.png"
STAR_FRAME = 4                                       # clean, sparkle-free frame


def build_star():
    """Writes the supplied star artwork 1:1 (no resampling) as a 32x32 4bpp sheet that shares the
    fx palette (indices 6..10), so the sprite can use the owner's palette slot."""
    src = Image.open(STAR_SRC).convert("RGBA")
    frame = src.crop((STAR_FRAME * 32, 0, STAR_FRAME * 32 + 32, 32))
    box = frame.getbbox()
    art = frame.crop(box)
    key = {(66, 37, 47): S_OUT, (240, 221, 17): S_GOLD, (240, 237, 103): S_LIGHT,
           (255, 255, 255): S_WHITE_STAR, (199, 105, 4): S_SHADE}
    out = Image.new("P", (32, 32), 0)
    flat = []
    for i in range(256):
        flat.extend(PALETTE.get(i, (0, 0, 0)))
    out.putpalette(flat)
    px, ap = out.load(), art.load()
    ox, oy = (32 - art.width) // 2, (32 - art.height) // 2
    for y in range(art.height):
        for x in range(art.width):
            r, g, b, a = ap[x, y]
            if a < 128:
                continue
            c = (r, g, b)
            if c not in key:
                c = min(key, key=lambda k: sum((u - v) ** 2 for u, v in zip(k, c)))
            px[ox + x, oy + y] = key[c]
    out.save(STAR_OUT, transparency=0)
    print(f"wrote {STAR_OUT} ({art.width}x{art.height} art, 1:1)")


FRAMES = [
    # (tile, frame size, centre offset, pixels) - arms stay 1 px thin; only peaks get a bright core
    (4, 8, 3, twinkle(0)),
    (5, 8, 3, twinkle(1)),
    (6, 8, 3, twinkle(2)),
    (8, 16, 7, twinkle(1)),
    (12, 16, 7, twinkle(2)),
    (16, 16, 7, twinkle(3)),
    (20, 16, 7, twinkle(2)),
    (24, 16, 7, twinkle(3)),
    (28, 16, 7, twinkle(5, wide=1)),
    (32, 16, 7, twinkle(2, burst=1)),
    (36, 16, 7, twinkle(3, burst=1)),
    (40, 16, 7, twinkle(4, burst=2)),
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

    for tile, size, centre, pixels in FRAMES:
        for (dx, dy), v in pixels.items():
            ox, oy = centre + dx, centre + dy
            if not (0 <= ox < size and 0 <= oy < size):
                raise ValueError(f"tile {tile}: pixel {(dx, dy)} leaves the {size}x{size} frame")
            put(tile, ox, oy, v)

    im.save(OUT, transparency=0)
    build_star()
    print(f"wrote {OUT} ({width}x{height})")


if __name__ == "__main__":
    main()
