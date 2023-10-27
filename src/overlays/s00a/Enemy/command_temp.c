#include "enemy.h"
#include "Game/linkvarbuf.h"

int s00a_command_800CEA2C( WatcherWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0xC8[i].watcher == 0 )
        {
            EnemyCommand_800E0D98.field_0xC8[i].watcher = work; //update to be a struct with watcher ptr as 4th attribute
            EnemyCommand_800E0D98.field_0xC8[i].field_04 = 2;
            COM_PlayerAddressOne_800E0F40[i] = -1;
            return i;
        }
    }

    return -1;
}

void s00a_command_800CEA84( int idx, int val )
{
    EnemyCommand_800E0D98.field_0x148[ idx ] = val;
}

int s00a_command_800CEA9C( int val )
{
    int i;
    for ( i = 0 ; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0x148[i] == val )
        {
            return 1;
        }
    }
    return 0;
}

void ENE_SetTopCommAL_800CEAE8( int alert )
{
    TOPCOMMAND_800E0F20.alert = alert;
}

void ENE_SetTopCommMD_800CEAF4( int mode )
{
    TOPCOMMAND_800E0F20.mode = mode;
}

void ENE_SetGopointLast_800CEB00(void)
{
    EnemyCommand_800E0D98.com_addr = COM_PlayerAddress_800E0D90;
    EnemyCommand_800E0D98.com_pos  = COM_PlayerPosition_800E0F30;
    EnemyCommand_800E0D98.com_map  = COM_PlayerMap_800E0F1C;
    EnemyCommand_800E0D98.field_0x40 = 1;
}

extern CONTROL *GM_WhereList_800B56D0[94];
extern SVECTOR GM_NoisePosition_800AB9F8;
extern int dword_800ABA0C; //GM_PlayerMap?

void s00a_command_800CEB54(void) 
{
    EnemyCommand_800E0D98.com_addr = HZD_GetAddress_8005C6C4( GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd, &GM_NoisePosition_800AB9F8, -1 );
    EnemyCommand_800E0D98.com_pos = GM_NoisePosition_800AB9F8;
    EnemyCommand_800E0D98.com_map = dword_800ABA0C;
}

int s00a_command_800CEBCC( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &EnemyCommand_800E0D98.field_0xA4;
    
    if ( unk->map_id == map_id )
    { 
        for ( i = 0 ; i < unk->n_entry ; i++ )
        {
            if ( unk->field_04[i].field_00 == val )
            {
                return unk->field_04[i].field_02;
            }
        }   
        goto end;
    }
    return 0;
end:
    return -1;
}

void s00a_command_800CEC40( SVECTOR *mov , int flag )
{
    s00a_dword_800E0D38.vx = mov->vx;
    s00a_dword_800E0D30 |= 1 | flag;
    s00a_dword_800E0D38.vy = mov->vy;
    s00a_dword_800E0D38.vz = mov->vz;

    if ( s00a_dword_800E0CA0 == 0 )
    {
        s00a_dword_800E0CA0 = 32;
    }
}

extern int COM_VibTime_800E0F68;

unsigned char s00a_dword_800C35DC[4];
unsigned char s00a_dword_800C35E0[4];

extern void NewPadVibration_8005D58C( unsigned char *ptr, int flags );

void s00a_command_800CEC90( void ) 
{
    if ( COM_VibTime_800E0F68 > 0 )
    {
        NewPadVibration_8005D58C( s00a_dword_800C35DC, 1 );
        NewPadVibration_8005D58C( s00a_dword_800C35E0, 2 );
        COM_VibTime_800E0F68--;
        return;
    }
    
    COM_VibTime_800E0F68 = 0;
}

void s00a_command_800CECF4(void)
{
    if ( s00a_dword_800E0CA0 == 32 )
    {
         GM_SeSet2_80032968( 0, 0x3F, 0x53 );
    }

    s00a_dword_800E0CA0--;

    if ( s00a_dword_800E0CA0 < 0 )
    {
        s00a_dword_800E0CA0 = 0;
    }
}

void s00a_command_800CED48( void )
{
    int i;
    for ( i = 0; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        EnemyCommand_800E0D98.field_0x148[i] = 255;
    }
}

