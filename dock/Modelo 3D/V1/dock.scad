$fn = 50;

// Mudar os parametros abaixo
larguraDock = 80;
espessuraDevice = 14;

// Não alterar a partir daqui
anguloDevice = 10;
compensacaoAngular = 4;
profundidadeBase = espessuraDevice + 15;
alturaBaseFrente = 20;
alturaBaseEncosto = 40;
alturaRecorteDevice = 12;
diametroLeds = 5;


base();
//recorteSensores();

module base(){
    //Base
    difference(){
        cube([larguraDock, profundidadeBase, alturaBaseEncosto]);
        // Recorte do device
        rotate([-anguloDevice,0,0]) translate([-1,-1 ,alturaBaseFrente])cube([larguraDock + 2,profundidadeBase / 2,alturaBaseEncosto]);
        //Recortes da parte frontal
        translate([-1,-1 ,alturaBaseFrente])cube([larguraDock + 2,profundidadeBase / 2,alturaBaseEncosto]);   
        rotate([-anguloDevice,0,0]) translate([-1,(profundidadeBase -espessuraDevice) / 2 - compensacaoAngular ,alturaRecorteDevice]) cube([larguraDock + 2, espessuraDevice, alturaBaseEncosto]);
        //Recorte dos sensores
        translate([(larguraDock - 6) / 2,profundidadeBase - 10, 0 ]) recorteSensores();
        
        translate([(larguraDock + 6) / 2,10, 0 ]) rotate([0,0,180]) recorteSensores();
        
        // recorte Led
    translate([(larguraDock - 16) / 2,(profundidadeBase- 12) / 2]) cube([16,12,7]);
        
        translate([(larguraDock - 6) / 2,0, 0]) cube([6,profundidadeBase,5]);
    }
    
    
    
}

module recorteSensores(){
    
    largura = 6;
    altura = 20;
    alturaLed = 15;
    anguloLeds = 0;
    
    // diametro led = 5
    // tamanho led = 12
    
    translate([0,9,0]) cube([largura,12,altura]);
    
    translate([largura / 2,12,alturaLed]) rotate([90,0,anguloLeds]) cylinder(h=15, d=diametroLeds);
}