# LEACH-in-C
An implementation of the LEACH algorithm, written in C. This is a port of a Matlab implementation of LEACH, which was written by Mohammad Hossein Homaei of the Wireless Sensor Network Laboratory of Iran, and is based on the *original* version of LEACH described by Heinzelman et. al. in "An Application-Specific Protocol Architecture for Wireless Microsensor Networks".

This work is currently in progress. 

**To do:**

	Collect relevant data about each round and output it to a file.

	Enable input of network information (locations of all nodes, size of field, number of round etc.)

	Compare results to the Matlab version.

	Implement a proper wireless propagation model. As of now it is assumed all messages reach their destination.

	Move files to separate folders - /network, /energy, and /leach, with headers and source files separated within.

	Visualisation of results

	Later, convert to a version that can be ran on Contiki