int s00a_command_800CED88( int ops, A4_STRUCT *unk )
{
    int i;
    i = 0;
    
    do {
        unk->field_04[i].field_00 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
        unk->field_04[i].field_02 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
        i++;
    } while ( GCL_Get_Param_Result_80020AA4() != NULL );

    
    return i;
}

int s00a_command_800CEDE8( int ops, short *addr, int map_id )
{
    int i;
    MAP *map;
    SVECTOR svec;
    unsigned char *res;
    map = Map_FromId_800314C0( map_id );

    for ( i = 0; ( res = GCL_Get_Param_Result_80020AA4() ) && i < 4 ; i++ )
    {
        GCL_StrToSV_80020A14( res, &svec );
        
        if ( svec.vy < 30000 )
        {
            addr[i] = HZD_GetAddress_8005C6C4( map->field_8_hzd, &svec, -1 ) & 0xFF;
        }
        else
        {
            addr[i] = 255;
        }
    }

    return i;
}

extern int GV_Time_800AB330;
extern const char aCresetposd_800E07FC[]; //" c_reset_pos = %d \n";
extern SVECTOR GM_PlayerPosition_800ABA10;

void s00a_command_800CEE98(void)
{
    int i;
    int s0;
    int dist2;
    int total;
    int delta;
    short dist1;
    int reset_pos;
    HZD_ZON *zone;
    SVECTOR svec;
    
    i = 0;
    delta = GV_Time_800AB330 % EnemyCommand_800E0D98.field_0x54;
    total = EnemyCommand_800E0D98.field_0x54;
    reset_pos = 0;
    
    for ( ; i < total ; i++  )
    {
        s0 = i + delta;
        if ( s0 >= total )
        {
            s0 -= total;
        }

        zone = &EnemyCommand_800E0D98.map->field_8_hzd->f00_header->navmeshes[ EnemyCommand_800E0D98.field_0x58[ s0 ] ];

        svec.vx = zone->x;
        svec.vy = GM_PlayerPosition_800ABA10.vy;
        svec.vz = zone->z;

        dist1 =  10000;
        dist2 = GV_DistanceVec3_80016E84( &svec, &GM_PlayerPosition_800ABA10 );
        if ( dist1 < dist2 )
        {
            reset_pos = s0;
            break;
        }

    }

    EnemyCommand_800E0D98.c_reset_pos = reset_pos;
    fprintf( 1, aCresetposd_800E07FC, reset_pos );
}


int s00a_command_800CEFE4( int val )
{
    return  EnemyCommand_800E0D98.field_0x0C % val;
}

void s00a_command_800CF024( int *val )
{
    if ( COM_GameStatus_800E0F3C & 1 )
    {
        *val = 0x82;
    }
    else
    {
        *val = 0x80;
    }
}

void s00a_command_800CF050( int *val )
{
    *val = 0x87;
}

void s00a_command_800CF05C( int *val )
{
    *val = 0x8B;
}

void s00a_command_800CF068( int *val )
{
    *val = 0x8A;
}

void s00a_command_800CF074( int *val )
{
    *val = 0x86;
}

void s00a_command_800CF080( int* val )
{
    switch( s00a_command_800CEFE4( 3 ) )
    {
    case 0:
        *val = 0x82;
        break;
    case 1:
    case 2:
        *val = 0x81;
        break;
    }
}

void s00a_command_800CF0CC( int *val )
{
    *val = 0x85;
}

extern const char aKottida_800E0810[]; //"kottida !!\n";

void s00a_command_800CF0D8( int* val )
{
    switch ( s00a_command_800CEFE4( 2 ) )
    {
    case 0:
        fprintf( 1, aKottida_800E0810 );
        *val = 0x81;
        return;
    case 1:
        *val = 0;
        return;
    }
}


int s00a_command_800CF13C( int val )
{
    switch( val )
    {
        case 240:
            s00a_command_800CF024( &val );
            break;
        case 241:
            s00a_command_800CF050( &val );
            break;
        case 242:
            s00a_command_800CF05C( &val );
            break;
        case 243:
            s00a_command_800CF068( &val );
            break;
        case 244:
            s00a_command_800CF074( &val );
            break;
        case 245:
            s00a_command_800CF0CC( &val );
            break;
        case 246:
            s00a_command_800CF080( &val );
            break;
        case 247:
            s00a_command_800CF0D8( &val );
            break;
    }

    return val;
}

