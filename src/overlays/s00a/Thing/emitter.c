#include "linker.h"
#include "Game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[8];
    char     pad[0x4];
} Work;

RECT rect_800C3320 = { 1000, 1000, 2000, 2000 };

extern int  GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 5

void EmitterShadePacks_800C3C08( POLY_FT4 *packs, int n_packs, DG_TEX *unused, char shade )
{
    DG_TEX *tex;

    tex = DG_GetTexture_8001D830( GV_StrCode_80016CCC( "sfex0236" ) );

    for ( n_packs--; n_packs >= 0; packs++, n_packs-- )
    {
        setPolyFT4( packs );
        setSemiTrans( packs, 1 );

        packs->r0 = shade;
        packs->g0 = shade;
        packs->b0 = shade;

        DG_SetPacketTexture( packs, tex ) ;

        packs->tpage = tex->field_4_tPage;
        packs->clut = tex->field_6_clut;
    }
}

void EmitterDie_800C3CD8( Work *work )
{
    GM_FreePrim( work->prim ) ;
}

int EmitterGetVecs_800C3D14( int param, SVECTOR *out )
{
    int   count;
    char *res;

    count = 0;
    while ( 1 )
    {
        res = GCL_Get_Param_Result_80020AA4();
        if ( res == NULL )
        {
            break;
        }

        GCL_StrToSV_80020A14( res, out );

        out++;
        count++;
    }

    return count;
}

int EmitterGetResources_800C3D68( Work *work, int map, int count )
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    GM_CurrentMap_800AB9B0 = map;

    work->prim = DG_GetPrim( 0x412, count, 0, work->vecs, &rect_800C3320 );
    prim = work->prim;
    if ( prim == NULL )
    {
        return -1;
    }

    prim->field_2E_k500 = 500;
    prim->field_2E_k500 *= 2;

    tex = DG_GetTexture_8001D830( GV_StrCode_80016CCC( "sfex0236" ) );
    if ( tex == NULL )
    {
        return -1;
    }

    EmitterShadePacks_800C3C08( &prim->field_40_pBuffers[0]->poly_ft4, count, tex, 64 );
    EmitterShadePacks_800C3C08( &prim->field_40_pBuffers[1]->poly_ft4, count, tex, 72 );

    return 0;
}

void * NewEmitter_800C3E50( int name, int where )
{
    Work *work;
    int   count;

    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( Work ) );
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C( &( work->actor ), NULL, (TActorFunction)EmitterDie_800C3CD8, "emitter.c" );

        count = EmitterGetVecs_800C3D14( GCL_GetOption_80020968( 'p' ), work->vecs );
        if ( EmitterGetResources_800C3D68( work, where, count ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
    }

    return work;
}
