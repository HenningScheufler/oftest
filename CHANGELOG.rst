
Changelog
=========

0.2.1 (2021-1-25)
-----------------

added:
- path_logs get all log.* in folder

0.2.0 (2021-1-20)
-----------------

added:
- log files are copied in logs folder

0.1.2 (2021-12-22)
------------------

added:
- success to run_case, run_reset_case, clean_case
- copy_log_files

::
    accessible with
    run_reset_case.success

    add copy_log_files() copy files to os.path.join("logs",current_test())
    use case
    if (not run_reset_case.success)
    oftest.copy_log_files()



0.1.1 (2021-12-22)
------------------

added exit code to run_case, run_reset_case, clean_case
accessible with:
c_mod.meta_data['return_value']

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


