import processing.serial.*;

Serial myPort;

String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;

PFont orcFont;

void setup() {
  size(1200, 700); // or use fullScreen();
  smooth();
  myPort = new Serial(this,"COM4",9600);
  myPort.bufferUntil('\n'); // ✅ read until newline (matches Arduino println)
}

void draw() {
  noStroke();
  fill(0,4); 
  rect(0, 0, width, height-height*0.065); 

  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

// read serial data correctly
void serialEvent (Serial myPort) {
  data = myPort.readStringUntil('\n');
  if(data == null) return;
  data = data.trim(); // remove newline/carriage return

  int index1 = data.indexOf(",");
  if(index1 == -1) return;
  angle = data.substring(0, index1);
  distance = data.substring(index1+1);

  try {
    iAngle = int(angle);
    iDistance = int(distance);
  } catch(Exception e) {
    // ignore parse errors
  }
}

void drawRadar() {
  pushMatrix();
  translate(width/2,height-height*0.074);
  noFill();
  strokeWeight(2);
  stroke(98,245,31);
  float[] arcSizes = {width-width*0.0625,width-width*0.27,width-width*0.479,width-width*0.687};
  for(int i=0;i<arcSizes.length;i++){
    arc(0,0,arcSizes[i],arcSizes[i],PI,TWO_PI);
  }
  line(-width/2,0,width/2,0);
  for(int a=30;a<=150;a+=30){
    line(0,0,(-width/2)*cos(radians(a)),(-width/2)*sin(radians(a)));
  }
  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(width/2,height-height*0.074);
  strokeWeight(9);
  stroke(255,10,10);
  pixsDistance = iDistance*((height-height*0.1666)*0.025);
  if(iDistance<40){
    line(pixsDistance*cos(radians(iAngle)),-pixsDistance*sin(radians(iAngle)),(width-width*0.505)*cos(radians(iAngle)),-(width-width*0.505)*sin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30,250,60);
  translate(width/2,height-height*0.074);
  line(0,0,(height-height*0.12)*cos(radians(iAngle)),-(height-height*0.12)*sin(radians(iAngle)));
  popMatrix();
}

void drawText() {
  pushMatrix();
  noStroke();
  fill(0,0,0);
  rect(0, height-height*0.0648, width, height);
  fill(98,245,31);
  textSize(25);
  text("Angle: "+iAngle+"°", 20, height-20);
  text("Distance: "+iDistance+" cm", 200, height-20);
  popMatrix();
}
