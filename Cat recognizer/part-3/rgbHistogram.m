function [sol] = rgbHistogram(path_to_image, count_bins)
  image = imread(path_to_image);
  [m n k] = size(image);
  sol = zeros(1, 3 * count_bins);
  aux = zeros(1, count_bins + 1);
  for z = 1 : 3
    imageAux = image(:, :, z);
    imageVector = imageAux(:)';  # fac matricea vector
    aux = histc(imageVector, 0:(256 / count_bins):256); 
    sol(1, (1 + (z - 1) * count_bins):(z * count_bins)) = aux(1:count_bins);
  endfor
end
