#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct CameraWork
{
    GV_ACT         actor;
    CONTROL        field_20;
    OBJECT_NO_ROTS field_9C;
    OBJECT_NO_ROTS field_C0;
    SVECTOR        field_E4;
    SVECTOR        field_EC;
    MATRIX         field_F4;
    int            field_114;
    int            field_118;
    int            field_11C;
    int            field_120;
    int            field_124;
    int            field_128;
    int            field_12C;
    int            field_130;
    SVECTOR        field_134_rots[1]; // TODO: are there 2 rots?
    int            field_13C;
    int            field_140;
    MATRIX         field_144;
    int            field_164;
    int            field_168;
    int            field_16C;
    int            field_170;
    int            field_174;
    int            field_178;
    int            field_17C;
    int            field_180;
    SVECTOR        field_184;
    int            field_18C;
    int            field_190;
    DG_PRIM       *field_194;
    DG_TEX        *field_198;
    short          field_19C;
    short          field_19E;
    SVECTOR        field_1A0;
    SVECTOR        field_1A8;
    int            field_1B0;
    int            field_1B4;
    short          field_1B8;
    short          field_1BA;
    short          field_1BC;
    short          field_1BE;
    SVECTOR        field_1C0;
    int            field_1C8;
    TARGET        *field_1CC;
    int            field_1D0;
    int            field_1D4;
    int            field_1D8;
    int            field_1DC;
    int            field_1E0;
    int            field_1E4;
    int            field_1E8;
    int            field_1EC;
    int            field_1F0;
    int            field_1F4;
    int            field_1F8;
    int            field_1FC;
    int            field_200;
    int            field_204;
    int            field_208;
    int            field_20C;
    int            field_210;
    int            field_214;
    int            field_218;
    int            field_21C;
    int            field_220;
    int            field_224;
    int            field_228;
    int            field_22C;
    int            field_230;
    int            field_234;
    int            field_238;
    int            field_23C;
    int            field_240;
    int            field_244;
    int            field_248;
    int            field_24C;
    int            field_250;
    int            field_254;
    int            field_258;
    int            field_25C;
    int            field_260;
    int            field_264;
    int            field_268;
    int            field_26C;
    int            field_270;
    int            field_274;
    int            field_278;
    unsigned short field_27C;
    short          field_27E;
    unsigned short field_280;
    unsigned short field_282;
    short          field_284;
    unsigned short field_286;
    short          field_288;
    short          field_28A;
    int            field_28C;
} CameraWork;

extern char    s01a_dword_800E44CC[];
extern char    s01a_aScamera_800E44C0[];
extern char    s01a_aCamarm_800E44AC[];
extern char    s01a_aCameral_800E44B4[];
extern SVECTOR camera_svec1_800C3B70;
extern RECT    camera_rect_800C3B68;

extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR GM_PlayerPosition_800ABA10;

// duplicate of s03e_guncame_800C7118
void s01a_camera_800D4CFC(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->field_40_pBuffers[0]->poly_ft4;
    setRGB0(poly, r, g, b);

    poly = &prim->field_40_pBuffers[1]->poly_ft4;
    setRGB0(poly, r, g, b);
}

int s01a_camera_800D4D28(char *opt, SVECTOR *svecs)
{
    int count;
    unsigned char *param;

    for (count = 0; (param = GCL_Get_Param_Result_80020AA4()); svecs++, count++)
    {
        GCL_StrToSV_80020A14(param, svecs);
    }
    return count;
}

