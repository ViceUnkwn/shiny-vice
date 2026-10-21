#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_util.h"
#include "main.h"
#include "pokemon.h"
#include "sprite.h"
#include "task.h"
#include "shiny_vice_fx.h"

#define TAG_SHINY_VICE_FX 40500

// Sheet layout (16x16 frames, 4 tiles each): 0 = star, 1..3 = twinkle small/medium/large.
#define FX_TILES_PER_FRAME 4

#define SPARKLE_BATTLE_FIRST_DELAY 150 // let the vanilla intro stars finish first
#define SPARKLE_BATTLE_MIN_GAP     50
#define SPARKLE_BATTLE_GAP_RANGE   70
#define SPARKLE_BATTLE_HALF_W      20
#define SPARKLE_BATTLE_HALF_H      22
#define SPARKLE_EMITTER_MIN_GAP    24
#define SPARKLE_EMITTER_GAP_RANGE  36

static const u32 sFxGfx[] = INCGFX_U32("graphics/shiny_vice/shiny_fx.png", ".4bpp");
static const u16 sFxPal[] = INCGFX_U16("graphics/shiny_vice/shiny_fx.png", ".gbapal");

static const struct SpriteSheet sFxSheet =
{
    .data = sFxGfx,
    .size = sizeof(sFxGfx),
    .tag = TAG_SHINY_VICE_FX,
};

static const struct SpritePalette sFxPalette =
{
    .data = sFxPal,
    .tag = TAG_SHINY_VICE_FX,
};

static const struct OamData sOamData_Fx =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1,
};

