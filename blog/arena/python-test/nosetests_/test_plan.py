# 1. you can run script: nosetests
# 2. you can using nose.main() below
# 3. python test_plan.py --plugins
# 4. basically override functions from Plugin
# 5. nosetests --with-coverage --cover-html
import nose
from HelloWorld import HelloWorld
nose.main(addplugins=[HelloWorld()])