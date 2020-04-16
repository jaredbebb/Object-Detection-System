import json
import fileinput
import os
import sys
import shutil

current_dir = os.getcwd()

def copy_dir():
	shutil.copy(current_dir+"/extra/env_config.cpp", current_dir+"/temp_lib/config/")
	shutil.copy(current_dir+"/extra/env_config.h", current_dir+"/temp_lib/config/")

def replace_tokens(file,searchExp,replaceExp):
    print("file:"+file)
    for line in fileinput.input(file, inplace=1):
        if searchExp in line:
            line = line.replace(searchExp,replaceExp)
        sys.stdout.write(line)

json_config_path = os.getcwd()+"/conf/config.json"
print("json_config_path:"+json_config_path)
with open(json_config_path) as f:
    data= json.load(f)

cpp_file = current_dir+"/temp_lib/config/env_config.cpp"
match= "{$env_variables}"


replace_tokens(cpp_file,match,str(data))