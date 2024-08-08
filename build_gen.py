"""Build generator for rebuilding Gran Turismo 2 game code."""
#import os
import sys
import ninja_syntax


# possible values: gt1, gt2, gt2k. only gt2 is supported for now.
GAME = "gt2"
# possible versions: jpbeta, jp10, jp11, us10, us11, us12, eubeta, eu10
# not all versions are possible.
REGION_VERSION = "us12"
# possible values: "arcade", "simdisk", "single", "yymmdd".
# "single" is unsupported atm. It will be supported for gt1 and for gt2 combined.
# yymmdd will also be used for denoting betas/demos that do not resemble retail.
DISK = "simdisk"
# unused, but is_demo = 1 means that the title is a demo that does not obey
# retail game structures.
IS_DEMO = 0
# are we building matching or nonmatching?
NON_MATCHING = 0
# are we building the main exe only or the overlays as well?
EXE_ONLY = 0

def detect_mainexe_name(region_version, disk):
    """Finds the executable name for the stated version of the disk."""
    version_exe = ""

    if disk == "arcade":
        if region_version == "jp11" or region_version == "us12":
            raise ValueError(region_version + " is not a valid arcade GT2 disk version.")
        if region_version in ["us10", "us11"]:
            version_exe = "scus_944.55"
        elif region_version in ["jpbeta", "jp10"]:
            version_exe = "scps_101.16"
        elif region_version in ["eubeta", "eu10"]:
            version_exe = "sces_023.80"
    elif disk == "simdisk":
        if region_version == "eubeta":
            raise ValueError(region_version + " is not a valid simulation GT2 disk version.")
        if region_version in ["us10", "us11", "us12"]:
            version_exe = "scus_944.88"
        elif region_version in ["jpbeta", "jp10", "jp11"]:
            version_exe = "scps_101.17"
        elif region_version == "eu10":
            version_exe = "sces_123.80"
    else:
        raise ValueError(disk + " is not a valid GT2 disk type.")
    return version_exe

VERSION_EXE = detect_mainexe_name(REGION_VERSION, DISK)

# miscellaneous string-building constants
ELF_EXT = ".elf"
EXE_EXT = ".exe"
LD_EXT = ".ld"
MAP_EXT = ".map"
O_EXT = ".o"
YAML_EXT = ".yaml"

# path string-building constants
VERSION = GAME + "_" + REGION_VERSION + "_" + DISK
BASEPATH = "config/" + VERSION
BASEPATH_AUTOGEN = BASEPATH + "/autogen/"
BINPATH = BASEPATH + "/ovl_bin"
BASEOVL = BASEPATH + "/orig_bin/GT2.OVL"
BASEEXE = BASEPATH + "/orig_bin/" + VERSION_EXE.upper()
INCPATH = "include"
INCOPT = " -I" + INCPATH + " "
BUILDDIR = "build/"
PIPE = " | "
UNDEFINED_SYMS_NAME = "_undefined_syms.txt"
UNDEFINED_SYMS_NAME_AUTO = "_undefined_syms_auto.txt"
UNDEFINED_FUNCS_NAME_AUTO = "_undefined_funcs_auto.txt"

# compiler options. please do not remove leading spaces.
ASFLAGS = INCOPT + "-march=r3000 -mtune=r3000 -no-pad-sections"
MASPSXFLAGS = "--aspsx-version=2.79 -G0" # not sure -G4096 is correct?
CFLAGS = (" -O2 -G0 -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fgnu-linker -mgas "
          "-mgpOPT -mgpopt -msoft-float -gcoff -quiet")
CPPFLAGS = INCOPT + "-lang-c"
LDFLAGS_BASE = " --no-check-sections -nostdlib"

# executable names and locations
CROSS = "mips-linux-gnu-"
AS = CROSS + "as -EL"
LD = CROSS + "ld -EL"
OBJCOPY = CROSS + "objcopy"
CPP = "tools/gcc2.8.1-mipsel/cpp"
CC = "tools/homebrew-psyq44/cc1"
PYTHON_EXE = "python"
OVL_SPLIT_EXE = "tools/GTModTools/ovl.py"
MASPSX_EXE = " tools/maspsx/maspsx.py "
SPLAT = "splat" # change this if you have splat installed elsewhere, like a test build
MASPSX = PYTHON_EXE + MASPSX_EXE + MASPSXFLAGS

# output locations
EXE = BUILDDIR + VERSION_EXE
ELF = EXE + ".elf"

# place .s targets here, autogenerated or not
asm_targets = ["asm/header.s",
               "asm/data/data.data.s", 
               "asm/data/data2.data.s"]
