# CPU_BURST

A CPU bursts when it is executing instructions; an I/O system bursts when it services requests to fetch information. 
The idea is that each component operates until it can’t.
A CPU can run instructions from the cache until it needs to fetch more instructions or data from memory. 
That ends the CPU burst and starts the I/O burst. 
The I/O burst reads or writes data until the requested data is read/written or the space to store its cache runs out.
That ends an I/O burst. The magic of an OS is the act of managing and scheduling these activities to maximize the use of the resources and minimize wait and idle time.
In real life, a lot of this activity can be managed in parallel, 
but in OS design you should consider the dependencies between I/O and CPU activities and events and make sure that each subsystem can burst as effectively as possible.

https://www.quora.com/What-is-meant-by-CPU-Burst-and-I-O-Burst

These examples show how two algorithms work.
##1 - FCFS (First Come First Serve)
##2 - SJF (Shortest Job First)

All source code written in C++ in Visual Studio 2015
