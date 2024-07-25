import ninja_syntax
import os
import sys

# possible values: gt1, gt2, gt2k. only gt2 is supported for now.
game = "gt2"
# possible versions: jpbeta, jp10, jp11, us10, us11, us12, eubeta, eu10
# not all versions are possible.
region_version = "us12"
# possible values: "arcade", "simdisk". 
# "combined" is unsupported atm. It will be supported for gt1 and for gt2 combined.
# yymmdd will also be used for denoting betas/demos that do not resemble retail.
disk = "simdisk"
# unused, but is_demo = 1 means that the title is a demo that does not obey
# retail game structures.
is_demo = 0

version_exe = ""

if disk == "arcade":
    if region_version == "jp11" or region_version == "us12":
        raise ValueError(region_version + " is not a valid arcade GT2 disk version.")
    elif region_version in ["us10", "us11"]:
        version_exe = "scus_944.55"
    elif region_version in ["jpbeta", "jp10"]:
        version_exe = "scps_101.16"
    elif region_version in ["eubeta", "eu10"]:
        version_exe = "sces_023.80"
elif disk == "simdisk":
    if region_version == "eubeta":
        raise ValueError(region_version + " is not a valid simulation GT2 disk version.")
    elif region_version in ["us10", "us11", "us12"]:
        version_exe = "scus_944.88"
    elif region_version in ["jpbeta", "jp10", "jp11"]:
        version_exe = "scps_101.17"
    elif region_version == "eu10":
        version_exe = "sces_123.80"
else:
    raise ValueError(disk + " is not a valid GT2 disk type.")

python_exe = "python"
ovl_split_exe = "tools/GTModTools/ovl.py"
version = game + "_" + region_version + "_" + disk
basepath = "config/" + version
binpath = basepath + "/ovl_bin"
baseovl = basepath + "/orig_bin/GT2.OVL"

splat_targets = [version_exe + ".yaml", 
                 "gt2_01.yaml",
                 "gt2_02.yaml",
                 "gt2_03.yaml", 
                 "gt2_04.yaml", 
                 "gt2_05.yaml", 
                 "gt2_06.yaml"]
splat_targets_path = [basepath + "/" + s for s in splat_targets]
ovl_split_cmd = python_exe + " " + ovl_split_exe + " unpack -o $out $in"  

writer = ninja_syntax.Writer(sys.stdout)

writer.rule("split", "splat split $in")
writer.rule("ovl_split", ovl_split_cmd)

writer.build(binpath, "ovl_split", baseovl)

for filename in splat_targets_path:
    target_num = splat_targets_path.index(filename)
    writer.build("src/autogen/ovr" + str(target_num) + ".c", "split", filename)
