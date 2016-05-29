# TaskGraph
This is to test the lifecycle of a gradle build, specifically the taskgraph ready

* The 3 critical pharse in a gradle build are: Initialization phase -> Configuration phase -> Execution phase
* There are 2 ways to hook into the build phase:
   * within a closure
   * implement a listner interface
* Hooks
   * gradle.beforeProject
   * gradle.buildFinished
   * gradle.taskGraph.whenReady
   * project.AfterEvaluate
   * project.beforeEvaluate
   * ...
* Listeners
   * BuildListener
   * ProjectEvaluationListener
   * TaskExecutionGraphListener