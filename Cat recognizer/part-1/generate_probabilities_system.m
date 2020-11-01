function [A, b] = generate_probabilities_system(rows)
  n = ((rows + 1) * rows) / 2;
  A = zeros(n, n);
  b = zeros(n, 1);
  # pentru A(1:3, :) valorile din matrice sunt hardcodate pentru ca rows > 2
  A(1, 1) = 4;
  A(1, 2:3) = -1;
  A(2, 1) = -1;
  A(2, 2) = 5;
  A(2, 3:5) = -1;
  A(3, 1:2) = -1;
  A(3, 3) = 5;
  A(3, 5:6) = -1;
  # se initializeaza pozitia din labirint ca fiind 4 si randul din labirint 3
  pos = 4;
  rand = 3;
  while (pos <= n)
    if (rand == rows)  # se verifica daca suntem pe ultimul rand din labirint
      if (pos + rows - 1 == n)  # daca e in coltul din stanga pe ultimul rand
        A(pos, pos - rows + 1) = -1;
        A(pos, pos + 1) = -1;
        A(pos, pos) = 4;
      elseif (pos == n)  # daca e in coltul din dreapta pe ultimul rand
        A(pos, pos - rows) = -1;
        A(pos, pos - 1) = -1;
        A(pos, pos) = 4;
      else
        A(pos, pos) = 5;
        A(pos, pos - rows) = -1;
        A(pos, pos - rows + 1) = -1;
        A(pos, pos - 1) = -1;
        A(pos, pos + 1) = -1;
      endif
    elseif (pos == ((rand - 1) * rand) / 2 + 1)  # daca e pe margine in stanga
      A(pos, pos - rand + 1) = -1;
      A(pos, pos + 1) = -1;
      A(pos, pos + rand) = -1;
      A(pos, pos + rand + 1) = -1;
      A(pos, pos) = 5;
    elseif (pos == ((rand + 1) * rand) / 2)  # daca e pe margine in dreapta
      A(pos, pos - rand) = -1;
      A(pos, pos - 1) = -1;
      A(pos, pos + rand) = -1;
      A(pos, pos + rand + 1) = -1;
      A(pos, pos) = 5;
    else  # daca e oriunde altundeva
      A(pos, pos - rand) = -1;
      A(pos, pos - rand + 1) = -1;
      A(pos, pos - 1) = -1;
      A(pos, pos + 1) = -1;
      A(pos, pos + rand) = -1;
      A(pos, pos + rand + 1) = -1;
      A(pos, pos) = 6;
    endif
    pos = pos + 1;
    if (pos > ((rand + 1) * rand) / 2)
      rand = rand + 1;
    endif
  endwhile
  b(n - rows + 1:n, 1) = 1;
endfunction