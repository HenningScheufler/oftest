
from os import path
import pytest, os
import oftest
import time
from oftest import run_case


@pytest.fixture()
def load_parser_controlDict():
    dir_name = path.dirname(path.abspath(__file__))
    controlDict = path.join(dir_name,"system/controlDict")
    return oftest.Pyfoam_parser(controlDict)

@pytest.fixture()
def load_parser_transport():
    dir_name = path.dirname(path.abspath(__file__))
    transportProperties = path.join(dir_name,"constant/transportProperties")
    return oftest.Pyfoam_parser(transportProperties)

@pytest.fixture()
def load_parser_fvSolution():
    dir_name = path.dirname(path.abspath(__file__))
    fvSolution = path.join(dir_name,"system/fvSolution")
    return oftest.Pyfoam_parser(fvSolution)

class TestClass:

    def test_completed(self,run_case):
        log = oftest.path_log()
        assert oftest.case_status(log) == 'completed'

    # def test_completed(self,run_case):
    #     time.sleep(10)
    #     assert True


    def test_writeNow(self,run_case,load_parser_controlDict):
        parser = load_parser_controlDict
        assert parser.value("startFrom") == "latestTime"
        assert parser.value("stopAt") == "nextWrite"
        assert parser.value("writeControl") == "timeStep"
        assert parser.value("writeInterval") == 1
        # time.sleep(20)


class TestClass2:
    file_mod1 =  { "constant/transportProperties": [ ("water/transportModel","unique-value-1"),
                                                    ("air/transportModel","unique-value-2") ] }

    file_mod2 =  { "system/fvSolution": [ ("PIMPLE/momentumPredictor","unique-value-3"),
                                         ("PIMPLE/nCorrectors","unique-value-4") ] }

    dir_name = os.path.dirname(os.path.abspath(__file__))
    c1 = oftest.Case_modifiers(file_mod1,dir_name)
    c2 = oftest.Case_modifiers(file_mod2,dir_name)


    def test_cleaned(self):
        dir_name = path.dirname(path.abspath(__file__))
        log_file = path.join(dir_name,'log.interIsoFoam')
        assert not os.path.exists(log_file)


    @pytest.mark.parametrize("run_case",[c1], indirect=True)
    def test_para_transport(self,run_case,load_parser_transport):
        par_Trans = load_parser_transport
        assert par_Trans.value("water/transportModel") == "unique-value-1"
        assert par_Trans.value("air/transportModel") == "unique-value-2"


    @pytest.mark.parametrize("run_case",[c2], indirect=True)
    def test_para_fvSolution(self,run_case,load_parser_fvSolution):
        par_fvS = load_parser_fvSolution
        assert par_fvS.value("PIMPLE/momentumPredictor") == "unique-value-3"
        assert par_fvS.value("PIMPLE/nCorrectors") == "unique-value-4"


def case_mods_transport(val):
    dir_name = os.path.dirname(os.path.abspath(__file__))
    file_mod =  { "constant/transportProperties": [ ("water/transportModel",f"unique-value-{val}"),
                                                     ("air/transportModel",f"unique-value-{val}") ] }
    c = oftest.Case_modifiers(file_mod,dir_name)
    return c

def case_mods_fvSolution(val):
    dir_name = os.path.dirname(os.path.abspath(__file__))
    file_mod =  { "system/fvSolution": [ ("PIMPLE/momentumPredictor",f"unique-value-{val}"),
                                        ("PIMPLE/nCorrectors",f"unique-value-{val}") ] }
    c = oftest.Case_modifiers(file_mod,dir_name)
    return c

c1 = case_mods_transport(1)
c2 = case_mods_transport(2)

c3 = case_mods_fvSolution(3)
c4 = case_mods_fvSolution(4)

run_case2 = run_case # copy fixture

@pytest.mark.parametrize("run_case",[(c1,),c2], indirect=['run_case'])
@pytest.mark.parametrize("run_case2",[c3,c4], indirect=['run_case2'])
def test_para_fvSolution(run_case,run_case2,load_parser_fvSolution,load_parser_transport):
    par_fvS = load_parser_fvSolution
    par_Trans = load_parser_transport
    print(run_case)
    print(run_case2)
    assert par_Trans.value("water/transportModel") == run_case.modifiers["constant/transportProperties"][0][1]
    assert par_Trans.value("air/transportModel") == run_case.modifiers["constant/transportProperties"][1][1]
    assert par_fvS.value("PIMPLE/momentumPredictor") == run_case2.modifiers["system/fvSolution"][0][1]
    assert par_fvS.value("PIMPLE/nCorrectors") == run_case2.modifiers["system/fvSolution"][1][1]

