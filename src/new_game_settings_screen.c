#include "global.h"
#include "new_game_settings_screen.h"
#include "bg.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "main_menu.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "shiny_vice_settings.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/rgb.h"

// This screen is built the same way as the Options menu (src/option_menu.c) and reuses its look:
// a header window, a list window with one 16px row per setting, and the highlighted row shown with
// a window effect. The list window fits exactly 7 rows, which is what ROW_COUNT is.

#define tMenuSelection  data[0]
#define tStarterRegion  data[1]
#define tConfirmed      data[2]

enum
{
    ROW_STARTER_REGION,
    ROW_DIFFICULTY,
    ROW_LEVEL_CAP,
    ROW_GRIND_MODE,
    ROW_NUZLOCKE,   // coming soon, skipped by the cursor
    ROW_RANDOMIZER, // coming soon, skipped by the cursor
    ROW_START,
    ROW_COUNT,
};

enum
{
    WIN_HEADER,
    WIN_OPTIONS,
};

#define VALUE_X        104 // left edge of each row's value area inside the list window
#define VALUE_RIGHT_X  198 // right edge that right-aligned values line up with
#define LIST_WIDTH_PX  208 // the list window is 26 tiles wide

static void Task_FadeIn(u8 taskId);
static void Task_ProcessInput(u8 taskId);
static void Task_FadeOut(u8 taskId);
static void StartFadeOut(u8 taskId, bool8 confirmed);
static void HighlightRow(u8 row);
static void DrawHeaderText(void);
static void DrawRowLabels(void);
static void DrawRowValue(u8 row, u8 starterRegion);
static void DrawBgWindowFrames(void);

static const u16 sMenuText_Pal[] = INCGFX_U16("graphics/interface/option_menu_text.pal", ".gbapal");
static const u16 sMenuBg_Pal[] = {RGB(17, 18, 31)};

static const u8 sText_Header[] = _("NEW GAME SETTINGS");

static const u8 *const sRowLabels[ROW_COUNT] =
{
    [ROW_STARTER_REGION] = COMPOUND_STRING("STARTERS"),
    [ROW_DIFFICULTY]     = COMPOUND_STRING("DIFFICULTY"),
    [ROW_LEVEL_CAP]      = COMPOUND_STRING("LEVEL CAP"),
    [ROW_GRIND_MODE]     = COMPOUND_STRING("MIN GRINDING"),
    [ROW_NUZLOCKE]       = COMPOUND_STRING("NUZLOCKE"),
    [ROW_RANDOMIZER]     = COMPOUND_STRING("RANDOMIZER"),
    [ROW_START]          = COMPOUND_STRING("START GAME"),
};

// Every value string starts with the same green colour codes the Options menu uses. DrawChoice swaps
// bytes 2 and 5 of a copy of the string to turn the selected choice red, exactly like option_menu.c.
static const u8 sText_Hoenn[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}HOENN");
static const u8 sText_Kanto[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}KANTO");
static const u8 sText_Johto[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}JOHTO");
static const u8 sText_Sinnoh[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SINNOH");
static const u8 sText_Unova[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}UNOVA");
static const u8 sText_Kalos[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}KALOS");
static const u8 sText_Alola[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}ALOLA");
static const u8 sText_Galar[]  = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}GALAR");
static const u8 sText_Paldea[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}PALDEA");

static const u8 sText_Normal[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}NORMAL");
static const u8 sText_HardDisabled[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}HARD");
static const u8 sText_Soon[]   = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}SOON");
static const u8 sText_LocksIn[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}LOCKS IN");

static const u8 *const sRegionTexts[SV_REGION_COUNT] =
{
    [SV_REGION_HOENN]  = sText_Hoenn,
    [SV_REGION_KANTO]  = sText_Kanto,
    [SV_REGION_JOHTO]  = sText_Johto,
    [SV_REGION_SINNOH] = sText_Sinnoh,
    [SV_REGION_UNOVA]  = sText_Unova,
    [SV_REGION_KALOS]  = sText_Kalos,
    [SV_REGION_ALOLA]  = sText_Alola,
    [SV_REGION_GALAR]  = sText_Galar,
    [SV_REGION_PALDEA] = sText_Paldea,
};

