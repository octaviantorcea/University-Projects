function [percentage] = evaluate(path_to_testset, w, histogram, count_bins)
  [X real] = preprocess(path_to_testset, histogram, count_bins);
  [n m] = size(X);
  for i = 1 : m;
    X(:, i) = (X(:, i) - mean(X(:, i))) / std(X(:, i));
  endfor
  Xtilda = X;
  Xtilda(:, m + 1) = 1;
  acc = 0;
  for i = 1 : n
    estimation = sum(w' .* Xtilda(i, :));
    if (estimation >= 0 && real(i) > 0)
      acc++;
    endif
    if (estimation < 0 && real(i) < 0)
      acc++;
    endif
  endfor
  percentage = acc / n;
endfunction
