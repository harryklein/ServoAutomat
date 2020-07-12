# Beschreibung
Bei ServoAutomat handelt es sich um eine Steuerung für einen Servo. Ein Tastendruck startet einem automatischen Ablauf. Es können mehrere Positionen hinterlegt werden, die nacheinander angefahren werden. Zusätzlich wird die zu wählende Geschwindigkeit festgelegt und die nach dem erreichen der Zielposition zu wartende Zeit. Wurden alle Positionen angefahren, so ist der Ablauf beendet und kann durch einen erneuten Tastendruck gestartet werden.

Eine Led zeigt an, ob der Ablauf gestartet werden kann.

## Programmbeschreibung
```
 +----------------------------------------------------+
 |                                                    |
 +-> START --> WAIT --> DELAY --> NEXT --+ --> STOP --+
      |                                 |
      +---------------------------------+
 ```
 * START
   * Setzt die neue Position und die gewüschte Geschwindigkeit 
   * Setzt den nächsten Status WAIT
 * WAIT
   * Wartet auf das Erreichen der Endposition.
   * Wenn die Endposition erreicht ist: nächster Status DELAY
 * DELAY
   * Warte die eingestellte Zeit
   * Wenn die Zeit verstrichen ist: nächster Status NEXT
 * NEXT
   * Wält den nächsten Schritt aus. nächster Status START 
   * Gibt es keinen weiteren Schritt: Status STOP
 * STOP
   * wird verlassen durch Tastendruck, es folgt Status START