static const union AnimCmd sAnim_Star[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Star[] =
{
    sAnim_Star,
};

static const union AnimCmd sAnim_Twinkle[] =
{
    ANIMCMD_FRAME(1 * FX_TILES_PER_FRAME, 3),
    ANIMCMD_FRAME(2 * FX_TILES_PER_FRAME, 3),
    ANIMCMD_FRAME(3 * FX_TILES_PER_FRAME, 4),
    ANIMCMD_FRAME(2 * FX_TILES_PER_FRAME, 3),
    ANIMCMD_FRAME(1 * FX_TILES_PER_FRAME, 3),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Twinkle[] =
{
    sAnim_Twinkle,
};

static void SpriteCB_Twinkle(struct Sprite *sprite);
static void SpriteCB_EmitterStar(struct Sprite *sprite);

static const struct SpriteTemplate sSpriteTemplate_Twinkle =
{
    .tileTag = TAG_SHINY_VICE_FX,
    .paletteTag = TAG_SHINY_VICE_FX,
    .oam = &sOamData_Fx,
    .anims = sAnimTable_Twinkle,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Twinkle,
};

static const struct SpriteTemplate sSpriteTemplate_Star =
{
    .tileTag = TAG_SHINY_VICE_FX,
    .paletteTag = TAG_SHINY_VICE_FX,
    .oam = &sOamData_Fx,
    .anims = sAnimTable_Star,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_EmitterStar,
};

// Private LCG: visual randomness must never touch Random()/gRngValue.
static u32 sFxRng;

static u32 FxRandom(u32 range)
{
    if (sFxRng == 0)
        sFxRng = gMain.vblankCounter1 | 1;
    sFxRng = sFxRng * 1103515245 + 12345;
    return ((sFxRng >> 16) & 0x7FFF) % range;
}

static bool32 LoadFxGfx(void)
{
    if (GetSpriteTileStartByTag(TAG_SHINY_VICE_FX) == 0xFFFF)
    {
        if (LoadSpriteSheet(&sFxSheet) == 0xFFFF)
            return FALSE;
    }
    if (IndexOfSpritePaletteTag(TAG_SHINY_VICE_FX) == 0xFF)
    {
        if (LoadSpritePalette(&sFxPalette) == 0xFF)
            return FALSE;
    }
    return TRUE;
}

static void SpriteCB_Twinkle(struct Sprite *sprite)
{
    if (sprite->animEnded)
        DestroySprite(sprite);
}

void ShinyViceFx_SpawnSparkle(s16 x, s16 y, u8 oamPriority, u8 subpriority)
{
    u8 spriteId;

    if (!LoadFxGfx())
        return;
    spriteId = CreateSprite(&sSpriteTemplate_Twinkle, x, y, subpriority);
    if (spriteId != MAX_SPRITES)
        gSprites[spriteId].oam.priority = oamPriority;
}

// Emitter star sprite data
#define sTimer   data[0]
#define sAreaX   data[1]
#define sAreaY   data[2]
#define sHalfW   data[3]
#define sHalfH   data[4]

static void SpriteCB_EmitterStar(struct Sprite *sprite)
{
    if (sprite->invisible)
        return;
    if (sprite->sTimer > 0)
    {
        sprite->sTimer--;
        return;
    }
    sprite->sTimer = SPARKLE_EMITTER_MIN_GAP + FxRandom(SPARKLE_EMITTER_GAP_RANGE);
    ShinyViceFx_SpawnSparkle(sprite->sAreaX - sprite->sHalfW + (s32)FxRandom(sprite->sHalfW * 2 + 1),
                             sprite->sAreaY - sprite->sHalfH + (s32)FxRandom(sprite->sHalfH * 2 + 1),
                             sprite->oam.priority,
                             0);
}

u8 ShinyViceFx_CreateEmitterStar(s16 x, s16 y, s16 areaX, s16 areaY, u8 halfW, u8 halfH, u8 oamPriority)
{
    u8 spriteId;

    if (!LoadFxGfx())
        return SPRITE_NONE;
    spriteId = CreateSprite(&sSpriteTemplate_Star, x, y, 0);
    if (spriteId == MAX_SPRITES)
        return SPRITE_NONE;
    gSprites[spriteId].oam.priority = oamPriority;
    gSprites[spriteId].sTimer = SPARKLE_EMITTER_MIN_GAP;
    gSprites[spriteId].sAreaX = areaX;
    gSprites[spriteId].sAreaY = areaY;
    gSprites[spriteId].sHalfW = halfW;
    gSprites[spriteId].sHalfH = halfH;
    return spriteId;
}

#undef sTimer
#undef sAreaX
#undef sAreaY
#undef sHalfW
#undef sHalfH

// Battle sparkle task data
#define tBattler data[0]
#define tTimer   data[1]

static void Task_BattleSparkle(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u32 battler = tBattler;
    struct Pokemon *mon;
    struct Pokemon *illusionMon;
    struct Sprite *monSprite;
    s16 x, y;

    if (!gMain.inBattle || gBattleSpritesDataPtr == NULL || battler >= gBattlersCount)
    {
        DestroyTask(taskId);
        return;
    }

    if (tTimer > 0)
    {
        tTimer--;
        return;
    }
    tTimer = SPARKLE_BATTLE_MIN_GAP + FxRandom(SPARKLE_BATTLE_GAP_RANGE);

    if (!IsBattlerSpriteVisible(battler) || gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
        return;

    mon = GetBattlerMon(battler);
    illusionMon = GetIllusionMonPtr(battler);
    if (illusionMon != NULL)
        mon = illusionMon;
    if (!IsValidForBattle(mon) || !IsMonShiny(mon))
        return;

    monSprite = &gSprites[gBattlerSpriteIds[battler]];
    x = GetBattlerSpriteCoord(battler, BATTLER_COORD_X) - SPARKLE_BATTLE_HALF_W + (s32)FxRandom(SPARKLE_BATTLE_HALF_W * 2 + 1);
    y = GetBattlerSpriteCoord(battler, BATTLER_COORD_Y) - SPARKLE_BATTLE_HALF_H + (s32)FxRandom(SPARKLE_BATTLE_HALF_H * 2 + 1);
    ShinyViceFx_SpawnSparkle(x, y, monSprite->oam.priority, 0);
}

void ShinyViceFx_StartBattleSparkle(u32 battler)
{
    u32 i;
    u8 taskId;

    for (i = 0; i < NUM_TASKS; i++)
    {
        if (gTasks[i].isActive && gTasks[i].func == Task_BattleSparkle && gTasks[i].data[0] == battler)
            return;
    }
    taskId = CreateTask(Task_BattleSparkle, 20);
    gTasks[taskId].tBattler = battler;
    gTasks[taskId].tTimer = SPARKLE_BATTLE_FIRST_DELAY;
}

#undef tBattler
#undef tTimer
