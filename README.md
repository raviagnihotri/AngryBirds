#AngryBirds
##Prosjektoppgaven i emnet "Effektiv kode med C og C++", 2013

###Ravi Agnihotri og Andreas Baaserud

##Introduksjon

Vi hadde et ønske om å lage noe morsomt for den siste oppgaven i emnet. Ideene var mange, men vi landet til slutt på
spillet **Angry Birds**. Spillet har blitt utrolig populært og kan spilles på en rekke plattformer, som Android, iOS og PC.
Siden ekte nerder hater GUIer, har vi valgt å portere spillet til Linux-terminalen. :)

##Teknisk bakgrunn

Spillet vil bruke **n-curses**-rammeverket for å kunne tegne grafikk i terminalvinduet på en "enkel" måte. Ingen av oss
har vært borti dette før, så bare dette er en utfordring i seg selv. Som følge av dette kan spillet kun kjøres i Linux.

Siden fuglene skal følge en bane fra sprettert til gris, må det ligge noe matematikk bak for å kalkulere banen. Vi kommer til 
å bruke matematikkbiblioteket for å kunne bruke trigonometriske formler osv.

##Omfang

Grunnet tid og kompleksitet må vi sette grenser på spillets kompleksitet. Vi har kommet på følgende avgrensninger:
- Tre hardkodede fugler med ulike parametere (vekt, flyvedyktighet, etc)
- Tre brett
- ?

Dersom programmeringen går noenlunde smertefritt, vil vi se på muligheten til å:
- opprette en egen fugl med egne parametere
- spice opp brukergrensesnittet
- implementere flere brett
- ta med andre koeffisienter i formelene som f.eks. vind





