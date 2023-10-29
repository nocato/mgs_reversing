#include "linker.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "loader.h"

extern int GM_LoadComplete_800ABA38;
extern int GM_LoadRequest_800AB3D0;
extern int GM_PadVibration2_800ABA54;

//Act
void Loader_Act_8002E390(struct Loader *pLoader)
{
    pLoader->field_2C_counter++;

    if (pLoader->field_24_proc_cancel_flags != 2)
    {
        if (pLoader->field_24_proc_cancel_flags == 3)
        {
            DG_OffsetDispEnv_80017784(pLoader->field_2C_counter & 2);
            GM_PadVibration2_800ABA54 = 100;
        }
    }

    if (pLoader->field_28_bRunning)
    {
        if (!FS_LoadStageSync_800237C0(pLoader->field_20_pStageFile))
        {
            pLoader->field_28_bRunning = 0;
        }
    }
    else
    {
        GV_DestroyActor_800151C8(&pLoader->base);
    }
}


//Die
void Loader_Kill_8002E41C(struct Loader *pLoader)
{
    printf("LoadEnd\n");
    FS_LoadStageComplete_80023804(pLoader->field_20_pStageFile);
    GM_LoadComplete_800ABA38 = -1;
}

//NewLoader
struct Loader *Loader_Init_8002E460(const char *pStageName)
{
    struct Loader *pLoader;

    // Loading "init" stage is required, it cannot be skipped
    // Thankfully it doesn't contain an overlay!
    if (strcmp(pStageName, "init") != 0)
    {
        pStageName = "s16b";
    }

    pLoader = (struct Loader *)GV_NewActor_800150E4(2, sizeof(struct Loader));
    printf("LoadReq\n");
    pLoader->field_20_pStageFile = FS_LoadStageRequest_800236E0(pStageName);

    if (!pLoader->field_20_pStageFile)
    {
        printf("NOT FOUND STAGE %s\n", pStageName);
    }

    GV_SetNamedActor_8001514C(&pLoader->base, (TActorFunction)Loader_Act_8002E390, (TActorFunction)Loader_Kill_8002E41C, "loader.c");

    pLoader->field_28_bRunning = 1;
    pLoader->field_24_proc_cancel_flags = (GM_LoadRequest_800AB3D0 & 0xf);
    GM_LoadComplete_800ABA38 = 0;
    return pLoader;
}
