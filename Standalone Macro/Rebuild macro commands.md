## Main alias command ( Allows you to choose who to be controlled )
```
/me         =/bct ${Me.CleanName} ${Me.CleanName}|${Target.ID}|${Zone.ID} <arg>
/all        =/bc all|${Target.ID}|${Zone.ID} <arg>
/group      =/bc group|${Target.ID}|${Zone.ID} <arg>
/tar        =/bc tar|${Target.ID}|${Zone.ID} <arg>
/<class>    =/bc <Class>|${Target.ID}|${Zone.ID} <arg>
/stop       =/bc all off
```
## Macro command : ( All macro command, and sub arguement-Optional )
```
Atk     <Arg2>: On|Off|It
Tank    <Arg2>: On|Off|aoe <class>|<class>
Sup     <Arg2>: On|Off|dru|enc|mag
Melee   <Arg2>: On|Off|pal|shd|rog|brd|mnk|ber|rng|bst
Stun    <Arg2>: On|Off
Aoe     <Arg2>: On|Off
Mez     <Arg2>: On|Off|Aoe
Hold    <Arg2>: On|Off|melee|caster|healer|<class>  ( Moving hold-Fight,Cast )

Dps     <Arg2>: Normal|Boost|Burn

( Heal and Curse is always on, Parallel and Rotation heal for constant cast, command not necessary in normal uses )
Heal    <arg2>: On|Off|fix|spam <class>|<class>
Curse   <arg2>: On|Off
Debuff  <arg2>: On|Off|status|dru1|dru2|<class>|but <classes>|Donor <class>|Bp <class>|Epic <class>

Buff    <arg2>: On|Off|aura|check  ( Self buff )
Sune    <arg2>: All|Tar            ( Long buff + Shrink + Healer Automation)
Finals  <arg2>: All|Tar            ( Short buff )
Spirit  <arg2>: On|Off             ( Donator Vambrace auto buff )
Twist   <arg2>: On|Off
Unbuff  <arg2>: All|Levi|Illu|<Spell>
Automation
Shrink
Levi
Spells  <arg2>: All|<save name>     ( ReLoad spells bar )

Stick   <arg2>: On|Off      ( Sticking )
Move    <arg2>: Square|Me|Tar|Talk|Say <text>|Combat <Stick|Move>  ( Roman formation|Move to me|target|target with standard say (to enter zone)|target with custom say|Combat melee follow )

Pos     <Arg2>: lit|ele|lli                         ( Start fight position )
Balance <Arg2>: On|Off|<% Value>                    ( Balance DPS )
Bane                        ( Vampire Bane )

Forage  <arg2>: On|Off
Combine                     ( Tradskill and bag combine )

Accept  <arg2>: On|Off|All|Me|Tar
Rez     <arg2>: On|Off|All|Me|Tar|Bot
Drag                        ( Drag corpse + Auto consent )
Coth    <arg2>: On|Off|Tar|ButTar|Group|Raid|Bot|Perma  ( Advanced coth )

Pet     <arg2>: Summon|Augment|Attack|Hold|Weapon <Normal|Zek>|Clear    ( Advanced pet management )

Bank    <arg2>: Clear|Stock ( Clear, and Auto stock in bank )
Inv     <arg2>: Tar|Food|Save|Restore|Check|Armor|Aug|Stock|Bank|Clean|Clear|OpenBag    ( Advanced inventory management )
Finditem                    ( Return bots item quantity and score - inv,bank,equip,forged)

Aug     /say #bot augmentitem
Stats   /bcaa //say #mystats
Focus   /bcaa //say #myfocus

form    <arg2>: Raid|Group  ( Auto form the raid or group )
zone    <arg2>: Out|Guild|Forest|Vale|<Zone>|Leef   ( Auto moving between zone )
loot    <arg2>: On|Off|All|Me|Tar|Ignore|Sell|Keep|Destroy|Quest|Max|Auto|Common|Notify     ( Advanced auto looting, by bots analysis repartition )

stop                        ( Stop all - Atk,Moving )
eq      <arg2>: Sound <On|Off>|Effect <On|Off>|Fps <Value>      ( Set some eq parameter )

macro   <arg2>: Start|Restart|End|Alias|Stat <LPS>
```
## Sample with this new structure
```
/all atk      ( all attack target )
/all debuff   ( all debuff target )
/me tank aoe  ( me tank with aoe aggro )
/me coth raid ( me coth the raid )
```
## Sample with the old structure
```
/allon        ( all attack target )
/debuffall    ( all debuff target )
/tankaoe      ( me tank with aoe aggro )
/cothraid     ( me coth the raid )
```
## Aliases with the old structure
```
/acceptall=/bc Accept|GO
/acceptoff=/bc AutoAccept|OFF
/accepton=/bc AutoAccept|GO
/accepttar=/bc Accept|${Target.CleanName}
/allfocus=/bcaa //say #myfocus
/alloff=/bc AllOff|0
/allon=/bc AllON|ALL|${Target.ID}
/allstats=/bcaa //say #mystats
/aoe=/bc AOETarget|GO
/aug=/say #bot augmentitem
/aura=/bc Aura|GO
/automation=/bc Automation|GO
/autooff=/bc AutoAttack|0|0
/bag=/bc OpenBag
/bane=/bc Bane|${Target.ID}
/bankclean=/bc bankclean
/bankstock=/bc bankstock
/boost=/bc MaxDPS|LOW
/buff=/bc BuffCheck
/burn=/bc MaxDPS|MAX
/combatmoveoff=/bc CombatMove|OFF
/combatmoveon=/bc CombatMove|GO
/combatstickoff=/bc CombatStick|OFF
/combatstickon=/bc CombatStick|GO
/cool=/bc MaxDPS|0
/coth=/bc CoTH|${Me.CleanName}|bot
/cothbot=/bc CoTH|${Me.CleanName}|bot
/cothbuttar=/bc CoTH|${Me.CleanName}|2|${Target.CleanName}
/cothgroup=/bc CoTH|${Me.CleanName}|group
/cothperma=/bc CoTH|${Me.CleanName}|perma|${Target.CleanName}
/cothraid=/bc CoTH|${Me.CleanName}|raid
/cothtar=/bc CoTH|${Me.CleanName}|1|${Target.CleanName}
/debuffall=/bc DebuffAll|${Target.ID}|${DruidDebuffed}
/debuffallbutdru=/bc DebuffAllButDruid|${Target.ID}
/debuffallbutdrushm=/bc DebuffAllButDruidShaman|${Target.ID}
/debuffdru1=/bc DebuffDru1|${Target.ID}
/debuffdru2=/bc DebuffDru2|${Target.ID}
/debuffenc=/bc DebuffEnc|${Target.ID}
/debuffmag=/bc DebuffMag|${Target.ID}
/debuffnec=/bc DebuffNec|${Target.ID}
/debuffshm=/bc DebuffShm|${Target.ID}
/depositstuff=/echo NinjadvLoot depositing items to guildbank
/dpsto=/bc DpsTo
/drag=/bc Drag|GO
/dru=/bc DruStatus
/drubp1=/bc DebuffDruBP1|${Target.ID}
/drubp2=/bc DebuffDruBP2|${Target.ID}
/drudonor1=/bc DebuffDruDonor1|${Target.ID}
/drudonor2=/bc DebuffDruDonor2|${Target.ID}
/druepic1=/bc DebuffDruEpic1|${Target.ID}
/druepic2=/bc DebuffDruEpic2|${Target.ID}
/elepos=/bca elepos
/end=/endmacro
/endall=/bcaa //endmacro
/finals=/bc Finals|GO
/finalstar=/bc Finals|${Target.CleanName}
/finditem=/bct ${Me.CleanName} finditem
/focus=/say #myfocus
/followme=/bc Follow|${Me.CleanName}
/followtar=/bc Follow|${Target.CleanName}
/food=/bc Restock|${Target.ID}
/forageoff=/bc FORAGE|OFF
/forageon=/bc FORAGE|GO
/gon=/bc GroupON|ALL|${Target.ID}
/guildhall=/bc Guildhall|GO
/healall=/bc HealALL|${Target.CleanName}
/healclr=/bc HealCleric|${Target.CleanName}
/healdru=/bc HealDruid|${Target.CleanName}
/healfix=/bc HealFix|FIX|${Target.CleanName}
/healoff=/bc HealingOff|0
/healothers=/bc HealOthers|GO
/healpal=/bc HealPaladin|${Target.CleanName}
/healshm=/bc HealShaman|${Target.CleanName}
/healspam=/bc HealSPAM|SPAM
/healspamclr=/bc HealSPAMclr|SPAM
/healspamdru=/bc HealSPAMdru|SPAM
/healspampal=/bc HealSPAMpal|SPAM
/healspamshm=/bc HealSPAMshm|SPAM
/invarmor=/bc Inventory|Armor
/invaug=/bc Inventory|Aug
/invbank=/bc Inventory|Bank
/invcheck=/bc Inventory|Check
/invclean=/bc Inventory|Clean
/invrestore=/bc Inventory|Restore
/invrestoreme=/bct ${Me.CleanName} Inventory|Restore
/invsave=/bc Inventory|Save
/invsaveme=/bct ${Me.CleanName} Inventory|Save
/invstock=/bct ${toonstock} Inventory|Stock
/it=/bct ${Me.CleanName} It|999999
/key=/keys
/levi=/bc levi
/litdebuf=/bca litdebuf ${Target}
/litpos=/bca litpos
/llipos=/bca llipos
/load=/loadspells
/lootall=/bc loot|ALL
/lootauto=/bct ${Me.CleanName} AdvLoot|Auto
/lootcommon=/bct ${Me.CleanName} AdvLoot|Common
/lootdestroy=/bct ${Me.CleanName} AdvLoot|Destroy
/lootignore=/bct ${Me.CleanName} AdvLoot|Ignore
/lootkeep=/bct ${Me.CleanName} AdvLoot|Keep
/lootnotify=/bct ${Me.CleanName} AdvLoot|Notify
/lootoff=/bc loot|0
/looton=/bc loot|GO
/lootquest=/bct ${Me.CleanName} AdvLoot|Quest
/lootsell=/bct ${Me.CleanName} AdvLoot|Sell
/make=/bc make
/mana=/bc mana
/maskoff=/bc MASK|OFF
/maskon=/bc MASK|GO
/me=/bct ${Me.CleanName}
/meit=/bct ${Me.CleanName} It|999999
/meleeall=/bc MeleeTarget|ALL|${Target.ID}
/meleeber=/bc MeleeTarget|BER|${Target.ID}
/meleebrd=/bc MeleeTarget|BRD|${Target.ID}
/meleebst=/bc MeleeTarget|BST|${Target.ID}
/meleehold=/bc MeleeHold
/meleeit=/varset TargetMeleeID 999999
/meleemnk=/bc MeleeTarget|MNK|${Target.ID}
/meleeoff=/bc MeleeTarget|0
/meleepal=/bc MeleeTarget|PAL|${Target.ID}
/meleerng=/bc MeleeTarget|RNG|${Target.ID}
/meleerog=/bc MeleeTarget|ROG|${Target.ID}
/meleeshd=/bc MeleeTarget|SHD|${Target.ID}
/meoff=/bct ${Me.CleanName} AllOff|0
/meon=/bct ${Me.CleanName} AllON|ALL|${Target.ID}
/mez=/bc Mez|AOE
/move=/bc MoveTarget|${Zone.ID}|${Target.ID}
/movetalk=/bc MoveTarget|${Zone.ID}|${Target.ID}|GO
/necit=/varset TargetNecromancerID 999999
/necoff=/bc NecTarget|0
/necon=/bc NecTarget|${Target.ID}
/normal=/bc MaxDPS|0
/petattack=/bc PetAttack|${Target.ID}
/petaugment=/bc PetAugment|GO
/petclear=/bc PetClear
/pethold=/bc PetHold|GO
/petsummon=/bc PetSummon|GO
/petweapon=/bc PetWeapon
/petzek=/bc PetZek
/potoff=/bc POT|OFF
/poton=/bc POT|GO
/restart=/bcaa //macro ${MainMacro}
/restock=/bc Restock|${Target.ID}
/rez=/bc RezMe|${Me.CleanName}
/rezall=/bc RezMe|All
/rezbot=/bc RezMe|Bot
/rezme=/bc RezMe|${Me.CleanName}
/reztar=/bc RezTar|${Target.ID}
/scoreitem=/bct ${Me.CleanName} scoreitem
/sellstuff=/echo NinjadvLoot selling items to vendor
/setalias=/noparse /bcaa //macro start.mac full
/shrink=/bc Shrink|GO
/shrinkall=/bc Shrink|ALL
/sn=/bc sn
/snt=/bc snt
/soundoff=/bc sound|0
/soundon=/bc sound|1
/spells=/bc Spells|GO
/spirit=/bc Spirit|GO
/square=/bca square 5 ${Me.Y},${Me.X} ${Me.Heading.Degrees}
/start=/noparse /bcaa //if (!${strMainTank.Length}) /macro start.mac
/stats=/say #mystats
/stickme2=/multiline @ /echo Command [ /stickme ]@ /noparse /bca //multiline ; /if (!${Defined[StickZone]}) /declare StickZone string global;/if (!${Defined[StickTar]}) /declare StickTar int global;/if (!${Defined[TankTarget]}) /declare TankTarget string global 0@ /bca //varset StickZone ${Zone.Name}@ /bca //varset StickTar ${Me.ID}@ /noparse /bca //if (!${Me.Class.Name.Equal[Cleric]} && !((${Me.Class.Name.Equal[Warrior]} || ${Me.Class.Name.Equal[Paladin]} || ${Me.Class.Name.Equal[Shadow Knight]}) && ${Me.CleanName.Lower.Equal[${strMainTank.Lower}]}) && ${Zone.Name.Find[${StickZone}]} && ${Spawn[${StickTar}].ID} && ${Spawn[${StickTar}].Distance}<300 && ${LineOfSight[${Me.Y},${Me.X},${Me.Z}:${Spawn[${StickTar}].Y},${Spawn[${StickTar}].X},${Spawn[${StickTar}].Z}]}) /multiline ; /echo Sticking to [ ${Spawn[${StickTar}].CleanName} ];/squelch /face ID ${StickTar} fast;/stick ID ${StickTar} 10 moveback behindonce@/noparse /bca //timed 10 /if (${Stick.Status.Equal[OFF]}) /bc NOT Sticking to [ ${Spawn[${StickTar}].CleanName} - ${Spawn[${StickTar}].Distance} - ${Spawn[${StickTar}].LineOfSight} - ${Zone.Name} ]
/stickme3=/multiline @ /echo AutoAdvPath [ /stickme ]@ /noparse /bca //multiline ; /if (!${Defined[StickZone]}) /declare StickZone string global;/if (!${Defined[StickTar]}) /declare StickTar int global;/if (!${Defined[TankTarget]}) /declare TankTarget string global 0@ /bca //varset StickZone ${Zone.Name}@ /bca //varset StickTar ${Me.ID}@ /noparse /bca //if (${TankTarget.Equal[0]} && ${Zone.Name.Find[${StickZone}]} && ${Spawn[${StickTar}].ID} && ${Spawn[${StickTar}].Distance}<300 && ${LineOfSight[${Me.Y},${Me.X},${Me.Z}:${Spawn[${StickTar}].Y},${Spawn[${StickTar}].X},${Spawn[${StickTar}].Z}]}) /multiline ; /echo [AutoAdvPath] Sticking to [ ${Spawn[${StickTar}].CleanName} ];/squelch /face ID ${StickTar} fast;/stick ID ${StickTar} 5 moveback behindonce
/stickme4=/multiline @ /echo AutoAdvPath [ /stickme ]@ /noparse /bca //multiline ; /if (!${Defined[StickZone]}) /declare StickZone string global;/if (!${Defined[StickTar]}) /declare StickTar int global;/if (!${Defined[TankTarget]}) /declare TankTarget string global 0@ /bca //varset StickZone ${Zone.Name}@ /bca //varset StickTar ${Me.ID}@ /noparse /bca //if (${TankTarget.Equal[0]} && ${Zone.Name.Find[${StickZone}]} && ${Spawn[${StickTar}].ID} && ${Spawn[${StickTar}].Distance}<300) /multiline ; /echo [AutoAdvPath] Sticking to [ ${Spawn[${StickTar}].CleanName} ];/squelch /face ID ${StickTar} fast;/stick ID ${StickTar} 10 moveback behindonce
/stickme=/multiline @ /echo Command [ /stickme ]@ /noparse /bca //multiline ; /if (!${Defined[StickZone]}) /declare StickZone string global;/if (!${Defined[StickTar]}) /declare StickTar int global;/if (!${Defined[TankTarget]}) /declare TankTarget string global 0@ /bca //varset StickZone ${Zone.Name}@ /bca //varset StickTar ${Me.ID}@ /noparse /bca //if (${TankTarget.Equal[0]} && ${Zone.Name.Find[${StickZone}]} && ${Spawn[${StickTar}].ID} && ${Spawn[${StickTar}].Distance}<300 && ${LineOfSight[${Me.Y},${Me.X},${Me.Z}:${Spawn[${StickTar}].Y},${Spawn[${StickTar}].X},${Spawn[${StickTar}].Z}]}) /multiline ; /echo Sticking to [ ${Spawn[${StickTar}].CleanName} ];/squelch /face ID ${StickTar} fast;/stick ID ${StickTar} 10 moveback behindonce@/noparse /bca //timed 10 /if (${Stick.Status.Equal[OFF]}) /bc NOT Sticking to [ ${Spawn[${StickTar}].CleanName} - ${Spawn[${StickTar}].Distance} - ${Spawn[${StickTar}].LineOfSight} - ${Zone.Name} ]
/stickoff=/multiline @ /echo Command [ /stickoff ]@ /noparse /bca //stick off
/stop=/bc AllOff|0
/stunoff=/bc StunTarget|0
/stunon=/bc StunTarget|GO
/sune=/bc Sune|GO
/sunecheck=/bc SuneCheck
/suneoff=/bc SuneCheck|0
/suneon=/bc SuneCheck|All
/sunetar=/bc Sune|${Target.CleanName}
/supall=/bc SupTarget|ALL|${Target.ID}
/supdru=/bc SupTarget|DRU|${Target.ID}
/supenc=/bc SupTarget|ENC|${Target.ID}
/supit=/varset TargetSupID 999999
/supmag=/bc SupTarget|MAG|${Target.ID}
/supoff=/bc SupTarget|0
/tank=/bc TankTarget|${Me.CleanName}|Target
/tankaoe=/bc TankTarget|${Me.CleanName}|AOE
/tankoff=/bc TankTarget|0
/tankpal=/bc TankTarget|PAL|Target
/tankpalaoe=/bc TankTarget|PAL|AOE
/tankshd=/bc TankTarget|SHD|Target
/tankshdaoe=/bc TankTarget|SHD|AOE
/tankwar=/bc TankTarget|WAR|Target
/tankwaraoe=/bc TankTarget|WAR|AOE
/then=/multiline ; /varset DidThenClause 1 ; /call ExecCommand
/toonstock=/bct ${toonstock} stock
/twistoff=/bc TWIST|OFF
/twiston=/bc TWIST|GO
/unbuff=/bc Unbuff|GO
/unbuffall=/bc Unbuff|GO
/unbufflevi=/bc Unbuff|GO LEVITATION
/unbufftar=/bc Unbuff|${Target.CleanName}
/valikoff=/bc VALIK|OFF
/valikon=/bc VALIK|GO
/wizit=/varset TargetWizardID 999999
/wizoff=/bc WizTarget|0
/wizon=/bc WizTarget|${Target.ID}
/zone=/bc zone
/zoneout=/bc zoneout
```
