# Laboratorio I - Sistemas Operativos I

## Consigna
>Instalar alguna distribución del sistema operativo Linux de manera nativa o en una máquina virtual, y documentar el procedimiento y resultado final.

## Desarrollo

Antes que nada, comencé por revisar las especificaciones de almacenamiento, memoria y procesamiento en mi computadora principal, las cuales son:

**Memoria RAM:**
- 16[GB] DDR4 @ 3200[MHz]

**Almacenamiento:**
- 1[TB] HDD SATAIII @ 7200[RPM] (x1)
- 500[GB] SSD SATAIII (x1)
- 500[GB] SSD NVMe M.2 (x1)

**Procesador:**
- AMD Ryzen 5 3600 @ 3.6[GHz]
 
### > ¿Dónde instalarlo?
Teniendo en cuenta que la unidad SSD NVMe M.2 la tengo con Windows para ocio principalmente (videojuegos), el HDD lo tengo para backups y archivos consultados con menor frecuencia (fotos, videos) y la SSD SATAIII la tengo para programas secundarios que no requieran una velocidad de ejecución demasiado alta ni consuman tantos recursos del sistema, opté por instalar el nuevo sistema operativo allí, en la SSD SATAIII.

### > ¿Cuál distribución elegí?
Luego de revisar varias reseñas sobre las distintas distribuciones de Linux (y basándome en mi experiencia de haber cursado gran parte de esta materia el año pasado), llegué a la conclusión de que la distribución que mejor se adapta a mis necesidades es ***Linux Mint***. Procedí a descargar desde la página oficial la última versión del OS: **Linux Mint 20.2 "Uma", Cinnamon** y prepararlo para instalar en mi unidad USB Kingston de 8[GB]con el software libre, gratuito y opensource de creación de unidades USB booteables: **Universal USB Installer**.

### > Particionando las unidades
Cabe resaltar que para evitar problemas, seguí un video tutorial sobre una instalación en modo dual-boot teniendo Windows previamente instalado para realizar las particiones correctamente.
Comencé particionando la unidad SSD objetivo reservando aproximadamente 150[GB] de espacio para Linux Mint.

### > Instalando el nuevo OS
Luego, con el pendrive booteable conectado a un puerto USB 3.0, reinicié la PC y accedí a la BIOS para cambiar el orden de booteo, poniendo en primer lugar a este pendrive.
Entre las opciones que aparecieron en un menú similar al de GRUB, seleccioné aquella que sirve para probar el sistema operativo desde el pendrive sin necesidad de instalarlo *(Start Linux Mint 20.2 Cinnamon 64-bit)*. Esto lo hice para probar que reconozca las dos pantallas que tengo, los periféricos y demás cosas. Cuando confirmé que no hubo problemas, cliqueé la opción de instalar el sistema operativo. Aquí asigné a la ruta **/** un total de 15[GB], al área de intercambio (swap) le asigné 8[GB] (la mitad de la cantidad de memoria RAM del sistema, según recomendación de varios tutoriales y blogs), y el resto de espacio quedó para **/home** (poco más de 120[GB]).
Previamente seguí las instrucciones de instalación que son bastante intuitivas y sencillas, configurando periféricos, fecha y hora, ubicación, etcétera.

### > Configurando el nuevo OS
Luego de la instalación, procedí a revisar las actualizaciones del sistema que figuraban pendientes con el gestor de actualizaciones y el gestor de controladores.
Seteé un fondo de pantalla, configuré el panel de aplicaciones, seteé temas y colores de mi agrado y procedí a instalar los programas que más uso, como Git, Discord, VSCode, Slack, Spotify, Whatsapp Desktop, OpenRGB, VLC, y demás. Afortunadamente soy un usuario desde siempre de softwares preinstalados en Linux como son el paquete de LibreOffice, Mozilla Firefox, TuxGuitar (este último venía con Huayra y Windows en las netbooks entregadas por el gobierno en 2011-2012), entre otros.
Además, configuré para que la pantalla de selección de sistema operativo (GRUB) dure un poco más de 10[s] para evitar entrar nuevamente a Linux accidentalmente cuando reinicio para pasar a Windows.

