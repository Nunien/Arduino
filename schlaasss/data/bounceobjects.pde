//g coresspond a la gravité
//modifier les valeurs de g et de r pour une chute plus rapide
float g = 0.25;
//r correspond a la force du rebond
float r = -0.75;
boolean lancer = false;
float xx, yy;
import gifAnimation.*;
Gif myAnimation = new Gif(PApplet Rparent, String filename);
//j ai rajoute ces deux lignes



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
int nbImages = 5;
String[] imageNames  = {"caca04.gif","crayon4couleurs.png","didier.png","gros pakito.png","nichonpiercing.png"};

void setup() {
  size (800, 600);
  smooth(); 
  imageMode(CENTER);
  bVec= new Bouncer[maxBouncers];
  }
  
  size(400,400);
    Gif myAnimation = new Gif(this, "testfond01.gif");
myAnimation.play();
//ainsi que celles la, les 3 du dessus
}

void mouseReleased() {
  lancer=true;
  xx=mouseX;
  yy=mouseY;
}

void draw() {
  
  image(myAnimation, 10,10);
  }
  //et celle la
  
  if (lancer && nbBouncers < maxBouncers) { // mouse pressed
    bVec[nbBouncers] = new Bouncer(xx, yy,imageNames[round(random(nbImages-1))]);
    lancer = false;
    nbBouncers++;
  }
  for (int i=0; i<nbBouncers; i++) {
    bVec[i].update();
  }
} 
