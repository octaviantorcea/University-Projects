function [G_J, c_J] = Jacobi_factorization(A, b)
  [n n] = size(A);
  Dr = zeros(n, 1); # pastrez matricea elementelor de pe diagonala ca un vector
  L = zeros(n, n);
  U = zeros(n, n);
  G_J = zeros(n, n);
  c_J = zeros(n, 1);
  for i = 1:n
    Dr(i) = 1 / A(i, i); # le pun direct inversate in vector
  endfor
  for i = 1:n-1
    for j = i+1:n
      U(i, j) = A(i, j);
    endfor
  endfor
  for i = 2:n
    for j = 1:i-1
      L(i, j) = A(i, j);
    endfor
  endfor
  c_J = Dr.*b;
  G_J = -Dr.*(L + U);
endfunction