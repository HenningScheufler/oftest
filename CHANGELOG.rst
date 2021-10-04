
Changelog
=========

0.1.0 (2021-05-7)
------------------

added expected_results: loads a results in csv format and return the results in 
a pandas DataFrame:

test = oftest.expected_results([1,2],('isoAlpha',32))
test['err_shape']

0.0.5 (2021-05-7)
------------------

update documentation and added docstrings

0.0.4 (2021-04-24)
------------------

* added fixture for running cleaning and modify

break compatiblity due to run_case does not clean the case anymore
please substitute with run_reset_case

TL;DR

run_case -> run_reset_case

0.0.3 (2021-04-23)
------------------

* changed License to GPL -> pyfoam is GPLv2

0.0.0 (2021-04-17)
------------------

* First release on PyPI.


