![ESPink top](https://github.com/LaskaKit/ESPink/blob/main/img/ESPink_pinout.JPG)

# ESPink - univerzální a velmi úsporná deska s ESP32 pro ePaper

[ePaper displeje](https://www.laskakit.cz/e-ink/) nabírají neuřitelné popularity a není divu. Především velmi nízký odběr a široký pozorovací úhel dělá ePaper tak populárním. 
Ale čím tento displej řídit? Proto jsme navrhli ESPink. Velká paměť, nízký odběr, snadné připojení I2C čidel a velká komunita bastlířů okolo ESP32.

Na desce samozřejmě najdeš konektor pro ePaper displeje. Někdy nazvaný také Eink. Displej sám o sobě je velmi úsporný, ale stejně i mimo fázi přepisu odebírá nějaké ty uA. 
I takovému odběru jsme chtěli zamezit a tak jsme do napájení přidali tranzistor, který napájení spíná. Tento tranzistor je připojen na GPIO2 a napájení ePaperu je připojeno, pokud se GPIO2 nastaví do HIGH. Stejným GPIO pinem (GPIO2) se spíná i napětí pro I2C čidla na uŠup konektoru.

Nízká spotřeba je dosažena i tím, že jsme použili programátor, který je sám o sobě velmi úsporný a tak jeho osazení na desce nepřinese o mnoho vyšší spotřebu.

Deska může být napájena z [lipol akumulátoru](https://www.laskakit.cz/baterie-a-akumulatory/) a ten je nabíjen z USB-C konektoru. 
Samozřejmě můžeš měřit i napětí na akumulátoru díky integrovanému děliči napětí a přivedeného na GPIO34.

Připojení čidel nebylo nikdy snažší a bezpečnější. Žádná nefungující čidla způsobená přepolováním. Díky našemu I2C μŠup konektoru, který obsahuje i zámek čidla jednoduše připojíš. 
Mezi taková čidla s μŠup konektorem patří [LaskaKit SHT40 Senzor teploty a vlhkosti vzduchu ](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) nebo  [LaskaKit SCD41 Senzor CO2, teploty a vlhkosti vzduchu ](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/).
Na desce je i SPI μŠup konektor, který může být použit například pro připojení naší desky nazvané microSD reader. 

K dispozici je i spousta GPIO, na které si můžeš zapájet, co budeš potřebovat.

![ESPink top](https://github.com/LaskaKit/ESPink/blob/main/img/ESPink_back_popis.JPG)

Dali jsme si záležet i na takových detailech, jako jsou například označené GPIO, které deska využívá. Na zadní straně se ještě nachází pájecí most, který určuje nabíjecí proud. 
Ve vychozím nastavení je nastaveno 400mA. Pokud chceš nabíjet 260mA, je nutné proškrábnout most a zapájet jej na druhé straně. 

ESPink najdeš na našem e-shopu https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
A několik vzorových kódu i na našem githubu https://github.com/LaskaKit/ESPink/tree/main/SW
