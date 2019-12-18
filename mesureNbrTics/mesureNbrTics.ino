// Liste des defines

#define UNCERTAINTY_ANGLE_RETURN 5 // Uncertenty in degree

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


float angleOrigine; // Angle entre le robot et l'origine
float distanceRetour; // Distance a parcourir jusqu'a la base
float angleRetour;

float xPosition = 0;
float yPosition = 0; // Variable coordonnees du robot

float distanceDeplacement;
float angleDeplacement = 0;

float angleReturn;
bool keepGo = true;




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


void loop() {
  while(comptTicsGauche < 300)
  {
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
    analogWrite(PWM_A, 100);
    analogWrite(PWM_B, 100);
  }
  digitalWrite(BRAKE_A, HIGH);
  digitalWrite(BRAKE_B, HIGH);

}


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
