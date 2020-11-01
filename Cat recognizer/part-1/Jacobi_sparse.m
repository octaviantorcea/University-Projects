function [x] = Jacobi_sparse(G_values, G_colind, G_rowptr, c, tol)
  n = length(c);
  xinit = zeros(n, 1);
  y = csr_multiplication(G_values, G_colind, G_rowptr, xinit);
  x = y + c;
  while (norm(x - xinit) > tol)
    xinit = x;
    y = csr_multiplication(G_values, G_colind, G_rowptr, xinit);
    x = y + c;
  endwhile
endfunction