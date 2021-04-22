import pytest
import os

def pytest_addoption(parser):
    parser.addoption(
        "--writeNSteps", action="store", default=0, help="only perform specified number of timestep"
    )
    # parser.addoption(
    #     "--writeNow", action='store_true', help="only perform one timestep",
    # )
    parser.addoption(
        "--no-Allclean", action='store_false',default=True ,help="do not clean case after run"
    )
