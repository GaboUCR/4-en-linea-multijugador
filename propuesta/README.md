# Funcionamiento de un Servidor Pub-Sub
El modelo de publicación-suscripción, comúnmente conocido como "pub-sub", es un patrón de mensajería en el cual los mensajes son enviados por publicadores y recibidos por suscriptores. A continuación, se presenta una descripción detallada de cómo funciona este modelo.

## Publicadores
En el modelo pub-sub, los publicadores son las entidades que generan y envían mensajes. Estos mensajes pueden contener cualquier tipo de información, y generalmente están relacionados con un tema o un tipo de evento en particular. En el contexto de un juego, un publicador podría ser una entidad que envía actualizaciones sobre el estado del juego.

## Suscriptores
Los suscriptores son las entidades que reciben los mensajes enviados por los publicadores. En lugar de recibir todos los mensajes que se envían, los suscriptores suelen "suscribirse" a los tipos específicos de mensajes que les interesan. Por ejemplo, un jugador podría suscribirse a actualizaciones sobre el estado del juego.

## Servidor
El servidor actúa como un intermediario entre los publicadores y los suscriptores. Cuando un publicador envía un mensaje, el servidor se encarga de entregar ese mensaje a todos los suscriptores que se hayan suscrito a ese tipo de mensaje.

El servidor también puede encargarse de filtrar los mensajes, de forma que cada suscriptor sólo reciba los mensajes que le interesan. Esto puede ser especialmente útil en situaciones en las que hay muchos mensajes siendo enviados, pero cada suscriptor sólo está interesado en un subconjunto de ellos.

En resumen, un servidor que sigue el modelo de publicación-suscripción facilita la comunicación eficiente entre múltiples entidades, permitiendo que los mensajes sean enviados y recibidos de forma selectiva y en tiempo real.


# Ventanas 

# Descripción de la Ventana NavBar
La ventana NavBar representa un componente esencial en la interfaz de usuario de la aplicación. Ubicada en la parte superior de la pantalla, NavBar actúa como una guía de navegación simplificada y accesible, permitiendo a los usuarios desplazarse con facilidad entre las distintas secciones del juego.

## Estructura de la Ventana NavBar
La ventana NavBar se compone de varios widgets internos, cada uno de ellos diseñado para realizar una función específica de navegación. A continuación, se presenta una descripción detallada de estos widgets:

### Logo del Juego
Este widget está posicionado a la izquierda de la NavBar. Al hacer clic en él, los usuarios son redirigidos a la pestaña principal de la aplicación. Aquí, pueden seleccionar una mesa para comenzar a jugar con otros jugadores.

### Reproducción de Partidas Anteriores
El siguiente widget en la NavBar permite a los usuarios acceder a una página que almacena sus partidas anteriores. Al hacer clic en este widget, los usuarios pueden revisar y reproducir partidas pasadas, lo que puede ser útil para analizar estrategias de juego y mejorar su desempeño.

### Información de la Cuenta del Usuario
El último widget en la NavBar dirige a los usuarios a una página donde pueden revisar y actualizar la información de su cuenta.

En resumen, la ventana NavBar funciona como un centro de navegación centralizado en la aplicación, mejorando la usabilidad y proporcionando un fácil acceso a las funciones más importantes del juego.


# Descripción de la Ventana NavBarU
La ventana NavBarU es otro componente crítico de la interfaz de usuario de la aplicación. Similar a NavBar, esta también está ubicada en la parte superior de la pantalla, pero se enfoca en proporcionar funcionalidades de autenticación y registro al usuario.

## Estructura de la Ventana NavBarU
La ventana NavBarU contiene dos widgets principales, cada uno de ellos diseñado para ofrecer una funcionalidad específica relacionada con el acceso y la creación de la cuenta del usuario. A continuación, se describe cada uno de estos widgets:

### Log In
El primer widget en la NavBarU está etiquetado como "Log In". Cuando se hace clic en este widget, se lleva a los usuarios a una pantalla donde pueden ingresar las credenciales de su cuenta para autenticarse y acceder a su perfil en el juego. Este paso es esencial para que los usuarios puedan guardar su progreso y personalizar su perfil.

### Sign In
El segundo widget en la NavBarU está etiquetado como "Sign In". Al hacer clic en este widget, los usuarios son dirigidos a una pantalla donde pueden crear una nueva cuenta en el sistema del juego. Esto incluye proporcionar nombre de usuario y contraseña.

En resumen, la ventana NavBarU desempeña un papel crucial en el manejo de la autenticación del usuario y la creación de cuentas. Con su diseño sencillo y accesible, ofrece a los usuarios una forma clara y fácil de ingresar y registrarse en el sistema del juego.

# Descripción de la Ventana Log In
La ventana "Log In" es una parte integral del proceso de autenticación de usuario en la aplicación. Esta ventana aparece cuando el usuario selecciona el widget "Log In" en la NavBarU.

## Estructura de la Ventana Log In
Esta ventana consiste en un formulario sencillo que solicita información necesaria para autenticarse en el sistema del juego. Los detalles requeridos en este formulario son:

Nombre de Usuario
El primer campo del formulario "Log In" es para el nombre de usuario. Los usuarios deben introducir el nombre de usuario con el que se registraron en el sistema del juego.

Contraseña
El segundo campo en el formulario es para la contraseña. Los usuarios deben ingresar la contraseña asociada a su nombre de usuario.

Una vez que los usuarios proporcionan esta información y seleccionan el botón de "Log In", la aplicación autentica al usuario y permite el acceso al sistema del juego.

# Descripción de la Ventana Sign In
La ventana "Sign In" es la interfaz a través de la cual los nuevos usuarios pueden crear una cuenta en el sistema del juego. Esta ventana se activa cuando el usuario selecciona el widget "Sign In" en la NavBarU.

## Estructura de la Ventana Sign In
La ventana "Sign In" también incluye un formulario que requiere la información necesaria para crear una nueva cuenta en el sistema del juego. Los detalles solicitados en este formulario incluyen:

Nombre de Usuario
El primer campo del formulario "Sign In" es para el nombre de usuario. Los usuarios deben introducir el nombre de usuario que desean utilizar en el sistema del juego.

Contraseña
El segundo campo en el formulario es para la contraseña. Los usuarios deben ingresar una contraseña que será asociada a su cuenta.

Después de que los usuarios completan esta información y seleccionan el botón de "Sign In", la aplicación crea una nueva cuenta para el usuario, permitiendo su acceso y uso del sistema del juego.

# Descripción de la Ventana Mesa
La ventana "Mesa" es un componente crítico de la aplicación que permite a los usuarios iniciar partidas con otros jugadores. Al seleccionar el widget del logo del juego en la ventana "NavBar" aparecen 20 ventanas Mesa.

