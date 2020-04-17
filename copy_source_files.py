import os
import sys
import shutil

print("using python version:",sys.version)

current_dir = os.getcwd()
print("cwd:",current_dir)

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

# create temp_lib/config/ dir
temp_lib_config_path = os.path.join(current_dir,"temp_lib/")
try:
    os.mkdir(path=temp_lib_config_path)
except FileExistsError  as e:
    print (e)


temp_lib_config_path = os.path.join(current_dir,"temp_lib/config/")
try:
    os.mkdir(path=temp_lib_config_path)
except FileExistsError  as e:
    print (e)

copy_dir()

oldmask = os.umask(oldmask)

