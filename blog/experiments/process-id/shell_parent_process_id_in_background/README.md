In the main process, you run another process in background to get the parent process id, if by that time the parent process has already exit, then what you get is the init process:
baiyanh   1212  0.0  0.4  40316  4212 ?        Ss   08:57   0:01 init --user


