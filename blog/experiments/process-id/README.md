1. batch vs shell on launching another script
   * call -> source: run in same process, and continue
   * default -> exec: run in same process, and exit immediately
   * start -> cmd &  run in a new process in background
   * nothing -> default: run in a new process in sync, windows doesn't have this.

2. If the parent process already exit:
   * linux: the child process's parent process (run in background) become user's init process
   * Windows: the child process's parent process id is still the already exit parent process
