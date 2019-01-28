#Speedtest

//-------------------------------------------------------------------------------------------------
This is a fun, interesting little project to measure the raw computing power of a machine. How
many floating point divisions can the computer do if it's fully utilized? I don't think this is the
same measurement as the traditional FLOPS (Floating Point Operations Per Second) measurement that's
typically used to gauge computer speed, but it's a reasonable approximation.

At the top of the code there's a constant named THREADS that controls how many pthreads the program
will use. This one number completely controls the thread count - no other modifications are necessary.
Initial attempts on the MacBook used a single thread which produced roughly 225 million (225M) floating
point divisions per second. Experimentation after that showed that optimal results are achieved when
the thread count matches the number of cores/processors. The MacBook's Intel Core i7 processor includes 4
cores, so the best results are achievable with 4 threads. You can, of course, use 8 threads or whatever
with 4 cores, but once the thread count exceeds the core count, adding threads no longer increases the
number of floating point divisions that can be done within a given time period. I suspect, in fact, that
a slight _decrease_ would be observed because of the excess threads being paused and the cores having to
switch context to go service them. I haven't shown this yet, however.

To date, I've run this code on three separate Linux boxen:
* My MacBook (obviously), with 4 cores
* "Ruth," an AWS t2.micro instance with 1 core
* "Biggie," a compute-optimized AWS c5.18xlarge instance with **72** cores

The run.bash script was used to run the speedtest executable 15 times in a row on each machine. Then
the output from the worker threads was pasted into a spreadsheet. The average column below reflects
an average over all threads, all runs; the max column reflects the most divisions accomplished across
all 15 runs.

The (very satisfying) results are summarized below.

| Machine | Average Divisions Per Core | Number of Cores | Max # of Divisions |
|---------|----------------------------|-----------------|--------------------|
| MacBook | 224M                       |  4              | 904M               |
| Ruth    | 190M                       |  1              | 191M               |
| Biggie  | 262M                       | 72              |  19B               |

