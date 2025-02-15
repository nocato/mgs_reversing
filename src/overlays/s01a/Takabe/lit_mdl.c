#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct LitMdlWork
{
    GV_ACT         actor;
    int            field_20;
    OBJECT_NO_ROTS field_24_obj;
    MATRIX         field_48_light;
    short          field_68;
    short          field_6A;
    short          field_6C;
    short          field_6E;
    int            field_70;
    short          field_74;
    short          field_76;
    int            field_78;
    int            field_7C;
    int            field_80;
    int            field_84;
    MATRIX         field_88_root;
    int            field_A8;
    int            field_AC;
    int            field_B0;
    int            field_B4;
    int            field_B8;
    int            field_BC;
    int            field_C0;
    int            field_C4;

    DG_DEF field_C8;
    DG_MDL field_E8;

    SVECTOR        field_140_vertexIndexOffsets[49];
    unsigned char  field_2C8_faceIndexOffsets[144];
    SVECTOR        field_358_normalIndexOffsets[7];
    unsigned char  field_390_normalFaceOffsets[144];
    unsigned char  field_420_uvOffsets[288];
    unsigned short field_540_materialOffsets[36];
} LitMdlWork;

DG_DEF litmdl_dg_def =
{
    1, 1,
    {-32000, -32000, -32000},
    {32000, 32000, 32000},
    {
        {
            1027, 36,
            {-32000, -32000, -32000},
            {32000, 32000, 32000},
            {0, 0, 0},
            -1, -1, 49,
            NULL, NULL, 6, NULL,
            NULL, NULL, NULL, 0
        }
    }
};

extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_lit_mdl_800E26EC.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_lit_mdl_800E2928.s")

void s01a_lit_mdl_800E2ABC(LitMdlWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->field_24_obj);
}

void s01a_lit_mdl_800E2D64(LitMdlWork *, SVECTOR *);

int s01a_lit_mdl_800E2ADC(LitMdlWork *work, int arg2, int arg3, int arg4, int raise)
{
    OBJECT_NO_ROTS *obj;
    short           map;

    memcpy(&work->field_C8, &litmdl_dg_def, sizeof(DG_DEF) + sizeof(DG_MDL));
    s01a_lit_mdl_800E2D64(work, &DG_ZeroVector_800AB39C);

    obj = &work->field_24_obj;
    obj->flag = 0x15D;
    obj->light = &work->field_48_light;
    obj->map_name = GM_CurrentMap_800AB9B0;
    obj->objs = DG_MakeObjs_80031760(&work->field_C8, obj->flag, 0);
    DG_QueueObjs_80018178(obj->objs);

    map = obj->map_name;
    work->field_24_obj.objs->group_id = map;
    work->field_24_obj.objs->root = &work->field_88_root;
    work->field_24_obj.objs->light = &work->field_48_light;
    work->field_24_obj.objs->objs[0].raise = raise;
    work->field_20 = GM_CurrentMap_800AB9B0;
    work->field_88_root = DG_ZeroMatrix_8009D430;
    work->field_B0 = 1;
    work->field_A8 = arg2;
    work->field_AC = arg3;
    work->field_B4 = arg4;
    work->field_B8 = arg4 / 6;
    work->field_BC = arg4 / 6;
    return 0;
}

void s01a_lit_mdl_800E2928(LitMdlWork *);

