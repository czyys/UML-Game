###### [PL]
# Aplikacja czasu rzeczywistego - Aircraft Fighter

## Zasady gry:
- Gra dwuosobowa, 2D, "z lotu ptaka"
- Gracz kontroluje statek
- Celem jest zniszczenie statku drugiego gracza

## Użyte technologie:
- Oxygine Framework 

## Skład zespołu:
- Kamil Armatys
- Wiktor Gryboś
- Wojciech Juszczak
- Cezary Sławecki (C)
- Vlad Udovychenko

## Link do aplikacji w wersji release:
[Download](https://www.dropbox.com/s/q0z11bg47ki8qd3/AircraftFighter.zip?dl=1)

## Instrukcja uzyskania aplikacji w wersji "release":
1. Skompilować cały projekt **(Build Solution)** wybierając opcję **Release** z **Solution Configurations**.
2. Wygenerowany plik **aircraft.exe** z folderu **proj.win32\Release_v140** przekopiować do folderu **data**.
3. W folderze tym znajdują się wszystkie pliki wymagane do uruchomienia gry.

Do poprawnego skompilowania projektu wymagane jest posiadanie frameworku **Oxygine** w wersji podanej poniżej:
[Dropbox download](https://dl.dropboxusercontent.com/u/70268100/oxygine-framework-with-sdl.zip)

Repozytorium **UML-Game** należy umieścić w folderze **oxygine-framework-with-sdl**

##Diagramy
- [Activity diagram](https://raw.githubusercontent.com/czyys/UML-Game/master/diagrams/Activity%20Diagram.png)
- [Class diagram](https://raw.githubusercontent.com/czyys/UML-Game/master/diagrams/Class%20Diagram.png)
- [Use case diagram](https://raw.githubusercontent.com/czyys/UML-Game/master/diagrams/Use%20case%20diagram.png)


##Informacja:
Dane na branchu **audio** nie są w ostatecznej formie, dlatego nie są zmergowane z masterem.

##Troubleshooting
```
aircraft.exe" is not responding
```
Ten błąd występuje w przypadku niewłaściwie utworzonych folderów. Żeby go rozwiązać należy zmienić nazwę folderu z danymi gry na **data** . Struktura folderów powinna wyglądać w następujący sposób:
```
Parent folder
    |
    |-data
       |
       |-data-ram
       |-fonts
       |-ui.xml.ox
       |-xmls
       |-aircraft.exe
       |-...
```




###### [EN]
# Real-time application - Aircraft Fighter

## Game rules:
- Two-Person 2D game 
- Payer controls an aircraft
- Game idea is to destroy a plane of another player

## Technologies used:
- Oxygine Framework 

## Our team:
- Kamil Armatys
- Wiktor Gryboś
- Wojciech Juszczak
- Cezary Sławecki (C)
- Vlad Udovychenko

## Link to the application (release version):
[Download](https://www.dropbox.com/s/q0z11bg47ki8qd3/AircraftFighter.zip?dl=1)

## Tutorial how to get an application in "release" version:
1. Compile whole project **(Build Solution)** by choosing **Release** from **Solution Configurations**.
2. Copy generated **aircraft.exe** file from **proj.win32\Release_v140** folder to **data** folder.
3. This folder contains all required files to start the game.

## Required project files:
To compile this project you must download **Oxygine Framework**:
[Dropbox download](https://dl.dropboxusercontent.com/u/70268100/oxygine-framework-with-sdl.zip)

Repository **UML-Game** must be placed in **oxygine-framework-with-sdl** folder.

##Diagrams
- [Activity diagram](https://raw.githubusercontent.com/czyys/UML-Game/master/diagrams/Activity%20Diagram.png)
- [Class diagram](https://raw.githubusercontent.com/czyys/UML-Game/master/diagrams/Class%20Diagram.png)
- [Use case diagram](https://raw.githubusercontent.com/czyys/UML-Game/master/diagrams/Use%20case%20diagram.png)

##Information:
**audio** branch is not merged to **master** branch (temporary not working).

##Troubleshooting
```
aircraft.exe" is not responding
```
This error appears when you have wrong game folders structure. To resolve this error rename you game folder to **data**.
Structure must looks like this:
```
Parent folder
    |
    |-data
       |
       |-data-ram
       |-fonts
       |-ui.xml.ox
       |-xmls
       |-aircraft.exe
       |-...
```

