PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central del grupo):
	-	Acceda la página de la [Práctica 2](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.

	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual, usando el repositorio remoto en GitHub como repositorio central para el trabajo colaborativo
	de los distintos miembros del grupo de prácticas o como copia de seguridad.
	-	Puede *confirmar* versiones del proyecto en su directorio local con las órdenes siguientes:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

	-	Las versiones confirmadas, y sólo ellas, se almacenan en el repositorio y pueden ser accedidas en cualquier momento.

*	Para interactuar con el contenido remoto en GitHub es necesario que los cambios en el directorio local estén confirmados.

	-	Puede comprobar si el directorio está *limpio* (es decir, si la versión actual está confirmada) usando el comando
		`git status`.

	-	La versión actual del directorio local se sube al repositorio remoto con la orden:

		```.sh
		git push
		```

		*	Si el repositorio remoto contiene cambios no presentes en el directorio local, `git` puede negarse
			a subir el nuevo contenido.

			-	En ese caso, lo primero que deberemos hacer es incorporar los cambios presentes en el repositorio
				GitHub con la orden `git pull`.

			-	Es posible que, al hacer el `git pull` aparezcan *conflictos*; es decir, ficheros que se han modificado
				tanto en el directorio local como en el repositorio GitHub y que `git` no sabe cómo combinar.

			-	Los conflictos aparecen marcados con cadenas del estilo `>>>>`, `<<<<` y `====`. Los ficheros correspondientes
				deben ser editados para decidir qué versión preferimos conservar. Un editor avanzado, del estilo de Microsoft
				Visual Studio Code, puede resultar muy útil para localizar los conflictos y resolverlos.

			-	Tras resolver los conflictos, se ha de confirmar los cambios con `git commit` y ya estaremos en condiciones
				de subir la nueva versión a GitHub con el comando `git push`.


	-	Para bajar al directorio local el contenido del repositorio GitHub hay que ejecutar la orden:

		```.sh
		git pull
		```
	
		*	Si el repositorio local contiene cambios no presentes en el directorio remoto, `git` puede negarse a bajar
			el contenido de este último.

			-	La resolución de los posibles conflictos se realiza como se explica más arriba para
				la subida del contenido local con el comando `git push`.



*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los
elementos más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

<p align="center">
  <img src="./documentation/etiquetacion.png" alt="Labeled signal" width="800" /><br />
  Figure 1: Labeled signal
</p>

	La gráfica roja es el contorno de la potencia.
	La gráfica verde es la tasa de cruces por cero.
	La gráfica negra es la señal que hemos grabado nosotros.
	Entre las dos señales de estadísticas se puede observar la etiquetación.

- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para
	  estar seguros de que un segmento de señal se corresponde con voz.

	  Para detectar el nivel promedio de silencio, promediamos la potencia media de las primeras tramas, considerando que son silencio, y con eso obtenemos k0. A partir de aquí definiremos un margen para obtener un umbral **k1 = k0 + alpha**. En el caso particular de nuestro audio, a simple vista, definiríamos la potencia media del ruido a -70 dB aproximadamente, y con un margen de unos 20 dB, definiríamos el umbral a -50 dB.

	* Duración mínima razonable de los segmentos de voz y silencio.

	  Para definir una duración mínima razonable de los segmentos de voz y silencio, vamos a considerar que el tiempo mínimo para detectar silencio es mayor que el tiempo mínimo para detectar voz. Esto es debido a dos motivos: primero, no queremos perder ninguú fragmento de voz, y segundo, cuando hablamos hacemos pausas, estas no se pueden detectar como silencio. En canvio, cuando la potencia está por encima del umbral, en la gran mayoría de casos se trata de voz, por eso la duración mínima de voz será menor. Visualizando la gráfica, podemos definir la duración mínima para detectar la voz con unas 5 tramas, y la duración mínima para detectar silencio de unas 15 tramas.

	* ¿Es capaz de sacar alguna conclusión a partir de la evolución de la tasa de cruces por cero?

	  Sí, se puede ver que en casos de voz donde la potencia media es baja la tasa de cruces por cero es alta. Esto es debido a que en las señales de voz sordas, a diferencia de las senyales de voz sonoras, la señal no es periódica. De hecho, es prácticamente aleatoria, y por eso, la tasa de cruces por cero es tan elevada. De aquí podriamos sacar la conclusión que en casos de potencia baja y tcpc alta podremos calificar de voz.


### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal en
  tiempo real tan exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.

- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 

<p align="center">
  <img src="./documentation/labels.png" alt="Lab and Vad labels" width="800" /><br />
  Figure 2: Comparison of Lab and Vad label
</p>

Para ver estas graficas con mas precisión, se pueden encontrar en el fichero `plots.ipynb`.

```
	**************** audios.lab ****************
	Recall V:  6.38/6.40   99.74%   Precision V:  6.38/6.80   93.85%   F-score V (2)  : 98.50%
	Recall S:  3.87/4.28   90.24%   Precision S:  3.87/3.88   99.57%   F-score S (1/2): 97.55%
	===> audios.lab: 98.027%
```
*NOTA: El audio realizado por nosotros vale cero las primeras tramas, suponemos que es por algun problema en el wavesurfer. Es por eso que para nuestro audio hemos modificado el parámetro que hace la media de las primeras muestras, de 10 a 40 y la alpha de 9.9 a 20. Sabemos que esto no es lo ideal, pero entendemos que es solo por este problema en el audio.*

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

La discrepancia principal entre el etiquetado manual y la detección automática, en nuestro caso, es que la detección automática solo tiene dos decimales de precision, mientras que en el etiquetado manual hay muchos más decimales. Excepto en algunos casos la detección es casi perfecta. El caso en que hay más error es en el paso de voz a silencio de la última transición. Esto es debido a la histéresis, ya que empieza a estar en silencio antes de pasar por el umbral. Esto podría ser peligroso ya que detectaría como voz tramos de silencio en casos donde apareciese mas ruido una vez ya calculados los umbrales iniciales. Este problema se podría solucionar mediante un **cálculo de ruido adaptativo**, que no solo se calculase al inicio, sino que se vayase actualizando.

- Evalúe los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` e inserte a 
  continuación las tasas de sensibilidad (*recall*) y precisión para el conjunto de la base de datos (sólo
  el resumen).

```
	**************** Summary ****************
  	Recall V:480.51/495.55 96.97%   Precision V:480.51/508.47 94.50%   F-score V (2)  : 96.46%
	Recall S:293.21/321.17 91.29%   Precision S:293.21/308.25 95.12%   F-score S (1/2): 94.33%
	===> TOTAL: 95.391%
```

### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

En esta imagen podemos ver 4 gráficas. En las dos primeras podemos ver la potencia media de la señal original y la señal corregida. En las dos segundas se puede ver la amplitud media de la señal original y la señal corregida.

<p align="center">
  <img src="./documentation/correction.png" alt="Signal corrected" width="800" /><br />
  Figure 2: Signal corrected
</p>

En esta imagen podemos ver las medidas estadísticas de la señal corregida. Se puede observar que, efectivamente, la señal está al cero cuando considera que esta en silencio.

<p align="center">
  <img src="./documentation/correction2.png" alt="Signal corrected" width="800" /><br />
  Figure 2: Signal corrected
</p>

#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.

<p align="center">
  <img src="./documentation/help_message.png" alt="Help message" width="500" /><br />
  Figure 2: Help message
</p>


### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).

  Para la detección hemos utilizado la máquina de estados ampliada, propuesta en el documento que explica la práctica. Hemos considerado los estados *maybe voice* y *maybe silence*, además de mínimas duraciones para voz y silencio. Ademas realizamos la media de las potencias de las primeras tramas para definir los umbrales. También hemos aplicado histéresis para definir el humbral de silencio. 

  Además hemos realizado un scipt con python llamado `plots.ipynb` que nos ha permitido analizar los resultados con una buena visualización.

- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.

Hemos encontrado la práctica muy interessante, nos ha permitido entender mejor el uso de docopt_c, meson, el manejo de ficheros de texto con C y de audio con wavesurfer y soundfile.


### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.
