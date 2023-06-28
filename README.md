# This is <ins>NOT</ins> a port of HBL to Aroma and <ins>NOT</ins> an application to use ELF applications on Aroma.

## Wii U Environment Swapper

This is a really NOT SO simple app that just restarts your console and swaps your environment. Makes life a lot easier when you need ELF homebrew though, this ended up being much more of an undertaking for the devs than we anticipated so round of applause to maxine and ESPECIALLY Trace who singlehandedly got all of the extra features working and greatly improved on the parity of the RPX/WUHB versions.

by the way if you want to build for ELF format the option is there it's just that why the hell would you use a .ELF file ever again.

### Building

To build this make sure you have `devkitPro`, `devkitPPC`, `libmocha` and `wut` installed via the (dkp-)pacman package manager. Then just run `make` in the same directory as the Makefile and use the resulting wuhb/rpx.

**Special thanks to  for the icons/art and [Fangal-Airbag](https://github.com/Fangal-Airbag)'s [WiiUReboot](https://github.com/Fangal-Airbag/WiiUReboot) which I originally used as a foundation**



Credits: 
maxine (me): project coordinator and development help
[TraceEntertains](https://github.com/TraceEntertains) A lot of code just a wild amount of code
[Ingunar](https://github.com/Ingunar) All of the things that look pretty are because of this guy
[Moonlumen](https://github.com/Moonlumen) Moral support and insane amounts of alpha testing
[WiiUReboot dev](https://github.com/Fangal-Airbag/WiiUReboot) Making an easy to read reboot app so I could understand WiiU Power Functions
