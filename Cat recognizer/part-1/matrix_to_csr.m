function [values, colind, rowptr] = matrix_to_csr(A)
  nz = 0;
  [n n] = size(A);
  for i = 1:n
    for j = 1:n
      if (A(i, j) != 0)
        nz = nz + 1;
      endif
    endfor
  endfor
  values = zeros(1, nz);
  colind = zeros(1, nz);
  rowptr = zeros(1, n + 1);
  nz = 1;
  count = 1;
  for i = 1:n
    ok = 0;
    for j = 1:n
      if (A(i, j) != 0)
        values(nz) = A(i, j);
        colind(nz) = j;
        if (ok == 0)
          rowptr(count) = nz;
          count = count + 1;
          ok = 1;
        endif
        nz = nz + 1;
      endif
    endfor
  endfor
  rowptr(n + 1) = nz;
endfunction