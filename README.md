# Scientific-Computing-Finite-Difference
![image](https://github.com/haoli94/Scientific-Computing-Finite-Difference/blob/master/algorithm.png)
![image](https://github.com/haoli94/Scientific-Computing-Finite-Difference/blob/master/Results/figure_1.png)
![image](https://github.com/haoli94/Scientific-Computing-Finite-Difference/blob/master/Results/figure_2.png)
Usage:./main < inputfile >< prefix >
It outputs intermediate solutions every 10 iterations and returns total iteration numberwhen the CGSolver converges.

Usage:  python3 postprocess.py< inputfile >< solutionfile >
It  outputs  the  mean  temperature  and  plots  a  pseudocolor  plot  of  the  temperaturedistribution inside the pipe wall with the mean temperature isoline.

Usage:  python3 animation.py< inputfile >< prefix >
It repeatedly plot all the solution files of a specific input file with an interval of 0.3s asthe animation. And the repeat delay is 1.0s.
