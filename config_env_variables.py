import json
import fileinput
import os
import sys
import shutil

print("using python version:",sys.version)

ROOT = os.getcwd()

def copy_dir():
	shutil.copy(ROOT+"/extra/env_config.cpp", ROOT+"/temp_lib/config/")
	shutil.copy(ROOT+"/extra/env_config.h", ROOT+"/temp_lib/config/")

def replace_all(file,searchExp,replaceExp):
    print("file:"+file)
    for line in fileinput.input(file, inplace=1):
        if searchExp in line:
            line = line.replace(searchExp,replaceExp)
        sys.stdout.write(line)

test_config = dict()


def construct_config_file_if_not_exists(original,target): 
    if not os.path.exists(target):
        shutil.copyfile(original,target)

construct_config_file_if_not_exists(ROOT+"/conf/config_demo.json",ROOT+"/conf/config.json")

json_config_path = os.getcwd()+"/conf/config.json"
print("json_config_path:"+json_config_path)
with open(json_config_path) as f:
    data= json.load(f)

cpp_file = ROOT+"/temp_lib/config/env_config.cpp"
match= "{$env_variables}"

copy_dir()
replace_all(cpp_file,match,str(data))
