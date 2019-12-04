/************************************************************
           ___    _____  ____ 
          / _ \  / ___/ / __ \
         / , _/ / /__  / /_/ /
        /_/|_|  \___/  \____/ 

  Auteur : Association Robotique Club de l'Ouest
  
  Petit exemple de logiciel pour l'acquisition de tics
  pour codeurs incrementals. 

  Cet exemple vos pour l'acquisition de deux codeurs
  incrementaux sur une Arduino Uno mais il est très 
  simplement adaptable sur d'autres types d'arduino

************************************************************/

//-----------------------------------------------------------
// Déclaration des constantes

// Pin moteur

int PWM_A = 3;
int DIR_A = 12;
int BRAKE_A = 9;

int PWM_B   = 11;
int DIR_B   = 13;
int BRAKE_B = 8;


// Pin interuption
const int interuptPin = 20;  
const int interuptPinB = 19;

// Pin de dephasage
const int dephase  = 17;
const int dephaseB  = 18;  


// Fin déclaration des constantes
//-----------------------------------------------------------

//-----------------------------------------------------------
// Déclaration des fonctions

void reagir();
void reagirB();

// Fin déclaration des fonctions
//-----------------------------------------------------------

//-----------------------------------------------------------
// Déclaration des variables globales
  
// Variables (compteurs) qui vont stocker 
// le nombre de tics comptés pour chaque codeur
long comptTics= 0;
long comptTicsB= 0;


// Fin Déclaration des variables globales
//-----------------------------------------------------------

//-----------------------------------------------------------
// Fonction d'initialisation
void setup()
{
  // Permet un affichage du résultat sur la consol Série
  Serial.begin(9600);   

  // Initialisation des pin 9 et 10 en entrèes
  pinMode(dephase, INPUT); 
  pinMode(dephaseB, INPUT); 


  // Déclaration des intéruptions
  // Ici les fonctions d'intéruptions s'éxecutent
  // sur fronts montants : RISING
  attachInterrupt(digitalPinToInterrupt(interuptPin), reagir, RISING);
  attachInterrupt(digitalPinToInterrupt(interuptPinB), reagirB, RISING);
}
// Fin initialisation
//-----------------------------------------------------------


//-----------------------------------------------------------
// Fonction principale
// Avec l'utilisation des intéruptions la fonction loop qui
// habituellement est très remplie, la ne sert presque à rien
// sinon afficher le résultat du comptage sur le port série
void loop()
{
  while(comptTicsB < 200)
  {
    Serial.print("CompteurA ");
    Serial.println(comptTics);
    Serial.print("CompteurB ");
    Serial.println(comptTicsB);
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM_A, 100);
    analogWrite(PWM_B, 100);
  }
  digitalWrite(BRAKE_A, HIGH);
  digitalWrite(BRAKE_B, HIGH);
}
// Fin fonction principale
//-----------------------------------------------------------


//-----------------------------------------------------------
// Fonction d'intéruption pour le codeur gauche
// 
// Fonction appelée par un tic du codeur gauche. 
// On regarde le sens de rotation de celui-ci 
// (on teste l'état de la voie déphasée) et on 
// incrémente ou décrémente le compteur comptG.
void reagir()
{  
  if(digitalRead(dephase) == HIGH)
  {
    comptTics--;        
  }
  else
  {
    comptTics++;      
  }      
}

void reagirB()
{  
  if(digitalRead(dephaseB) == HIGH)
  {
    comptTicsB++;        
  }
  else
  {
    comptTicsB--;      
  }      
}
// Fin fonction d'intéruption pour le codeur gauche
//-----------------------------------------------------------


// Fin fonction d'intéruption pour le codeur droit
//-----------------------------------------------------------


// moteur droit 1 tic = 1,285mm 
