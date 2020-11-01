function [w] = learn(X, y)
  [line col] = size(X);
  Xtilde = X;
  Xtilde(1:line, col + 1) = 1;
  [Q R] = Householder(Xtilde);
  w = SST(R, Q' * y);
end
