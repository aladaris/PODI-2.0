# PODI 2.0

Controlador MIDI diseñado para interactuar con el [P.O.D 2.0](http://line6.com/pod20/) de Line 6.
Se trata de una "caja" con una entrada para un "FootSwitch" de dos botones, que se utilizará para controlarla. También dispone de dos conexiones MIDI (in/out) para interactuar con el P.O.D.
La idea detrás de este desarrollo es poder controlar el susodicho P.O.D 2.0 mediante un "FootSwitch" sin necesidad de soltar la guitarra.

* **Versión 1.0**
  * Mediante los botones del FootSwitch se pueden recorrer los programas del P.O.D secuencialmente (UP/DOWN).
  * Cada botón del FootSwitch tiene asignada una función extra (Modo Afinación y Modo Manual) que se activa dejando pulsado el correspondiente botón durante un tiempo.
  * Hay comunicación continua con el P.O.D (tanto se envían como se reciben comandos MIDI), de manera que los dispositivos estén siempre coordinados.
  * Se almacena en la memoria EEPROM, del microcontrolador PIC, el canal actual y dicha información se mantiene aunque se apague el dispositivo.

* **Futuras versiones**
  * Se pretende implementar la posibilidad de moverse secuencialmente entre los distintos efectos y emulaciones de amplificadores de las que dispone el P.O.D; todo ello sin necesitar de otro FootSwitch o uno con más pulsadores.