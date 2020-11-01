function [sol] = hsvHistogram(path_to_image, count_bins)
  # FUNCTIE PENTRU RGB2HSV
  rgb = imread(path_to_image);
  rgb = double(rgb) / 256;
  [m n k] = size(rgb);
  hsv = zeros(m, n, k);
  # aici compar cate doua, deoarece nu ma lasa sa compar cate trei... nu stiu de ce
  Cmax = max(rgb(:, :, 1), rgb(:, :, 2));
  Cmax = max(Cmax, rgb(:, :, 3));
  Cmin = min(rgb(:, :, 1), rgb(:, :, 2));
  Cmin = min(Cmin, rgb(:, :, 3));
  delta = Cmax - Cmin;
  # PENTRU H
  ## trebuie sa iau niste matrici auxiliare(R, G, B si aux) pentru ca dintr-un motiv
  ## necunoscut octave nu accepta sintaxa h(:, :, 1)(Cmax == rgb(:, :, 1) & delta != 0)
  ## in conditiile in care si h(:, :, 1) si rgb(:, :, 1) tot matrici sunt
  #
  aux = zeros(m, n);
  R = rgb(:, :, 1);
  G = rgb(:, :, 2);
  B = rgb(:, :, 3);
  aux(Cmax == R & delta != 0) = 60 * mod((G(Cmax == R & delta != 0) - B(Cmax == R & delta != 0)) ./ delta(Cmax == R & delta != 0), 6);
  aux(Cmax == G & delta != 0) = 60 * ((B(Cmax == G & delta != 0) - R(Cmax == G & delta != 0)) ./ delta(Cmax == G & delta != 0) + 2);
  aux(Cmax == B & delta != 0) = 60 * ((R(Cmax == B & delta != 0) - G(Cmax == B & delta != 0)) ./ delta(Cmax == B & delta != 0) + 4);
  hsv(:, :, 1) = aux / 360;
  # PENTRU S
  E = ones(m, n);
  aux = zeros(m, n);
  E(Cmax>0) = Cmax(Cmax>0);
  aux(Cmax>0) = (ones(m, n) .* delta)(Cmax>0);
  hsv(:, :, 2) = aux ./ E;
  # PENTRU V
  hsv(:, :, 3) = Cmax;
  # END RGB2HSV
  
  # aici incepe functia pentru histograma HSV
  sol = zeros(1, 3 * count_bins);
  aux = zeros(1, count_bins + 1);
  for z = 1 : 3
    imageAux = hsv(:, :, z);
    imageVector = imageAux(:)';  # fac matricea vector
    aux = histc(imageVector, 0:(1.01 / count_bins):1.01); 
    sol(1, (1 + (z - 1) * count_bins):(z * count_bins)) = aux(1:count_bins);
  endfor
end
