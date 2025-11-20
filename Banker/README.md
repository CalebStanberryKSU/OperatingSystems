This program implements the Banker’s Algorithm, a deadlock avoidance algorithm used to ensure that resource allocation will not lead to an unsafe state.

**Purpose of the Program**

The program:  
	1.	Reads an input file containing:  
	•	The allocation matrix  
	•	The maximum resource matrix  
	•	The available resources  
	2.	Computes the need matrix  
	3.	Runs the Banker’s Safety Algorithm to determine whether the system is in a safe or unsafe state  
	•	If safe, outputs a valid safe sequence of process execution  
 
**Banker’s Algorithm**

Banker’s Algorithm is used to determine whether granting a resource request would keep the system in a safe state.

A state is safe if:  
	•	There exists an ordering of all processes such that each one can obtain its needed resources and complete execution.

The algorithm checks:  
	1.	If a process’s Need ≤ Available  
	2.	If yes, the process is “safe” to run  
	3.	When a process completes, its allocated resources are added back  
	4.	Repeat until all processes finish or no eligible process remains  

If all processes can eventually finish, then the system is in a safe state  
Otherwise, the system is in unsafe state

**Safe Sequence**

A safe sequence is:  
P3 -> P4 -> P1 -> P2 -> P0

**Usage Instructions**

*Files Included*  
	•	banker.cpp  
	•	input.txt  
	•	README  

*Compile & Run*  
Run the following in terminal: 
g++ banker.cpp -o banker  
./banker  

*Input File Format*  
input.txt consists of 11 lines:  
	1.	First 5 lines = Allocated matrix (5×3)  
	2.	Next 5 lines = Maximum matrix (5×3)  
	3.	Last line = Available resources (1×3)  

*Separate resource counts with whitespace
