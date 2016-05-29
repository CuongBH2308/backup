### Python Testing Tools
* unittest - https://docs.python.org/2/library/unittest.html
   * test fixture - a test environment with setUp-runTest-tearDown steps, it is a concept
   * test case - TestCase, FunctionTestCase
      * each test method starts with test_*
      * reuse the test fixture
      * FunctionTestCase capture AssertionError (assert)
   * test suite - TestSuite (addTest)
   * test loader - TestLoader (discover(), loadTestsFromTestCase)
   * test runner - TextTestRunner
   * failure: failures are caused by incorrect result - a 5 where you expected a 6.
   * error: Errors are caused by incorrect code - e.g., a TypeError caused by an incorrect function call.
* testtools - http://testtools.readthedocs.org/en/latest/overview.html
   * an extension of python's unittest framework: 
   * asserter
      * ExpectedException
      * assertIn, assertNotIn
      * assertIs, assertIsNot
      * assertIsInstance
      * expectFailure (a bug not yet fixed, it is not a decorator, but an assertion, will have unexpected success)
   * matcher
      * assertThat, expectThat(continue the test even fail) is used with Matchers
      * Equals, Is, IsInstance, GreaterThan, LessThan, FileExists, DirContains, FileContains
      * Not, Annotate, AfterPreprocessing, MatchesAll, MatchesAny,
      * And you can write your own matchers
   * debug info (TestCase.addDetail), like attach a log file
   * more control over the unittest framework
      * TestCase.addCleanup (not for all, but just for this case)
      * TestCase.skipTest
      * TestCase.addOnException
   * all assert* from unittest are still works
* nose - http://nose.readthedocs.org/en/latest/
   * test loading
   * test running
   * test reporting
   * extendable use plugins: nosetests --plugins
   * tag tests, rather than naming conventions
   * loading ducktype test case: not necessary TestCase subclass, as long as match the test name
   * assertX function supported in nose.tools
   * parallel testing (-processes, from Multiprocess plugin)
      * fixture bounded
   * test timeout
   * test coverage