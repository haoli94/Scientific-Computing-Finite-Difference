# Scientific-Computing-Finite-Difference
 \begin{algorithm}  
        \caption{Conjugate Gradient (CG) method}  
        \begin{algorithmic}[1]
            \Require $b\hspace{5} and \hspace{5} CSR\hspace{5}matrix\hspace{5}constructed\hspace{5}in\hspace{5}  HeatEquation2D,the\hspace{5}prefix\hspace{5}and\hspace{5}inputfile$
            \Ensure $Converged\hspace{5}solution\hspace{5}u_n$ 
            \Function {CG Solver}{$val, row\_ptr, col\_idx,b,x,\epsilon,soln,filename$} 
                \State $std::vector<double> A u_0 \gets matdotvec(val,row\_ptr,col\_idx,x);$ 
                \State $r_0 \gets b $ - $A u_0 $ 
                \State $||r_0||_2 \gets L2norm(r_0)$ 
                \State $p_0 \gets r_0$ 
                \State $niter \gets 0$ 
                \State $soln\_write(filename,soln,iter,x)$
                \While {$niter < nitermax$} 
                    \State $niter \gets niter + 1$ 
                    \State $alpha_n \gets (r_n{^T}r_n)/(p_n{^T} A\hspace{5}p_n)$ 
                    \State $u_{n+1} \gets u_n + alpha_n\hspace{5}p_n$ 
                    \State $r_{n+1} \gets r_n \hspace{5} $-$\hspace{5} alpha_n \hspace{5} A  \hspace{5} p_n$ 
                    \State $||r_n||_2 \gets L2norm(r_n)$ 
                    \If{$||r_n||_2/||r_n||_2 < \epsilon$} 
                        \State $break$ 
                    \EndIf 
                    \If{$iter\%10 \equiv\equiv 0$} 
                        \State $soln\_write(filename,soln,iter,x)$ 
                    \EndIf
                    \State $beta_n \gets (r_{n+1}^T r_{n+1})/(r_n^T r_n)$ 
                    \State $ p_{n+1} = r_{n+1} + beta_n\hspace{5}p_n$ 
                \EndWhile 
                \State \Return{$result$}  
        \end{algorithmic}    
    \end{algorithm}  
