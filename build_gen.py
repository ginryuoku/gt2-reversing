"""Build generator for rebuilding Gran Turismo 2 game code."""

# import os
import sys
from tools import ninja_syntax


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
            raise ValueError(
                region_version + " is not a valid arcade GT2 disk version."
            )
        if region_version in ["us10", "us11"]:
            version_exe = "scus_944.55"
        elif region_version in ["jpbeta", "jp10"]:
            version_exe = "scps_101.16"
        elif region_version in ["eubeta", "eu10"]:
            version_exe = "sces_023.80"
    elif disk == "simdisk":
        if region_version == "eubeta":
            raise ValueError(
                region_version + " is not a valid simulation GT2 disk version."
            )
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
MASPSXFLAGS = "--aspsx-version=2.79 -G0"  # not sure -G4096 is correct?
CFLAGS = (
    " -O2 -G0 -fpeephole -ffunction-cse -fkeep-static-consts -fpcc-struct-return -fcommon"
    " -fgnu-linker -msplit-addresses -mgas -mgpOPT -mgpopt -msoft-float -gcoff -quiet"
)
CFLAGS46 = CFLAGS + " -fargument-alias -fident"
CPPFLAGS = INCOPT + "-lang-c"
LDFLAGS_BASE = " --no-check-sections -nostdlib"

# executable names and locations
CROSS = "mips-linux-gnu-"
AS = CROSS + "as -EL"
LD = CROSS + "ld -EL"
OBJCOPY = CROSS + "objcopy"
CPP = "tools/gcc2.8.1-mipsel/cpp"
CC = "tools/homebrew-psyq44/cc1"
CPP46 = "tools/gcc2.95.2-mipsel/cpp"
CC46 = "tools/gcc2.95.2-mipsel/cc1"
PYTHON_EXE = "python"
OVL_SPLIT_EXE = "tools/GTModTools/ovl.py"
MASPSX_EXE = " tools/maspsx/maspsx.py "
SPLAT = "splat"  # change this if you have splat installed elsewhere, like a test build
MASPSX = PYTHON_EXE + MASPSX_EXE + MASPSXFLAGS

# output locations
EXE = BUILDDIR + VERSION_EXE
ELF = EXE + ".elf"