![Capture](https://github.com/GaboUCR/4-en-linea-multijugador/assets/69367406/c6a6354e-af5d-4d88-ac20-80db9fafea3a)

## Estructura de la Ventana Mesa
La ventana "Mesa" consiste en veinte mesas individuales, cada una representada con su número correspondiente. Cada mesa incluye un widget interactivo que permite a los usuarios unirse a la mesa para jugar una partida.

## Unirse a la Mesa
Cada mesa incluye un widget donde, al hacer clic, el nombre del usuario se visualiza y se marca un checkbox. Esto indica que el usuario se ha unido a la mesa y está listo para jugar.

## Inicio de la Partida
Cuando dos usuarios han hecho clic en el widget de la misma mesa, se considera que ambos jugadores están listos y la partida comienza.

En resumen, la ventana "Mesa" es una interfaz interactiva que facilita el inicio de las partidas entre usuarios. Con su diseño claro y su fácil navegación, ofrece a los usuarios una manera sencilla y rápida de unirse a una partida y empezar a jugar.

# Descripción de la Ventana Juego
La ventana "Juego" es el corazón de la aplicación, donde ocurre la interacción principal con el usuario. En esta ventana, los jugadores interactúan con el tablero del juego para realizar sus movimientos.

## Estructura de la Ventana Juego
La ventana "Juego" consiste en un tablero interactivo que permite a los usuarios colocar sus fichas al hacer clic en la posición deseada.

### Tablero de Juego
El tablero de juego está diseñado de manera que los usuarios pueden hacer clic en la posición en la que desean colocar su ficha. Cada vez que un usuario hace clic en una posición, su ficha se coloca allí, y el turno pasa al siguiente jugador.

En resumen, la ventana "Juego" proporciona la interfaz esencial para la interacción del juego, permitiendo a los usuarios colocar sus fichas y jugar la partida.

# Descripción de la Ventana Jugadores
La ventana "Jugadores" está ubicada en la parte superior de la pantalla y proporciona información relevante sobre la partida en curso.

## Estructura de la Ventana Jugadores
La ventana "Jugadores" muestra el número de la mesa en la que se está jugando y los nombres de los dos jugadores participantes. Además, incluye un indicador de turno para cada jugador.

### Número de Mesa
La ventana "Jugadores" muestra el número de la mesa en la que se está jugando la partida. Esto ayuda a los jugadores a identificar su partida actual.

### Información de los Jugadores
La ventana también muestra los nombres de los dos jugadores. Junto a cada nombre, hay un checkbox que se marca para indicar de quién es el turno actual.

En resumen, la ventana "Jugadores" proporciona una visión general clara y rápida de la partida en curso, incluyendo quién está jugando y de quién es el turno actual.

![Capture](https://github.com/GaboUCR/4-en-linea-multijugador/assets/69367406/ea8f35b5-e00f-4afa-97e0-86662491e535)

# Descripción de la Ventana Partidas
La ventana "Partidas" es una sección de la aplicación dedicada a almacenar y mostrar las partidas que los usuarios han jugado anteriormente. Los usuarios pueden acceder a esta ventana seleccionando el widget de partidas anteriores en la ventana "NavBar".

## Estructura de la Ventana Partidas
La ventana "Partidas" muestra una lista de partidas previas, cada una de ellas con información detallada sobre la partida, incluyendo el número de la partida, los nombres de los jugadores y el resultado de la partida.

### Número de Partida
Cada partida está identificada por un número único, que ayuda a los usuarios a identificar y recordar partidas específicas.

### Nombres de los Jugadores
Los nombres de los dos jugadores que participaron en la partida se muestran para cada partida. Esto permite a los usuarios ver con quién jugaron en partidas anteriores.

### Resultado de la Partida
Un checkbox junto a los nombres de los jugadores indica quién ganó la partida. Esto proporciona a los usuarios una forma rápida y clara de ver el resultado de cada partida.

### Botón de visualizar
Un botón que abre una pestaña nueva hacia la ventana de visualización que se detalla más adelante

En resumen, la ventana "Partidas" es una herramienta útil que permite a los usuarios revisar sus partidas anteriores, recordar contra quién jugaron y ver los resultados de sus juegos. Esta ventana mejora la experiencia del usuario al permitirle seguir su progreso y analizar sus partidas anteriores.


![Capture](https://github.com/GaboUCR/4-en-linea-multijugador/assets/69367406/6feda4e4-98b6-41e0-bfda-cbb0917c15c7)

# Descripción de la Ventana Cuenta
La ventana "Cuenta" ofrece a los usuarios un resumen personalizado de su perfil dentro de la aplicación. Incluye información como el nombre de usuario y la cantidad de partidas ganadas.

## Estructura de la Ventana Cuenta
La ventana "Cuenta" se organiza en varias secciones para presentar de forma clara y concisa la información del perfil del usuario.

### Nombre de Usuario
Esta sección muestra el nombre de usuario del perfil. Este es el nombre que los demás usuarios ven durante las partidas y en la lista de partidas pasadas.

### Partidas Ganadas
Esta sección enseña el número de partidas ganadas.

# Descripción de la Ventana Visualización
La ventana "Visualización" ofrece a los usuarios una forma de revisar y analizar partidas jugadas anteriormente. Es similar a la ventana "Juego" en términos de estructura, pero incluye widgets adicionales para controlar la reproducción de la partida.

## Estructura de la Ventana Visualización
La ventana "Visualización" muestra un tablero de juego, idéntico al de la ventana "Juego", y tiene un widget para avanzar y retroceder entre las jugadas.

### Tablero de Juego
Como en la ventana "Juego", la ventana "Visualización" presenta un tablero de juego donde se muestran las posiciones de las fichas de los jugadores tal como estaban durante la partida.

### Avanzar y Retroceder Jugadas
Dos widgets con forma de flecha permiten a los usuarios avanzar y retroceder en el tiempo a través de las jugadas de la partida. La flecha hacia adelante mueve al usuario a la siguiente jugada, mientras que la flecha hacia atrás lo lleva a la jugada anterior.

En resumen, la ventana "Visualización" ofrece a los usuarios una forma de revisar y analizar partidas pasadas, proporcionando una herramienta para entender mejor las estrategias utilizadas y mejorar sus habilidades de juego.

![Capture](https://github.com/GaboUCR/4-en-linea-multijugador/assets/69367406/23ef3095-f4f1-4773-b536-86093c218843)

# Funcionamiento de las Ventanas en el Modelo Pub-Sub
El juego propuesto involucra varias ventanas interactivas que necesitan actualizarse en tiempo real según las acciones de los jugadores. Esto se realiza a través de un servidor que sigue el modelo de publicación-suscripción (pub-sub). A continuación, se describen los detalles de este proceso.

## Ventana 'Mesa'
La ventana 'Mesa' incluye dos widgets que cambian de estado cuando un jugador hace clic en ellos. Específicamente, al hacer clic en un widget, se muestra el nombre del jugador y se marca una casilla de verificación para indicar que el jugador desea participar en el juego.

## Actualización de la ventana 'Mesa'
Cuando un jugador interactúa con los widgets en la ventana 'Mesa', el servidor es informado de este cambio. En respuesta, el servidor publica una actualización a todos los clientes suscritos, informándoles del cambio de estado. De esta forma, todos los jugadores son informados de las acciones de los demás.

## Ventana 'Juego'
La ventana 'Juego' incluye un tablero de juego que debe ser actualizado cada vez que un jugador hace una jugada.

## Actualización de la ventana 'Juego'
Al igual que con la ventana 'Mesa', cuando un jugador realiza una jugada, el servidor es informado de esta acción. El servidor entonces publica una actualización a todos los clientes suscritos, permitiendo que todos los jugadores vean la jugada en tiempo real.

## Ventana 'Jugadores'
La ventana 'Jugadores' opera de una manera similar a las ventanas 'Mesa' y 'Juego'. Los cambios de estado en esta ventana también son comunicados al servidor, que a su vez los publica a todos los clientes suscritos.

En resumen, el uso del modelo pub-sub permite que las ventanas del juego sean actualizadas en tiempo real, manteniendo a todos los jugadores sincronizados con el estado actual del juego.
