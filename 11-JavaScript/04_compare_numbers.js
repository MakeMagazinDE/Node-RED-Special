/*
  Diese Funktion vergleicht zwei Zahlen.
*/
function vergleicheZahlen(a, b) {
  if (a > b) {
    console.log('a ist größer als b.');
  } else if (a === b) { // Achtung: ===
    console.log('a ist gleich b.');
  } else {
    console.log('a ist kleiner als b.');
  }
}
vergleicheZahlen(7, 5);
vergleicheZahlen(7, 7);
vergleicheZahlen(5, 7);
