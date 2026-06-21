# Guida: risolvere esercizi di calcolo combinatorio e backtracking
### ASD – Politecnico di Torino

Questa guida ti porta da "leggo il testo" a "ho il codice corretto" per tutta la
famiglia di esercizi basati su esplorazione combinatoria (anagrammi, powerset,
partizioni, otto regine, sum of subsets, sudoku/maze, problemi di ottimo come
`bestConcat`). Il cuore è in due parti: **come scegliere il modello combinatorio**
e **uno scheletro di codice unico** che adatti al modello scelto.

---

## 1. Riconoscere che è un problema di backtracking

Quasi sempre il testo contiene uno di questi segnali:

- "genera **tutte** le sequenze / combinazioni / configurazioni …"
- "trova **la migliore / la più lunga / la massima** tra tutte le …"
- "**quanti** modi ci sono di …" (conteggio)
- "disponi / assegna / colora … **rispettando il vincolo** …"
- problemi a griglia in cui ogni cella ha più scelte e devi tornare indietro se ti
  incastri (sudoku, labirinto, cavallo).

In pratica: lo spazio delle soluzioni è un **albero di scelte**, ad ogni livello
scegli "il prossimo elemento/casella", e se una scelta non porta a nulla **torni
indietro** (backtrack). Se invece il problema ha sottostruttura ottima con
sovrapposizione di sottoproblemi, è programmazione dinamica, non backtracking — ma
i testi di questa famiglia te lo dicono quasi sempre con "tutte/parte" e "vincolo".

---

## 2. Scegliere il modello combinatorio (la parte che vale i punti)

Rispondi a **tre domande** sul testo, in quest'ordine.

**D1 — L'ordine conta?** `[a, b]` è diverso da `[b, a]`?
**D2 — Sono ammesse ripetizioni?** Posso usare lo stesso elemento più di una volta?
**D3 — Uso tutti gli elementi o solo una parte?** ("tutte o parte" ⟹ classe variabile)

La combinazione delle risposte ti dà il modello:

| Ordine conta | Ripetizioni | Quanti | Modello | Spazio |
|:---:|:---:|:---:|---|---|
| Sì | No | parte (k variabile) | **Disposizioni semplici** | somma di D(n,k) |
| Sì | No | tutti (k = n) | **Permutazioni semplici** | n! |
| Sì | Sì | k posizioni | **Disposizioni con ripetizione** | n^k |
| No | No | k tra n | **Combinazioni semplici** | C(n,k) |
| No | Sì | k tra n | **Combinazioni con ripetizione** | C(n+k-1, k) |
| — | — | ogni elem. dentro/fuori | **Powerset (sottoinsiemi)** | 2^n |
| — | — | ripartire in blocchi | **Partizioni (modello Er)** | numeri di Bell/Stirling |

### Tradurre il linguaggio del testo → modello

Parole-spia tipiche dei temi d'esame:

- **L'ordine conta:** "sequenza ordinata", "in che ordine", "permutazione",
  "anagramma", "disposizione", "stringa ottenuta concatenando…".
- **L'ordine NON conta:** "sottoinsieme", "scegliere k tra n", "gruppo", "squadra",
  "insieme di…".
- **Niente ripetizioni:** "ciascuno **al più una volta**", "senza ripetere",
  "elementi **distinti**".
- **Con ripetizioni:** "anche ripetuti", "con ripetizione", "ogni casella può
  contenere uno qualsiasi…".
- **Classe variabile ("tutte o parte"):** registri una soluzione **ad ogni nodo**,
  non solo alle foglie.
- **Tutti gli n elementi:** permutazioni → registri solo alle foglie (livello == n).
- **Dentro/fuori per ogni elemento:** "accendere/spegnere", "incluso o no",
  "selezionare un sottoinsieme" ⟹ powerset.
- **Ripartire in gruppi/blocchi:** ⟹ partizioni, modello Er.

### Il modello Er (per partizioni e per evitare duplicati simmetrici)

Quando assegni ogni elemento a un "blocco" o "gruppo", e i blocchi **non hanno
identità** (il gruppo {1,2} è uguale a sé stesso comunque lo chiami), l'enumerazione
ingenua genera lo stesso raggruppamento più volte (simmetria delle etichette). Il
modello **Er** elimina queste duplicazioni con una regola semplice:

