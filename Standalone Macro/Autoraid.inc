| AutoRaid by moguay v1.9.4 - moguayv@gmail.com

| 1.0 - THF balanced raid
| 1.9.1 - Add live/test server raid (V2.0 prepare)
| 1.9.2 - Add cache
| 1.9.3 - Add custom conf
| 1.9.4 - Reforge macro structure - autoraid.mac (for standalaone) and autoraid.inc (for include in macro)
| 1.9.4 - Add automatic notification broadcast for groups that may be invited in another raid

|--------------------------------------------------------------------------
| - 0 configuration
| - No specific plugin needed (mq2turbo can be use)
| Features for raid fight logic
| - Classes priority distribution
| - Distribution adapted to different server
| - Power sorting of bots
| - Balanced power of bots
| - 4 Groups type management (Tank, Melee, Pet, Caster class)

| - TANK/Offtank, Healer and Bard have a specific repartition logic

| - Add cache sub function (AutoRaid-Cache.ini)
| - Cache is renew when the bots change
| - Cache can be edited manually to perform personalized raid formation
| - Group and Raid invite verification + add notification if lag
| - Add multiple custom configuration (for manually dispatching)
|       > /mac autoraid load form1      to make formation from AutoRaid-Form1.ini
|       > /mac autoraid save form1      to save formation in AutoRaid-Form1.ini
| Example of the contents of the file
| [Autoraid]
| INVITE_LIST1=WAR:Bufo#1 WAR:Boulon SHD:Guismo CLR:Moguay RNG:Framboise DRU:Diancecht
| INVITE_LIST2=PAL:Leapyear#2 SHM:Oskiti BRD:Olirr ROG:Tenaciousd BER:Liime BER:Jeewid
| INVITE_LIST3=CLR:Erelog#4 BRD:Cendrillon WIZ:Lungorthin WIZ:Lugorthin WIZ:Charmant MAG:Sherly
| INVITE_LIST4=ENC:Ogen#0 BST:Hykim

| -------------------------------------------------------------------------
| Moguay Core Command for external execution
| -------------------------------------------------------------------------

Sub Command_raid(string CommandText)
    /if (!${Defined[i]}) /declare i int local
    /if (${Macro.Params}>1) {
        /for i 1 to ${Math.Calc[${Macro.Params}-1]}
            /varset CommandText ${CommandText} ${Param${i}}
        /next i
    }

    /if (${Select[${CommandText},NULL]}) /varset CommandText ""
    /call function_autoraid "raid ${CommandText.Replace[|, ]}"
/return

Sub Command_group(string CommandText)
    /if (!${Defined[i]}) /declare i int local
    /if (${Macro.Params}>1) {
        /for i 1 to ${Math.Calc[${Macro.Params}-1]}
            /varset CommandText ${CommandText} ${Param${i}}
        /next i
    }

    /if (${Select[${CommandText},NULL]}) /varset CommandText ""
    /call function_autoraid "group ${CommandText.Replace[|, ]}"
/return

| -------------------------------------------------------------------------
| Main auto raid command function
| -------------------------------------------------------------------------

