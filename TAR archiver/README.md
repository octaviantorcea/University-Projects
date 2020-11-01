# TAR Archiver - Tema 3 Programarea Calculatoarelor

Implementati un program în limbajul C care simulează un utilitar ce creează o
arhivă de tipul tar. Utilitarul este reprezentat de un fisier executabil cu
numele archiver, care atunci când rulează poate interpreta anumite comenzi de
la standard input (stdin). Comenzile pe care programul poate să le interpreteze
sunt:
• create nume_arhivă nume_director - creează o arhivă tar cu numele nume_arhivă
ce contine fisiere din directorul nume_director.
• list nume_arhivă - afisează numele fisierelor continute în arhiva nume_arhivă.
• extract nume_fisier nume_arhivă - extrage continutul fisierului nume_fisier
salvat în arhiva nume_arhivă.
• exit - încheie executia programului.
