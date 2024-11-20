#MINISHELL

STEP 1: Tokenizer:

La tokenizzazione è un passo fondamentale nel processo di parsing e aiuta enormemente a semplificare l'analisi sintattica. Ecco una spiegazione più dettagliata:
Cos'è la tokenizzazione:
La tokenizzazione è il processo di suddividere una stringa di input (nel nostro caso, un comando Bash) in unità più piccole e significative chiamate "token". Ogni token rappresenta un elemento atomico del linguaggio, come una parola, un operatore, o un simbolo speciale.
Come funziona:

Il tokenizzatore (o lexer) legge l'input carattere per carattere.
Identifica sequenze di caratteri che formano unità logiche (token).
Classifica ogni token in base al suo tipo (ad esempio, parola, operatore, simbolo speciale).

Perché è utile per il parsing:

Semplificazione: Invece di lavorare con singoli caratteri, il parser può operare su unità di significato più grandi e coerenti.
Classificazione: I token sono già categorizzati, facilitando le decisioni del parser su come interpretarli.
Pulizia dell'input: La tokenizzazione può eliminare spazi bianchi non significativi e gestire casi speciali come le stringhe tra virgolette.
Preparazione per l'analisi sintattica: Fornisce una struttura dati ordinata che il parser può facilmente attraversare.
Separazione delle responsabilità: Divide il problema complesso dell'analisi in due fasi più gestibili.

Esempio pratico per Bash:
Consideriamo il comando Bash:
Copyecho "Hello World" | grep Hello > output.txt
Dopo la tokenizzazione, potremmo avere una lista di token come questa:

[WORD, "echo"]
[STRING, "Hello World"]
[PIPE, "|"]
[WORD, "grep"]
[WORD, "Hello"]
[REDIR_OUT, ">"]
[WORD, "output.txt"]

Questo rende molto più facile per il parser riconoscere la struttura del comando, identificando facilmente l'operatore di pipe (|) e la redirezione (>).