# place .s targets here, autogenerated or not
asm_targets = [
    "asm/header.s",
    "asm/bios/bcopy.s",
    "asm/bios/bzero.s",
    "asm/bios/printf.s",
    "asm/bios/puts.s",
    "asm/bios/strncmp.s",
    "asm/data/ovr0_0.rodata.s",
    "asm/data/ovr0_1.rodata.s",
    "asm/data/ovr0_data.data.s",
    "asm/data/ovr0_padding.bss.s",
    "asm/data/autogen/ovr1_000.rodata.s",
    "asm/data/autogen/ovr1_001.rodata.s",
    "asm/data/autogen/ovr1_002.rodata.s",
    "asm/data/autogen/ovr1_003.rodata.s",
    "asm/data/autogen/ovr1_004.rodata.s",
    "asm/data/autogen/ovr1_005.rodata.s",
    "asm/data/autogen/ovr1_006.rodata.s",
    "asm/data/autogen/ovr1_007.rodata.s",
    "asm/data/autogen/ovr1_008.rodata.s",
    "asm/data/autogen/ovr1_009.rodata.s",
    "asm/data/autogen/ovr1_010.rodata.s",
    "asm/data/autogen/ovr1_011.rodata.s",
    "asm/data/autogen/ovr1_012.rodata.s",
    "asm/data/autogen/ovr1_013.rodata.s",
    "asm/data/autogen/ovr1_014.rodata.s",
    "asm/data/autogen/ovr1_015.rodata.s",
    "asm/data/autogen/ovr1_016.rodata.s",
    "asm/data/autogen/ovr1_017.rodata.s",
    "asm/data/autogen/ovr1_018.rodata.s",
    "asm/data/autogen/ovr1_019.rodata.s",
    "asm/data/autogen/ovr1_020.rodata.s",
    "asm/data/autogen/ovr1_021.rodata.s",
    "asm/data/autogen/ovr1_022.rodata.s",
    "asm/data/autogen/ovr1_023.rodata.s",
    "asm/data/autogen/ovr1_024.rodata.s",
    "asm/data/autogen/ovr1_025.rodata.s",
    "asm/data/autogen/ovr1_026.rodata.s",
    "asm/data/autogen/ovr1_027.rodata.s",
    "asm/data/autogen/ovr1_028.rodata.s",
    "asm/data/autogen/ovr1_029.rodata.s",
    "asm/data/autogen/ovr1_030.rodata.s",
    "asm/data/autogen/ovr1_031.rodata.s",
    "asm/data/autogen/ovr1_032.rodata.s",
    "asm/data/autogen/ovr5.data.s",
    "asm/data/autogen/ovr5_00.rodata.s",
    "asm/data/autogen/ovr5_01.rodata.s",
    "asm/data/autogen/ovr5_02.rodata.s",
    "asm/data/autogen/ovr5_03.rodata.s",
    "asm/data/autogen/ovr5_04.rodata.s",
    "asm/data/autogen/ovr5_05.rodata.s",
    "asm/data/autogen/ovr6_00.rodata.s",
    "asm/data/autogen/ovr6_01.rodata.s",
    "asm/data/autogen/ovr6_02.rodata.s",
    "asm/data/gt2main0.rodata.s",
    "asm/data/gt2main1.rodata.s",
    "asm/data/gt2main2.rodata.s",
    "asm/data/gt2main3.rodata.s",
    "asm/data/gt2main4.rodata.s",
    "asm/data/gt2main5.rodata.s",
    "asm/data/gt2main6.rodata.s",
    "asm/data/gt2main7.rodata.s",
    "asm/data/gt2main8.rodata.s",
    "asm/data/gt2main9.rodata.s",
    "asm/data/gt2main10.rodata.s",
    "asm/data/gt2main11.rodata.s",
    "asm/data/gt2main12.rodata.s",
    "asm/data/gt2main13.rodata.s",
    "asm/data/gt2main14.rodata.s",
    "asm/data/gt2main15.rodata.s",
    "asm/data/gt2main16.rodata.s",
    "asm/data/gt2main17.rodata.s",
    "asm/data/gt2main18.rodata.s",
    "asm/data/gt2main19.rodata.s",
    "asm/data/gt2main20.rodata.s",
    "asm/data/gt2main21.rodata.s",
    "asm/data/gt2main.data.s",
]
# place binary targets here (likely the textures for OVR0)
bin_targets = ["assets/notice.tim.gz.bin", "assets/logo-scea.tim.gz.bin"]
# this stays empty and is filled with the autogen ovr[n].c files
cpp_targets_autogen = []
cpp_targets_autogen_splits = []
# any c files autogenerated go here that aren't covered by cpp_targets_autogen
cpp_targets_autogen_end = [
    "src/lib/lib.c",
    #    "src/lib/libpad.c",
    "src/lib/libpress.c",
    #    "src/lib/bios.c",
    "src/autogen/start.c",
    "src/autogen/start/gt2_callback_double_buffer_flip.c",
    "src/autogen/start/gt2_callback_double_buffer_flip_prep.c",
    "src/autogen/start/gt2_main_copyfunc0.c",
    "src/autogen/start/gt2_flip_class_type_info.c",
    "src/autogen/start/gt2_flip_si_type_info.c",
    "src/autogen/start/gt2_flip_type_info.c",
    "src/autogen/start/gt2_flip_user_type_info.c",
    "src/autogen/start/gt2_main_funcA.c",
    "src/autogen/start/gt2_main_func53.c",
    "src/autogen/start/gt2_main_gtmode_get_part_number.c",
    "src/autogen/start/gt2_main_gtmode_task7000_error.c",
    "src/autogen/start/gt2_main_invoke_flip_14ScreenViewLoop.c",
    "src/autogen/start/gt2_main_menu_func1.c",
    "src/autogen/start/gt2_main_race_func16_141.c",
    "src/autogen/start/gt2_main_race_func16_1418.c",
    "src/autogen/start/gt2_main_race_switch_func1.c",
    "src/autogen/start/gt2_main_race_switch_func2.c",
    "src/autogen/start/gt2_main_race_maxspeed_format.c",
    "src/autogen/start/gt2_main_shared_arcaderace_funcE.c",
    "src/autogen/start/gt2_main_shared_arcadegtrace_func0.c",
    "src/autogen/start/gt2_main_shared_menuarcade_func1.c",
    "src/autogen/start/gt2_main_shared_race_func0.c",
    "src/autogen/start/gt2_main_shared_racemenu_func5.c",
    "src/autogen/start/gt2_main_shared_racemenu_func7.c",
    "src/autogen/start/gt2_main_shared_racemenu_func40.c",
    "src/autogen/start/gt2_main_shared_racemenu_func43.c",
    "src/autogen/start/gt2_main_shared_racemenuarcade_func430.c",
    "src/autogen/start/gt2_main_shared_racemenuarcade_funcE.c",
    "src/autogen/start/gt2_main_shared_gt_race_func0.c",
    "src/autogen/start/gt2_main_shared_gt_race_func3.c",
    "src/autogen/start/gt2_main_shared_gt_race_func31.c",
    "src/autogen/start/gt2_main_shared_gt_race_func5.c",
    "src/autogen/start/gt2_main_shared_gt_race_func50.c",
    "src/autogen/start/gt2_main_switch_func000.c",
    "src/autogen/start/gt2_switchtable_user0.c",
    "src/autogen/start/gt2_main_task02100.c",
    "src/autogen/start/gt2_main_task033.c",
    "src/autogen/start/gt2_main_task04_pad_config_task01.c",
    "src/autogen/start/gt2_main_task05_sdkevent_f2.c",
    "src/autogen/start/gt2_unknown_task14_00.c",
    "src/autogen/start/gt2_unknown_task14_003.c",
    "src/autogen/ovr0/gt2_ovr0_task0a_ovr_func0.c",
    "src/autogen/ovr0/gt2_ovr0_task080.c",
    "src/autogen/ovr0/gt2_ovr0_vol_loader_task3.c",
    "src/autogen/ovr0/gt2_ovr0_task08_play_music_a440.c",
    "src/autogen/ovr0/gt2_ovr0_task0b02_carobj_loader.c",
    "src/autogen/ovr0/gt2_ovr0_task0b03_carlogo_loader.c",
    "src/autogen/ovr0/gt2_ovr0_task0b04_carwheel_loader.c",
    "src/autogen/ovr0/gt2_ovr0_task0b05_enginedata_loader.c",
    "src/autogen/ovr0/gt2_ovr0_task0b10.c",
    "src/autogen/ovr1/func_80011704.c",
    "src/autogen/ovr1/func_80012274.c",
    "src/autogen/ovr1/func_80015FF8.c",
    "src/autogen/ovr1/func_80016328.c",
    "src/autogen/ovr1/func_80016368.c",
    "src/autogen/ovr1/func_80017048.c",
    "src/autogen/ovr1/func_80017200.c",
    "src/autogen/ovr1/func_80017500.c",
    "src/autogen/ovr1/func_80017784.c",
    "src/autogen/ovr1/func_80017D1C.c",
    "src/autogen/ovr1/func_80017DC8.c",
    "src/autogen/ovr1/func_800196BC.c",
    "src/autogen/ovr1/func_80027C70.c",
    "src/autogen/ovr1/func_800299D8.c",
    "src/autogen/ovr1/func_8002A700.c",
    "src/autogen/ovr1/func_8002B170.c",
    "src/autogen/ovr1/func_8002C76C.c",
    "src/autogen/ovr1/func_8002D20C.c",
    "src/autogen/ovr1/func_8002D308.c",
    "src/autogen/ovr1/func_8002E204.c",
    "src/autogen/ovr1/func_8002FB18.c",
    "src/autogen/ovr1/func_80030D18.c",
    "src/autogen/ovr1/func_80030F94.c",
    "src/autogen/ovr1/func_800347C4.c",
    "src/autogen/ovr1/func_80036980.c",
    "src/autogen/ovr1/func_80037834.c",
    "src/autogen/ovr1/func_8003932C.c",
    "src/autogen/ovr1/func_8003C12C.c",
    "src/autogen/ovr1/func_800418E8.c",
    "src/autogen/ovr1/func_800449C8.c",
    "src/autogen/ovr1/func_80045AE8.c",
    "src/autogen/ovr1/func_800465E0.c",
    "src/autogen/ovr1/func_800474F4.c",
    "src/autogen/ovr1/func_80047EA0.c",
    "src/autogen/ovr1/func_80048208.c",
    "src/autogen/ovr1/func_80048258.c",
    "src/autogen/ovr1/func_80049A14.c",
    "src/autogen/ovr1/func_8004BA40.c",
    "src/autogen/ovr1/func_8004C1EC.c",
    "src/autogen/ovr1/func_8004D474.c",
    "src/autogen/ovr1/func_8004F8B4.c",
    "src/autogen/ovr1/func_80051BF4.c",
    "src/autogen/ovr1/func_80052638.c",
    "src/autogen/ovr1/func_80052D84.c",
    "src/autogen/ovr1/func_8005480C.c",
    "src/autogen/ovr1/func_80054B9C.c",
    "src/autogen/ovr1/func_800551BC.c",
    "src/autogen/ovr1/func_80055328.c",
    "src/autogen/ovr1/func_80055D50.c",
    "src/autogen/ovr1/func_80056194.c",
    "src/autogen/ovr1/func_8005731C.c",
    "src/autogen/ovr1/func_800574C0.c",
    "src/autogen/ovr1/func_80057A70.c",
    "src/autogen/ovr1/func_800585C0.c",
    "src/autogen/ovr1/func_80058E28.c",
    "src/autogen/ovr1/func_80059800.c",
    "src/autogen/ovr1/func_8005A5F8.c",
    "src/autogen/ovr5/func_80013108.c",
    "src/autogen/ovr5/func_80014380.c",
    "src/autogen/ovr5/func_80014FEC.c",
    "src/autogen/ovr5/func_8001503C.c",
    "src/autogen/ovr5/func_800153B4.c",
    "src/autogen/ovr5/func_8001706C.c",
    "src/autogen/ovr5/func_80018768.c",
    "src/autogen/ovr5/func_80018A84.c",
    "src/autogen/ovr5/func_80019634.c",
    "src/autogen/ovr5/func_8001973C.c",
    "src/autogen/ovr5/func_8001B6F0.c",
    "src/autogen/ovr5/func_8001DCD0.c",
    "src/autogen/ovr5/func_8001DD3C.c",
    "src/autogen/ovr5/func_8001DDAC.c",
    "src/autogen/ovr5/func_8001E26C.c",
    "src/autogen/ovr5/gt2_ovr5_format_number.c",
    "src/autogen/ovr5/gt2_ovr5_get_machine_test_game_mode.c",
    "src/autogen/ovr5/gt2_ovr5_get_stat_widget_display_value.c",
    "src/autogen/ovr5/gt2_ovr5_is_event_synthesizer.c",
    "src/autogen/ovr5/gt2_ovr5_is_international_league.c",
    "src/autogen/ovr5/gt2_ovr5_is_gt_world_cup.c",
    "src/autogen/ovr5/gt2_ovr5_ui_can_buy_caller0.c",
    "src/autogen/ovr6/gt2_ovr6_task4.c",
]
# place any actual c files here
cpp_targets_end = [
    # verified only works on 2.8.1
    "src/ovr0/gt2_ovr0_task0a_ovr_entrypoint.c",
    "src/ovr0/gt2_ovr0_task0.c",
    "src/ovr0/gt2_ovr0_vol_search_vol_dir.c",
    "src/ovr0/gt2_ovr0_vol_build_file_indices_cache.c",
    "src/ovr0/gt2_ovr0_vol_gtfs_init.c",
    "src/ovr0/gt2_show_vendor_bootlogo_task0.c",
    "src/ovr0/gt2_sysinit_vsync_setup.c",
    "src/ovr0/gt2_main_task0a_ovr_func1.c",
    "src/ovr0/gt2_ovr0_task0b.c",
    "src/ovr0/gt2_main_task0b34.c",
    "src/ovr0/gt2_main_task0b4.c",
    "src/ovr0/gt2_main_task0b5.c",
    "src/ovr0/gt2_main_task0b6.c",
    "src/ovr0/gt2_main_task0b7.c",
    "src/ovr0/gt2_unknown_task0.c",
    "src/ovr0/gt2_vsync_handler.c",
    "src/ovr2/gt2_ovr2_max3.c",
    "src/ovr2/gt2_ovr2_min3.c",
    "src/ovr3/gt2_ovr3_max3.c",
    "src/ovr3/gt2_ovr3_min3.c",
    "src/ovr4/gt2_ovr4_max3.c",
    "src/ovr4/gt2_ovr4_min3.c",
    "src/ovr5/gt2_ovr5_max3.c",
    "src/ovr5/gt2_ovr5_min3.c",
    "src/start/gt2_main_vol_get_file_data_sector_offset.c",
    "src/start/gt2_main_task2.c",
    "src/start/gt2_main_task0b11.c",
    "src/start/gt2_main_task0b110.c",
    "src/start/gt2_main_task0b20.c",
    "src/start/gt2_main_task0b31.c",
    "src/start/gt2_main_race_func7.c",
    "src/start/gt2_main_race_func8.c",
    "src/start/gt2_main_race_func20.c",
    "src/start/gt2_main_race_switch_func0.c",
    "src/start/gt2_main_shared_gt_race_func02.c",
    "src/start/gt2_main_shared_gtracemenu_func0.c",
    "src/start/gt2_main_shared_arcade_func0.c",
    "src/start/gt2_main_shared_arcaderace_funcF.c",
    "src/start/gt2_main_shared_arcaderace_func32.c",
    "src/start/gt2_main_shared_arcaderace_func33.c",
    "src/start/gt2_main_shared_racegtarcade_func6.c",
    "src/start/gt2_main_sharedovr_func_1A.c",
    "src/start/gt2_main_strcpy_slim.c",
    "src/start/gt2_main_linear_interpolation.c",
    "src/start/gt2_exit_task0.c",
    "src/start/gt2_save_crc32.c",
    "src/start/gt2_fxpoint_multi8.c",
    "src/start/gt2_fxpoint_multi12.c",
    "src/start/gt2_fxpoint_multi16.c",
    "src/start/gt2_unknown_task1B.c",
]
cpp_targets_46 = [
    # verified
    "src/ovr0/gt2_main_task075.c",
    "src/ovr0/gt2_main_task078.c",
    "src/ovr0/gt2_main_task0800.c",
    "src/ovr0/gt2_sysinit.c",
    "src/ovr0/gt2_ovr0_task0b0_car_loader.c",
    "src/ovr0/gt2_main_task0b01_noop_loader.c",
    "src/ovr0/gt2_main_task0b2.c",
    "src/ovr0/gt2_main_task0b30.c",
    "src/ovr0/gt2_ovr0_strchr.c",
    "src/ovr0/gt2_unknown_task1.c",
    "src/ovr4/gt2_ovr4_memset_caller.c",
    "src/start/gt2_unknown_nop0.c",
    "src/start/gt2_unknown_nop1.c",
    "src/start/gt2_unknown_nop2.c",
    "src/start/gt2_unknown_nop3.c",
    "src/start/gt2_unknown_nop4.c",
    "src/start/gt2_unknown_task4.c",
    "src/start/gt2_unknown_task1E.c",
    "src/start/gt2_unknown_task1F.c",
    "src/start/gt2_unknown_task22.c",
    "src/start/gt2_unknown_task24.c",
    "src/start/gt2_sysinit_task0.c",
    "src/start/gt2_main_bool_flip.c",
    "src/start/gt2_main_func012.c",
    "src/start/gt2_main_arcade_func0.c",
    "src/start/gt2_main_compare_2eq1.c",
    "src/start/gt2_main_compare_2neq1.c",
    "src/start/gt2_main_menu_func3.c",
    "src/start/gt2_main_menu_func4.c",
    "src/start/gt2_main_menu_func5.c",
    "src/start/gt2_main_menu_func6.c",
    "src/start/gt2_main_menu_func7.c",
    "src/start/gt2_main_race_func1.c",
    "src/start/gt2_main_race_func2.c",
    "src/start/gt2_main_race_func4.c",
    "src/start/gt2_main_race_func16_001.c",
    "src/start/gt2_main_race_func16_20.c",
    "src/start/gt2_main_race_func16_1411.c",
    "src/start/gt2_main_race_func21.c",
    "src/start/gt2_main_race_func23.c",
    "src/start/gt2_main_race_func34.c",
    "src/start/gt2_main_race_func41_0.c",
    "src/start/gt2_main_race_setter0.c",
    "src/start/gt2_main_race_setter1.c",
    "src/start/gt2_main_race_setter2.c",
    "src/start/gt2_main_race_setter3.c",
    "src/start/gt2_main_race_setter5.c",
    "src/start/gt2_main_race_switch_func12.c",
    "src/start/gt2_main_race_switch_func13.c",
    "src/start/gt2_main_return_arb_ptr0.c",
    "src/start/gt2_main_saveregisters.c",
    "src/start/gt2_main_set_arb_ptr_from_int0.c",
    "src/start/gt2_main_shared_gt_race_func05_nop.c",
    "src/start/gt2_main_shared_gt_race_get_completion_flag.c",
    "src/start/gt2_main_shared_menuarcade_func3.c",
    "src/start/gt2_main_shared_race_func1.c",
    "src/start/gt2_main_shared_race_func2_nop.c",
    "src/start/gt2_main_shared_racemenu_func3010.c",
    "src/start/gt2_main_sharedovr_func2_00.c",
    "src/start/gt2_main_sharedovr_func6_nop.c",
    "src/start/gt2_main_sharedovr_func15_nop.c",
    "src/start/gt2_main_sharedovr_func_15_ret1.c",
    "src/start/gt2_main_sharedovr_func_19_0.c",
    "src/start/gt2_main_strlen.c",
    "src/start/gt2_main_strcpy.c",
    "src/start/gt2_memset_caller_ovr5.c",
    "src/start/gt2_memset_caller_15a5c.c",
    "src/start/gt2_main_task1.c",
    "src/start/gt2_main_task200112.c",
    "src/start/gt2_main_task031_nop_zero.c",
    "src/start/gt2_main_task032_nop.c",
    "src/start/gt2_main_task0780.c",
    "src/start/gt2_main_memcpy.c",
    "src/start/gt2_main.c",
    "src/start/gt2_exit.c",
    "src/start/gt2_init.c",
    "src/start/gt2_bios_set_kanji_font_table.c",
    "src/start/gt2_sdk_builtin_vec_delete0.c",
    "src/start/gt2_sdk_builtin_vec_delete1.c",
    "src/start/gt2_sdk_builtin_vec_delete2.c",
    "src/start/__builtin_delete.c",
]
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
# USER-EDITABLE: how many splits are present?
target_splits = [5, 48, -1, 0, 0, 17, -1, 80]

