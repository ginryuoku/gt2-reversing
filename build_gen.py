import ninja_syntax
import os
import sys

python_exe = "python"
ovl_split_exe = "tools/GTModTools/ovl.py"
version = "gt2_us12_simdisk"
basepath = "config/" + version
binpath = basepath + "/ovl_bin"
baseovl = basepath + "/orig_bin/GT2.OVL"

splat_targets = ["scus_944.88.yaml", "gt2_01.yaml", "gt2_02.yaml", "gt2_03.yaml", "gt2_04.yaml", "gt2_05.yaml", "gt2_06.yaml"]
splat_targets_path = [basepath + "/" + s for s in splat_targets]
ovl_split_cmd = python_exe + " " + ovl_split_exe + " unpack -o $out $in"  

writer = ninja_syntax.Writer(sys.stdout)

writer.rule("split", "splat split $in")
writer.rule("ovl_split", ovl_split_cmd)

writer.build(binpath, "ovl_split", baseovl)

for filename in splat_targets_path:
    target_num = splat_targets_path.index(filename)
    writer.build("src/autogen/ovr" + str(target_num) + ".c", "split", filename)
