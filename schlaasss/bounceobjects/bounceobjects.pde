//g coresspond a la gravité
//modifier les valeurs de g et de r pour une chute plus rapide
float g = 0.25;
//r correspond a la force du rebond
float r = -0.75;
boolean lancer = false;
float xx, yy;




class Bouncer {
  float x, y, vy, d; //
  PImage monImage;

  Bouncer(float ix, float iy, String in) {
    x = ix;
    y = iy;
    vy= -10;
    d = 1.0;
    if (random(-10,+10) < 0){
      d = -1.0;
    }
    monImage= loadImage(in);
  }

  void update() {
    if (y>height-30) {
      y=height-30;
      vy*=r;
    }

    vy+= g;
    y += vy;
    x +=.75*d;
    //sans changer les dimanesions de l'image:
    // image(monImage, x, y);
    image(monImage, x, y,70,70);  // image sera 30px x 30px
  }
}

Bouncer[] bVec;
int nbBouncers = 0;
int maxBouncers = 100;
int nbImages = 19;
String[] imageNames  = {"caca.png","avion.png","bebe.png","bogda.png","nichonpiercing.png","boule.png","cochon.png","crayon.png","dentier.png","didier.png","enfantnichon.png","grospakito.png","main.png","nike.png","piece.png","pinguin.png","poupee.png","sida.png","worm.png"};

void setup() {
  size (800, 600);
  smooth(); 
  imageMode(CENTER);
  bVec= new Bouncer[maxBouncers];
  }
  

}

void mouseReleased() {
  lancer=true;
  xx=mouseX;
  yy=mouseY;
}

void draw() {
  
 
  
  if (lancer && nbBouncers < maxBouncers) { // mouse pressed
    bVec[nbBouncers] = new Bouncer(xx, yy,imageNames[round(random(nbImages-1))]);
    lancer = false;
    nbBouncers++;
  }
  for (int i=0; i<nbBouncers; i++) {
    bVec[i].update();
  }
} 