# build target lists
for i in range(7):
    OVRNAME = "ovr" + str(i)
    cpp_targets_autogen.append("src/autogen/" + OVRNAME + ".c")
    if target_splits[i] >= 0:
        for idx in range(target_splits[i] + 1):
            cpp_targets_autogen_splits.append(
                "src/autogen/" + OVRNAME + "_" + str(idx) + ".c"
            )
    if i == 0:
        for idx in range(target_splits[7] + 1):
            cpp_targets_autogen_splits.append("src/autogen/start_" + str(idx) + ".c")
        splat_targets.append(VERSION_EXE + YAML_EXT)
        ld_maps.append(VERSION_EXE + MAP_EXT)
        ld_targets.append(VERSION_EXE + LD_EXT)
        ld_out.append(ELF)
        undefined_funcs.append("mainexe" + UNDEFINED_FUNCS_NAME_AUTO)
        # asm_targets.append("asm/autogen/" + OVRNAME + ".s")
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
        if undefined_syms_auto[i] == 1:
            undefined_syms.append("/autogen/" + OVRNAME + UNDEFINED_SYMS_NAME_AUTO)
        else:
            undefined_syms.append("/" + OVRNAME + UNDEFINED_SYMS_NAME)

for i in range(7):
    ld_flag_table.append(
        "-T "
        + BASEPATH
        + undefined_syms[i]
        + " -T "
        + BASEPATH_AUTOGEN
        + undefined_funcs[i]
    )