extern SVECTOR GM_PlayerPosition_800ABA10;

void s00a_command_800CF200(void) 
{
    if ( EnemyCommand_800E0D98.field_0x170 < 6000 && ( mts_get_tick_count_8008BBB0() - EnemyCommand_800E0D98.field_0x174 ) > 40 )
    {
       if ( EnemyCommand_800E0D98.field_0x17A && GM_CurrentWeaponId != WEAPON_PSG1 )
       {
           GM_Sound_800329C4( &GM_PlayerPosition_800ABA10, 0xA, 2 );
       }
        EnemyCommand_800E0D98.field_0x174 = mts_get_tick_count_8008BBB0();
    }
}

extern int s00a_dword_800C35E4[];

void s00a_command_800CF298( ENEMY_COMMAND* command )
{
    int i;
    int t2;
    int t3;
    int t4;
    int dists[8];
    int temp1, temp2;
    int temp3, temp4;
    WatcherWork *work;

    dists[0] = 0x7530;

    for ( i = 0 ; i < command->field_0x08 ; i ++ )
    {
        //WatcherWork *work;
        work = command->field_0xC8[ EnemyCommand_800E0D98.field_0x68[ i ] ].watcher;

        if ( work->act_status & 0x10000000 )
        {
            dists[i] = 0x7530;
        }
        else
        {
            dists[i] = work->sn_dis;
        }
    }


    for ( t3 = command->field_0x08 - 1 ; t3 > -1 ; t3 = t4  )
    { 
        t4 = -1;
        for ( i = 1 ; t3 >= i ; i ++ )
        {    
            //TODO, fix without using dowhile
            do 
            {
                temp2 = dists[ i - 1 ];
                t2 = i - 1;
            } while (0);

            temp1 = dists[ i ];
            
            if ( temp1 < temp2 )
            {
                dists[ i - 1 ] = temp1;
                dists[ i ] = temp2;

                temp4 = EnemyCommand_800E0D98.field_0x68[ i - 1 ];
                temp3 = EnemyCommand_800E0D98.field_0x68[ i  ];
                t4 = t2;
                
                EnemyCommand_800E0D98.field_0x68[ i - 1 ] = temp3;
                EnemyCommand_800E0D98.field_0x68[ i ] = temp4;
            }            
        }
    }

    EnemyCommand_800E0D98.field_0x170 = dists[0];
    
    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        //WatcherWork *work;
        work = command->field_0xC8[ EnemyCommand_800E0D98.field_0x68[ i ] ].watcher;
        work->field_BFC = s00a_dword_800C35E4[ i ];
        work->field_C00 = i;
    }
}

void s00a_command_800CF420( ENEMY_COMMAND* command )
{
    int i;
    int dis;
    int sound;
    WatcherWork *work;
    EnemyCommand_800E0D98.field_0x1C--;
    if ( EnemyCommand_800E0D98.field_0x1C < 0 )
    {
        EnemyCommand_800E0D98.field_0x1C = 0;
    }

    if ( EnemyCommand_800E0D98.field_0x1C > 0 )
    {
        return;
    }

    sound = 0;
    dis   = 100000;
    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        if ( command->field_0xC8[ i ].field_04 == 2 )
        {
            work = command->field_0xC8[ i ].watcher;
            if ( work->pad.sound && work->sn_dis < dis )
            {
                sound = work->pad.sound;
                dis = work->sn_dis;
            }
            work->pad.sound = 0;
        }
    }

    if ( sound )
    {
        EnemyCommand_800E0D98.field_0x1C = 0x1E;
        GM_SeSet_80032858(NULL, s00a_command_800CF13C( sound ) );
    }
}

extern const char s00a_aResetmaxdnumd_800E083C[];

