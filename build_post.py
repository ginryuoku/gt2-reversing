"""Does postbuild tasks."""

import filecmp
import os

# If true, doesn't exit with an error
NON_MATCHING = False


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


def check_matching_executables(infile, outfile, pretty_name):
    """Runs diff against built executables or objects."""
    differ = filecmp.cmp(infile, outfile)
    if differ is True:
        print(infile + " matches " + pretty_name + ".")
    else:
        print(infile + " doesn't match " + pretty_name + ".")
    return differ


# possible values: gt1, gt2, gt2k. only gt2 is supported for now.
GAME = "gt2"
# possible versions: jpbeta, jp10, jp11, us10, us11, us12, eubeta, eu10
# not all versions are possible.
REGION_VERSION = "us12"
# possible values: "arcade", "simdisk".
# "combined" is unsupported atm. It will be supported for gt1 and for gt2 combined.
# yymmdd will also be used for denoting betas/demos that do not resemble retail.
DISK = "simdisk"
VERSION = GAME + "_" + REGION_VERSION + "_" + DISK
BASEPATH = "config/" + VERSION
BUILDDIR = "build/"
BINPATH = BASEPATH + "/ovl_bin"
EXE_EXT = ".exe"

MAINEXE_NAME = detect_mainexe_name(REGION_VERSION, DISK)
ORIG_MAINEXE_NAME = BASEPATH + "/orig_bin/" + MAINEXE_NAME.upper()
BUILT_MAINEXE_NAME = BUILDDIR + MAINEXE_NAME

ovl_split_inputs = []
ovl_split_outputs = []
ovl_name = []

mainexe_dirs = [
    "asm/nonmatchings/autogen/ovr0",
    "asm/nonmatchings/autogen/ovr0_0",
    "asm/nonmatchings/autogen/ovr0_1",
    "asm/nonmatchings/autogen/ovr0_2",
    "asm/nonmatchings/autogen/ovr0_3",
    "asm/nonmatchings/autogen/ovr0_4",
    "asm/nonmatchings/autogen/ovr0_5",
    "asm/nonmatchings/autogen/ovr0_6",
    "asm/nonmatchings/autogen/start",
    "asm/nonmatchings/autogen/start_0",
    "asm/nonmatchings/autogen/start_1",
    "asm/nonmatchings/autogen/start_2",
    "asm/nonmatchings/autogen/start_3",
    "asm/nonmatchings/autogen/start_4",
    "asm/nonmatchings/autogen/start_5",
    "asm/nonmatchings/autogen/start_6",
    "asm/nonmatchings/autogen/start_7",
    "asm/nonmatchings/autogen/start_8",
    "asm/nonmatchings/autogen/start_9",
    "asm/nonmatchings/autogen/start_10",
    "asm/nonmatchings/autogen/start_11",
    "asm/nonmatchings/autogen/start_12",
    "asm/nonmatchings/autogen/start_13",
    "asm/nonmatchings/autogen/start_14",
    "asm/nonmatchings/autogen/start_15",
    "asm/nonmatchings/autogen/start_16",
    "asm/nonmatchings/autogen/start_17",
    "asm/nonmatchings/autogen/start_18",    
    "asm/nonmatchings/autogen/start_19",
    "asm/nonmatchings/autogen/start_20",
    "asm/nonmatchings/autogen/start_21",
    "asm/nonmatchings/autogen/start_22",
    "asm/nonmatchings/autogen/start_23",
    "asm/nonmatchings/autogen/start_24",
    "asm/nonmatchings/autogen/start_25",
    "asm/nonmatchings/autogen/start_26",
    "asm/nonmatchings/autogen/start_27",
    "asm/nonmatchings/autogen/start_28",
    "asm/nonmatchings/autogen/start_29",
    "asm/nonmatchings/autogen/start_30",
    "asm/nonmatchings/autogen/start_31",
    "asm/nonmatchings/autogen/start_32",
    "asm/nonmatchings/autogen/start_33",
    "asm/nonmatchings/autogen/start_34",
    "asm/nonmatchings/autogen/start_35",
    "asm/nonmatchings/autogen/start_36",
    "asm/nonmatchings/autogen/start_37",
    "asm/nonmatchings/autogen/start_38",
    "asm/nonmatchings/autogen/start_39",
    "asm/nonmatchings/autogen/start_40",
    "asm/nonmatchings/autogen/start_41",
    "asm/nonmatchings/autogen/start_42",
    "asm/nonmatchings/autogen/start_43",
    "asm/nonmatchings/autogen/start_44",
    "asm/nonmatchings/autogen/start_45",
    "asm/nonmatchings/autogen/start_46",
    "asm/nonmatchings/autogen/start_47",
    "asm/nonmatchings/autogen/start_48",
    "asm/nonmatchings/autogen/start_49",
    "asm/nonmatchings/autogen/start_50",
    "asm/nonmatchings/autogen/start_51",
    "asm/nonmatchings/autogen/start_52",
    "asm/nonmatchings/autogen/start_53",
    "asm/nonmatchings/autogen/start_54",
    "asm/nonmatchings/autogen/start_55",
    "src/autogen/ovr0",
    "src/autogen/start",
    "src/ovr0",
    "src/start",
]
mainexe_ns_dirs = mainexe_dirs
mainexe_decomped_dirs = ["src/ovr0", "src/start"]
mainexe_files = ["./asm/header.s"]