splat_targets_path = [BASEPATH + "/" + s for s in splat_targets]
ld_targets_path = [BASEPATH + "/autogen/" + s for s in ld_targets]
cpp_targets = (
    cpp_targets_autogen
    + cpp_targets_autogen_splits
    + cpp_targets_autogen_end
    + cpp_targets_end
)
cpp46_targets = cpp_targets_46

# command invocations for rules
OVL_SPLIT_CMD = PYTHON_EXE + " " + OVL_SPLIT_EXE + " unpack -o $out $in"
AS_CMD = AS + ASFLAGS + " -o $out $in"
ASSET_CMD = LD + " -r -b binary -o $out $in"
SPLAT_CMD = SPLAT + " split $in"
CPP_CMD = (
    CPP
    + CPPFLAGS
    + " $in | "
    + CC
    + CFLAGS
    + PIPE
    + MASPSX
    + PIPE
    + AS
    + ASFLAGS
    + " -o $out"
)
CPP46_CMD = (
    CPP46
    + CPPFLAGS
    + " $in | "
    + CC46
    + CFLAGS
    + CFLAGS46
    + PIPE
    + MASPSX
    + PIPE
    + AS
    + ASFLAGS
    + " -o $out"
)
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
# builds C files into objects (using 2.95.2)
writer.rule("cpp46", CPP46_CMD, depfile="$out.asmproc.d")
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
        implicit_outs.extend(cpp_targets_autogen_splits)
        implicit_outs.extend(cpp_targets_autogen_end)
        writer.build(TARGET_NAME, "split", filename, implicit_outputs=implicit_outs)
    else:
        writer.build(
            TARGET_NAME,
            "split",
            filename,
            implicit=[ovl_split_outputs[target_num - 1]],
            implicit_outputs=implicit_outs,
        )

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