GV_ACT *s01a_lit_mdl_800E2C88(int arg0, int arg1, int arg2, int arg3)
{
    LitMdlWork *work;

    work = (LitMdlWork *)GV_NewActor_800150E4(7, sizeof(LitMdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s01a_lit_mdl_800E2928,
                                  (TActorFunction)s01a_lit_mdl_800E2ABC, "lit_mdl.c");
        if (s01a_lit_mdl_800E2ADC(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

void s01a_lit_mdl_800E2D3C(LitMdlWork *work, int ang)
{
    work->field_B4 = ang;
    work->field_B8 = ang / 6;
    work->field_BC = ang / 6;
}

void s01a_lit_mdl_800E2D64(LitMdlWork *work, SVECTOR *unused)
{
    DG_MDL        *mdl;
    int            i, j;
    unsigned char *faceIndexOffsetIter;
    int            curFaceIndexOffset;
    char          *uvOffsetIter;
    SVECTOR       *vertexIndexOffsetIter;
    short         *materialOffsetIter;
    SVECTOR       *normalIndexOffsetIter;
    char          *normalFaceOffsetIter;
    int            uvOff1, uvOff2, uvOff3, uvOff4;
    short          hash;

    mdl = &work->field_E8;
    mdl->vertexIndexOffset_38 = work->field_140_vertexIndexOffsets;
    mdl->normalIndexOffset_44 = work->field_358_normalIndexOffsets;
    mdl->normalFaceOffset_48 = work->field_390_normalFaceOffsets;
    mdl->uvOffset_4C = work->field_420_uvOffsets;
    faceIndexOffsetIter = mdl->faceIndexOffset_3C = work->field_2C8_faceIndexOffsets;
    mdl->materialOffset_50 = work->field_540_materialOffsets;

    for (j = 0; j < 6; j++)
    {
        curFaceIndexOffset = j * 7;
        for (i = 6; i > 0; curFaceIndexOffset++, i--)
        {
            *faceIndexOffsetIter++ = curFaceIndexOffset;
            *faceIndexOffsetIter++ = curFaceIndexOffset + 7;
            *faceIndexOffsetIter++ = curFaceIndexOffset + 8;
            *faceIndexOffsetIter++ = curFaceIndexOffset + 1;
        }
    }

    vertexIndexOffsetIter = work->field_140_vertexIndexOffsets;
    for (i = 49; i > 0; vertexIndexOffsetIter++, i--)
    {
        LSTORE(0, &vertexIndexOffsetIter->vx);
        LSTORE(0, &vertexIndexOffsetIter->vz);
    }

    hash = 0x59FC;
    DG_GetTexture_8001D830(hash);

    materialOffsetIter = work->field_540_materialOffsets;
    for (i = 36; i > 0; materialOffsetIter++, i--)
    {
        *materialOffsetIter = hash;
    }

    uvOffsetIter = work->field_420_uvOffsets;
    uvOff3 = 0;
    for (j = 0; j < 6; j++)
    {
        uvOff1 = uvOff3;
        uvOff3 = (j + 1) * 255 / 6;
        uvOff3 *= 2;

        if (uvOff3 > 255)
        {
            uvOff3 = 511 - uvOff3;
        }

        uvOff4 = 0;
        for (i = 0; i < 6; i++)
        {
            uvOff2 = uvOff4;
            uvOff4 = (i + 1) * 255 / 6;
            uvOff4 *= 2;

            if (uvOff4 > 255)
            {
                uvOff4 = 511 - uvOff4;
            }

            uvOffsetIter[0] = uvOff1;
            uvOffsetIter[1] = uvOff2;
            uvOffsetIter[2] = uvOff3;
            uvOffsetIter[3] = uvOff2;
            uvOffsetIter[4] = uvOff3;
            uvOffsetIter[5] = uvOff4;
            uvOffsetIter[6] = uvOff1;
            uvOffsetIter[7] = uvOff4;
            uvOffsetIter += 8;
        }
    }

    normalFaceOffsetIter = work->field_390_normalFaceOffsets;
    for (j = 0; j < 6; j++)
    {
        for (i = 6; i > 0; i--)
        {
            *normalFaceOffsetIter++ = 0;
            *normalFaceOffsetIter++ = 0;
            *normalFaceOffsetIter++ = 0;
            *normalFaceOffsetIter++ = 0;
        }
    }

    normalIndexOffsetIter = work->field_358_normalIndexOffsets;
    for (i = 6; i > 0; normalIndexOffsetIter++, i--)
    {
        normalIndexOffsetIter->vx = 0;
        normalIndexOffsetIter->vy = 0;
    }

    work->field_48_light.m[0][0] = 0;
    work->field_48_light.m[0][1] = 0;
    work->field_48_light.m[0][2] = 0;

    work->field_68 = 0;
    work->field_6E = 0;
    work->field_74 = 0;

    work->field_48_light.t[0] = 56;
    work->field_48_light.t[1] = 71;
    work->field_48_light.t[2] = 47;
}
