#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"

typedef struct SmokeWork
{
    GV_ACT   actor;
    DG_PRIM *field_20;
    SVECTOR  field_24;
    DG_TEX  *field_2C;
    int      field_30;
    int      field_34;
    int      field_38;
    int      field_3C;
} SmokeWork;

const char aSmoke[] = "smoke";
const char aSmokeC[] = "smoke.c";

RECT smoke_rect = {500, 1000, 1000, 2000};

extern int GM_CurrentMap_800AB9B0;
extern int GV_Clock_800AB920;

int s00a_smoke_800D2694(SmokeWork *work)
{
    int       color;
    POLY_FT4 *poly;

    if (work->field_3C > 128)
    {
        return 1;
    }

    poly = &work->field_20->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;
    color = work->field_3C / 2;
    poly->r0 = color;
    poly->g0 = color;
    poly->b0 = color;
    work->field_3C++;
    return 0;
}

int s00a_smoke_800D26F0(SmokeWork *work)
{
    int       color;
    POLY_FT4 *poly;

    if (work->field_3C > 128)
    {
        return 1;
    }

    poly = &work->field_20->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;
    color = 64 - work->field_3C / 2;
    poly->r0 = color;
    poly->g0 = color;
    poly->b0 = color;
    work->field_3C++;
    return 0;
}

void s00a_smoke_800D2758(POLY_FT4 *poly, DG_TEX *text, SmokeWork *work)
{
    short clut;
    int   x0, y0;
    int   width, height;
    int   field_30;
    char  offx, offy;

    if (++work->field_30 >= 59)
    {
        work->field_30 = 0;
    }

    field_30 = work->field_30 / 2;
    y0 = field_30 & 0xF;
    x0 = field_30 / 8;
    x0 = x0 & 0x3;

    width = text->field_A_width + 1;
    offx = text->field_8_offx;

    poly->u0 = poly->u2 = offx + width * y0 / 8;
    poly->u1 = poly->u3 = offx + width * (y0 + 1) / 8 - 1;

    height = text->field_B_height + 1;
    offy = text->field_9_offy;

    poly->v0 = poly->v1 = offy + height * x0 / 4;
    poly->v2 = poly->v3 = offy + height * (x0 + 1) / 4 - 1;

    poly->tpage = text->field_4_tPage;
    clut = text->field_6_clut;

    poly->y1 += 100;

    poly->clut = clut;
    poly->tpage = (poly->tpage & 0xFF9F) | 0x20;
}

void s00a_smoke_800D2888(POLY_FT4 *prim, DG_TEX *unused, short color)
{
    DG_TEX        *tex1, *tex2;
    unsigned short tpage;
    int            width, height;
    unsigned char  offx, offy;
    short          clut;

    // We already have this exact texture in variable called "unused", but let's waste
    // cycles and get it again just to be sure:
    tex1 = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aSmoke));
    tex2 = tex1; // ...and make an additional copy to waste even more cycles

    setPolyFT4(prim);
    setSemiTrans(prim, 1);

    prim->r0 = color;
    prim->g0 = color;
    prim->b0 = color;

    width = tex1->field_A_width;
    offx = tex1->field_8_offx;
    prim->u0 = prim->u2 = offx;
    prim->u1 = prim->u3 = offx + (width + 1) / 8 - 1;

    height = tex1->field_B_height;
    offy = tex1->field_9_offy;
    prim->v0 = prim->v1 = offy;
    prim->v2 = prim->v3 = offy + (height + 1) / 4 - 1;

    tpage = tex2->field_4_tPage;
    prim->tpage = tpage;

    clut = tex2->field_6_clut;

    prim->tpage = (tpage & 0xFF9F) | 0x20;
    prim->clut = clut;
}

void s00a_smoke_800D296C(SmokeWork *work)
{
    switch (work->field_34)
    {
    case 0:
        if (work->field_3C > 100)
        {
            work->field_3C = 0;
            work->field_34 = 1;
        }
        work->field_3C++;
        break;
    case 1:
        if (s00a_smoke_800D26F0(work))
        {
            work->field_3C = 0x1E;
            work->field_38 = 2;
            work->field_34 = 5;
        }
        break;
    case 2:
        if (s00a_smoke_800D2694(work))
        {
            work->field_3C = 0;
            work->field_34 = 0;
        }
        break;
    case 5:
        if (--work->field_3C <= 0)
        {
            work->field_3C = 0;
            work->field_34 = work->field_38;
        }
        break;
    }
    s00a_smoke_800D2758(&work->field_20->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4, work->field_2C, work);
}

void s00a_smoke_800D2A80(SmokeWork *work)
{
    s00a_smoke_800D296C(work);
}

void s00a_smoke_800D2AA0(SmokeWork *work)
{
    DG_PRIM *prim;

    prim = work->field_20;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void s00a_smoke_800D2ADC(SVECTOR *svec)
{
    GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), svec);
}

int s00a_smoke_800D2B0C(SmokeWork *work, int where)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    GM_CurrentMap_800AB9B0 = where;
    prim = DG_GetPrim(0x412, 1, 0, &work->field_24, &smoke_rect);
    work->field_20 = prim;
    if (prim != NULL)
    {
        tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aSmoke));
        work->field_2C = tex;
        if (tex != 0)
        {
            s00a_smoke_800D2888(&prim->field_40_pBuffers[0]->poly_ft4, tex, 0x80);
            s00a_smoke_800D2888(&prim->field_40_pBuffers[1]->poly_ft4, tex, 0x80);
            work->field_30 = GV_RandU_80017090(0x1FU);
            work->field_3C = 0;
            work->field_34 = 0;
            return 0;
        }
    }
    return -1;
}

GV_ACT *s00a_smoke_800D2BEC(int name, int where, int argc, char **argv)
{
    SmokeWork *work;

    work = (SmokeWork *)GV_NewActor_800150E4(5, sizeof(SmokeWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_smoke_800D2A80,
                                  (TActorFunction)s00a_smoke_800D2AA0, aSmokeC);
        s00a_smoke_800D2ADC(&work->field_24);
        if (s00a_smoke_800D2B0C(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