ovr1_dirs = [
    "asm/nonmatchings/autogen/ovr1",
    # "asm/ovr1",
    # "src/ovr1"
]
ovr1_decomped_dirs = ["src/ovr1"]
ovr2_dirs = [
    "asm/nonmatchings/autogen/ovr2",
    # "asm/ovr2",
    # "src/ovr2"
]
ovr2_decomped_dirs = ["src/ovr2"]
ovr3_dirs = [
    "asm/nonmatchings/autogen/ovr3",
    # "asm/ovr3",
    # "src/ovr3"
]
ovr3_decomped_dirs = ["src/ovr3"]
ovr4_dirs = [
    "asm/nonmatchings/autogen/ovr4",
    # "asm/ovr4",
    # "src/ovr4"
]
ovr4_decomped_dirs = ["src/ovr4"]
ovr5_dirs = [
    "asm/nonmatchings/autogen/ovr5",
    # "asm/ovr5",
    # "src/ovr5"
]
ovr5_decomped_dirs = ["src/ovr5"]
ovr6_dirs = [
    "asm/nonmatchings/autogen/ovr6",
    # "asm/ovr6",
    # "src/ovr6"
]
ovr6_decomped_dirs = ["src/ovr6"]


def make_directory_list(dirs):
    """Makes a directory list object for further parsing."""
    dirs_list = []
    for x in dirs:
        if os.path.isdir(x):
            dirs_list.extend(list(os.scandir(x)))
    return dirs_list


mainexe_dirs_list = make_directory_list(mainexe_dirs)
ovr1_dirs_list = make_directory_list(ovr1_dirs)
ovr2_dirs_list = make_directory_list(ovr2_dirs)
ovr3_dirs_list = make_directory_list(ovr3_dirs)
ovr4_dirs_list = make_directory_list(ovr4_dirs)
ovr5_dirs_list = make_directory_list(ovr5_dirs)
ovr6_dirs_list = make_directory_list(ovr6_dirs)

# number of files
mainexe_count = len(mainexe_files) + len([1 for x in mainexe_dirs_list if x.is_file()])
ovr1_count = len([1 for x in ovr1_dirs_list if x.is_file()])
ovr2_count = len([1 for x in ovr2_dirs_list if x.is_file()])
ovr3_count = len([1 for x in ovr3_dirs_list if x.is_file()])
ovr4_count = len([1 for x in ovr4_dirs_list if x.is_file()])
ovr5_count = len([1 for x in ovr5_dirs_list if x.is_file()])
ovr6_count = len([1 for x in ovr6_dirs_list if x.is_file()])

mainexe_decomped_dirs_list = make_directory_list(mainexe_decomped_dirs)
ovr1_decomped_dirs_list = make_directory_list(ovr1_decomped_dirs)
ovr2_decomped_dirs_list = make_directory_list(ovr2_decomped_dirs)
ovr3_decomped_dirs_list = make_directory_list(ovr3_decomped_dirs)
ovr4_decomped_dirs_list = make_directory_list(ovr4_decomped_dirs)
ovr5_decomped_dirs_list = make_directory_list(ovr5_decomped_dirs)
ovr6_decomped_dirs_list = make_directory_list(ovr6_decomped_dirs)


def count_ns(symbol_addr_filename):
    """Counts named symbols."""
    named_symbols = 0
    filepath = BASEPATH + symbol_addr_filename
    if os.path.isfile(filepath) is True:
        with open(filepath, encoding="utf-8") as f:
            for line in f:
                if (
                    "//" not in line
                    and not line.isspace()
                    and "str_" not in line
                    and "gt2_vol_" not in line
                ):
                    named_symbols += 1
    return named_symbols


# number of named symbols
MAINEXE_NS_COUNT = count_ns("/mainexe_symbol_addrs.txt")
OVR1_NS_COUNT = count_ns("/ovr1_symbol_addrs.txt")
OVR2_NS_COUNT = count_ns("/ovr2_symbol_addrs.txt")
OVR3_NS_COUNT = count_ns("/ovr3_symbol_addrs.txt")
OVR4_NS_COUNT = count_ns("/ovr4_symbol_addrs.txt")
OVR5_NS_COUNT = count_ns("/ovr5_symbol_addrs.txt")
OVR6_NS_COUNT = count_ns("/ovr6_symbol_addrs.txt")


