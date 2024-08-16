# gt2-reversing
RE repo for Gran Turismo 2 (PS1)

To build the repo, you'll need to be running Linux. (WSL2 should work, with caveats below. MSYS2 or macOS almost certainly won't!) You'll also need python3 with a working splat installation from pip, a mipsel-compatible bintools (Arch and Debian/Ubuntu have one), and ninja. Finally, once you've checked out the git repo, you'll need to make sure submodules are initialized, since we need a few outside tools to get things working, like maspsx and GTModTools.

The first step is to obtain a copy of `SCUS_944.88` and `GT2.OVL` from your copy of the simulation disk from the North American 1.2 (Greatest Hits) release. I use this as the basis for decompilation, since it should be nearly identical to the PAL release, but the infrastructure is intended to be able to decompile any near-final or final release of GT2.

Once you have those, place them in `config/gt2_us12_simdisk/orig_bin`. Linux is case sensitive, so leave the names alone.

Finally, to actually build, run `python3 build_gen.py > build.ninja`, and then `ninja`. 

The result will be in `build/`, and consists of seven files: `scus_944.88`, and `gt2_0(1-6).exe`. The build does not currently reassemble the overlays. Rebuilding GT2.OVL does not produce a matching archive; doing that will require far more gzip archaeology and messing with timestamps than I feel is prudent or necessary, especially as GT2 doesn't actually care too much about what's in there, just that it is built correctly (has correct relocations, and the largest overlay does not collide with GT2's start() function).

### specific note for WSL2 and Ubuntu in general

Do not try to check out or build the repo on one of your NTFS mountpoints. This can only lead to pain and suffering. WSL2 is some very impressive tooling but there's some things it just can't cope with and apparently due to 64-bit vs. 32-bit inodes, this is one of them. Check out and build the repo inside your actual Linux (I suggest your home directory, so for example `/home/ginryuoku/projects/gt2-reversing`). We have to use some pretty ancient compilers to build the decomp, so please keep this in mind.

Nenkai summarized the WSL2 environment setup process as follows:

* `git clone --recurse-submodules --remote-submodules https://github.com/ginryuoku/gt2-reversing.git` (must be in linux, can access files from windows with \\wsl$)
* `apt install python3-pip python-is-python3`
* `python3 -m pip install -U splat64[mips]`
* `sudo dpkg --add-architecture i386` (fixes cc1 issue, 32bit executables)
* `apt install libc6:i386 libncurses5:i386 libstdc++6:i386`
* `apt install binutils-mips-linux-gnu`

This should also work on bare-metal Ubuntu.

### what you need for Gentoo and Arch

Gentoo is a bit fussy, and so is Arch. 

For splat: On Ubuntu you can sort of get around pip whining because they patched it for less user-hostility, but you're stuck with using `pipx` on Arch and Gentoo to install splat. 

For multilib: Arch needs `[multilib]` enabled. I'm not sure what packages need `x86_abi_32`, strictly speaking, on Gentoo, but installing Steam seems to provide enough 32-bit libraries to make it work. Wine would probably also work. You probably just need a 32-bit glibc, libstdc++ and ncurses (`x86_abi_32`) in practice.

For binutils: We provide two compilers out of the box (technically three, but one is just there to provide a cpp binary), but we don't provide a binutils, because a modern binutils will do. On Arch, you install binutils from the AUR as `binutils-mips-linux-gnu`. On Gentoo, you need to install crossdev, and then `crossdev -s0 --target mips-linux-gnu` gets you your binutils. I have absolutely no idea whatsoever if actually building to s4 would get you a viable PS1 compiler, but I strongly doubt it. Just use `-s0` to get yourself a binutils without the other baggage.

### build triples

Currently, this repo only supports US 1.2, but I do have some preliminary support in the build system for attempting to split, splat and build other versions. The format is as follows:

`(game)_(region+version)_(disk)`

"game" is obviously 'gt2' for now.

"region+version" takes the following versions: jpbeta, jp10, jp11, us10, us11, us12, eubeta, eu10. not all version codes are valid for the next part.

"disk" is one of four things, though only "simdisk" is supported for now. they are "arcade", "simdisk", "single" and a yymmdd date code. the date code is for prototype titles that aren't close enough to retail to be analyzed in the same manner. "single" is for GT1, GT2K and presumably the combined disk once this repo is capable of building *new* variations of GT2, not just perfectly match Polyphony's binaries from November and December 1999.

