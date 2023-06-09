Berecz Antónia – Grafika beadandó

Koncepció:
A virtuális térben szeretnék elhelyezni négy objektumot, illetve 3 objektumot és egy kerettel ellátott képet. 
A program célja, hogy a különböző objektumokkal való interaktálódás által, a felhasználó elültethessen, illetve
megnöveszthessen egy napraforgót.

1. Indítás esetén elsőkörben egy „képernyőt” szeretnék a felhasználó elé tárni.
    •	Egy kerettel ellátott képet tervezek beszúrni 
    •	A kép a későbbiekben változik majd, illetve több kép lesz ugyanarra a pozícióra beillesztve különböző időpontokban
    •	A kép (képek) egy rajzolt napraforgó növekedésének szakaszait jeleníti majd meg.
    •	Koncepcionálisan minimum 4 kép (illetve képsorozat) kerül majd beillesztésre
        o	Föld ásás nélkül
          Egy egyszerű rajzol tájkép, ahol sértetlen a talaj 
        o	Ágyás
          Megásott ágyás. Az előbb bemutatott képen megjelenik egy kisebb gödör.
          kb. 8 kép
        o	Napraforgómag
        	A napraforgómag belehullik az ágyásba.
	        kb. 20 kép
        o	Napraforgó
          A napraforgó fokozatos megnő és virágot bont.
          kb. 40 kép

2. A felhasználótól a térben három különböző irányban 3 másik objektumot szeretnék elhelyezni.
    •	Ásó
      Ezzel az eszközzel szeretném „megásni” az ágyást. 
    •	Napraforgómag
      Ezt fogjuk „elültetni”
    •	Vizes vödör
      Ennek hatására fog „megnőni” a naprafogónk.
        
3. A program működése
    •	Terv szerint, amikor a felhasználó belép a programba, egy alapmegvilágítást tapasztalhat, 
      amitől minden objektum látszik.
    •	A felhasználó körbenézhet az objektumok között.
    •	Az ásóra jóval nagyobb megvilágítás esik, ami kijelöli az objektumot.
    •	Amennyiben a felhasználó rákattint az ásó objektumra, a kamera pozíció visszatér a kiindulópontra, 
      vagyis a beépített képernyőre a tájképről és elindul az első képsorozat.
        o	A földben ágyás keletkezik.
    •	A nagyobb megvilágítás ezúttal a napraforgómagra esik.
    •	Amennyiben a felhasználó rákattint a napraforgó objektumra, a kamera ismét a képernyőt mutatja.
    •	Elindul a második képsorozat.
        o	A napraforgómag belehullik az ágyásba.
    •	A fény ezúttal a vizesvödröt világítja meg.
    •	Amennyiben a felhasználó rákattint a vizesvödör objektumra, ismét a képernyőt fogja látni.
    •	Elindul a harmadik képsorozat.
        o	A napraforgó teljesen „kifejődik”.

4. Program elemzése a követelmények tekintetében:
    •	Kamerakezelés:
      A kamera mozgása alapvetően az egér segítségével, a felhasználó által is vezérelhető lesz lesz, illetve egyes cselekvések (kattintás) hatására automatikus             automatikusan is szöget fog váltani.
    •	Objektumok
      Kép, illetve objektum is beszúrásra fog kerülni
    •	Animáció, mozgatás
      A program állapota attól függően fog változni, hogy a felhasználó rákattint-e az adott elemekre, illetve a napraforgó növekedése tulajdonképpen stop motion             megoldással fog megjelenítésre kerülni.
    •	Textúrák
      Az objektumok textúrákkal fognak rendelkezni.
    •	Fények
      A fények a kattintásoktól függően módosulni fognak, illetve az alap fénybeállításokat is állítani lehet majd a – és a + gombok használatával, adott értékeken           belül.
    •	Használati útmutató
      A felhasználó az F1 billentyű megnyomásával elérheti a súgó felületet, illetve segítséget, magyarázatot kaphat a program használatához. 