# place binary targets here (likely the textures for OVR0)
bin_targets = ["assets/textures.bin"]
# this stays empty and is filled with the autogen ovr[n].c files
cpp_targets_autogen = []
# any c files autogenerated go here that aren't covered by cpp_targets_autogen
cpp_targets_autogen_end = ["src/autogen/start.c",
                           "src/autogen/start_0.c",
                           "src/autogen/ovr0_0.c",
                           "src/autogen/ovr0_1.c",
                           "src/autogen/ovr0_2.c",
                           "src/autogen/ovr0_3.c",
                           "src/autogen/ovr0_4.c",
                           "src/autogen/ovr0_5.c",
                           "src/autogen/ovr0_6.c",
                           "src/autogen/ovr0_7.c",
                           "src/autogen/ovr0_8.c",
                           "src/autogen/ovr0_9.c",
                           "src/autogen/ovr0_A.c",
                           "src/autogen/ovr0_B.c"]
# place any actual c files here
cpp_targets_end = ["src/ovr0/gt2_main_task0a_ovr_entrypoint.c",
                   "src/ovr0/gt2_main_task0.c",
                   "src/ovr0/gt2_show_vendor_bootlogo_task0.c",
                   "src/ovr0/gt2_sysinit.c",
                   "src/ovr0/gt2_main_task078.c",
                   "src/ovr0/gt2_main_task0800.c",
                   "src/ovr0/gt2_main_task0a_ovr_func1.c",
                   "src/ovr0/gt2_main_task0b.c",
                   "src/ovr0/gt2_main_task0b0_car_loader.c",
                   "src/ovr0/gt2_main_task0b01_noop_loader.c",
                   "src/ovr0/gt2_main_task0b2.c",
                   "src/ovr0/gt2_main_task0b30.c",
                   "src/ovr0/gt2_main_task0b34.c",
                   "src/ovr0/gt2_main_task0b4.c",
                   "src/ovr0/gt2_main_task0b5.c",
                   "src/ovr0/gt2_main_task0b6.c",
                   "src/ovr0/gt2_main_task0b7.c",
                   "src/ovr0/gt2_unknown_task0.c",
                   "src/ovr0/gt2_unknown_task1.c",
                   "src/ovr0/gt2_vsync_handler.c",
                   "src/start/gt2_main.c"]
# these stay empty.
# yes, even ld_flags, because we need to do some command generation to make it work.
splat_targets = []
ld_maps = []
ld_targets = []
ld_flag_table = []
ld_out = []
ovl_split_outputs = []
all_objects = []
diff_okay_list = []

# definition for undefined syms path table
undefined_syms = []
undefined_funcs = []
# USER-EDITABLE: does OVR0 (mainexe) or OVR1-6 use an autogenerated undefined symbols table?
undefined_syms_auto = [0, 0, 0, 0, 0, 0, 0]

# build target lists
for i in range(7):
    OVRNAME = "ovr" + str(i)
    cpp_targets_autogen.append("src/autogen/" + OVRNAME + ".c")
    if i == 0:
        splat_targets.append(VERSION_EXE + YAML_EXT)
        ld_maps.append(VERSION_EXE + MAP_EXT)
        ld_targets.append(VERSION_EXE + LD_EXT)
        ld_out.append(ELF)
        undefined_funcs.append("mainexe" + UNDEFINED_FUNCS_NAME_AUTO)
        #asm_targets.append("asm/autogen/" + OVRNAME + ".s")
        if undefined_syms_auto[i] == 1:
            undefined_syms.append("/autogen/mainexe" + UNDEFINED_SYMS_NAME_AUTO)
        else:
            undefined_syms.append("/mainexe" + UNDEFINED_SYMS_NAME)
    else:
        GAME_OVRNAME = GAME + "_0" + str(i)
        splat_targets.append(GAME_OVRNAME + YAML_EXT)
        ld_targets.append(GAME_OVRNAME + LD_EXT)
        ld_maps.append(GAME_OVRNAME + MAP_EXT)
        ld_out.append(BUILDDIR + GAME_OVRNAME + ELF_EXT)
        ovl_split_outputs.append(BINPATH + "/" + GAME_OVRNAME + EXE_EXT)
        undefined_funcs.append(OVRNAME + UNDEFINED_FUNCS_NAME_AUTO)
        #cpp_targets_autogen.append("src/autogen/" + OVRNAME + ".c")
        if undefined_syms_auto[i] == 1:
            undefined_syms.append("/autogen/" + OVRNAME + UNDEFINED_SYMS_NAME_AUTO)
        else:
            undefined_syms.append("/" + OVRNAME + UNDEFINED_SYMS_NAME)

for i in range(7):
    ld_flag_table.append("-T " + BASEPATH + undefined_syms[i] + " -T " + BASEPATH_AUTOGEN +
                    undefined_funcs[i])

splat_targets_path = [BASEPATH + "/" + s for s in splat_targets]
ld_targets_path = [BASEPATH + "/autogen/" + s for s in ld_targets]
cpp_targets = cpp_targets_autogen + cpp_targets_autogen_end + cpp_targets_end

# command invocations for rules
OVL_SPLIT_CMD = PYTHON_EXE + " " + OVL_SPLIT_EXE + " unpack -o $out $in"
AS_CMD = AS + ASFLAGS + " -o $out $in"
ASSET_CMD = LD + " -r -b binary -o $out $in"
SPLAT_CMD = SPLAT + " split $in"
CPP_CMD = CPP + CPPFLAGS + " $in | " + CC + CFLAGS + \
          PIPE + MASPSX + PIPE + AS + ASFLAGS + " -o $out"

