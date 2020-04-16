import os
import sys
import shutil

print("using python version:",sys.version)

current_dir = os.getcwd()

def copy_dir():
	shutil.copy(current_dir+"/extra/env_config.cpp", current_dir+"/temp_lib/config/")
	shutil.copy(current_dir+"/extra/env_config.h", current_dir+"/temp_lib/config/")


def construct_file_if_not_exists(original,target): 
    if not os.path.exists(target):
        print("path doesn't exist, creating path")
        shutil.copyfile(src=original,dst=target)



#create /conf/config.json for testing
construct_file_if_not_exists(current_dir+"/conf/config_demo.json",current_dir+"/conf/config.json")

# change permissions to rwx

oldmask = os.umask(0o000)
print("oldmask",oldmask)


# create temp_lib/config/ dir
temp_lib_config_path = os.path.join(current_dir,"temp_lib/")
print("temp_lib_config_path",temp_lib_config_path)
os.mkdir(path=temp_lib_config_path)

temp_lib_config_path = os.path.join(current_dir,"temp_lib/config/")
print("temp_lib_config_path",temp_lib_config_path)
os.mkdir(path=temp_lib_config_path)

copy_dir()

oldmask = os.umask(oldmask)
print("oldmask",oldmask)