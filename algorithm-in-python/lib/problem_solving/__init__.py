# This is to support namespace package
# here package algorithm comes from:
# 1. lib/algorithm
# 2. tests/algorithm
# So in order for the tests have same structure as lib
# we need to use namespace package, as below
import pkgutil
__path__ = pkgutil.extend_path(__path__, __name__)