for filename in cpp46_targets:
    target_num = cpp46_targets.index(filename)
    OUTPUT = BUILDDIR + filename + O_EXT
    all_objects.append(OUTPUT)
    writer.build(OUTPUT, "cpp46", filename)

for filename in ld_targets_path:
    target_num = ld_targets_path.index(filename)
    ldflags = ld_flag_table[target_num]
    ld_map = BUILDDIR + ld_maps[target_num]
    writer.build(BUILDDIR + ld_targets[target_num], "copy", filename)

    if EXE_ONLY == 0 or (EXE_ONLY == 1 and target_num == 0):
        implicit_inputs = []
        implicit_inputs.extend(all_objects)
        implicit_inputs.append(ld_map)
        writer.build(
            ld_out[target_num],
            "ld",
            BUILDDIR + ld_targets[target_num],
            implicit=implicit_inputs,
            variables={
                "ldflags": ldflags,
                "ldmap": ld_map,
                "ldflags_base": LDFLAGS_BASE,
            },
        )

for i in range(7):
    if i == 0:
        INPUTFILE = ELF
        OUTPUT = EXE
        DIFF_OKAY = OUTPUT + ".ok"
        diff_okay_list.append(DIFF_OKAY)
        writer.build(OUTPUT, "objcopy", INPUTFILE)
        writer.build(
            DIFF_OKAY, "diff", BASEEXE, variables={"built": OUTPUT}, implicit=OUTPUT
        )
    else:
        INPUTFILE = BUILDDIR + GAME + "_0" + str(i) + ELF_EXT
        OUTPUT = BUILDDIR + GAME + "_0" + str(i) + EXE_EXT
        DIFF_OKAY = OUTPUT + ".ok"
        diff_okay_list.append(DIFF_OKAY)
        OUTPUT_DIFF = BINPATH + "/" + GAME + "_0" + str(i) + EXE_EXT
        writer.build(OUTPUT, "objcopy", INPUTFILE)
        writer.build(
            DIFF_OKAY, "diff", OUTPUT_DIFF, variables={"built": OUTPUT}, implicit=OUTPUT
        )

writer.build("build_progress.txt", "postbuild", implicit=diff_okay_list)

writer.rule("regen_ninja", f"{sys.executable} $in > $out")
writer.build("build.ninja", "regen_ninja", __file__)
