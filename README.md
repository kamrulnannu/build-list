Given a csv or txt file, each row being  
(start_job_id, start_job_run_time, next_job_id). A sample file:  
  
start_job,run_time,next_job  
8,1500,7  
1,2000,5  
7,3000,10  
5,2000,  8  
10, 10,0  
15, 160,90  
20,300,0  
  
Implement an efficent program to do following: 
  
1. Identify all Job Chains (all single linked list). next_job == 0 means  
   end of a list. In the above example file, there are two lists:  
  
   (a) (1, 2000, 5)(5, 2000, 8)(8, 1500, 7)(7, 3000, 10)(10, 10, 0)  
  
   (b) (20, 300, 0)  
  
   Note that one node's next_job is the start_job of the next node of  
   a chain. next_job = 0 for last node a chain.  
  
   Also note that job line (15, 160, 90) is not part of any of the above  
   two job chains. It is an input file error.  
  
2. Compute and print start_job, last_job, total_run_time average_run_time and jobs
   in chain of each job chain (output for above example):  
    (a)  
        StartJob: 1  
        LastJob: 10  
        JobChainTime: 02:141:50  
        AvgJobTime: 00:28:22  
  
    Chain: (1, 2000, 5)(5, 2000, 8)(8, 1500, 7)(7, 3000, 10)(10, 10, 0)  
  
    (b)  
        StartJob: 20  
        LastJob: 20  
        JobChainTime: 00:05:00  
        AvgJobTime: 00:05:00  
  
     Chain: (20, 300, 0)  
  
The program should read file from standard input (e.g. $ prog < input.txt)  
and ouput to standard out.  
