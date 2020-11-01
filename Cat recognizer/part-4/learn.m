function [w] = learn(X, y, lr, epochs)
  [n m] = size(X);
  for i = 1 : m  # scalarea lui X
    X(:, i) = (X(:, i) - mean(X(:, i))) / std(X(:, i));
  endfor
  Xtilde = X;
  Xtilde(:, m + 1) = 1;
  w = -0.1 + 0.2 * rand(m + 1, 1);
  for x = 1 : epochs  # algoritmul descris in cerinta
    id = round(1 + (n - 1) * rand(64, 1));
    Xbatch = Xtilde(id, :);
    ybatch = y(id);
    for i = 1 : m + 1
      suma = 0;
      for j = 1 : 64
        suma += (Xbatch(j, :) * w - ybatch(j)) * Xbatch(j, i);
      endfor
      w(i) = w(i) - (lr / n) * suma;
    endfor
  endfor
endfunction