> l'elemento `i` può essere messo solo in un blocco **già esistente** (indici
> `0 .. numBlocchi-1`) oppure aprire **il primo blocco nuovo** (indice `numBlocchi`),
> mai saltare a un blocco vuoto più in là.

Così ogni partizione è generata una e una sola volta. È più efficiente delle
disposizioni con ripetizione perché taglia in radice le configurazioni equivalenti.

---

## 3. Il framework di implementazione (scheletro unico)

Tutti questi esercizi sono lo **stesso** algoritmo con quattro pezzi che cambiano.
Lo scheletro generico:

```c
void solve(/* stato: sol[], livello, struttura di disponibilita', + dati */)
{
    /* (A) REGISTRAZIONE: e' una soluzione da considerare? */
    if (/* condizione di registrazione */)
    {
        /* processa: conta, stampa, oppure aggiorna il best */
        /* return; se sei a una foglia "chiusa", altrimenti prosegui */
    }

    /* (B) GENERAZIONE CANDIDATI per il livello corrente */
    for (/* ogni candidato c ammesso dal MODELLO */)
    {
        /* (C) PRUNING di feasibility: c viola un vincolo del problema? */
        if (/* c non e' valido */)
            continue;

        /* (D) APPLICA -> RICORRI -> DISFA (backtrack) */
        applica(c);                 /* marca used / scrivi in sol / aggiorna stato */
        solve(/* stato aggiornato, livello+1 */);
        disfai(c);                  /* annulla, speculare ad applica */
    }
}
```

I quattro pezzi:

- **(A) Registrazione** — *dove* riconosci una soluzione. Dipende dalla D3:
  foglia (`livello == n`) per permutazioni/classe fissa; **ad ogni nodo** per
  "tutte o parte".
- **(B) Candidati** — *cosa* puoi scegliere al livello corrente. È qui che il
  **modello** entra nel codice (vedi sotto).
- **(C) Pruning** — *quali candidati scartare subito* perché violano un vincolo
  del problema (non del modello).
- **(D) Apply/undo** — il backtrack. L'undo deve essere **speculare** all'apply,
  o lasci lo stato sporco nei rami fratelli.

### Come il modello plasma la generazione dei candidati (B)

| Modello | Come generi i candidati al livello | Strumento |
|---|---|---|
| Permutazioni / disposizioni semplici | tutti gli elementi **non ancora usati** | array `used[]` |
| Disposizioni con ripetizione | **tutti** gli elementi, sempre | nessun `used[]` |
| Combinazioni semplici | elementi con indice **> dell'ultimo scelto** | parametro `start` |
| Powerset | due rami per ogni elemento: **incluso / escluso** | scelta binaria per livello |
| Partizioni (Er) | blocco `0..numBlocchi-1` **oppure** nuovo blocco `numBlocchi` | contatore `numBlocchi` |

Regola mnemonica:

- `used[]` ⟹ **non ripetizione** + l'ordine conta (permutazioni/disposizioni).
- `start` (indice crescente) ⟹ **ordine non conta** (combinazioni): impedisci di
  rigenerare lo stesso sottoinsieme in ordine diverso.
- niente vincolo sull'indice ⟹ **con ripetizione**.

---

## 4. Dove registrare la soluzione (A) — l'errore più subdolo

- **Solo alle foglie** (`livello == n`): permutazioni complete, disposizioni di
  classe fissa, configurazioni che hanno senso solo "piene" (es. otto regine: una
  soluzione è valida solo quando hai piazzato tutte e 8 le regine).
- **Ad ogni nodo**: quando il testo dice "**tutte o parte**", ogni soluzione
  parziale è già una soluzione legittima. Esempio `bestConcat`: ogni prefisso valido
  è una concatenazione ammessa, quindi confronti col best ad **ogni** livello.
- **Quando un contatore/obiettivo è raggiunto**: sum of subsets (somma == target),
  cambio monete (resto == 0).

Sbagliare questo punto è la causa numero uno di soluzioni "quasi giuste": registri
alle foglie un problema che andava registrato ad ogni nodo (e perdi le soluzioni
parziali) o viceversa.

---

## 5. Il pruning (l'altra domanda d'esame)

Distingui sempre due cose, perché l'esame premia la precisione:

1. **Regola del modello** (NON è pruning): `used[]`, `start`, il contatore Er.
   Questi *definiscono lo spazio* corretto (non-ripetizione, ordine, ecc.).