// Same window and background layout as the Options menu.
static const struct WindowTemplate sWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitNewGameSettings(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        ChangeBgX(3, 0, BG_COORD_SET);
        ChangeBgY(3, 0, BG_COORD_SET);
        InitWindows(sWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sMenuBg_Pal, BG_PLTT_ID(0), sizeof(sMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sMenuText_Pal, BG_PLTT_ID(1), sizeof(sMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        PutWindowTilemap(WIN_OPTIONS);
        DrawRowLabels();
        gMain.state++;
        break;
    case 8:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 9:
    {
        u8 taskId = CreateTask(Task_FadeIn, 0);
        struct ShinyViceSettings defaults;
        u8 row;

        ShinyViceSettings_SetDefaults(&defaults);
        gTasks[taskId].tMenuSelection = ROW_STARTER_REGION;
        gTasks[taskId].tStarterRegion = defaults.starterRegion;
        gTasks[taskId].tConfirmed = FALSE;

        for (row = 0; row < ROW_COUNT; row++)
            DrawRowValue(row, gTasks[taskId].tStarterRegion);
        HighlightRow(gTasks[taskId].tMenuSelection);

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    }
    case 10:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_FadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_ProcessInput;
}

static bool8 IsRowSelectable(u8 row)
{
    return row == ROW_STARTER_REGION || row == ROW_START;
}

static u8 NextRow(u8 row, s8 direction)
{
    do
    {
        row = (row + direction + ROW_COUNT) % ROW_COUNT;
    } while (!IsRowSelectable(row));
    return row;
}

static s16 WrapValue(s16 value, s8 direction, u8 count)
{
    return (value + direction + count) % count;
}

static void Task_ProcessInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (JOY_NEW(A_BUTTON))
    {
        if (tMenuSelection == ROW_START)
            StartFadeOut(taskId, TRUE);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        StartFadeOut(taskId, FALSE);
    }
    else if (JOY_NEW(DPAD_UP))
    {
        tMenuSelection = NextRow(tMenuSelection, -1);
        HighlightRow(tMenuSelection);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        tMenuSelection = NextRow(tMenuSelection, 1);
        HighlightRow(tMenuSelection);
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        s8 direction = JOY_NEW(DPAD_RIGHT) ? 1 : -1;

        if (tMenuSelection != ROW_STARTER_REGION)
            return;

        tStarterRegion = WrapValue(tStarterRegion, direction, SV_REGION_COUNT);

        DrawRowValue(tMenuSelection, tStarterRegion);
        CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
    }
}

static void StartFadeOut(u8 taskId, bool8 confirmed)
{
    s16 *data = gTasks[taskId].data;

    tConfirmed = confirmed;
    if (confirmed)
    {
        struct ShinyViceSettings settings;

        ShinyViceSettings_SetDefaults(&settings);
        settings.starterRegion = tStarterRegion;
        ShinyViceSettings_StagePending(&settings);
    }

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_FadeOut;
}

static void Task_FadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        bool8 confirmed = gTasks[taskId].tConfirmed;

        DestroyTask(taskId);
        FreeAllWindowBuffers();
        if (confirmed)
            SetMainCallback2(CB2_NewGameBirchSpeechAfterSettings);
        else
            SetMainCallback2(CB2_ReinitMainMenu);
    }
}

static void HighlightRow(u8 row)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(row * 16 + 40, row * 16 + 56));
}

// Draws one choice. The selected choice is drawn red; the others keep the green codes in the string.
static void DrawChoice(const u8 *text, u8 x, u8 row, bool8 selected)
{
    u8 buffer[32];
    u16 i;

    for (i = 0; text[i] != EOS && i < ARRAY_COUNT(buffer) - 1; i++)
        buffer[i] = text[i];

    if (selected)
    {
        buffer[2] = TEXT_COLOR_RED;
        buffer[5] = TEXT_COLOR_LIGHT_RED;
    }

    buffer[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, buffer, x, row * 16 + 1, TEXT_SKIP_DRAW, NULL);
}

static void DrawRowValue(u8 row, u8 starterRegion)
{
    // Clear the row's value area first: values change width (for example KANTO -> SINNOH).
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), VALUE_X, row * 16, LIST_WIDTH_PX - VALUE_X, 16);

    switch (row)
    {
    case ROW_STARTER_REGION:
        DrawChoice(sRegionTexts[starterRegion], VALUE_X, row, TRUE);
        break;
    case ROW_DIFFICULTY:
        DrawChoice(sText_Normal, VALUE_X, row, TRUE);
        DrawChoice(sText_HardDisabled, GetStringRightAlignXOffset(FONT_NORMAL, sText_HardDisabled, VALUE_RIGHT_X), row, FALSE);
        break;
    case ROW_LEVEL_CAP:
    case ROW_GRIND_MODE:
    case ROW_NUZLOCKE:
    case ROW_RANDOMIZER:
        DrawChoice(sText_Soon, VALUE_X, row, FALSE);
        break;
    case ROW_START:
        DrawChoice(sText_LocksIn, VALUE_X, row, FALSE);
        break;
    }
}

static void DrawHeaderText(void)
{
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, sText_Header, 8, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void DrawRowLabels(void)
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < ROW_COUNT; i++)
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, sRowLabels[i], 8, (i * 16) + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options list window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