### > Algunos problemas
Lamentablemente la instalación no estuvo exenta de problemas/complicaciones, pero afortunadamente no fueron graves ni nada similar.
- La primer complicación que encontré fue que el menú de GRUB no aparecía al iniciar/reiniciar el sistema. La PC booteaba directamente en Windows. Para arreglar esto, entré a la BIOS del sistema y en las prioridades de booteo vi que **Windows Boot Manager** figuraba primero en la lista, y en segunda posición figuraba **ubuntu**, y recordé que GRUB no fue instalado en la misma SSD que Windows, por lo que no se ejecutaba al inicar/reiniciar el sistema. Cambiando el orden de los mismos el problema se solucionó sin complicaciones.
- Otra complicación que tuve fue sobre las velocidades de internet. En mi casa tengo contratado un servicio de 100 megas (cableado) con WiFi a 2.4[GHz] y 5.8[GHz], pero como no tengo la PC cerca del módem cuento con una placa de red comprada hace tiempo que me sirve para conectarme a la red de 2.4[GHz] (menor velocidad de internet pero mejor alcance). En Windows, las velocidades de descarga promedio llegaban a 30[MB/s] aproximadamente; aveces más, aveces menos. En Linux, las velocidades de descarga eran demasiado bajas: 6[KB/s], picos de 300[KB/s], un caso extremo fue de 145[B/s] (sí, bytes por segundo, ni siquiera kilobytes). Adjunto captura de pantalla: ![captura2](https://user-images.githubusercontent.com/66426042/128896774-2af9a99b-37ea-4889-be4d-542e71b6ec2a.png). Estas velocidades tan bajas se daban en clases virtuales, abriendo cualquier página web y descargando actualizaciones del sistema. Pensé que era un tema de drivers porque el problema persistió por un día entero luego de probar reconectarme a la red, reiniciar el módem, reiniciar el OS... pero el gestor de controladores no mostraba ninguna actualización pendiente. Me dijeron que sería probable que el sistema estuviese descargando algunas cosas en segundo plano pero no encontré mucho al respecto que consumiera tanto internet. Luego de probar varias cosas sin éxito, las velocidades se restablecieron solas y no he tenido más problemas de internet en Linux. Sospecho que algún proceso estaba descargando algo en segundo plano como me sugirieron que podría ser.
- Otra cosa que se me complicó fue setear todo correctamente en VSCode para programar en Java y C/C++, que son los lenguajes que más manejo. Fue relativamente "complicado" porque la instalación del OpenJDK en Windows y en Linux es bastante distinta (en Windows uno le hace doble click a un archivo .exe y problema resuelto, en Linux uno se enfrenta generalmente a archivos .deb y .tar.gz por primera vez y no sabe bien cómo tratarlos ni qué son). Con ayuda de blogs y algunos tutoriales sencillos y cortos, la configuración del entorno para programar en dichos lenguajes se realizó con éxito y no hubo problemas.
- Finalmente, menciono que, lamentablemente, hay programas para Windows que no tienen su equivalente en Linux aún; por ejemplo, MPLAB y Proteus para programar PICs en assembly y simular su funcionamiento (o quizás su alternativa aún no la he encontrado), pero no es un problema porque aún conservo Windows en la otra SSD y esto me permite trabajar en ello sin problemas al alcance de un reinicio de PC.

### > Conclusión
La instalación de manera nativa es más cómoda y rápida que en una máquina virtual. Es un OS muy ligero, rápido y cómodo para trabajar en todo tipo de cosas. La idea de trabajar con software libre, gratuito y open source es algo que me fascina y de a poco voy reemplazando el software pago o por suscripción por sus alternativas libres y gratuitas que son tanto o más poderosas que las mismas. Uno siente un control mucho mayor sobre qué sucede en el sistema.
Finalmente, si bien hay que saber manejar la terminal, sus comandos y las cuestiones de bajo nivel del sistema para considerarse alquien que ***sabe*** manejar Linux, sigue habiendo muchas herramientas user-friendly que podrían servir para que cada vez más gente con poca experiencia en computación se sienta cómoda con esta gran alternativa al ya conocido Windows.

### > Capturas de pantalla
A continuación adjunto algunas capturas de pantalla del sistema operativo corriendo de manera nativa en modo dual-boot.

![captura6](https://user-images.githubusercontent.com/66426042/128896754-94c1ed39-3293-4e5c-94a3-c7120c00668f.png)
![captura5](https://user-images.githubusercontent.com/66426042/128896764-ad24821a-d3df-4fc0-bc07-5bd27709bb82.png)
![captura4](https://user-images.githubusercontent.com/66426042/128896766-fb04dcda-13be-44d9-b466-35a1ca9f6736.png)
![captura3](https://user-images.githubusercontent.com/66426042/128896771-c7c7869d-8292-4aba-80fc-f2725b2f0c59.png)
![captura1](https://user-images.githubusercontent.com/66426042/128896777-8f044323-2a09-4089-9b5c-8b035dbd3190.png)

