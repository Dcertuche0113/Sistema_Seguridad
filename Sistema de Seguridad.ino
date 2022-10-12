#include <LiquidCrystal.h>
#include <Keypad.h>  // importa libreria Keypad//
int led1 = 50;       //verde
int led2 = 51;       //amarillo
int led3 = 52;       //rojo
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte FILAS = 4;           // define numero de filas
const byte COLUMNAS = 4;        // define numero de columnas
char keys[FILAS][COLUMNAS] = {  // define la distribucion de teclas
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte pinesFilas[FILAS] = { 22, 23, 24, 25 };        // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = { 26, 27, 28, 29 };  // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;                      // almacena la tecla presionada
char CLAVE[4];                   // almacena en un array 6 digitos ingresados
char CLAVE_MAESTRA[4] = "0000";  // almacena en un array la contraseña maestra
byte INDICE = 0;                 // indice del array
byte INTENTOS = 0;

void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);  // inicializa comunicacion serie
  lcd.begin(16, 2);    // columnas 16 * 2 filas//
}

void loop() {

  if (INTENTOS == 3) {    // Después de 3 intentos fallidos entrará a bloquear el sistema

    sistemaBloqueado();
  }
  pantallaInicio();
  digitar();
  claves();
}

void digitar() {
  do {
    TECLA = teclado.getKey();  // obtiene tecla presionada y asigna a variable
    if (TECLA)                 // comprueba que se haya presionado una tecla
    {
      lcd.setCursor(INDICE, 1);
      lcd.print("*");  //MOSTRAR EN PANTALLA
      delay(50);
      CLAVE[INDICE] = TECLA;
      INDICE++;
    }

  } while (INDICE < 4);
}

void claves() {

  if (INDICE == 4) {    // Si ya se ingresaron los 4 dígitos entonces entrará a comparar las claves

    if (CLAVE[0] == CLAVE_MAESTRA[0] && CLAVE[1] == CLAVE_MAESTRA[1] && CLAVE[2] == CLAVE_MAESTRA[2] && CLAVE[3] == CLAVE_MAESTRA[3]) {   // Compara la clave ingresada con la clave correcta
      delay(50);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Clave correcta");
      delay(50);
      arregloLEDs();
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      lcd.clear();
      INTENTOS = 0;
      INDICE = 0;

    } else {    // Si la clave no es correcta entonces entrará aquí

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Clave Incorrecta");
      delay(50);
      arregloLEDs();
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      lcd.clear();

      INTENTOS++;   // La variable INTENTOS aumentará en 1 hasta un máximo de 3
      INDICE = 0;
    }
  }
}

void pantallaInicio() {

  lcd.setCursor(0, 0);        // Posicion del mensaje
  lcd.print("Contraseña:");   // Mensaje mostrado
  delay(50);
  INDICE = 0;                 // Se establece la variable INDICE en 0
}

void sistemaBloqueado() {

  lcd.setCursor(0, 0);
  lcd.print("Sistema");
  lcd.setCursor(0, 1);
  lcd.print("Bloqueado");
  arregloLEDs();
  digitalWrite(led3, HIGH);
  delay(250);
  lcd.clear();
  lcd.print("Espere");
  lcd.setCursor(0, 1);
  lcd.print("Por favor");
  delay(5000);
  lcd.clear();
  lcd.print("Sistema");
  lcd.setCursor(0, 1);
  lcd.print("Desbloqueado");
  delay(500);
  digitalWrite(led3, LOW);
  arregloLEDs();
  lcd.clear();
  INTENTOS = 0;
  INDICE = 0;
}

void arregloLEDs() {

  digitalWrite(led1, HIGH);
  delay(250);
  digitalWrite(led1, LOW);
  delay(250);
  digitalWrite(led2, HIGH);
  delay(250);
  digitalWrite(led2, LOW);
  delay(250);
  digitalWrite(led3, HIGH);
  delay(250);
  digitalWrite(led3, LOW);
  delay(250);
}