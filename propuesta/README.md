# Descripción de la Ventana NavBar
La ventana NavBar representa un componente esencial en la interfaz de usuario de la aplicación. Ubicada en la parte superior de la pantalla, NavBar actúa como una guía de navegación simplificada y accesible, permitiendo a los usuarios desplazarse con facilidad entre las distintas secciones del juego.

## Estructura de la Ventana NavBar
La ventana NavBar se compone de varios widgets internos, cada uno de ellos diseñado para realizar una función específica de navegación. A continuación, se presenta una descripción detallada de estos widgets:

### Logo del Juego
Este widget está posicionado a la izquierda de la NavBar. Al hacer clic en él, los usuarios son redirigidos a la pestaña principal de la aplicación. Aquí, pueden seleccionar una mesa para comenzar a jugar con otros jugadores.

### Reproducción de Partidas Anteriores
El siguiente widget en la NavBar permite a los usuarios acceder a una página que almacena sus partidas anteriores. Al hacer clic en este widget, los usuarios pueden revisar y reproducir partidas pasadas, lo que puede ser útil para analizar estrategias de juego y mejorar su desempeño.

### Compra de Íconos
El tercer widget en la NavBar lleva a los usuarios a una sección especial donde pueden "comprar" íconos para personalizar su perfil. Estos íconos se pueden adquirir con una moneda ficticia, lo que añade un elemento adicional de interacción y personalización a la experiencia de juego.

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

