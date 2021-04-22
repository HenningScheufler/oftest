========
Overview
========

.. start-badges

.. list-table::
    :stub-columns: 1

    * - docs
      - |docs|
    * - tests
      - | |travis| |appveyor| |requires|
        | |codecov|
    * - package
      - | |version| |wheel| |supported-versions| |supported-implementations|
        | |commits-since|
.. |docs| image:: https://readthedocs.org/projects/oftest/badge/?style=flat
    :target: https://oftest.readthedocs.io/
    :alt: Documentation Status

.. |version| image:: https://img.shields.io/pypi/v/oftest.svg
    :alt: PyPI Package latest release
    :target: https://pypi.org/project/oftest

.. |wheel| image:: https://img.shields.io/pypi/wheel/oftest.svg
    :alt: PyPI Wheel
    :target: https://pypi.org/project/oftest

.. |supported-versions| image:: https://img.shields.io/pypi/pyversions/oftest.svg
    :alt: Supported versions
    :target: https://pypi.org/project/oftest

.. |supported-implementations| image:: https://img.shields.io/pypi/implementation/oftest.svg
    :alt: Supported implementations
    :target: https://pypi.org/project/oftest

.. |commits-since| image:: https://img.shields.io/github/commits-since/HenningScheufler/oftest/v0.0.0.svg
    :alt: Commits since latest release
    :target: https://github.com/HenningScheufler/oftest/compare/v0.0.2...master



.. end-badges

test framework for OpenFOAM

* Free software: BSD 2-Clause License

Installation
============

::

    pip install oftest

You can also install the in-development version with::

    pip install https://github.com/HenningScheufler/oftest/archive/master.zip


Documentation
=============


https://oftest.readthedocs.io/


Development
===========

To run all the tests run::

    tox


Usage
=====

add conftest.py and pytest.ini to your project

cat pytest.ini:

::

    [pytest]
    #minversion = 6.0
    addopts = -ra -v --import-mode=importlib --tb=no --cache-clear
    testpaths =
        tests

cat conftest.py:

::

    import pytest

    def pytest_addoption(parser):
        parser.addoption(
            "--writeNSteps", action="store", default=0, help="only perform specified number of timestep"
        )
        parser.addoption(
            "--no-Allclean", action='store_false',default=True ,help="do not clean case after run"
        )

we assume that all OpenFOAM test are located in the tests folder and that each test can be started with a
Allrun or Allclean script. By adding a test_*.py to each OpenFOAM test, py.test automatically discovers all
tests in the folder and they can be run with:

::

    py.test

with the command line option the test only run one time step

::

    py.test --writeNSteps 1


Extensions
----------

Running py.test with multple threads:

pip install pytest-xdist

the output can be pretified with the extension:

pip install pytest-sugar