import oftest, pytest
from os import path
import numpy as np
from itertools import islice

def test_read_csv_geoField():
    dir_name = path.dirname(path.abspath(__file__))
    filename = path.join(dir_name,"T.csv")
    df = oftest.read_csv_geoField(filename)
    patches_and_internal = set(df[4].unique().tolist())
    expected_Values = {'left', 'bottom', 'internal', 'top', 'right'}

    assert (len(patches_and_internal.difference(expected_Values)) == 0)

def test_log_status():
    dir_name = path.dirname(path.abspath(__file__))
    f_completed = path.join(dir_name,"log.completed")
    f_fe = path.join(dir_name,"log.fatalError")
    f_fpe = path.join(dir_name,"log.floatPointExp")
    f_running = path.join(dir_name,"log.running")

    assert oftest.case_status(f_completed) == "completed"
    assert oftest.case_status(f_fe) == "error"
    assert oftest.case_status(f_fpe) == "error"
    assert oftest.case_status(f_running) == "running"


def test_run_time():
    dir_name = path.dirname(path.abspath(__file__))
    f_completed = path.join(dir_name,"log.completed")
    t_exec, t_clock = oftest.run_time(f_completed)
    assert t_exec == 30.55
    assert t_clock == 30.0


# def test_answer(request):
#     print(request.config.getoption("--writeNow"))
#     print(request.fixturenames)
#     assert True


# from datetime import datetime, timedelta

# testdata = [
#     (datetime(2001, 12, 12), datetime(2001, 12, 11), timedelta(1)),
#     (datetime(2001, 12, 11), datetime(2001, 12, 12), timedelta(-1)),
# ]

# @pytest.mark.parametrize("a,b,expected", testdata)
# def test_timedistance_v0(a, b, expected):
#     diff = a - b
#     assert diff == expected

# @pytest.mark.parametrize("a,b,expected", testdata, ids=["forward", "backward"])
# def test_timedistance_v1(a, b, expected):
#     diff = a - b
#     assert diff == expected


# def idfn(val):
#     if isinstance(val, (datetime,)):
#         # note this wouldn't show any hours/minutes/seconds
#         return val.strftime("%Y%m%d")


# @pytest.mark.parametrize("a,b,expected", testdata, ids=idfn)
# def test_timedistance_v2(a, b, expected):
#     diff = a - b
#     assert diff == expected


# @pytest.mark.parametrize(
#     "a,b,expected",
#     [
#         pytest.param(
#             datetime(2001, 12, 12), datetime(2001, 12, 11), timedelta(1), id="forward"
#         ),
#         pytest.param(
#             datetime(2001, 12, 11), datetime(2001, 12, 12), timedelta(-1), id="backward"
#         ),
#     ],
# )
# def test_timedistance_v3(a, b, expected):
#     diff = a - b
#     assert diff == expected
