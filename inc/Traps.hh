class Traps : public Interactuable{

  
};
//Hole on the floor
[](Interactuable& this, Interactuable& trap, float distance){
  if(distance <= cell.width/4){
    this.damage(50);
    //Animacion de caida?
    this.respawn();
  }
}

//Claymore
[](Interactuable& this, Interactuable& trap, float distance){
  if(distance <= cell.width * 2){
    //Comprobar si esta dentro de un angulo de 45º (yo noseee :S)
    this.damage(100);
    //Estara muerto
  }
}

//Bear trap
[](Interactuable& this, Interactuable& trap, float distance){
	if(distance <= cell.width/4){
		this.immobilize(2); //2 seconds
		this.damage(50);
	}
}

//Rope trap
[](Interactuable& this, Interactuable& trap, float distance){
	if(distance <= cell.width/4){
		this.immobilize(0); //0 means forever
		this.damage(25);
	}
}

//Movement detector
[](Interactuable& this, Interactuable& trap, float distance){
	if(distance <= cell.width * 2){
		//Muestra todo lo que hay en un c?rculo de dos casillas de radio (trampas incluidas)
	}
}
