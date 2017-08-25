## Main alias command ( Allows you to choose who to be controlled )
```
/me      <cmd> <Option> =/bct ${Me.CleanName} ${Me.CleanName}:${Target.ID}:${Zone.ID}:${Me.Y.Int},${Me.X.Int},${Me.Z.Int},${Me.Heading.Degrees.Int}
/all     <cmd> <Option> =/bc all:${Target.ID}:${Zone.ID}:${Me.Y.Int},${Me.X.Int},${Me.Z.Int},${Me.Heading.Degrees.Int}
/group   <cmd> <Option> =/bc group:${Target.ID}:${Zone.ID}:${Me.Y.Int},${Me.X.Int},${Me.Z.Int},${Me.Heading.Degrees.Int}
/tar     <cmd> <Option> =/bc tar:${Target.ID}:${Zone.ID}:${Me.Y.Int},${Me.X.Int},${Me.Z.Int},${Me.Heading.Degrees.Int}
/<class> <cmd> <Option> =/bc <Class>:${Target.ID}:${Zone.ID}:${Me.Y.Int},${Me.X.Int},${Me.Z.Int},${Me.Heading.Degrees.Int}
/stop                   =/bc all:0:${Zone.ID}:0 off

```

## Macro command : ( All macro command, and sub arguement-Optional )
```
/Tank    <Option>: Off|Aoe <class>|<class>                    ( Tank/Offtank )
/Atk     <Option>: Off|It                                     ( Global attack )
/Melee   <Option>: Off|pal|shd|rog|brd|mnk|ber|rng|bst        ( Melee attack )
/Sup     <Option>: Off|dru|enc|mag                            ( Support attack )
/Nuk     <Option>: Off                                        ( Wizard attack )
/Nec     <Option>: Off                                        ( Necro attack )
/Aoe     <Option>: Off                                        ( Aoe spells atk )
/Mez     <Option>: Off|Auto|Tar|Aoe                           ( Mez auto/tar/aoe )
/Stun    <Option>: On|Off|Ini                                 ( Stun atk/mode )
/Hold    <Option>: On|Off|melee|caster|healer|<class>         ( Moving hold-Fight,Cast )

/Dps     <Option>: Normal|Boost|Burn                          ( Dps mode )

                                                              ( Heal and Curse is always auto, Parallel and Rotation heal for constant cast, command not necessary in normal uses )
/Heal    <Option>: On|Off|fix|spam <class>|<class>            ( Auto heal, Fix=Quick heal, Spam=Simple heal spamming )
/Curse   <Option>: On|Off                                     ( Auto cure )
/Debuff  <Option>: Off|status|dru1|dru2|<class>|but <classes>|Donor <class>|Bp <class>|Epic <class>
                                                              ( Auto Debuff tar, auto dru rotation, manual )

                                                              ( All cast is managed by Queue by priority, and casted only if necessary - Filtered before casting or Breaked before the end )
/Mcast   <arg>: Type Spell|Spells on Tar|Tars                 ( Manual self/target casting Spell|Disc|Alt )
               Type=heal|cheal|force|first|after|curse|mbuff  (mass group buff)|group

                                                              ( All buff is auto launched only if necessary - Self/Tar/Group/Buff block analysis )
/Buff    <Option>: On|Off|All|Ini                             ( Self buff )
/Sune    <Option>: All|Tar                                    ( Long buff + Shrink + Healer Automation)
/Finals  <Option>: All|Tar                                    ( Short buff )
/Spirit  <Option>: On|Off                                     ( Donator Vambrace auto buff )
/Aura                                                         ( auracast )
/Twist   <Option>: On|Off|<Sequence>|Ini                      ( Bard twist, twist auto on atk )
/Unbuff  <Option>: All|Levi|Illu|<Spell>                      ( Unbuff - Auto unbuff is coded in hard for specific class in raid )
/Automation                                                   ( Summon healer automation )
/Shrink  <Option>: All                                        ( Shrink bots )
/Levi                                                         ( Necro, Clicies levi )
/Spells  <Option>: All|<save name>|Ini                        ( ReLoad spells bar )

/Stick   <Option>: On|Off                                     ( Sticking )
/Move    <Option>: Me|Tar|Talk|Say <text>
                                                              ( Move to me|target|target with standard say (to enter zone)|target with custom say )
/Square                                                       ( Roman formation )
/Combat  <Option>: Stick|Move                                 ( Combat melee follow/move )
                                                             
/Coth    <Option>: On|Off|Tar|ButTar|Group|Raid|Bot|Perma
                                                              ( Advanced coth - Parallel cothing )

/Pos     <Option>: lit|ele|lli                                ( Start fight position )
/Balance <Option>: On|Off|<% Value>                           ( Balance DPS )
/Bane                                                         ( Vampire Bane )

/Forage  <Option>: On|Off                                     ( Forage )
/Combine                                                      ( Tradskill and bag combine )

/Accept  <Option>: On|Off|All|Me|Tar                          ( Accept dialog )
/Rez     <Option>: On|Off|All|Me|Tar|Bot                      ( Auto Drag + Consent + Rez + Accept )
/Drag                                                         ( Auto Drag + Consent )

/Pet     <Option>: Summon|Augment|Attack|Hold|Weapon <Normal|Zek>|Clear
                                                              ( Advanced pet management -  )

/Bank    <Option>: Clear|Stock                                ( Clear, and Auto stock in bank )
/Inv     <Option>: Tar|Food|Save|Restore|Check|Armor|Aug|Stock|Bank|Clean|Clear|OpenBag|FindItem
                                                              ( Advanced inventory management )
/Finditem                                                     ( Return bots item quantity and score - inv,bank,equip,forged)

/Aug     =/say #bot augmentitem                               ( Force to forge augement )
/Stats   =/bcaa //say #mystats                                ( View mystats server on all bots )
/Focus   =/bcaa //say #myfocus                                ( View myfocus server on all bots )

/form    <Option>: Raid|Group|Ini                             ( Auto form the raid or group )
/zone    <Option>: Out|Guild|Forest|Vale|<Zone>|Leaf          ( Auto moving between zone )
/loot    <Option>: On|Off|All|Me|Tar|Ignore|Sell|Keep|Destroy|Quest|Max|Auto|Common|Notify
                                                              ( Advanced auto looting, by bots analysis repartition )

/stop                                                         ( Stop all - Atk,Moving,Twist )

/eq      <Option>: Sound <On|Off>|Effect <On|Off>|Fps <Value>|AutoClip <Value>
                                                              ( Set some eq parameter )
/ini     <Option>: MainTank|Channel|MeleeRange|ToonTrade|EQDIR|MQDIR|DRUID1|DRUID2|SUNEVAMBRACELIST|VAMPIREBANELIST
                                                              ( Set some default ini parameter, to be defined )
/macro   <Option>: Start|Restart|End|Alias|Stat <LPS>         ( Macro management )

Hidden Function:
HIDDEN FOR ALL...

TODO:
- Full rewite EQBC Event
- Adding new alias on start
- Possible retro compatibility ?
- Adding bc commands for each new macro command and write each function for argmument
- Adding sub command "Ini" to set defaut setup.ini (ex /pet default on - for auto pet atk on)
- Merge sn/snt by mcast command and test it
- Add Buff on/off to setup.ini
- Add Spirit on/off to setup.ini
- Merge Combine in macro, create recipe ini file, probably possible or not!
- Replace Aug function into Inv by augitem
- Replace Stats/Focus function into Inv by stats/focus ?
- Merge Zone to guild, Donator/Lucky Charm/Vale Token
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
HIDDEN FOR ALL...
...
```
