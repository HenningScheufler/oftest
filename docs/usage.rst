=====
Usage
=====


quick start
-----------
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
			"--no-clean-up", action='store_false',default=True ,help="do not clean case after run"
		)

we assume that all OpenFOAM tests are located in the tests folder and that each test can be started with a
Allrun or Allclean script. By adding a test_*.py to each OpenFOAM test, pytest automatically discovers all
tests in the folder and they can be run with:

::

	py.test

with the command line option the test only run one time step

::

	py.test --writeNSteps 1


Running all OpenFOAM tutorials
------------------------------

cp -r $FOAM_TUTORIALS OfTestTut
cd OfTestTut

add new file add_tests.py:

::

	import os
	import glob
	from shutil import copyfile

	def list_files(filepath):
		paths = []
		for root, dirs, files in os.walk(filepath):
		for file in files:
			if file == "Allrun":  #lower().endswith(filetype.lower()):
				paths.append(os.path.join(root, file))
		return paths

	allruns = list_files(".")

	VALID_DIRS = ["compressible","combustion","discreteMethods","DNS",
				"electromagnetics","finiteArea","heatTransfer","incompressible",
				"lagrangian","multiphase","stressAnalysis",]

	test_template = "test_template.py"

	for allrun in allruns:

		for v_dir in VALID_DIRS:
			if v_dir in allrun:
				dir_name = os.path.dirname(allrun)
				basename = os.path.basename(dir_name)
				test_filename = "test_" + basename + ".py"
				dst = os.path.join(dir_name,test_filename)
				copyfile(test_template, dst)


add new test_template.py:

::

	import os
	import pytest
	import oftest
	from oftest import run_reset_case

	def test_completed(run_reset_case):
		log = oftest.path_log()
		assert oftest.case_status(log) == 'completed' # checks if run completes


python add_test.py # adds the test_files

Running

::

	py.test --co

should yield rougly 300 collects tests

The test are then run with

py.test --writeNSteps=1 -k "not adjoint"

with both these options we run the test one timestep without any test containing the adjoint keyword (they take along time)

and we should get following output

.. image:: media/test-tut-of2012.png
  :width: 800

and finally a report

.. image:: media/tut_of2012-report.png
  :width: 800

Parameter studies
-----------------


::


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

	@pytest.mark.parametrize("run_reset_case",[c3,c4], indirect=['run_reset_case'])
	@pytest.mark.parametrize("modify_case",[c1,c2], indirect=['modify_case'])
	def test_deomcase(modify_case,run_reset_case,load_parser_fvSolution,load_parser_transport):
		pass


With this approach we will generate 4 testcase which will be executed by the Allrun script and after the test is finshied
the case will be clean by the Allclean script.



Extensions
----------

Running py.test with multple threads:

pip install pytest-xdist

the output can be pretified with the extension:

pip install pytest-sugar