# number of matched symbols:
def count_ms(dirs_list, files=""):
    """Counts matched symbols."""
    matched_symbols = len(
        [
            1
            for x in dirs_list
            if x.is_file()
            and "func_800" not in x.name
            and "jtbl_" not in x.name
            and "str_" not in x.name
        ]
    )
    if files != "":
        matched_symbols += len(files)
    return matched_symbols


mainexe_ms_fc = count_ms(mainexe_dirs_list, mainexe_files)
ovr1_ms_fc = count_ms(ovr1_dirs_list)
ovr2_ms_fc = count_ms(ovr2_dirs_list)
ovr3_ms_fc = count_ms(ovr3_dirs_list)
ovr4_ms_fc = count_ms(ovr4_dirs_list)
ovr5_ms_fc = count_ms(ovr5_dirs_list)
ovr6_ms_fc = count_ms(ovr6_dirs_list)

mainexe_dcs_fc = len(mainexe_files) + len(
    [1 for x in mainexe_decomped_dirs_list if x.is_file()]
)
ovr1_dcs_fc = len([1 for x in ovr1_decomped_dirs_list if x.is_file()])
ovr2_dcs_fc = len([1 for x in ovr2_decomped_dirs_list if x.is_file()])
ovr3_dcs_fc = len([1 for x in ovr3_decomped_dirs_list if x.is_file()])
ovr4_dcs_fc = len([1 for x in ovr4_decomped_dirs_list if x.is_file()])
ovr5_dcs_fc = len([1 for x in ovr5_decomped_dirs_list if x.is_file()])
ovr6_dcs_fc = len([1 for x in ovr6_decomped_dirs_list if x.is_file()])

overall_count = (
    mainexe_count
    + ovr1_count
    + ovr2_count
    + ovr3_count
    + ovr4_count
    + ovr5_count
    + ovr6_count
)
overall_ns_count = (
    MAINEXE_NS_COUNT
    + OVR1_NS_COUNT
    + OVR2_NS_COUNT
    + OVR3_NS_COUNT
    + OVR4_NS_COUNT
    + OVR5_NS_COUNT
    + OVR6_NS_COUNT
)
overall_ms_fc = (
    mainexe_ms_fc
    + ovr1_ms_fc
    + ovr2_ms_fc
    + ovr3_ms_fc
    + ovr4_ms_fc
    + ovr5_ms_fc
    + ovr6_ms_fc
)
overall_dcs_fc = (
    mainexe_dcs_fc
    + ovr1_dcs_fc
    + ovr2_dcs_fc
    + ovr3_dcs_fc
    + ovr4_dcs_fc
    + ovr5_dcs_fc
    + ovr6_dcs_fc
)


def print_symbols(name, count, ns_count, ms_fc, dcs_fc):
    """Pretty printer for our progress calculations."""

    if ns_count > count:
        ns_count = count

    prg_ns = ns_count / count
    prg_ms = ms_fc / count
    prg_dcs = dcs_fc / count


    if prg_ns > 0:
        print(f"{name}: named symbols:      {ns_count} / {count} ( {prg_ns:2.2%} )")
    if prg_ms > 0:
        print(f"{name}: matched symbols:    {ms_fc} / {count} ( {prg_ms:2.2%} )")
    if prg_dcs > 0:
        print(f"{name}: decomped symbols:   {dcs_fc} / {count} ( {prg_dcs:2.2%} )")


print_symbols(
    "main_exe", mainexe_count, MAINEXE_NS_COUNT, mainexe_ms_fc, mainexe_dcs_fc
)
print_symbols("overlay1", ovr1_count, OVR1_NS_COUNT, ovr1_ms_fc, ovr1_dcs_fc)
print_symbols("overlay2", ovr2_count, OVR2_NS_COUNT, ovr2_ms_fc, ovr2_dcs_fc)
print_symbols("overlay3", ovr3_count, OVR3_NS_COUNT, ovr3_ms_fc, ovr3_dcs_fc)
print_symbols("overlay4", ovr4_count, OVR4_NS_COUNT, ovr4_ms_fc, ovr4_dcs_fc)
print_symbols("overlay5", ovr5_count, OVR5_NS_COUNT, ovr5_ms_fc, ovr5_dcs_fc)
print_symbols("overlay6", ovr6_count, OVR6_NS_COUNT, ovr6_ms_fc, ovr6_dcs_fc)
print_symbols(
    " overall", overall_count, overall_ns_count, overall_ms_fc, overall_dcs_fc
)
