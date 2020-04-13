import json
import fileinput
import sys,os, shutil

print("python version:",sys.version)

root = os.getcwd()

def copy_dir():
	shutil.copy(root+"/extra/env_config.cpp", root+"/temp_lib/config/")
	shutil.copy(root+"/extra/env_config.h", root+"/temp_lib/config/")

def replace_all(file,searchExp,replaceExp):
    print("file:"+file)
    for line in fileinput.input(file, inplace=1):
        if searchExp in line:
            line = line.replace(searchExp,replaceExp)
        sys.stdout.write(line)

json_config_path = os.getcwd()+"/conf/config.json"
print("json_config_path:"+json_config_path)
with open(json_config_path) as f:
    data= json.load(f)

cpp_file = root+"/temp_lib/config/env_config.cpp"
match= "{$env_variables}"

copy_dir()
replace_all(cpp_file,match,str(data))