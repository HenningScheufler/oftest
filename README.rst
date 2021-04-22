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

.. |travis| image:: https://api.travis-ci.com/HenningScheufler/oftest.svg?branch=master
    :alt: Travis-CI Build Status
    :target: https://travis-ci.com/github/HenningScheufler/oftest

.. |appveyor| image:: https://ci.appveyor.com/api/projects/status/github/HenningScheufler/oftest?branch=master&svg=true
    :alt: AppVeyor Build Status
    :target: https://ci.appveyor.com/project/HenningScheufler/oftest

.. |requires| image:: https://requires.io/github/HenningScheufler/oftest/requirements.svg?branch=master
    :alt: Requirements Status
    :target: https://requires.io/github/HenningScheufler/oftest/requirements/?branch=master

.. |codecov| image:: https://codecov.io/gh/HenningScheufler/oftest/branch/master/graphs/badge.svg?branch=master
    :alt: Coverage Status
    :target: https://codecov.io/github/HenningScheufler/oftest

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
    :target: https://github.com/HenningScheufler/oftest/compare/v0.0.0...master



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

Note, to combine the coverage data from all the tox environments run:

.. list-table::
    :widths: 10 90
    :stub-columns: 1

    - - Windows
      - ::

            set PYTEST_ADDOPTS=--cov-append
            tox

    - - Other
      - ::

            PYTEST_ADDOPTS=--cov-append tox



Usage
=====

py.test tutorials_of2012/*  --collect-only --cache-clear --import-mode=importlib

py.test tutorials_of2012/*  --collect-only --cache-clear --import-mode=importlib