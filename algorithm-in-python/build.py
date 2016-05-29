#!/usr/local/bin/python

import os
import stat
from os.path import join
import shutil
import compileall
import sys
import subprocess
import unittest
import types
import argparse

"""
Compile Tools Compare
1. pycompile - you can put the result to a different location
2. compileall - you can batch process
"""

"""
Static Analysis Tools Compare
1. pep8: check if your code conforms to PEP8 style standard
2. pylint: check pep8 style (slightly different) + code smells
3. pychecker
4. pyflakes
"""

# pydoc support?
# pychecker
# coverage
# pyflakes
# doc generation


parser = argparse.ArgumentParser()
parser.add_argument("--steps", help="comma separated list of steps")
xargs = parser.parse_args()

steps_set = set(xargs.steps.split(',')) if xargs.steps else None


def check_step(step):
    def step_impl(*args, **kwargs):
        success = None
        print "*"*10 + step.func_name + "*"*10
        try:
            step(*args, **kwargs)
        except EnvironmentError as e:
            success = False
            print step.func_name + ' failed: ' + e.message
            raise
        else:
            success = True
            print step.func_name + ' finished successfully!'
        print "\n"
        return success

    if not steps_set or step.func_name in steps_set:
        return step_impl
    else:
        return lambda self: True


# class level decorator to modify a class, like add an attribute, add a
# function and then return the class (like return a function in method
# decorators)
def add_print_public(cls):
    public_func = []
    for attr, value in cls.__dict__.items():
        if (isinstance(value, (property, types.FunctionType)) and
                not attr.startswith('_')):
            public_func.append(attr)

    def print_public(dummy):
        print cls.__name__ + " public intefaces:\n" + "\n".join(public_func)

    setattr(cls, "print_public", print_public)
    return cls


def force_rmtree(name):
    def del_readonly(dummy_action, name, dummy_exc):
        os.chmod(name, stat.S_IWRITE)
        os.remove(name)
    shutil.rmtree(name, onerror=del_readonly)


@add_print_public
class PyBuild(object):
    def __init__(self):
        self.src_dir = '.'
        self.build_dir = '../build'
        self.install_dir = '../install'

    @check_step
    def build(self):
        if os.path.isdir(self.build_dir):
            force_rmtree(self.build_dir)
        shutil.copytree('.', self.build_dir)
        compileall.compile_dir(join(self.build_dir, 'lib'), force=True)
        compileall.compile_dir(join(self.build_dir, 'tests'), force=True)
        compileall.compile_dir(join(self.build_dir, 'arena'), force=True)

    @check_step
    def install(self):
        if os.path.isdir(self.install_dir):
            force_rmtree(self.install_dir)
        print "Copy files from %s to %s" % (self.build_dir, self.install_dir)
        shutil.copytree(join(self.build_dir, 'lib'),
                        join(self.install_dir, 'lib'))

    @check_step
    def pep8(self):
        print "Run pep8 against files in %s" % self.src_dir
        ret = self._run_command('pep8 --show-pep8 --statistic ./lib build.py')
        if ret != 0:
            raise EnvironmentError("pep8 checking failed with issues")

    @check_step
    def pylint(self):
        print "Run pylint against files in %s" % self.src_dir
        target = './lib/algorithm ./lib/data_structure build.py'
        pylint_cmd = 'pylint -j 0 -r n --rcfile=config/pylint.rc '
        ret = self._run_command(pylint_cmd + target)
        if ret != 0:
            raise EnvironmentError("pylint checking failed with %d issues" %
                                   ret)

    @check_step
    def test(self, filters="test*.py"):
        sys.path.append(join(self.build_dir, 'lib'))
        test_filter = filters

        # use defaultTestLoader mulitple times result in an error
        # of module can't be loaded, use a new instance everytime
        test_loader = unittest.TestLoader()
        test_suites = test_loader.discover(
            start_dir=join(self.build_dir, 'tests'),
            pattern=test_filter)
        test_runner = unittest.TextTestRunner(verbosity=2)
        result = test_runner.run(test_suites)
        assert result.wasSuccessful(), "Test failed"

    @staticmethod
    def _run_command(cmdline):
        command = cmdline.split()
        result = subprocess.call(command)
        return result

py_build = PyBuild()
# py_build.print_public() # no-member

build = py_build.build()
pep8 = py_build.pep8()
pylint = py_build.pylint()
test = py_build.test()

if build and pep8 and pylint and test and py_build.install():
    print "The entire build process succeeded!!!\n"
else:
    print "There are issues with the build, please check the log!!!\n"
    sys.exit(1)
