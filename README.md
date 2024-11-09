Autores:

Brayan Israel Lira Gutiérrez bi.liragutierrez@ugto.mx

Ponce Ruiz Angel Mario am.ponceruiz@ugto.mx

Jorge Andrés Jiménez Salazar ja.jimenez.salazar@ugto.mx

Eduardo Ramírez de la Fuente e.ramirezdelafuente@ugto.mx

Profesor: Huetzin Aaron Pérez Olivas

Descripción del proyecto:

En esta práctica se explorará el uso de la tecnología Bluetooth Low Energy (BLE) en 
conjunto con un ESP32 para la lectura de un potenciómetro y el control de un LED. El 
objetivo principal es utilizar el ESP32 para leer los valores analógicos del potenciómetro, 
convertirlos a voltaje y visualizarlos en el monitor serial y a través de la aplicación nRF 
Connect. Adicionalmente, se implementarán funciones de control del LED mediante 
comandos seriales y comunicación BLE.

Introducción

La función Bluetooth es una tecnología de comunicación inalámbrica que puede ser usada para transmisión de datos de corto alcance de un dispositivo digital a otro. Bluetooth es esencialmente una conexión inalámbrica uno a uno que usa ondas de radio de banda de 2,4 GHz.

Bluetooth Low Energy (BLE) en el ESP32

El Bluetooth Low Energy (BLE) en el ESP32 es una tecnología revolucionaria que ha transformado la manera en que los dispositivos se comunican entre sí. Diseñado para aplicaciones que requieren un consumo de energía extremadamente bajo, BLE permite la transmisión eficiente de datos en dispositivos como wearables, sensores de salud, sistemas de automatización del hogar y más. El ESP32, con su capacidad de actuar tanto como servidor como cliente BLE, ofrece una flexibilidad impresionante para desarrolladores y entusiastas de la tecnología. Esta tecnología no solo mejora la eficiencia energética, sino que también proporciona una comunicación segura y confiable, haciendo posible una amplia gama de aplicaciones innovadoras en el mundo de la Internet de las Cosas (IoT).

nRF Connect

La aplicación nRF Connect es una herramienta poderosa y versátil diseñada para interactuar con dispositivos Bluetooth Low Energy (BLE). Desarrollada por Nordic Semiconductor, esta aplicación permite a los usuarios escanear, publicitar y explorar dispositivos BLE, así como comunicarse con ellos de manera eficiente. nRF Connect es compatible con varios perfiles adoptados por Bluetooth SIG y ofrece funcionalidades avanzadas como la actualización de firmware del dispositivo (DFU), análisis de datos publicitarios, y la configuración del servidor GATT. Además, la aplicación es ideal para desarrolladores y entusiastas que buscan una solución robusta para probar y desarrollar aplicaciones BLE en dispositivos móviles.

Potenciómetro

Un potenciómetro es un componente esencial en el mundo de la electrónica, conocido por su capacidad para ajustar niveles de voltaje en un circuito de manera precisa y manual. Este dispositivo, que funciona como un resistor variable, permite controlar la cantidad de corriente que fluye a través de un circuito, lo que lo hace indispensable en una variedad de aplicaciones. Desde el ajuste de volumen en dispositivos de audio hasta la calibración de sensores en entornos industriales, los potenciómetros ofrecen una solución versátil y eficiente para el control de diferentes parámetros eléctricos. Su diseño simple, con tres terminales y un cursor móvil, facilita su integración en numerosos dispositivos, destacándose por su fiabilidad y facilidad de uso.

LEDs

Los diodos emisores de luz, comúnmente conocidos como LEDs (Light Emitting Diodes), son componentes electrónicos que han revolucionado la iluminación y la tecnología visual. A diferencia de las bombillas tradicionales, los LEDs son altamente eficientes, duraderos y versátiles. Funcionan mediante la emisión de luz cuando una corriente eléctrica pasa a través de un material semiconductor, lo que los hace ideales para una amplia gama de aplicaciones, desde pantallas y señales hasta iluminación ambiental y dispositivos electrónicos. Su capacidad para producir luz en diversos colores y su bajo consumo energético los han convertido en una opción preferida en muchas industrias, destacándose por su eficiencia y sostenibilidad.







