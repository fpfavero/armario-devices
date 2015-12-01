$fn = 20;

// Mudar os parametros abaixo
larguraDock = 140;
espessuraDevice = 14;

// Não alterar a partir daqui
anguloDevice = 8;
compensacaoAngular = 0;
profundidadeBase = espessuraDevice + 22;
alturaBaseFrente = 20;
alturaBaseEncosto = 40;
alturaRecorteDevice = 15;
diametroLeds = 3.2;
tamanhoLeds = 8;


base();
//led();

//recorteSensores();

module base(){
    //Base
    difference(){
        union(){
       roundedcube(larguraDock, profundidadeBase, alturaBaseEncosto, 18,18,15,15);
        translate([larguraDock / 2 - 17, profundidadeBase, 0]) cube([34, 20, 12]);
            
        }
        // Recorte do device
         difference(){
           union(){
  rotate([-anguloDevice,0,0]) translate([-1,-1 ,alturaBaseFrente])cube([larguraDock + 2,profundidadeBase / 2,alturaBaseEncosto]);
            translate([-1,-1 ,alturaBaseFrente])cube([larguraDock + 2,profundidadeBase / 2,alturaBaseEncosto]);
        
      }
        translate([-2,profundidadeBase /4 - 5 ,2]) rotate([0,90,0]) rotate([0,0,-anguloDevice])  resize([40,30,0]) cylinder(d = profundidadeBase /2, h = larguraDock + 4, $fn = 50);
}
  
        
        
        //Recortes da parte frontal
         
        rotate([-anguloDevice,0,0]) translate([-1,(profundidadeBase -espessuraDevice) / 2 - compensacaoAngular ,alturaRecorteDevice]) cube([larguraDock + 2, espessuraDevice, alturaBaseEncosto]);
        
        // Recorte carregador
       translate([0,profundidadeBase / 2 + 9, 0]) cube([larguraDock,6,6]); 
 
        
        //Recorte dos sensores
        translate([(larguraDock - 6) / 2,profundidadeBase - 12, 0 ]) recorteSensores();
        
        translate([(larguraDock + 6) / 2,18, 0 ]) rotate([0,0,180]) recorteSensores();
        
    // recorte eletronica
    translate([((larguraDock) / 2) - 12,(profundidadeBase) - 4, 0]) cube([24, 20, 10]);
        
    // recorte Led
    translate([(larguraDock) / 2,(profundidadeBase) / 2]) cylinder($fn=6, d=25, h =10);
    
  translate([(larguraDock) / 2,(profundidadeBase) / 2, 9]) sphere(d=5);
    
    
        
        
        
        translate([(larguraDock - 10) / 2,10, 0]) cube([10,profundidadeBase + 20,8]);
    }
    
    
    
}


module recorteSensores(){
    
    largura = 6;
    altura = 18;
    alturaLed = 15;
    anguloLeds = 0;
    
    // diametro led = 5
    // tamanho led = 12
    
    translate([0,9,0]) cube([largura,8,altura]);
    
    translate([largura / 2,12,alturaLed]) rotate([90,0,anguloLeds]) cylinder(h=tamanhoLeds + 1, d=diametroLeds);
}

module led(){
    cylinder($fn=6, d=23, h =1.3);
    translate([0,0,1.3]) cylinder($fn=20, d=8, h =3);
    translate([0,0,4.3]) sphere(d = 5);
}

module roundedcube(xdim ,ydim ,zdim,rdim1, rdim2, rdim3, rdim4){
    hull(){
        translate([rdim1,rdim1,0]) cylinder(r=rdim1, h=zdim);
        translate([xdim-rdim2,rdim2,0]) cylinder(r=rdim2, h=zdim);

        translate([rdim3,ydim-rdim3,0]) cylinder(r=rdim3, h=zdim);
        translate([xdim-rdim4,ydim-rdim4,0]) cylinder(r=rdim4, h=zdim);
    }
}