# GlobalNLocalAlignment
C implementation of Local and Global alignment using classic dinamic programming algorithms


In order to try the library out you can run the makefile and try out (minimun a file for d and q sequences): 
  
  #To try Global alignment:
  ./Main global data/affine1d.fasta data/affine1q.fasta data/affine2d.fasta data/affine2q.fasta
  
  #To try local alignment
  ./Main local data/local1d.fasta data/local1q.fasta data/local2d.fasta data/local2q.fasta data/local3d.fasta data/local3q.fasta        data/local5d.fasta data/local5q.fasta
 
The format of input files is the following, specify if you want query or database sequence (>q or >d respectively) and under it the sequence you want.
  >q 
  ACCT
  
You can also change the scoring system for global and local alignment at their corresponding .h files
  
  
 

  
 
  
