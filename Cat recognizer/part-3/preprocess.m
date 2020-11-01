function [X, y] = preprocess(path_to_dataset, histogram, count_bins)
  type = 1;
  if (strcmp(histogram, "HSV") == 0)
    type = 2;
  endif
  dirCats = strcat(path_to_dataset, 'cats/');
  catFiles = getImgNames(dirCats);
  dirNotCats = strcat(path_to_dataset, 'not_cats/');
  notCatFiles = getImgNames(dirNotCats);
  [m1 n1] = size(catFiles);
  [m2 n2] = size(notCatFiles);
  y = zeros(m1 + m2, 1);
  y(1:m1) = 1;
  y((m1 + 1):(m1 + m2), 1) = -1;
  X = zeros(m1 + m2, count_bins * 3);
  for i = 1 : m1
    path = strcat(dirCats, catFiles(i, :));
    if (type != 1)
      X(i, :) = rgbHistogram(path, count_bins);
    else
      X(i, :) = hsvHistogram(path, count_bins);
    endif
  endfor
  for i = 1 : m2
    path = strcat(dirNotCats, notCatFiles(i, :));
    if (type != 1)
      X(i + m1, :) = rgbHistogram(path, count_bins);
    else
      X(i + m1, :) = hsvHistogram(path, count_bins);
    endif
  endfor
endfunction
