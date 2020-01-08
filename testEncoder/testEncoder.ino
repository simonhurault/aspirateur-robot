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
// Liste des defines

#define UNCERTAINTY_ANGLE_RETURN 5 // Uncertenty in degree
#define DISTANCE_BETWEEN_WHEELS 20

//-----------------------------------------------------------
// Déclaration des constantes

// Pin moteur

const int PWM_A = 3;
const int DIR_A = 12;
const int BRAKE_A = 9;

const int PWM_B   = 11;
const int DIR_B   = 13;
const int BRAKE_B = 8;


// Pin interuption
const int interuptPin = 20;  
const int interuptPinB = 19;

// Pin de dephasage
const int dephaseDroite  = 17;
const int dephaseGauche  = 18;  

// Coefficient tics

const float coeffGaucheDistance = 0.1217; // distance par tics en cm
const float coeffDroiteDistance = 0.1183;


// Fin déclaration des constantes
//-----------------------------------------------------------


//-----------------------------------------------------------
// Déclaration des fonctions

void reagirDroite();
void reagirGauche();
float modulo(float value);


// Fin déclaration des fonctions
//-----------------------------------------------------------

//-----------------------------------------------------------
// Déclaration des variables globales
  
// Variables (compteurs) qui vont stocker 
// le nombre de tics comptés pour chaque codeur
long comptTicsDroite= 0;
long comptTicsGauche= 0;

float distanceRetour; // Distance a parcourir jusqu'a la base
float angleRetour;

float xPosition = 0;
float yPosition = 0; // Variable coordonnees du robot
float teta = 0; // Agnle total d'orientation du robot
float angleDeplacement = 0;

float distanceDeplacement; // Distance totale parcourue
float distanceL; // Distance parcourue par roue gauche
float distanceR; // Distance parcourue par roue droite

float angleReturn;
float cir;
bool keepGo = true;


// Fin Déclaration des variables globales
//-----------------------------------------------------------

//-----------------------------------------------------------
// Fonction d'initialisation
void setup()
{
  // Permet un affichage du résultat sur la consol Série
  Serial.begin(9600);   

  // Initialisation des pin 9 et 10 en entrèes
  pinMode(dephaseDroite, INPUT); 
  pinMode(dephaseGauche, INPUT); 


  // Déclaration des intéruptions
  // Ici les fonctions d'intéruptions s'éxecutent
  // sur fronts montants : RISING
  attachInterrupt(digitalPinToInterrupt(interuptPin), reagirDroite, RISING);
  attachInterrupt(digitalPinToInterrupt(interuptPinB), reagirGauche, RISING);
  
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
  pinMode(DIR_B, OUTPUT);    // Direction pin on channel B 
  digitalWrite(BRAKE_A, LOW);
  digitalWrite(BRAKE_B, LOW);
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
  if(keepGo)
  {
  while(millis() < 5000)
  {
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
    analogWrite(PWM_A, 100);
    analogWrite(PWM_B, 100);
  }
  
   digitalWrite(BRAKE_A, HIGH);
   digitalWrite(BRAKE_B, HIGH);
   distanceL = coeffGaucheDistance * comptTicsGauche;
   distanceR = coeffDroiteDistance * comptTicsDroite;
   distanceDeplacement = (distanceL + distanceR) / 2; // Moyenne de la distance parcourue par les 2 roues
   angleDeplacement = (distanceR - distanceL) / DISTANCE_BETWEEN_WHEELS;
 
   Serial.print("angleDeplacement = ");
   Serial.println(angleDeplacement);
   
   Serial.print("angleDeplacement apres mod = ");
   Serial.println(angleDeplacement);
   cir = distanceL / angleDeplacement;
  
   xPosition += cir * (1 - cos(angleDeplacement));
   yPosition += cir * sin(angleDeplacement);
   teta += angleDeplacement;
  

   digitalWrite(BRAKE_A, HIGH);
   digitalWrite(BRAKE_B, HIGH);
   
  // Retour base

  

  distanceRetour = sqrt(pow(xPosition, 2) + pow(yPosition, 2));

  
  angleReturn = 180 - teta + atan(yPosition/xPosition); // Angle that we need to turn to point the base
  Serial.print("angleReturn = ");
  Serial.println(angleReturn);

  comptTicsGauche = 0;
  comptTicsDroite = 0;
  angleDeplacement = 0;

  while (angleDeplacement < angleReturn - UNCERTAINTY_ANGLE_RETURN || angleDeplacement > angleReturn + UNCERTAINTY_ANGLE_RETURN )
  {
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, HIGH);
    analogWrite(PWM_A, 100);
    analogWrite(PWM_B, 100);
    distanceL = coeffGaucheDistance * comptTicsGauche;
    distanceR = coeffDroiteDistance * comptTicsDroite;
    distanceDeplacement = (distanceL + distanceR) / 2; // Moyenne de la distance parcourue par les 2 roues
    angleDeplacement = (distanceR - distanceL) / DISTANCE_BETWEEN_WHEELS;
    Serial.print("angleDeplacement = ");
    Serial.println(angleDeplacement);
  }
  digitalWrite(BRAKE_A, HIGH);
  digitalWrite(BRAKE_B, HIGH);
  keepGo = false;
  }
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
void reagirDroite()
{  
  if(digitalRead(dephaseDroite) == HIGH)
  {
    comptTicsDroite--;        
  }
  else
  {
    comptTicsDroite++;      
  }      
}

void reagirGauche()
{  
  if(digitalRead(dephaseGauche) == HIGH)
  {
    comptTicsGauche++;        
  }
  else
  {
    comptTicsGauche--;      
  }      
}
// Fin fonction d'intéruption pour le codeur gauche
//-----------------------------------------------------------


// Fin fonction d'intéruption pour le codeur droit
//-----------------------------------------------------------

/*
 * This function return a float value at the modulo 180
 * @param float value : value that we want the modulo
 * return the value at the modulo 180
 */
float modulo(float value)
{
  while(value > 180 || value < -180)
  {
    if (value > 180)
    {
      value -= 180;
    }
     
    else
    {
      value += 180;
    }
  }
  return value;
}


// moteur droit 1 tic = 1,285mm 
// moteur A = 1313 pour 360°

//Moteur B = 1343 pour 360°




// 857 = 360°
