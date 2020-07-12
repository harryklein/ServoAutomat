# Beschreibung
Bei ServoAutomat handelt es sich um eine Steuerung für einen Servo. Ein Tastendruck startet einem automatischen Ablauf. Es können mehrere Positionen hinterlegt werden, die nacheinander angefahren werden. Zusätzlich wird die zu wählende Geschwindigkeit festgelegt und die nach dem erreichen der Zielposition zu wartende Zeit. Wurden alle Positionen angefahren, so ist der Ablauf beendet und kann durch einen erneuten Tastendruck gestartet werden.

Eine Led zeigt an, ob der Ablauf gestartet werden kann.

## Programmbeschreibung

stateDiagram-v2
    [*] --> Still
    Still --> [*]