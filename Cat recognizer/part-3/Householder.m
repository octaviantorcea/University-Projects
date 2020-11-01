function [Q, R] = Householder(A)
  [m n] = size(A);
  H = eye(m);
  for p = 1 : min(m - 1, n)
    sum = 0;
    vp = zeros(m, 1);
    vp(p + 1:m, 1) = A(p + 1:m, p);
    for i = p : m
      sum += A(i, p) ^ 2;
    endfor
    sigma = sign(A(p, p)) * sqrt(sum);
    vp(p) = sigma + A(p, p);
    Hp = eye(m) - 2 * (vp * vp') / (vp' * vp);
    A = Hp * A;
    H = Hp * H;
  endfor
  Q = H';
  R = A;
endfunction
