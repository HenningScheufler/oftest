import pytest
import os
from dataclasses import dataclass,field
from PyFoam.RunDictionary.ParsedParameterFile import ParsedParameterFile
from typing import List, Tuple
from shutil import copyfile


def base_dir() -> str:
    f_name = os.getenv('PYTEST_CURRENT_TEST').split('::')[0]
    dir_name = os.path.dirname(f_name)
    return dir_name

def path_log(app_name : str="") -> str:
    dir_name = base_dir()
    if app_name:
        return os.path.join(dir_name,"log." + app_name)

    controlDict = os.path.join(dir_name,"system/controlDict")
    p = Pyfoam_parser(controlDict)
    app_name = p.value("application")

    return os.path.join(dir_name,"log." + app_name)


class Parser:

    def __init__(self,filename):
        self.filename = filename

    def value(self,keyword):
        pass

    def set(self,keyword):
        pass

    def writeFile(self):
        pass


class Pyfoam_parser(Parser):

    def __init__(self,filename):
        self.filename = filename
        self._ppp = ParsedParameterFile(self.filename)

    def _nested_get(self,dic, keyword):
        key_list = keyword.split('/')
        key_list[:] = [x for x in key_list if x]
        if len(key_list) == 1:
            return dic[key_list[0]]
        for key in key_list:
            dic = dic[key]
        return dic

    def _nested_set(self,dic, keyword, value):
        key_list = keyword.split('/')
        key_list[:] = [x for x in key_list if x]
        if len(key_list) == 1:
            dic[key_list[-1]] = value
            return
        for key in key_list[:-1]:
            dic = dic.setdefault(key, {})
        dic[key_list[-1]] = value

    def value(self,keyword):
        return self._nested_get(self._ppp.content,keyword)

    def set(self,keyword,value):
        self._nested_set(self._ppp.content,keyword,value)

    def writeFile(self):
        self._ppp.writeFile()


class Case_modifiers:
    def __init__(self,case_modifiers: dict,dir_name: str): #: list[Case_modifier]):
        """[summary]
        dict format
        {
            "system/controlDict": [ ("stopAt","writeNow"),
                                    ("endTime",10.1) ]
        }
        Args:
            self ([type]): [description]
        """
        self.modifiers = case_modifiers
        self.dir_name = dir_name


    def __str__(self):
        return str(self.modifiers)

    def add_mod(self,file_path,key,val):
        if file_path not in self.modifiers:
            self.modifiers[file_path] = []
        self.modifiers[file_path].append((key,val))

    def update_case(self):
        """
            update the based on the specified modifiers
        """
        for key in self.modifiers:
            bkp_file = key + ".orig"

            bkp_path = os.path.join(self.dir_name,bkp_file)
            file_path = os.path.join(self.dir_name,key)
            # backup file
            copyfile(file_path, bkp_path)

            p = Pyfoam_parser(os.path.join(self.dir_name,key))
            for key_val in self.modifiers[key]:
                p.set(key_val[0],key_val[1])
            p.writeFile()

    def revert_change(self):
        for key in self.modifiers:
            bkp_file = key + ".orig"

            bkp_path = os.path.join(self.dir_name,bkp_file)
            file_path = os.path.join(self.dir_name,key)
            copyfile(bkp_path,file_path)

    # def __del__(self):
        # pass



@pytest.fixture(scope="class")
def run_case(request):
    mod_case = hasattr(request,"param")
    dir_name = base_dir()
    c_mod = Case_modifiers({},dir_name)
    if mod_case:
        if not isinstance(request.param, Case_modifiers):
            raise TypeError("parameter needs to be a Case_modifiers")
        c_mod = request.param

    nsteps = request.config.getoption("--writeNSteps")
    if nsteps:
        c_mod.add_mod("system/controlDict","startFrom","latestTime")
        c_mod.add_mod("system/controlDict","stopAt","nextWrite")
        c_mod.add_mod("system/controlDict","writeControl","timeStep")
        c_mod.add_mod("system/controlDict","writeInterval",nsteps)

    c_mod.update_case()

    os.system(f"{dir_name}/Allrun -test")

    yield

    c_mod.revert_change()
    # if not request.config.getoption("--no-Allclean"):
    os.system(f"{dir_name}/Allclean")