Sub function_autoraid(string CommandText)

    | -------------------------------------------------------------------------
    | Init server processing
    | -------------------------------------------------------------------------

    | Auto processing selection
    /declare bProcessing bool local false
    /declare Processing int local ${Select[${MacroQuest.Server.Arg[1, ]},live,test,HiddenForest,PF]}

    | Force processing for debug
    | /varset Processing 1

    | Sub processing var
    /if (!${Defined[LIVE]}) /declare LIVE bool outer ${Bool[${Select[${Processing},1,2]}]}
    /if (!${Defined[THF]})  /declare THF bool outer  ${Bool[${Select[${Processing},3]}]}
    /if (!${Defined[PF]})   /declare PF bool outer  ${Bool[${Select[${Processing},4]}]}

    | -------------------------------------------------------------------------
    | Init best class distribution logic
    | -------------------------------------------------------------------------

    |                                  |------live------|------test-----|------THF------|------PF------|
    /declare Tank1      string local    WAR/SHD/PAL     ,WAR/SHD/PAL    ,SHD/WAR         ,WAR/SHD/PAL    
    /declare Tank2      string local    WAR/SHD/PAL     ,WAR/SHD/PAL    ,PAL             ,WAR/SHD/PAL    
                                                                                         
    /declare Gheal1     string local    CLR/DRU         ,CLR/DRU        ,CLR/PAL         ,CLR/DRU        
    /declare Gheal2     string local    SHM             ,SHM            ,PAL/WAR         ,SHM            
    /declare Gheal3     string local    DRU             ,DRU            ,CLR/PAL         ,DRU            
    /declare Gheal4     string local    0               ,0              ,SHM             ,0              
                                                                                         
    /declare Melee1     string local    ROG/BER/MNK     ,ROG/BER/MNK    ,ROG/BER/MNK     ,ROG/BER/MNK    
    /declare Melee2     string local    BST/RNG/MNK     ,BST/RNG/MNK    ,BST/RNG/MNK     ,BST/RNG/MNK    
    /declare Melee3     string local    RNG/BST/MNK     ,RNG/BST/MNK    ,RNG/BST/MNK     ,RNG/BST/MNK    
                                                                                         
    /declare Nuke1      string local    ENC/WIZ/DRU     ,ENC/WIZ/DRU    ,ENC/WIZ/DRU     ,ENC/WIZ/DRU    
                                                                                         
    /declare Pet1       string local    NEC/MAG         ,NEC/MAG        ,NEC/MAG/BST     ,NEC/MAG        

    | Selection of the distribution
    /varset Tank1   ${Tank1.Arg[${Processing},,].Replace[ ,]}
    /varset Tank2   ${Tank2.Arg[${Processing},,].Replace[ ,]}
    /varset Gheal1  ${Gheal1.Arg[${Processing},,].Replace[ ,]}
    /varset Gheal2  ${Gheal2.Arg[${Processing},,].Replace[ ,]}
    /varset Gheal3  ${Gheal3.Arg[${Processing},,].Replace[ ,]}
    /varset Gheal4  ${Gheal4.Arg[${Processing},,].Replace[ ,]}
    /varset Melee1  ${Melee1.Arg[${Processing},,].Replace[ ,]}
    /varset Melee2  ${Melee2.Arg[${Processing},,].Replace[ ,]}
    /varset Melee3  ${Melee3.Arg[${Processing},,].Replace[ ,]}
    /varset Nuke1   ${Nuke1.Arg[${Processing},,].Replace[ ,]}
    /varset Pet1    ${Pet1.Arg[${Processing},,].Replace[ ,]}

    /if (!${Defined[GROUP_TYPE]})   /declare GROUP_TYPE[4]  string outer
    | Prio tank -> offtank -> Healer -> melee
    /varset GROUP_TYPE[1]   ${Tank1} ${Gheal1} ${Tank2} ${Gheal1}${If[!${THF},*5,]} BRD/${Melee1} ${Melee1} ${Melee2} ${Melee3} ${Melee1}/${Melee2}*6 ${Pet1}*6 ${Nuke1}*6 ${Tank1}/${Tank2}*3
    | Prio offtank -> Heal -> melee
    /varset GROUP_TYPE[2]   ${Gheal2} ${Gheal4} BRD/${Melee1} ${Melee1} ${Melee2} ${Melee3} ${Melee1}/${Melee2}*6 ${Pet1}*6 ${Nuke1}*6 ${Tank1}*6
    | Prio Heal -> Pet
    /varset GROUP_TYPE[3]   ${Gheal3} ${Gheal4} BRD/${Pet1} ${Pet1}*6 ${Nuke1}*6 ${Melee1}*6 ${Melee2}*6 ${Tank1}*6
    | Prio Heal -> Nuke
    /varset GROUP_TYPE[4]   ${Gheal3} ${Gheal4} BRD/${Nuke1} ${Nuke1}*6 ${Pet1}*6 ${Melee1}*6 ${Melee2}*6 ${Tank1}*6

    | Debug broadcast Group_type
    | /echo DEBUG: GROUP_TYPE[1]=${GROUP_TYPE[1]}
    | /echo DEBUG: GROUP_TYPE[2]=${GROUP_TYPE[2]}
    | /echo DEBUG: GROUP_TYPE[3]=${GROUP_TYPE[3]}
    | /echo DEBUG: GROUP_TYPE[4]=${GROUP_TYPE[4]}

    |--THF balancing (full raid)
    | WAR           CLR/PAL         BRD         SHD         ROG/BER/RNG/MNK ROG/BER/RNG/MNK
    | PAL           SHM/CLR         BRD         NEC/MAG/BST NEC/MAG/BST WIZ/DRU/ENC WIZ/DRU/ENC

    |--LIVE MAX DPS (full raid)
    | WAR/PAL/SHD   WAR/PAL/SHD     CLR         CLR         CLR         CLR
    | SHM           BRD             ROG/BER     ROG/BER/MNK BST/RNG/MNK RNG/BST/MNK
    | DRU           BRD/ENC         WIZ/MAG/NEC WIZ/MAG/NEC WIZ/MAG/NEC WIZ/MAG/NEC

    |--LIVE MAX DPS (small raid)
    | WAR/PAL/SHD   SHM             BRD         ROG/BER     ROG/BER/MNK BST/RNG/MNK
    | CLR/DRU       BRD/ENC         WIZ/MAG/NEC WIZ/MAG/NEC WIZ/MAG/NEC WIZ/MAG/NEC

    | -------------------------------------------------------------------------
    | Init cache file
    | -------------------------------------------------------------------------


    /if (!${Defined[IniName]})      /declare IniName    string outer ${MacroDir}AutoRaid-${If[${Defined[strMainTank]},${strMainTank}-,]}Cache.ini
    /if (!${Defined[IniCustom]})    /declare IniCustom  string outer ${MacroDir}AutoRaid-Custom.ini
    /if (!${Defined[Section]})      /declare Section    string outer Autoraid
    /if (!${Defined[RaidCACHE]})    /declare RaidCACHE  string outer
    /declare oldTurbo  int local

    | Defined custom by default if data found
    /if (${Bool[${Ini[${IniCustom},${Section},BotsList]}]}) /varset IniName ${IniName}

    | -------------------------------------------------------------------------
    | Init raid calculation
    | -------------------------------------------------------------------------

    | Function declare for broadcasting
    /if (!${Defined[functionName]}) /declare functionName string outer
    /varset functionName Auto-Raid

    | Broadcasting configuration
    /if (!${Defined[echo]}) /declare echo string global ${If[${Plugin[MQ2CEcho].Name.Equal[MQ2CEcho]},cecho,echo]}

    | | Support broadcasting
    | /if (!${Defined[MacroSupport]}) /declare MacroSupport string local ${BCr}#${BCx} ${BCm}You like and want to support this development${BCx}, ${BCr}you can donate${BCx}: https://paypal.me/moguay

    | /if (${echo.NotEqual[cecho]}) {
    |     /docommand /bct ${Me.CleanName} ${MacroSupport}
    |     /docommand /${echo} [${functionName}] by moguay v${AutoraidVersion} - moguayv@gmail.com
    | }

    | Macro Parameters
    /if (!${Defined[i]}) /declare i int local
    /if (!${Defined[CommandText]})  /declare CommandText string local
    /if (!${Defined[CustomIni]})    /declare CustomIni string local
    /if (!${Defined[CustomNew]})   /declare CustomNew bool local FALSE
    /if (!${Defined[CustomLoad]})   /declare CustomLoad bool local FALSE
    /if (!${Defined[CustomSave]})   /declare CustomSave bool local FALSE

    /if (!${Defined[MasterPCRaid]}) /declare MasterPCRaid string outer

    /if (${Macro.Params} > 0) {
        /for i 1 to ${Math.Calc[${CommandText.Count[ ]}+1]}
            /if (${Bool[${Ini[AutoRaid-${If[${Defined[strMainTank]},${strMainTank}-,]}${CommandText.Arg[${i}, ]}.ini,${Section},INVITE_LIST1]}]}) {
                /varset CustomIni ./AutoRaid-${If[${Defined[strMainTank]},${strMainTank}-,]}${CommandText.Arg[${i}, ]}.ini
                /if (!${CustomSave}) /varset CustomLoad TRUE
            }

            /if (${Spawn[PC =${CommandText.Arg[${i}, ]}].ID}) {
                /varset MasterPCRaid ${Spawn[PC =${CommandText.Arg[${i}, ]}].CleanName}
            } else /if (${Spawn[id ${CommandText.Arg[${i}, ]}].ID} && ${Spawn[id ${CommandText.Arg[${i}, ]}].Type.Equal[PC]}) {
                /varset MasterPCRaid ${Spawn[id ${CommandText.Arg[${i}, ]}].CleanName}
            } else /if (${Bool[${CommandText.Arg[${i}, ].Equal[disband]}]}) {
                /call Disband
                /docommand /${echo} [${functionName}]: Disaband : ALL
                /return
            } else /if (${Select[${CommandText.Arg[${i}, ]},invite,join]}) {
                /if (${Raid.Locked}) {
                    /echo The raid is locked, you can't invite
                    /return
                }
                /varset CustomNew TRUE
                /varset CustomSave FALSE
                /varset CustomLoad FALSE
                /varset bProcessing FALSE
            } else /if (${Bool[${CommandText.Arg[${i}, ].Equal[build]}]}) {
                /varset CustomSave FALSE
                /varset CustomLoad FALSE
                /varset bProcessing TRUE
            } else /if (${Bool[${CommandText.Arg[${i}, ].Equal[new]}]}) {
                /varset CustomNew TRUE
                /varset CustomSave FALSE
                /varset CustomLoad FALSE
                /varset bProcessing TRUE
            } else /if (${Bool[${CommandText.Arg[${i}, ].Equal[save]}]}) {
                /varset CustomSave TRUE
                /varset CustomLoad FALSE
                /varset bProcessing TRUE
            } else /if (${Bool[${CommandText.Arg[${i}, ].Equal[load]}]}) {
                /varset CustomSave FALSE
                /varset CustomLoad TRUE
                /varset bProcessing TRUE
            } else {
                /varset CustomIni ${MacroDir}AutoRaid-${If[${Defined[strMainTank]},${strMainTank}-,]}${CommandText.Arg[${i}, ]}.ini
            }

        /next i
        /if (${CustomLoad} || ${CustomSave}) /varset IniName ${CustomIni}
        
        | /echo debug:CustomSave=${CustomSave} CustomLoad=${CustomLoad} IniName=${IniName} CustomIni=${CustomIni}
    }

    | Enable function statistic
    /if (!${Defined[FormRaidTimer]})    /declare FormRaidTimer timer outer
    /varset FormRaidTimer 1000s


    | Calculation speed management
    /if (${bProcessing}) {
        /if (${Plugin[MQ2Turbo].Name.Equal[MQ2Turbo]}) {
            /varset oldTurbo ${turbo}

            /if (${intTurbo2}!=NULL) {
                /squelch /turbo ${intTurbo2}
            } else {
                /squelch /turbo 2000
            }
            /docommand /${echo} [${functionName}]: Calculation mode activated in [ludicrous speed]
        } else {
            /docommand /${echo} [${functionName}]: Calculation mode activated in [turtle speed]
        }
    }

    | Misc function
    /call definedNbGroup
    /call DeclareOuterVar
    /if (${CustomSave}) {
        /call SaveForm ${CustomSave}
        /return
    }
    /call RestoreForm ${CustomLoad}

    /if (!${bProcessing}) {
        | -------------------------------------------------------------------------
        | Invite all in raid
        | -------------------------------------------------------------------------
        /if (${RaidCACHE}==NULL || ${CustomNew}) {
            /call SortPClist
            /call RaidInviteALL
        }

    }
    /if (${bProcessing}) {
        /if (${RaidCACHE}==NULL) /call SortPClist

        | -------------------------------------------------------------------------
        | Basic class repartition logic
        | -------------------------------------------------------------------------
        /if (${NUMBER_OF_GROUP} == 1) {
            /call BasicRaid ${CommandText}

        | -------------------------------------------------------------------------
        | Advanced class repartition logic
        | -------------------------------------------------------------------------
        } else /if (${NUMBER_OF_GROUP} >= 2) {
            /call AdvancedRaid ${CommandText}
        }
    }

    | Reset speed management
    /if (${Plugin[MQ2Turbo].Name.Equal[MQ2Turbo]}) /squelch /turbo ${oldTurbo}