2. **Pruning di feasibility**: scarti i candidati che violano un **vincolo del
   problema**. È il `continue` di (C). Riduce drasticamente il branching.
   - otto regine: stessa colonna o diagonale ⟹ scarto.
   - `bestConcat`: iniziale della stessa categoria della finale precedente ⟹ scarto.
3. **Pruning di bound (branch & bound)** — solo per problemi di **ottimo**: se il
   miglior valore raggiungibile da questo ramo non può battere il record corrente,
   taglio l'intero sottoalbero.
   - `bestConcat`: `caratteri_correnti + lunghezza_parole_residue <= best ⟹ return`.

Nella relazione scrivi sempre: *qual è il modello e perché* (D1/D2/D3), *qual è il
pruning di feasibility* (il vincolo), e *se c'è un bound* (e perché lo è/non lo è).
**Non descrivere un pruning che non hai implementato**: l'esaminatore confronta
codice e testo.

---

## 6. Procedura passo-passo (da usare all'esame)

1. **Modello.** Rispondi D1 (ordine?), D2 (ripetizioni?), D3 (tutti o parte?) →
   leggi il modello dalla tabella. Scrivi subito una riga di giustificazione.
2. **Stato.** Decidi cosa rappresenta una soluzione parziale: `sol[]` (o la stringa,
   la griglia…), il `livello`, e *come tracci la disponibilità* (`used[]` / `start`
   / posizione / `numBlocchi`).
3. **Registrazione (A).** Foglia o ogni nodo? Scrivi la condizione.
4. **Candidati (B).** Scrivi il `for` secondo il modello (tabella della §3).
5. **Pruning (C).** Inserisci i `continue` per i vincoli del problema.
6. **Apply/undo (D).** Applica, ricorri con `livello+1`, disfai in modo speculare.
7. **Ottimo?** Aggiungi `best*` + l'aggiornamento, ed eventualmente il bound pruning.
8. **Wrapper.** Alloca le strutture di lavoro, lancia `solve`, raccogli/ricostruisci
   il risultato, libera tutto.

---

## 7. Errori ricorrenti da controllare prima di consegnare

- Dimenticato l'**undo** nel backtrack (`used[j] = 0`) → stato sporco nei fratelli.
- Registrazione nel **posto sbagliato** (foglia vs ogni nodo).
- Confuso **con ripetizione** (niente `used[]`) e **semplici** (con `used[]`).
- Combinazioni senza il parametro **`start`** → generi permutazioni duplicate.
- **Condizione di pruning invertita** → l'albero si svuota subito o non pota nulla.
- `return` con il **tipo sbagliato** nei rami d'errore (es. `return -1;` in una
  funzione che ritorna un puntatore → usa `return NULL;`).
- Helper interni non marcati **`static`**.
- Pruning **descritto ma non implementato** nella relazione.

---

## 8. Mappa esercizi → modello (riferimenti rapidi)

| Esercizio tipo | Modello | Pezzo chiave |
|---|---|---|
| Anagrammi con ripetizione | disposizioni con ripetizione | nessun `used[]`, livello = posizione |
| Anagrammi distinti / permutazioni | permutazioni semplici | `used[]`, registra a foglia |
| Powerset | sottoinsiemi (2^n) | ramo incluso/escluso per elemento |
| Partizioni / k-blocchi | partizioni (Er) | blocco esistente o nuovo (`numBlocchi`) |
| Sum of subsets | powerset + target | registra quando somma == target; bound sul resto |
| Cambio monete | disposizioni con ripetizione + ottimo | minimo numero di pezzi; bound |
| Otto regine | permutazioni / disposizioni semplici | `used[]` colonne + vincolo diagonali |
| `bestConcat` | disposizioni semplici | `used[]`, registra ad ogni nodo, vincolo + bound |
| Sudoku / maze / cavallo | backtracking su griglia | candidati per cella + vincolo + undo |

---

### In una frase

Identifica il **modello** con D1/D2/D3, traducilo nel **modo in cui generi i
candidati** (`used[]` / `start` / nessun vincolo / Er), decidi **dove registrare**
la soluzione, applica il **pruning del vincolo** col `continue`, e ricordati sempre
l'**undo** speculare nel backtrack. È sempre lo stesso scheletro.