void s01a_camera_800D4D7C(CONTROL *arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    SVECTOR svec;
    int vy;
    int ratan2val;

    GV_SubVec3_80016D40(arg1, &arg0->field_0_mov, &svec);
    arg2->vy = ratan2(svec.vx, svec.vz) & 0xFFF;
    vy = svec.vy;
    svec.vy = 0;
    ratan2val = ratan2(GV_VecLen3_80016D80(&svec), vy) & 0xFFF;
    arg2->vx = ratan2val - 1024;
    if (arg2->vx < 0)
    {
        arg2->vx = ratan2val + 3072;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D4E08.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D4FE8.s")
void s01a_camera_800D4FE8(SVECTOR *, SVECTOR *, int);

void s01a_camera_800D509C(CameraWork *work)
{
    s01a_camera_800D4D7C(&work->field_20, &GM_PlayerPosition_800ABA10, &work->field_20.field_4C_turn);
    s01a_camera_800D4FE8(&work->field_1C0, &work->field_20.field_4C_turn, work->field_282);
}

void s01a_camera_800D50EC(CameraWork *work)
{
    s01a_camera_800D4D7C(&work->field_20, &GM_PlayerPosition_800ABA10, &work->field_20.field_4C_turn);
    s01a_camera_800D4FE8(&work->field_1C0, &work->field_20.field_4C_turn, work->field_282);
    work->field_20.field_8_rot = work->field_20.field_4C_turn;
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D515C.s")

void s01a_camera_800D522C(CameraWork *work)
{
    if (mts_get_tick_count_8008BBB0() - work->field_286 >= 13)
    {
        if (work->field_28A != 0)
        {
            GM_SeSet_80032858(&work->field_20.field_0_mov, 94);
        }
        work->field_286 = mts_get_tick_count_8008BBB0();
    }
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D528C.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5338.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D53E4.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5504.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5624.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D57CC.s")
void s01a_camera_800D57CC(CameraWork *work);
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5970.s")
void s01a_camera_800D5970(CameraWork *work);
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5A68.s")
void s01a_camera_800D5A68(CameraWork *work);
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5B9C.s")
void s01a_camera_800D5B9C(CameraWork *work);

void s01a_camera_800D5C7C(CameraWork *work)
{
    switch (work->field_1E0)
    {
    case 0:
        s01a_camera_800D57CC(work);
        break;
    case 1:
        s01a_camera_800D5970(work);
        break;
    case 2:
        s01a_camera_800D5A68(work);
        break;
    case 3:
        s01a_camera_800D5B9C(work);
        break;
    }
}

void s01a_camera_800D5D10(short *arg0)
{
    // FIXME
    arg0[0x5C / 2] = arg0[0x2A / 2];
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5D1C.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5EC0.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camera_800D5F64.s")
void s01a_camera_800D5F64(CameraWork *work);

void s01a_camera_800D6174(CameraWork *work)
{
    CONTROL *ctrl;
    SVECTOR *svec;

    ctrl = &work->field_20;
    ctrl->field_3A_radar_atr |= RADAR_UNK3;

    svec = &work->field_20.field_3C;
    svec->vx = 0;
    svec->vy = work->field_27E;
    svec->vz = work->field_280 * 2;
    svec->pad = 0;
}

int s01a_camera_800D61AC(CameraWork *work, int arg1, int arg2)
{
    char *opt;

    opt = (char *)GCL_GetOption_80020968('m');
    if (opt)
    {
        // field_27C is set to 0 after the if...
        work->field_27C = GCL_StrToInt_800209E8(opt);
    }
    else
    {
        work->field_27C = 0;
    }
    work->field_27C = 0; // lol

    opt = (char *)GCL_GetOption_80020968('l');
    if (opt)
    {
        work->field_27E = GCL_StrToInt_800209E8(opt);
    }
    else
    {
        work->field_27E = 0;
    }

    opt = (char *)GCL_GetOption_80020968('w');
    if (opt)
    {
        work->field_280 = GCL_StrToInt_800209E8(opt);
        if (work->field_280 > 512)
        {
            work->field_280 = 512;
        }
    }
    else
    {
        work->field_280 = 0;
    }

    work->field_1C8 = 0;
    if (GCL_GetOption_80020968('h'))
    {
        work->field_1C8 = 1;
    }

    opt = (char *)GCL_GetOption_80020968('x');
    if (opt)
    {
        work->field_282 = GCL_StrToInt_800209E8(opt);
        if (work->field_282 > 1024)
        {
            work->field_282 = 1024;
        }
    }
    else
    {
        work->field_282 = 0;
    }

    work->field_20.field_0_mov.vy += 25;
    work->field_20.field_0_mov.vz += 450;

    work->field_EC = work->field_20.field_8_rot;
    work->field_1C0 = work->field_EC;
    if (work->field_1C0.vx > 512)
    {
        work->field_1C0.vx = 512;
    }
    work->field_EC.vx = 0;
    s01a_camera_800D4CFC(work->field_194, work->field_198, 0, 0xFF, 0);
    DG_SetPos2_8001BC8C(&work->field_20.field_0_mov, &work->field_EC);
    DG_MovePos_8001BD20(&work->field_E4);
    GM_ActObject2_80034B88((OBJECT *)&work->field_C0);
    opt = (char *)GCL_GetOption_80020968('r');
    if (opt)
    {
        work->field_19C = s01a_camera_800D4D28(opt, &work->field_1A0);
        work->field_19E = 0;
    }
    else
    {
        work->field_19C = 0;
    }
    if (work->field_27C == 2)
    {
        work->field_1A8 = work->field_1A0;
    }
    if (GCL_GetOption_80020968('e'))
    {
        work->field_28C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_28C = -1;
    }
    s01a_camera_800D6174(work);
    work->field_1E0 = 0;
    if (work->field_27C == 2)
    {
        work->field_1E8 = 3;
    }
    else
    {
        work->field_1E8 = 1;
    }
    work->field_1EC = 0;
    work->field_1F0 = 0;
    return 0;
}

int s01a_camera_800D640C(CameraWork *work)
{
    OBJECT_NO_ROTS *obj;

    obj = &work->field_C0;
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode_80016CCC(s01a_aCamarm_800E44AC), 0x36D, 0);
    GM_ConfigObjectLight_80034C44((OBJECT *)obj, &work->field_F4);
    DG_GetLightMatrix2_8001A5D8(&work->field_20.field_0_mov, &work->field_F4);
    work->field_E4.vy = -25;
    work->field_E4.vx = 0;
    work->field_E4.vz = -450;

    return 0;
}

// duplicate of s03e_guncame_800C8E04
void s01a_camera_800D648C(POLY_FT4 *poly, DG_TEX *tex, int col)
{
    char          height;
    char          width;
    unsigned char x_offset;
    unsigned char y_offset;

    setPolyFT4(poly);
    setRGB0(poly, col, col, col);
    setSemiTrans(poly, 1);

    x_offset = tex->field_8_offx;
    width = x_offset + tex->field_A_width;

    y_offset = tex->field_9_offy;
    height = y_offset + tex->field_B_height;

    poly->u0 = x_offset;
    poly->v0 = y_offset;
    poly->u1 = width;
    poly->v1 = y_offset;
    poly->u2 = x_offset;
    poly->v2 = height;
    poly->u3 = width;
    poly->v3 = height;

    poly->tpage = tex->field_4_tPage;
    poly->clut = (unsigned short)tex->field_6_clut;
}

int s01a_camera_800D6504(CameraWork *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_184.vx = 50;
    work->field_184.vy = 300;
    work->field_184.vz = 350;
    prim = DG_GetPrim(0x412, 1, 0, &work->field_184, &camera_rect_800C3B68);
    work->field_194 = prim;
    if (prim != NULL)
    {
        prim->field_2E_k500 = 500;
        work->field_198 = tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(s01a_aCameral_800E44B4));
        if (tex != NULL)
        {
            s01a_camera_800D648C(&prim->field_40_pBuffers[0]->poly_ft4, tex, 0x80);
            s01a_camera_800D648C(&prim->field_40_pBuffers[1]->poly_ft4, tex, 0x64);
            return 0;
        }
    }
    return -1;
}

int s01a_camera_800D65EC(CameraWork *work, int arg1, int arg2)
{
    TARGET         *target, *target2;
    int             type;
    char           *opt;
    CONTROL        *ctrl;
    OBJECT_NO_ROTS *obj;

    ctrl = &work->field_20;
    if (GM_InitLoader_8002599C(ctrl, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(ctrl, (char *)GCL_GetOption_80020968('p'), (char *)GCL_GetOption_80020968('d'));
    GM_ConfigControlAttribute_8002623C(ctrl, 0x49);
    GM_ConfigControlHazard_8002622C(ctrl, -1, -2, -1);

    work->field_20.field_44_step = DG_ZeroVector_800AB39C;

    type = 0x41;
    obj = &work->field_9C;

    opt = (char *)GCL_GetOption_80020968('n');
    if (opt)
    {
        type = GCL_StrToInt_800209E8(opt);
    }

    // Dead code (if with identical cases):
    if (type == 0x41)
    {
        opt = s01a_aScamera_800E44C0;
    }
    else
    {
        opt = s01a_aScamera_800E44C0;
    }
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode_80016CCC(opt), 0x32D, 0);

    obj->objs->rots = work->field_134_rots;
    GM_ConfigObjectLight_80034C44((OBJECT *)obj, &work->field_144);
    GM_ConfigObjectStep_80034C54((OBJECT *)obj, &work->field_20.field_44_step);
    DG_GetLightMatrix2_8001A5D8(&ctrl->field_0_mov, &work->field_144);

    work->field_1BA = 175;
    work->field_1B8 = 0;
    work->field_1BC = 600;

    s01a_camera_800D640C(work);
    s01a_camera_800D6504(work);

    target = GM_AllocTarget_8002D400();
    work->field_1CC = target2 = target;
    if (target)
    {
        GM_SetTarget_8002DC74(target2, 20, 2, &camera_svec1_800C3B70);
        work->field_284 = 1;
        work->field_286 = 0;
        work->field_288 = 1;
        work->field_28A = 1;
        return 0;
    }

    return -1;
}

void s01a_camera_800D678C(CameraWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->field_20);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_9C);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_C0);

    prim = work->field_194;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    GM_FreeTarget_8002D4B0(work->field_1CC);
}

GV_ACT *s01a_camera_800D67F8(int arg0, int arg1)
{
    CameraWork *work;

    work = (CameraWork *)GV_NewActor_800150E4(4, sizeof(CameraWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s01a_camera_800D5F64,
                                  (TActorFunction)s01a_camera_800D678C, s01a_dword_800E44CC);
        if (s01a_camera_800D65EC(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        s01a_camera_800D61AC(work, arg0, arg1);
    }
    return &work->actor;
}