# invoke ninja's writer
writer = ninja_syntax.Writer(sys.stdout)

# list of rules
# assembles loose files per asm_targets
writer.rule("asm", AS_CMD)
# splats files per pre-gen table
writer.rule("split", SPLAT_CMD)
# splits GT2.OVL into files as needed
writer.rule("ovl_split", OVL_SPLIT_CMD)
# builds binary objects into object files.
writer.rule("asset", ASSET_CMD)
# builds C files into objects
writer.rule("cpp", CPP_CMD, depfile="$out.asmproc.d")
# links objects into final elf files
writer.rule("ld", LD + " $ldflags -T $in -Map $ldmap $ldflags_base -o $out")
# objcopy .elf to a final exe
writer.rule("objcopy", OBJCOPY + " $in $out -O binary")
# compare binaries
writer.rule("diff", "diff $in $built && touch $out")
# generic copy rule to prep build/
writer.rule("copy", "cp $in $out")
# emits build statistics
writer.rule("postbuild", "python build_post.py | tee build_progress.txt")

# generate actual ninja rules
writer.build(BINPATH, "ovl_split", BASEOVL, implicit_outputs=ovl_split_outputs)

for filename in splat_targets_path:
    target_num = splat_targets_path.index(filename)
    TARGET_NAME = "src/autogen/ovr" + str(target_num) + ".c"
    implicit_outs = []
    implicit_outs.append(ld_targets_path[target_num])
    implicit_outs.append(BASEPATH_AUTOGEN + undefined_funcs[target_num])
    implicit_outs.append(BUILDDIR + ld_maps[target_num])
    if target_num == 0:
        implicit_outs.extend(asm_targets)
        implicit_outs.extend(bin_targets)
        implicit_outs.extend(cpp_targets_autogen_end)
        writer.build(TARGET_NAME, "split", filename, implicit_outputs=implicit_outs)
    else:
        writer.build(TARGET_NAME,
                     "split",
                     filename,
                     implicit=[ovl_split_outputs[target_num - 1]],
                     implicit_outputs=implicit_outs)

for filename in asm_targets:
    target_num = asm_targets.index(filename)
    OUTPUT = BUILDDIR + filename + O_EXT
    all_objects.append(OUTPUT)
    writer.build(OUTPUT, "asm", filename)

for filename in bin_targets:
    target_num = bin_targets.index(filename)
    OUTPUT = BUILDDIR + filename + O_EXT
    all_objects.append(OUTPUT)
    writer.build(OUTPUT, "asset", filename)

for filename in cpp_targets:
    target_num = cpp_targets.index(filename)
    OUTPUT = BUILDDIR + filename + O_EXT
    all_objects.append(OUTPUT)
    writer.build(OUTPUT, "cpp", filename)

for filename in ld_targets_path:
    target_num = ld_targets_path.index(filename)
    ldflags = ld_flag_table[target_num]
    ld_map = BUILDDIR + ld_maps[target_num]
    writer.build(BUILDDIR + ld_targets[target_num], "copy", filename)

    if EXE_ONLY == 0 or (EXE_ONLY == 1 and target_num == 0):
        implicit_inputs = []
        implicit_inputs.extend(all_objects)
        implicit_inputs.append(ld_map)
        writer.build(ld_out[target_num],
                     "ld",
                     BUILDDIR + ld_targets[target_num],
                     implicit=implicit_inputs,
                     variables={'ldflags':ldflags,'ldmap':ld_map,'ldflags_base':LDFLAGS_BASE})

for i in range(7):
    if i == 0:
        INPUTFILE = ELF
        OUTPUT = EXE
        DIFF_OKAY = OUTPUT + ".ok"
        diff_okay_list.append(DIFF_OKAY)
        writer.build(OUTPUT, "objcopy", INPUTFILE)
        writer.build(DIFF_OKAY, "diff", BASEEXE, variables={'built':OUTPUT},implicit=OUTPUT)
    else:
        INPUTFILE = BUILDDIR + GAME + "_0" + str(i) + ELF_EXT
        OUTPUT = BUILDDIR + GAME + "_0" + str(i) + EXE_EXT
        DIFF_OKAY = OUTPUT + ".ok"
        diff_okay_list.append(DIFF_OKAY)
        OUTPUT_DIFF = BINPATH + "/" + GAME + "_0" + str(i) + EXE_EXT
        writer.build(OUTPUT, "objcopy", INPUTFILE)
        writer.build(DIFF_OKAY, "diff", OUTPUT_DIFF, variables={'built':OUTPUT},implicit=OUTPUT)

writer.build("build_progress.txt", "postbuild", implicit=diff_okay_list)

writer.rule("regen_ninja", f"{sys.executable} $in > $out")
writer.build("build.ninja", "regen_ninja", __file__)
