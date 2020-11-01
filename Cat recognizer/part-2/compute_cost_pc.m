function [cost] = compute_cost_pc(points, centroids)
  [n d] = size(points);
  [NC d] = size(centroids);
  # prefer sa am un vector de lungime n (=numarul de puncte) in care sa tin
  # minte pt fiecare punct carui cluster ii apartine
  idPoints = zeros(n, 1);
  for i = 1:n  # pentru fiecare punct
    minDistance = 100000;
    for j = 1:NC  # pentru fiecare centroid
      distance = 0;
      for k = 1:d  # pentru fiecare dimensiune
        distance = distance + (points(i, k) - centroids(j, k))^2;
      endfor
      distance = sqrt(distance);
      if (distance < minDistance)
        minDistance = distance;
        idPoints(i) = j;
      endif
    endfor
  endfor
  cost = 0;
  for i = 1:n  # pentru fiecare punct
    distance = 0;
    for j = 1:d  # pentru fiecare dimensiune
      distance = distance + (points(i, j) - centroids(idPoints(i), j))^2;
    endfor
    distance = sqrt(distance);
    cost = cost + distance;
  endfor
endfunction