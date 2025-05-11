# Reflektor pinout V2

## Peryferia

- silnik krokowy osi pan + sterownik
- silnik krokowy osi tilt + sterownik
- krańcówki osi

- oświetlenie LED RGB

- potencjometr ✔️
- przycisk 1
- przycisk 2

## Dostępne piny

- D0 - GPIO16 - in/out ✔️
- D1 - GPIO5 - in/PWM ✔️
- D2 - GPIO4 - in/PWM ✔️
- D3 - GPIO0 - in/PWM (pulled up) ✔️
- D4 - GPIO2 - in/PWM (pulled up) ✔️
- D5 - GPIO14 - in/PWM ✔️
- D6 - GPIO12 - in/PWM ✔️
- D7 - GPIO13 - in/PWM ✔️
- D8 - GPIO15 - in/PWM (pulled down) (fails if HIGH) ✔️
- RX - GPIO3 - in ✔️
- TX - GPIO1 - PWM (fails if LOW) ❌
- A0 - ADC0 - in (analog input) ✔️

# Piny i ich funkcje

- D0 - wspólny pin kierunku silników krokowych
- D1 - silnik krokowy osi pan - krok
- D2 - silnik krokowy osi tilt - krok

- D3 - krańcówka osi pan (zwierać z VCC)
- D4 - krańcówka osi tilt (zwierać z VCC)

- D5 - kolor czerwony
- D6 - kolor zielony
- D7 - kolor niebieski

- A0 - potencjometr
- D8 - przycisk1 (zwierać z VCC) (nie trzymać przy uruchamianiu)
- RX - przycisk2 (podciągnąć do GND, zwierać z VCC)

# Sekcje sterowników

## Sterownik wejść

- przycisk 1 (D8)
- przycisk 2 (RX)
- potencjometr (A0)
- krańcówka osi tilt (D4)

## Sterownik silników

- krok silnika osi pan (D1)
- krok silnika osi tilt (D2)
- kierunek silników (D0)

## Sterownik oświetlenia

- kolor czerwony (D5)
- kolor zielony (D6)
- kolor niebieski (D7)