/return

| -------------------------------------------------------------------------
| Init invite all bots in raid
| -------------------------------------------------------------------------

Sub RaidInviteALL(string CommandText)

    | Disbanding group and raid
    | /call Disband

    | Loops vars
    /if (!${Defined[e]}) /declare e int local
    /if (!${Defined[i]}) /declare i int local

    | Rewrite var
    /varset e 1
    /if (!${Defined[INVITE_CMD${e}]})   /declare INVITE_CMD${e} string local
    /if (!${Defined[INVITE_LIST${e}]})  /declare INVITE_LIST${e} string local

    /varset GROUP_MASTER_LIST_FIND ||
    /varset GROUP_ALT_LIST

    | NetBots scan
    /for i 1 to ${Math.Calc[${BEST_ORDERED_LIST.Count[|]} + 1]}
        | Exclude if already in raid
        /if (!${NetBots[${BEST_ORDERED_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid}) {
        | Exclude MASTERS and ALTS already called
        /if (!${GROUP_MASTER_LIST_FIND.Find[|${BEST_ORDERED_LIST.Arg[${i},|]}#]} && ${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].ID} && ${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].ID}!=${Me.ID}) {
            | /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox No_Button leftmouseup ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox CD_No_Button leftmouseup
            | /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox CD_No_Button leftmouseup
            /delay 2
            /raidinvite ${BEST_ORDERED_LIST.Arg[${i},|]}
            /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //varset AcceptType 5s
            /delay 5
            | try to accept
            | /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox Yes_Button leftmouseup ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox CD_Yes_Button leftmouseup
            | /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox CD_OK_Button leftmouseup
            | /varset INVITE_CMD${e} ${INVITE_CMD${e}}; /invite ${BEST_ORDERED_LIST.Arg[${i},|]}
            /varset INVITE_LIST${e} ${INVITE_LIST${e}}${If[${Bool[${INVITE_LIST${e}}]}, ,]}${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}:${BEST_ORDERED_LIST.Arg[${i},|]}
            /varset GROUP_ALT_LIST ${GROUP_ALT_LIST}${If[${Bool[${GROUP_ALT_LIST}]},|,]}${BEST_ORDERED_LIST.Arg[${i},|]}
        }
        }
    /next i

    | GROUP Send invite
    /docommand /${echo} [${functionName}]: RaidInvite : ${INVITE_LIST${e}}
    | /bct ${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]} //multiline ; ${INVITE_CMD${e}}

| /echo ${GROUP_MASTER_LIST} :: ${GROUP_ALT_LIST}
    /docommand /${echo} [${functionName}]: nbr of pc: [${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 2 + ${GROUP_ALT_LIST.Count[|]}].Int}] done in (${Math.Calc[(10000-${FormRaidTimer})/10]}s)

/return

| -------------------------------------------------------------------------
| Init basic raid calculation
| -------------------------------------------------------------------------

Sub BasicRaid(string CommandText)

    | Disbanding group and raid
    /call Disband

    | Loops vars
    /if (!${Defined[e]}) /declare e int local
    /if (!${Defined[i]}) /declare i int local

    | /call SortPClist

    /if (!${Defined[NUMBER_OF_GROUP]})  /declare NUMBER_OF_GROUP int outer 1
    /varset NUMBER_OF_GROUP 1

    /docommand /${echo} [${functionName}]: Determine best master for the group...

    /call CreateBestMasterList2

    | Rewrite var
    /varset e 1
    /if (!${Defined[INVITE_CMD${e}]})   /declare INVITE_CMD${e} string local
    /if (!${Defined[INVITE_LIST${e}]})  /declare INVITE_LIST${e} string local

    /varset GROUP_MASTER_LIST_FIND |${GROUP_MASTER_LIST}|
    /varset GROUP_ALT_LIST

    | NetBots scan
    /for i 1 to ${Math.Calc[${BEST_ORDERED_LIST.Count[|]} + 1]}
        | Exclude MASTERS and ALTS already called
        /if (!${GROUP_MASTER_LIST_FIND.Find[|${BEST_ORDERED_LIST.Arg[${i},|]}#]} && ${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].ID}) {
            /varset INVITE_CMD${e} ${INVITE_CMD${e}}; /invite ${BEST_ORDERED_LIST.Arg[${i},|]}
            /varset INVITE_LIST${e} ${INVITE_LIST${e}}${If[${Bool[${INVITE_LIST${e}}]}, ,]}${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}:${BEST_ORDERED_LIST.Arg[${i},|]}
            /varset GROUP_ALT_LIST ${GROUP_ALT_LIST}${If[${Bool[${GROUP_ALT_LIST}]},|,]}${BEST_ORDERED_LIST.Arg[${i},|]}
        }
    /next i

    | GROUP Send invite
    /docommand /${echo} [${functionName} Basic]: Send Master[${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#]}] invite : ${INVITE_LIST${e}}
    /bct ${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]} //multiline ; ${INVITE_CMD${e}}

| /echo ${GROUP_MASTER_LIST} :: ${GROUP_ALT_LIST}
    /docommand /${echo} [${functionName}]: nbr of pc: [${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1 + ${GROUP_ALT_LIST.Count[|]}].Int}] done in (${Math.Calc[(10000-${FormRaidTimer})/10]}s)

/return

| -------------------------------------------------------------------------
| Main Advanced raid calculation
| -------------------------------------------------------------------------

Sub AdvancedRaid(string CommandText)

    | Disbanding group and raid
    /call Disband

    | Loops vars
    /if (!${Defined[e]}) /declare e int local
    /if (!${Defined[f]}) /declare f int local
    /if (!${Defined[g]}) /declare g int local
    /if (!${Defined[h]}) /declare h int local
    /if (!${Defined[i]}) /declare i int local
    /if (!${Defined[j]}) /declare j int local
    /if (!${Defined[k]}) /declare k int local
    /if (!${Defined[l]}) /declare l int local
    /if (!${Defined[m]}) /declare m int local
    /if (!${Defined[n]}) /declare n int local
    /if (!${Defined[NextAltSearch]}) /declare NextAltSearch bool local FALSE

    /if (${RaidCACHE}==NULL) {

        /call CreateBestMasterList

        /call CreateBestMasterList2

            /varset GROUP_MASTER_LIST_FIND |${GROUP_MASTER_LIST}|

            /docommand /${echo} [${functionName}]: Determine best bot for each group...(Power and Class balanced on pairs of groups) wait...

            /for f 2 to 20

                | GROUP scan ||| ${NUMBER_OF_GROUP}
                /for e 1 to ${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1].Int}
                    /if (!${Defined[INVITE_CMD${e}]})   /declare INVITE_CMD${e} string local
                    /if (!${Defined[INVITE_LIST${e}]})  /declare INVITE_LIST${e} string local

                    | GROUP_TYPE scan
                    /varset j 0
                    /if (${Int[${GROUP_MASTER_LIST.Arg[${e},|].Arg[2,#]}]}) /varset j ${Int[${GROUP_MASTER_LIST.Arg[${e},|].Arg[2,#]}]}

                    | ${f} VAR end loop condition - boosting code condition
                    /if (${j} && ${GROUP_TYPE[${j}].Arg[${f}, ].Length}) {

                        /for k 1 to ${If[${Int[${GROUP_TYPE[${j}].Arg[${f}, ].Arg[2,*]}]} > 1,${Int[${GROUP_TYPE[${j}].Arg[${f}, ].Arg[2,*]}]},1]}
                        /varset NextAltSearch FALSE
                        | Sub CLASS GROUP_TYPE scan
                        /for l 1 to ${Math.Calc[${GROUP_TYPE[${j}].Arg[${f}, ].Arg[1,*].Count[/]} + 1]}
                            | NetBots scan
                            /for i 1 to ${Math.Calc[${BEST_ORDERED_LIST.Count[|]} + 1]}
                                | Exclude FULL List
                                /if (!((${Int[${GROUP_MASTER_LIST.Arg[${e},|].Arg[2,#]}]} && ${Math.Calc[${INVITE_LIST${e}.Count[ ]} + 1].Int} >= 5) || (!${Int[${GROUP_MASTER_LIST.Arg[${e},|].Arg[2,#]}]} && ${Math.Calc[${INVITE_LIST${e}.Count[ ]} + 1].Int} >= 6))) {
| /echo Scan: ${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Name}
                                    | Rewrite var
                                    /varset GROUP_ALT_LIST_FIND |${GROUP_ALT_LIST}|
                                    | Exclude MASTERS and ALTS already called
                                    /if (!${GROUP_MASTER_LIST_FIND.Find[:${BEST_ORDERED_LIST.Arg[${i},|]}#]} && !${GROUP_ALT_LIST_FIND.Find[|${BEST_ORDERED_LIST.Arg[${i},|]}|]}) {
                                        | Find the bot class combination
                                        /if (${GROUP_TYPE[${j}].Arg[${f}, ].Arg[1,*].Arg[${l},/].Equal[${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}]} || !${Int[${GROUP_MASTER_LIST.Arg[${e},|].Arg[2,#]}]}) {
                                            /varset INVITE_CMD${e} ${INVITE_CMD${e}}; /invite ${BEST_ORDERED_LIST.Arg[${i},|]}
| /echo Match[${j}]: ${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Name}
| /echo ${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Name}
                                            /varset INVITE_LIST${e} ${INVITE_LIST${e}}${If[${Bool[${INVITE_LIST${e}}]}, ,]}${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}:${BEST_ORDERED_LIST.Arg[${i},|]}
                                            /varset GROUP_ALT_LIST ${GROUP_ALT_LIST}${If[${Bool[${GROUP_ALT_LIST}]},|,]}${BEST_ORDERED_LIST.Arg[${i},|]}

                                            /varset NextAltSearch TRUE
                                            /break
                                        }
                                    }
                                }
                            /next i
                            /if (${NextAltSearch}) /break
                        /next l
                        /next k
                    }
                /next e
            /next f

        }

        | Write master Cache
        /if (${RaidCACHE}==NULL && ${IniName.Find[Cache]}) {
            /ini "${IniName}" "${Section}" "BotsList" "${NetBots.Client}"
        }

        | GROUP Send invite
        /for e 1 to ${NUMBER_OF_GROUP}
            | Write groups Cache
            /if (${RaidCACHE}==NULL) {
                | /ini "${IniName}" "${Section}" "INVITE_CMD${e}" "${INVITE_CMD${e}}"
                /ini "${IniName}" "${Section}" "INVITE_LIST${e}" "${GROUP_MASTER_LIST.Arg[${e},|]} ${INVITE_LIST${e}}"
            | Read groups Cache
            } else /if (${Defined[INVITE_LIST${e}]}) {
                /varset GROUP_MASTER_LIST ${GROUP_MASTER_LIST}${If[${Bool[${GROUP_MASTER_LIST}]},|,]}${Spawn[pc =${INVITE_LIST${e}.Arg[1, ].Arg[1,#].Arg[2,:]}].Class.ShortName}:${INVITE_LIST${e}.Arg[1, ].Arg[1,#].Arg[2,:]}#${INVITE_LIST${e}.Arg[1, ].Arg[2,#]}
                /if (${INVITE_LIST${e}.Arg[1, ].Find[#]}) /call ListDelbyArg INVITE_LIST${e} 1 " "
                /if (!${Defined[INVITE_CMD${e}]})   /declare INVITE_CMD${e} string outer
                /for i 1 to ${Math.Calc[${INVITE_LIST${e}.Count[ ]} + 1]}
                    /varset INVITE_CMD${e} ${INVITE_CMD${e}}; /invite ${INVITE_LIST${e}.Arg[${i}, ].Arg[2,:]}
                    /varset GROUP_ALT_LIST ${GROUP_ALT_LIST}${If[${Bool[${GROUP_ALT_LIST}]},|,]}${INVITE_LIST${e}.Arg[${i}, ].Arg[2,:]}
                /next i
            }

            | Send invite
            /if (${Defined[INVITE_LIST${e}]} && ${NetBots[${INVITE_LIST${e}.Arg[1, ].Arg[1,#].Arg[2,:]}].ID}) {
                /docommand /${echo} [${functionName}${If[${RaidCACHE}==NULL, Advanced,]}]: Master[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#]}][Type${GROUP_MASTER_LIST.Arg[${e},|].Arg[2,#]}] invite : ${INVITE_LIST${e}}
                /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //multiline ; /echo [Group ${functionName}] Sending group invite...${INVITE_CMD${e}}
    | /echo >> /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //multiline ; /echo [Group ${functionName}] Sending group invite...${INVITE_CMD${e}}

                /if (!${Defined[GROUP_MASTER_NAME_LIST]})   /declare GROUP_MASTER_NAME_LIST string local
                /varset GROUP_MASTER_NAME_LIST ${GROUP_MASTER_NAME_LIST}${If[${Bool[${GROUP_MASTER_NAME_LIST}]}, ,]}${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}
                /delay 2
            }
        /next e

        | WAIT Grouping
        /for e 1 to ${NUMBER_OF_GROUP}
            /if (${Defined[INVITE_LIST${e}]} && ${NetBots[${INVITE_LIST${e}.Arg[1, ].Arg[1,#].Arg[2,:]}].ID}) {
                /for i 1 to ${Math.Calc[${INVITE_LIST${e}.Count[ ]} + 1].Int}
                    /if (!${NetBots[${INVITE_LIST${e}.Arg[${i}, ].Arg[2,:]}].Grouped}) {
                        /delay 5 (${NetBots[${INVITE_LIST${e}.Arg[${i}, ].Arg[2,:]}].Grouped})
                        /if (!${NetBots[${INVITE_LIST${e}.Arg[${i}, ].Arg[2,:]}].Grouped}) {
                            | retry to invite
                            /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //invite ${INVITE_LIST${e}.Arg[${i}, ].Arg[1,#].Arg[2,:]}
                            /bct ${INVITE_LIST${e}.Arg[${i}, ].Arg[1,#].Arg[2,:]} //varset AcceptType 5s
                            | /delay 5
                            | try to accept
                            | /bct ${INVITE_LIST${e}.Arg[${i}, ].Arg[1,#].Arg[2,:]} //nomodkey /notify GroupWindow FollowButton leftmouseup
                        }
                        /delay 5s (${NetBots[${INVITE_LIST${e}.Arg[${i}, ].Arg[1,#].Arg[2,:]}].Grouped})
                        | Broadcast lag
                        /if (!${NetBots[${INVITE_LIST${e}.Arg[${i}, ].Arg[1,#].Arg[2,:]}].Grouped}) /docommand /${echo} [${functionName}] Grouping lag for : ${INVITE_LIST${e}.Arg[${i}, ].Arg[1,#].Arg[2,:]}
                    }
                /next i

                | RAID Send invite
                /if (${e} > 1 && ${e} <= ${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1]} && !${CommandText.Find[group]}) {
                    /delay 2
                    /bct ${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]} //multiline ; /docommand /${echo} [Form ${functionName}] Send raidinvite to group leader <${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}>; /raidinvite ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}
                    /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //varset AcceptType 5s
                    | /delay 2
                }
            }
        /next e

        | GROUP Shout ready to invite
        /if (${CommandText.Find[group]}) {
            /if (${MasterPCRaid.Length}) {
                /docommand /${If[${Spawn[PC =${MasterPCRaid}].Guild.Equal[${Spawn[id ${Me.ID}].Guild}]},Guildsay,Shout]} Raidinvite request for <${MasterPCRaid}>, you need to invite in raid <${GROUP_MASTER_NAME_LIST}>
            }
            | /shout [${If[${Defined[strMainTank]},${strMainTank},${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]}]}] team are ready to accept raid invite on: ${GROUP_MASTER_NAME_LIST}

        | RAID Send accept
        } else {
            /for e 2 to ${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1].Int}
                /if (${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].ID}) {
                /if (!${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid}) {
                    /delay 1s (${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid})
                    | Send accept
                    /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //varset AcceptType 5s
                    | /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox Yes_Button leftmouseup ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox CD_Yes_Button leftmouseup

                    /delay 2s (${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid})
                    | /if (!${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid}) {
                    |     | retry to invite
                    |     /bct ${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]} //raidinvite ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}
                    |     /delay 5
                    |     | try to accept
                    |     /bct ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox Yes_Button leftmouseup ; /if ($\\{Window[ConfirmationDialogBox].Open}) /squelch /notify ConfirmationDialogBox CD_Yes_Button leftmouseup
                    | }
                    | /delay 5s (${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid})
                    | Broadcast lag
                    /if (!${NetBots[${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}].Raid}) /docommand /${echo} [${functionName}] Raid lag for : ${GROUP_MASTER_LIST.Arg[${e},|].Arg[1,#].Arg[2,:]}
                }
                }
            /next e

            /if (!${NetBots[${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]}].Raid}) {
                | Broadcast lag
                /docommand /${echo} [${functionName}] Raid lag for : ${GROUP_MASTER_LIST.Arg[1,|].Arg[1,#].Arg[2,:]}
            }
        }

    /docommand /${echo} [${functionName}]: nbr of pc: [${Math.Calc[${GROUP_MASTER_LIST.Count[|]} ${If[${GROUP_MASTER_LIST.Length},+ 1,]} + ${GROUP_ALT_LIST.Count[|]} ${If[${GROUP_ALT_LIST.Length},+ 1,]}].Int}] done in (${Math.Calc[(10000-${FormRaidTimer})/10]}s ${If[${RaidCACHE}!=NULL,with cache,without cache]})

/return

| -------------------------------------------------------------------------
| Misc function
| -------------------------------------------------------------------------

Sub Disband

    | Disbanding group and raid
    /bcaa //squelch /raiddisband
    /bcaa //squelch /disband

    | WAIT Grouping
    /if (!${Defined[BEST_ORDERED_LIST]})        /declare BEST_ORDERED_LIST string outer
    /if (!${Defined[i]}) /declare i int local
    /for i 1 to ${Math.Calc[${BEST_ORDERED_LIST.Count[|]} + 1]}
        /if (${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Grouped}) {
            /delay 5 (!${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Grouped})
            | /if (${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Grouped}) /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //multiline ; /if ($\\{Window[ConfirmationDialogBox].Open}) /nomodkey /notify ConfirmationDialogBox No_Button leftmouseup ; /raiddisband; /disband
            /if (${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Grouped}) /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //raiddisband; /disband
            /delay 5s (!${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Grouped})
            /if (${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Grouped}) /docommand /${echo} [${functionName}] Disband lag for : ${BEST_ORDERED_LIST.Arg[${i},|]}
        }
    /next i

    /if (${RaidCACHE}!=NULL) /delay 5

/return

Sub SortPClist

    | Loops vars
    /if (!${Defined[f]}) /declare f int local
    /if (!${Defined[i]}) /declare i int local
    /if (!${Defined[j]}) /declare j int local

    /docommand /${echo} [${functionName}]: Sorting pc list (best to lower)...

    /if (!${Defined[ClassList]})                /declare ClassList string local WAR SHD PAL CLR WIZ ROG BER RNG DRU SHM NEC MAG ENC BRD RNG MNK BST
    /if (!${Defined[BEST_ORDERED_LIST]})        /declare BEST_ORDERED_LIST string outer
    /varset BEST_ORDERED_LIST
    /if (!${Defined[BEST_ORDERED_LISTFind]})    /declare BEST_ORDERED_LISTFind string local

    /declare PCMax string local

    /for f 1 to ${Math.Calc[${ClassList.Count[ ]} + 1]}
        /for i 1 to ${NetBots.Counts}
            /if (!${ClassList.Find[${Spawn[pc =${NetBots.Client.Arg[${i}]}].Class.ShortName}]}) {
                /docommand /${echo} [${functionName}]: <ERROR Unknow class found on ${NetBots[${NetBots.Client.Arg[${i}]}].Name} please restart EQ>
                /varset BEST_ORDERED_LIST
                /return
            }
| /echo debug: check ${NetBots.Client.Arg[${i}]}
            
            /if (!${BEST_ORDERED_LISTFind.Find[|${NetBots.Client[${i}]}|]}) {
            /if (!${BankerToons.Find[|${NetBots.Client[${i}]}|]}) {
            /if (${ClassList.Arg[${f}, ].Equal[${NetBots[${NetBots.Client.Arg[${i}]}].Class.ShortName}]}) {
                :BestRetry
                /for j 1 to ${NetBots.Counts}
                    | /if (${NetBots.Client.Arg[${j}].NotEqual[${NetBots.Client.Arg[${i}]}]}) {
                    /if (!${BEST_ORDERED_LISTFind.Find[|${NetBots.Client[${j}]}|]}) {
                    /if (${ClassList.Arg[${f}, ].Equal[${NetBots[${NetBots.Client.Arg[${j}]}].Class.ShortName}]}) {
                        | WAR,SHD,PAL,ROG,BER,BRD,MNK,RNG,BST
                        /if (${Select[${NetBots[${NetBots.Client.Arg[${j}]}].Class.ShortName},WAR,SHD,PAL,ROG,BER,BRD,MNK,RNG,BST]}) {
                            /if (${NetBots[${NetBots.Client.Arg[${j}]}].MaxHPs} > ${NetBots[${NetBots.Client.Arg[${i}]}].MaxHPs}) {
                                /varset PCMax ${NetBots.Client[${j}]}
                            }
                        | DRU,ENC,MAG,WIZ,NEC,CLR,SHM
                        } else {
                            /if (${NetBots[${NetBots.Client.Arg[${j}]}].MaxMana} > ${NetBots[${NetBots.Client.Arg[${i}]}].MaxMana}) {
                                /varset PCMax ${NetBots.Client[${j}]}
                            }
                        }
                    }
                    }
                    | }
                /next j
                /if (${PCMax.Length}) {
                    /varset BEST_ORDERED_LIST ${BEST_ORDERED_LIST}${If[${Bool[${BEST_ORDERED_LIST}]},|,]}${PCMax}
                    /varset BEST_ORDERED_LISTFind |${BEST_ORDERED_LIST}|
                    /varset PCMax
                    /goto :BestRetry
                } else {
                    /varset PCMax ${NetBots.Client[${i}]}
                    /varset BEST_ORDERED_LIST ${BEST_ORDERED_LIST}${If[${Bool[${BEST_ORDERED_LIST}]},|,]}${PCMax}
                    /varset BEST_ORDERED_LISTFind |${BEST_ORDERED_LIST}|
                    /varset PCMax
                }
            }
            }
            }
        /next i
    /next f

/return

Sub DefinedNbGroup

    /if (!${Defined[i]}) /declare i int local
    /if (!${Defined[j]}) /declare j int local 0
    
    /if (!${Defined[NUMBER_OF_GROUP]})  /declare NUMBER_OF_GROUP int outer
    
    /for i 1 to ${NetBots.Counts}
        /if (${BankerToons.Find[|${NetBots.Client[${i}]}|]}) /varcalc j ${j} + 1
    /next i

    | NUMBER_OF_GROUP = ARROUND UP (NB BOTS / 6)
    /if (${Math.Calc[(${NetBots.Counts} - ${j}) / 6]} > ${Math.Calc[(${NetBots.Counts} - ${j}) / 6].Int}) {
        /varset NUMBER_OF_GROUP ${Math.Calc[((${NetBots.Counts} - ${j}) / 6) + 1].Int}
    } else {
        /varset NUMBER_OF_GROUP ${Math.Calc[(${NetBots.Counts} - ${j}) / 6].Int}
    }

    /docommand /${echo} [${functionName}]: Calculate the number of group needed [${NUMBER_OF_GROUP}] for [${Int[${Math.Calc[${NetBots.Counts} - ${j}]}]}] bots

/return

Sub CreateBestMasterList(int NUMBER_OF_GROUP)

    | Loops vars
    /if (!${Defined[f]}) /declare f int local
    /if (!${Defined[g]}) /declare g int local
    /if (!${Defined[i]}) /declare i int local
    /if (!${Defined[j]}) /declare j int local
    /if (!${Defined[k]}) /declare k int local
    /if (!${Defined[l]}) /declare l int local
    /if (!${Defined[RETRY]})    /declare RETRY int local 1

    /docommand /${echo} [${functionName}]: Determine best master for each group...

    | Find all Master for each group
    :RetryMasterSearch

    | CLASS GROUP_TYPE scan
    /declare lNextMasterSearch bool local FALSE
    /declare lEndMasterSearch bool local FALSE

    /varset lNextMasterSearch FALSE
    /for f 1 to ${RETRY}
        | GROUP_TYPE scan
        /for k 1 to 4
        | ${If[${NUMBER_OF_GROUP} < 4,${NUMBER_OF_GROUP},4]}
            /if (${NUMBER_OF_GROUP} > 4 && ${k} > 4) {
                /varcalc j 8 - ${k}
                | /echo debug j=${j}
            } else {
                /varset j ${k}
            }

            | Sub CLASS GROUP_TYPE scan
            /varset lNextMasterSearch FALSE
            /for l 1 to ${Math.Calc[${GROUP_TYPE[${j}].Arg[${f}, ].Arg[1,*].Count[/]} + 1]}
                | NetBots scan
                /for i 1 to ${Math.Calc[${BEST_ORDERED_LIST.Count[|]} + 1]}
                    | Rewrite var
                    /varset GROUP_MASTER_LIST_FIND |${GROUP_MASTER_LIST}|

                    | Exclude MASTERS and ALTS already called
                    /if (!${GROUP_MASTER_LIST_FIND.Find[:${BEST_ORDERED_LIST.Arg[${i},|]}#]}) {
                        | Find the bot class combination
                        /if (${GROUP_TYPE[${j}].Arg[${f}, ].Arg[1,*].Arg[${l},/].Equal[${Spawn[pc =${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}]}) {

                            || LIST GROUP_MASTER
                            /varset GROUP_MASTER_LIST ${GROUP_MASTER_LIST}${If[${Bool[${GROUP_MASTER_LIST}]},|,]}${NetBots[${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}:${BEST_ORDERED_LIST.Arg[${i},|]}#${j}
                            /bct ${BEST_ORDERED_LIST.Arg[${i},|]} //docommand /nomodkey /notify ConfirmationDialogBox No_Button leftmouseup

                            /if (${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1].Int} >= ${NUMBER_OF_GROUP}) {
                                /varset lEndMasterSearch TRUE
                                /if (${lEndMasterSearch}) /break
                                |  /goto :EndMasterSearch
                            }
                            /varset lNextMasterSearch TRUE
                            /if (${lNextMasterSearch}) /break
                            |  /goto :NextMasterSearch
                        }
                    }
                /next i
                /if (${lNextMasterSearch}) /break
                /if (${lEndMasterSearch}) /break
            /next l
            |  :NextMasterSearch
            /if (${lEndMasterSearch}) /break
        /next k
        /if (${lEndMasterSearch}) /break
    /next f
    |  :EndMasterSearch

    /if (${RETRY} <= 1 && ${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1].Int} < ${NUMBER_OF_GROUP}) {
        /varset RETRY 50
        /goto :RetryMasterSearch
    }

/return

Sub CreateBestMasterList2(int NUMBER_OF_GROUP)

    | Loops vars
    /if (!${Defined[i]}) /declare i int local

    | Not found - Find only all best bot to determine Master for each group

    /if (!${GROUP_MASTER_LIST.Length}) {
        /declare lNextMasterSearch2 bool local FALSE
        
        :NextMasterSearch2
            /varset lNextMasterSearch2 FALSE
            | NetBots scan
            /for i 1 to ${Math.Calc[${BEST_ORDERED_LIST.Count[|]} + 1]}
                | Rewrite var
                /varset GROUP_MASTER_LIST_FIND |${GROUP_MASTER_LIST}|

                | Exclude MASTERS and ALTS already called
                /if (!${GROUP_MASTER_LIST_FIND.Find[|${BEST_ORDERED_LIST.Arg[${i},|]}#]}) {
                    || LIST GROUP_MASTER
                    /varset GROUP_MASTER_LIST ${GROUP_MASTER_LIST}${If[${Bool[${GROUP_MASTER_LIST}]},|,]}${Spawn[pc =${BEST_ORDERED_LIST.Arg[${i},|]}].Class.ShortName}:${BEST_ORDERED_LIST.Arg[${i},|]}#${j}

                    /if (${Math.Calc[${GROUP_MASTER_LIST.Count[|]} + 1].Int} >= ${NUMBER_OF_GROUP}) {
                        /break
                        |  /goto :EndMasterSearch2
                    }
                    /varset lNextMasterSearch2 TRUE
                    /break
                    |  /goto :NextMasterSearch2
                }
            /next i
        /if (${lNextMasterSearch2}) /goto :NextMasterSearch2
        |  :EndMasterSearch2
    }

/return

Sub DeclareOuterVar

    /if (!${Defined[BEST_ORDERED_LIST]})        /declare BEST_ORDERED_LIST string outer
    /if (!${Defined[GROUP_MASTER_LIST]})        /declare GROUP_MASTER_LIST string outer
    /if (!${Defined[GROUP_MASTER_LIST_FIND]})   /declare GROUP_MASTER_LIST_FIND string outer
    /if (!${Defined[GROUP_ALT_LIST]})           /declare GROUP_ALT_LIST string outer
    /if (!${Defined[GROUP_ALT_LIST_FIND]})      /declare GROUP_ALT_LIST_FIND string outer

/return

Sub SaveForm(bool CustomSave)

    | Loops vars
    /if (!${Defined[e]}) /declare e int local
    /if (!${Defined[f]}) /declare f int local
    /if (!${Defined[i]}) /declare i int local

    /if (!${Defined[count]}) /declare count int local 0

    /if (!${Raid.Members} || !${Bool[${Raid.Leader}]}) /return

    /if (!${Defined[INVITE_LIST1]}) /declare INVITE_LIST1 string outer
    /varset INVITE_LIST1 ${NetBots[${Raid.Leader}].Class.ShortName}:${Raid.Leader}#0
    /varset NUMBER_OF_GROUP 1
    /varcalc count ${count} + 1
    
    /for e 1 to 50
        /declare lscanFullGroup bool local FALSE
        :scanFullGroup
        /varset lscanFullGroup FALSE
        /for f 1 to ${Raid.Members}
| /echo debug::(${Raid.Member[${f}].Group} == ${e})
            /if (${Raid.Member[${f}].Group} == ${e}) {
| /echo debug:::INVITE_LIST${e} ${NetBots[${Raid.Member[${f}]}].Class.ShortName}:${Raid.Member[${f}]}#0
                /if (!${Defined[INVITE_LIST${e}]} && ${Raid.Member[${f}].GroupLeader}) {
                    /if (!${Defined[INVITE_LIST${e}]})  /declare INVITE_LIST${e} string outer
                    /if (!${NetBots[${Raid.Member[${f}]}].ID}) {
                        /varset INVITE_LIST${e} ???:${Raid.Member[${f}]}#0
                    } else {
                        /varset INVITE_LIST${e} ${NetBots[${Raid.Member[${f}]}].Class.ShortName}:${Raid.Member[${f}]}#0
                    }
                    /varcalc NUMBER_OF_GROUP ${NUMBER_OF_GROUP} + 1
                    /varcalc count ${count} + 1
                    /varset lscanFullGroup TRUE
                    /break
                    |  /goto :scanFullGroup
                } else /if (${Defined[INVITE_LIST${e}]} && !${Raid.Member[${f}].GroupLeader}) {
                    /if (${NetBots[${Raid.Member[${f}]}].ID}) {
                        /varset INVITE_LIST${e} ${INVITE_LIST${e}}${If[${Bool[${INVITE_LIST${e}}]}, ,]}${NetBots[${Raid.Member[${f}]}].Class.ShortName}:${Raid.Member[${f}]}
                    } else {
                        /varset INVITE_LIST${e} ${INVITE_LIST${e}}${If[${Bool[${INVITE_LIST${e}}]}, ,]}???:${Raid.Member[${f}]}
                    }
                    /varcalc count ${count} + 1
                }
            }
            /if (${count} >= ${Raid.Members}) {
                /call SaveIni
                /return
            }
        /next f
        /if (${lscanFullGroup}) /break
    /next e
    /if (${lscanFullGroup}) /goto :scanFullGroup

    /docommand /${echo} [${functionName}]: SaveForm unknow ERROR

/return

Sub SaveIni

    | Loops vars
    /if (!${Defined[e]}) /declare e int local

    | Write GROUP
    /for e 1 to ${NUMBER_OF_GROUP}
            /ini "${IniName}" "${Section}" "INVITE_LIST${e}" "${INVITE_LIST${e}}"
    /next e

    /docommand /${echo} [${functionName}]: Saving configuration file: [${IniName}]

/return

Sub RestoreForm(bool CustomLoad)

    | Loops vars
    /if (!${Defined[e]}) /declare e int local
    /if (!${Defined[i]}) /declare i int local

    /if (!${Defined[NUMBER_OF_GROUP]})  /declare NUMBER_OF_GROUP int outer

    /if (${CustomLoad} || ${Ini[${IniName},${Section},BotsList].Equal[${NetBots.Client}]}) {

        | Read master Cache
        /for e 1 to 50
            | Read groups Cache
            /if (${Bool[${Ini[${IniName},${Section},INVITE_LIST${e}]}]}) {
                /if (!${Defined[INVITE_LIST${e}]})  /declare INVITE_LIST${e} string outer
                /varset NUMBER_OF_GROUP ${e}
                /varset INVITE_LIST${e} ${Ini[${IniName},${Section},INVITE_LIST${e}]}
            } else {
                /break
                |  /goto :GroupCacheSkip
            }
        /next e
        |  :GroupCacheSkip

        /if (!${Defined[RaidCACHE]}) /declare RaidCACHE bool outer
        /varset RaidCACHE TRUE

        /if (${CustomLoad}) {
            /docommand /${echo} [${functionName}]: Using configuration file: [${IniName}] NbGroup:${NUMBER_OF_GROUP}
        } else {
            /docommand /${echo} [${functionName}]: Using cache file.
        }

    }

/return