void s00a_command_800CF504( C8_STRUCT* struct_c8 )
{
    int x = struct_c8->field_08;
    switch ( x )
    {
    case 0:
        if ( struct_c8->field_04 == 1 )
        {
            struct_c8->field_08 = 1;
            struct_c8->field_00 = struct_c8->watcher->field_B78 + 1;
        }
        return;
    case 1:
        struct_c8->field_00--;
        if ( !struct_c8->field_00 && struct_c8->watcher->field_B81  )
        {
            struct_c8->field_08 = 2;
            struct_c8->field_00 = 0;
            EnemyCommand_800E0D98.reset_enemy_num++;
        }
        return;
    case 2:
        switch ( EnemyCommand_800E0D98.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( EnemyCommand_800E0D98.field_0x168 & 1 )
            {
                s00a_command_800CEE98();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
        return;
        case TOP_COMM_ALERT:
                if ( EnemyCommand_800E0D98.reset_enemy_num < EnemyCommand_800E0D98.reset_enemy_max + 1  || EnemyCommand_800E0D98.reset_enemy_max == 255 )
                {
                    if ( EnemyCommand_800E0D98.reset_enemy_num < 0 )
                    {
                        EnemyCommand_800E0D98.reset_enemy_num = 0;
                    }

                    s00a_command_800CEE98();
                    struct_c8->field_04 = x;
                    struct_c8->field_08 = 0;
                    printf( s00a_aResetmaxdnumd_800E083C, EnemyCommand_800E0D98.reset_enemy_max, EnemyCommand_800E0D98.reset_enemy_num );
                }
            return;
        }
        return;
    }
}

int s00a_command_800CF688( int a0, int a1 )
{
    if ( a0 < a1 )
    {
        a0 = a1;
    }

    return a0;
}

extern void ENE_SetTopCommAL_800CEAE8( int );

void s00a_command_800CF6A0( int val, ENEMY_COMMAND* command )
{
    if ( command->alert - val > 4 )
    {
        command->alert -= 4;
    }
    else
    {
        command->alert = val;
    }

    if ( command->alert < TOPCOMMAND_800E0F20.alert )
    {
        command->alert = TOPCOMMAND_800E0F20.alert;
    }

    ENE_SetTopCommAL_800CEAE8( 0 );
}


void GM_AlertModeSet_8002EA68( int );
extern const char aGmenemywatchcountd_800E0854[]; //GM_EnemyWatchCount = [%d] \n

void s00a_command_800CF704( ENEMY_COMMAND *command )
{
    int alert;
    
    switch ( command->mode )
    {
        default:
            TOPCOMMAND_800E0F20.mode = command->mode;
            return;
        case 0:
            COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vx;
            COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vx + 500;
            if ( command->alert >= 255 )
            {
                command->alert = 255;
                GM_AlertModeSet_8002EA68(3);
                command->mode = 1;
                EnemyCommand_800E0D98.reset_enemy_num = 0;
                COM_GameStatus_800E0F3C |= 0x1;
    
                if ( !( COM_GameStatus_800E0F3C & 2 ) )
                {
                    GM_TotalBeingFound ++;
                    printf( aGmenemywatchcountd_800E0854, GM_TotalBeingFound );
                }
                EnemyCommand_800E0D98.field_0x182 = 0;
            }
        break;
        case 1:
            COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vy;
            COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vy + 500;      

            
            if ( command->alert <= 0 ) 
            {
                GM_AlertModeSet_8002EA68(2);
                command->mode = 2;
                command->field_0x10 = 300;
                GM_SetAlertMax( 0x100 );
                s00a_command_800CED48();
                EnemyCommand_800E0D98.field_0x182 = 1;
                return;
            }
            alert = command->alert;
            if ( alert >= 0x101 ) 
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
        case 2:
            COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vz;
            COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vz + 500;     
            command->field_0x10--;
            if ( command->field_0x10 <= 0 )
            {
                GM_AlertModeSet_8002EA68(0);
                command->mode = 0;
                command->field_0x10 = 0;
                EnemyCommand_800E0D98.field_0x180 = 0;
                EnemyCommand_800E0D98.field_0x182 = 0;
            }
            if ( command->alert >= 255 )
            {
                command->alert = 0xFF;
                GM_AlertModeSet_8002EA68(3);
                command->mode = 1;
            }
            alert = command->field_0x10;
            if ( alert >= 0x101 ) 
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
            s00a_command_800CF200();
        break;
    }

    TOPCOMMAND_800E0F20.mode = command->mode;
}