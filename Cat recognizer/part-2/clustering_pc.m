function [centroids] = clustering_pc(points, NC)
  [n d] = size(points);
  # prefer sa am un vector de lungime n (=numarul de puncte) in care sa tin 
  # minte pt fiecare punct carui cluster ii apartine
  idPoints = zeros(n, 1);
  count = 1;
  for i = 1:n
    idPoints(i) = count;
    count = count + 1;
    if (count > NC)
      count = 1;
    endif
  endfor
  centroids = zeros(NC, d);
  for i = 1:NC  # pt fiecare cluster
    for y = 1:d  # pt fiecare dimensiune a unui punct
      suma = 0;
      count = 0;
      for x = 1:n  # verific fiecare punct daca apartine respectivului cluster
        if (idPoints(x) == i)
          suma = suma + points(x, y);
          count = count + 1;
        endif
      endfor
      centroids(i, y) = suma / count;
    endfor
  endfor
  success = 0;
  while (success == 0)
    oldCentroids = centroids;
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
    for i = 1:NC  # pt fiecare cluster
      for y = 1:d  # pt fiecare dimensiune a unui punct
        suma = 0;
        count = 0;
        for x = 1:n  # verific fiecare pct daca apartine respectivului cluster
          if (idPoints(x) == i)
            suma = suma + points(x, y);
            count = count + 1;
          endif
        endfor
        centroids(i, y) = suma / count;
      endfor
    endfor
    success = 1;
    for i = 1:NC
      if (norm(centroids(i,:) - oldCentroids(i,:)) > 0.000001)
        success = 0;
      endif
    endfor
  endwhile
endfunction