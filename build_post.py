"""Does postbuild tasks."""
import filecmp
import sys

# If true, doesn't exit with an error
NON_MATCHING = False

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

mainexe_name = detect_mainexe_name(REGION_VERSION, DISK)
orig_mainexe_name = BASEPATH + "/orig_bin/" + mainexe_name.upper()
built_mainexe_name = BUILDDIR + mainexe_name

ovl_split_inputs = []
ovl_split_outputs = []
ovl_name = []

for i in range(1,7):
    GAME_OVRNAME = GAME + "_0" + str(i)
    ovl_split_inputs.append(BUILDDIR + GAME + "_0" + str(i) + EXE_EXT)
    ovl_split_outputs.append(BINPATH + "/" + GAME_OVRNAME + EXE_EXT)
    ovl_name.append("ovr" + str(i))

build_passed = True

for i in range(7):
    if i == 0:
        check = check_matching_executables(orig_mainexe_name, built_mainexe_name, "the mainexe")
    else:
        check = check_matching_executables(ovl_split_inputs[i - 1],
                                           ovl_split_outputs[i - 1],
                                           ovl_name[i - 1])
    if check is False:
        build_passed = False

if build_passed is False and NON_MATCHING is False:
    sys.exit(1)
