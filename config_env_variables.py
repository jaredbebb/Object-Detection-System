import json
import fileinput
import os
import sys
import shutil

print("using python version:",sys.version)

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


def construct_file_if_not_exists(original,target): 
    if not os.path.exists(target):
        print("path doesn't exist, creating path")
        shutil.copyfile(src=original,dst=target)

#create /conf/config.json for testing
construct_file_if_not_exists(current_dir+"/conf/config_demo.json",current_dir+"/conf/config.json")

# change permissions to rwx
os.umask(0o777)

# create temp_lib/config/ dir
temp_lib_config_path = os.path.join(current_dir,"temp_lib/")
print("temp_lib_config_path",temp_lib_config_path)
os.mkdir(path=temp_lib_config_path,mode=0o777)

temp_lib_config_path = os.path.join(temp_lib_config_path,"config/")
print("temp_lib_config_path",temp_lib_config_path)
os.makedirs(name=temp_lib_config_path,mode=0o777, exist_ok=True)

json_config_path = os.getcwd()+"/conf/config.json"
print("json_config_path:"+json_config_path)
with open(json_config_path) as f:
    data= json.load(f)

cpp_file = current_dir+"/temp_lib/config/env_config.cpp"
match= "{$env_variables}"

copy_dir()
replace_tokens(cpp_file,match,str(data))
