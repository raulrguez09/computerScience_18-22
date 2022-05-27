CREATE TABLE jugadores(
    nombre VARCHAR2(20) NOT NULL,
    apellidos VARCHAR2(40) NOT NULL,
    teléfono VARCHAR2(20) NOT NULL,
    nombreUsuario VARCHAR2(15) NOT NULL PRIMARY KEY,
    edad INT NOT NULL,
    altura FLOAT NOT NULL,
    peso FLOAT NOT NULL,
    carreraProfesional VARCHAR(30) NOT NULL,
    equipo VARCHAR2(20) DEFAULT NULL,
    puntos INT DEFAULT 0,
    jugSancionado NUMBER(1) DEFAULT 0,
    deportesPreferentes VARCHAR2(100),
    disponibilidadMaterial NUMBER(1) NOT NULL,
    descripcionMaterial VARCHAR2(500) DEFAULT 'NO TIENE MATERIAL',
    descripcionSancion VARCHAR2(500)
);

CREATE TABLE equipos(
    nombreEquipo VARCHAR2(20) NOT NULL PRIMARY KEY,
    deporte VARCHAR2(100),
    tag VARCHAR2(3) NOT NULL,
    equipoSancionado NUMBER(1) DEFAULT 0,
    lider VARCHAR2(20) NOT NULL,
    descripcionSancion VARCHAR2(500)
);

CREATE TABLE encuentros( 
        codEnc VARCHAR2 (5) NOT NULL PRIMARY KEY, 
       	puntuacionLocal INT DEFAULT 0 CHECK (puntuacionLocal>=0),
       	puntuacionVisitante INT DEFAULT 0 CHECK (puntuacionVisitante>=0),
        usuarioLider VARCHAR(15) NOT NULL,
        deporteEnc VARCHAR2(20) NOT NULL CHECK (deporteEnc='Fútbol' OR deporteEnc='Baloncesto' OR deporteEnc='Pádel'),
        horaEnc TIMESTAMP NOT NULL,
        ubicacionEncuentro VARCHAR2(100) NOT NULL,
        material_Personal VARCHAR2(100) NOT NULL,
       apuestaEnc INT DEFAULT 0 CHECK (apuestaEnc>=0),
);

CREATE TABLE ubicacion(
    codUbi VARCHAR2(5) NOT NULL PRIMARY KEY,
    localizacion VARCHAR2(100) NOT NULL,
    deportesUbi VARCHAR2(20) NOT NULL,
    descAct VARCHAR2(500),
    necesarioPago NUMBER(1) DEFAULT 0 CHECK (necesarioPago=0 OR necesarioPago=1) NOT NULL,
    pagoAlquiler FLOAT DEFAULT 0 NOT NULL CHECK(pagoAlquiler>=0),
    horaApertura DATE NOT NULL,
    horaCierre DATE NOT NULL,
    justBaja VARCHAR2(500),
    fueraServicio INT  DEFAULT 0 CHECK (fueraServicio=0 OR fueraServicio=1)  NOT NULL
);


CREATE TABLE premios(
    codPre VARCHAR2(8) NOT NULL PRIMARY KEY,
    nombre VARCHAR2(50) NOT NULL,
    descripción VARCHAR2(300) NOT NULL,
    cantidad INT NOT NULL,
    precio INT NOT NULL    
);


CREATE TABLE valoraciones(
    codVal VARCHAR2(5) NOT NULL PRIMARY KEY,
    titulo VARCHAR2(50) NOT NULL,
    nomUsuario VARCHAR2(50) NOT NULL,
    comentario VARCHAR2(500) NOT NULL,
    FOREIGN KEY (nomUsuario) REFERENCES jugadores(nombreUsuario)
);

CREATE TABLE quejas(
    codQuej VARCHAR2(5) NOT NULL PRIMARY KEY,
    titulo VARCHAR2(50) NOT NULL ,
    incidente VARCHAR2(100) NOT NULL,
    nomUsuario VARCHAR2(50) NOT NULL,
    comentario VARCHAR2(500) NOT NULL,   
    FOREIGN KEY (nomUsuario) REFERENCES jugadores(nombreUsuario)
);

CREATE TABLE pertenece(
    equipo VARCHAR2(20) NOT NULL,
    jugador VARCHAR(15) NOT NULL,
    PRIMARY KEY(equipo, jugador),
    FOREIGN KEY (jugador) REFERENCES jugadores(nombreUsuario),
    FOREIGN KEY (equipo) REFERENCES equipos(nombreEquipo)
);


CREATE TABLE inscripcionE(

    codEnc VARCHAR2 (5) NOT NULL, 
    equipo NOT NULL,
    PRIMARY KEY(equipo, codEnc),
    FOREIGN KEY (codEnc) REFERENCES encuentros(codEnc),
    FOREIGN KEY (equipo) REFERENCES equipos(nombreEquipo)
);


CREATE TABLE inscripciónJ(
    nombreUsuario VARCHAR2(15) NOT NULL,
    codEnc VARCHAR2 (5) NOT NULL,
    PRIMARY KEY(nombreUsuario, codEnc),
    FOREIGN KEY (codEnc) REFERENCES encuentros(codEnc),
    FOREIGN KEY (nombreUsuario) REFERENCES jugadores(nombreUsuario)
);


CREATE TABLE alquiler(
    codUbi VARCHAR2(5) NOT NULL,
    Usuario VARCHAR(15) NOT NULL,
    fechaAlq TIMESTAMP NOT NULL,
    horaInicio DATE NOT NULL,
    horaFin DATE NOT NULL,
    deporteAlq VARCHAR2(20) NOT NULL,
    PRIMARY KEY(Usuario, fechaAlq, horaInicio, horaFin, deporteAlq),
    FOREIGN KEY (Usuario) REFERENCES jugadores(nombreUsuario),
    FOREIGN KEY (codUbi) REFERENCES ubicacion(codUbi)
);


CREATE TABLE consigue(
    nomUsuario VARCHAR2(15) NOT NULL REFERENCES jugadores(nombreUsuario),
    codigoPremio VARCHAR2(16) NOT NULL,
    codPre VARCHAR(8) NOT NULL REFERENCES premios(codPre),
    PRIMARY KEY(nomUsuario,codigoPremio)
);

CREATE TABLE adquiere ( 
        nomUsuario VARCHAR2(15) NOT NULL REFERENCES jugadores(nombreUsuario), 
        codEnc VARCHAR2(5) NOT NULL REFERENCES encuentros(codEnc),
        cantidadPuntos INT NOT NULL,
        PRIMARY KEY( nomUsuario, codEnc)
);

insert into Jugadores (nombre, apellidos, teléfono, nombreUsuario, edad, altura, peso, carreraProfesional, equipo, deportesPreferentes, disponibilidadMaterial, descripcionMaterial) values('Pepe', 'Castro Moreno', 619619619, 'Pepe88', 20, 180,  90, 'No tiene', 'No tiene',  'Fútbol', 1, 'Balón de futbol' );
insert into Jugadores (nombre, apellidos, teléfono, nombreUsuario, edad, altura, peso, carreraProfesional, equipo, deportesPreferentes, disponibilidadMaterial, descripcionMaterial) values('Willy', 'Fernandez Jimenez', 607607607, 'Willy777', 18, 190,  80, 'No tiene', 'No tiene',  'Baloncesto', 1, 'Balón de baloncesto' );
insert into Jugadores (nombre, apellidos, teléfono, nombreUsuario, edad, altura, peso, carreraProfesional, equipo, deportesPreferentes, disponibilidadMaterial) values('Julian', 'Muñoz Castro', 629629629, 'Julian1234', 35, 150,  60, 'Jugador del Numancia en ACB', 'No tiene actualmente',  'Baloncesto', 0);


insert into equipos(nombreEquipo,tag , deporte, lider) values ('betis', 'bts', 'Baloncesto', 'Julian1234');
insert into equipos(nombreEquipo,tag , deporte, lider) values ('alaves', 'alv', 'Fútbol', 'Pepe88');
insert into equipos(nombreEquipo,tag , deporte, lider) values ('numanciafc', 'nmc', 'Baloncesto', 'Willy777');

insert into ubicacion (codUbi,localizacion,deportesUbi,necesarioPago,pagoAlquiler,horaApertura,horaCierre) values ('10001','Estadio Los Carmenes,SN,GRANADA','Fútbol','1','5','09:00','21:00');
insert into ubicacion (codUbi,localizacion,deportesUbi,horaApertura,horaCierre) values ('10002','Poligono industrial Motril','Baloncesto','10:30','20:00');
insert into ubicacion (codUbi,localizacion,deportesUbi,necesarioPago,pagoAlquiler,horaApertura,horaCierre) values ('10003','Polideportivo Maracena, SN, Maracena','Baloncesto','1','7','08:30','23:00');

insert into encuentros(codEnc,puntuacionLocal,puntuacionVisitante,usuarioLider,deporteEnc,horaEnc,ubicacionEncuentro,material_Personal,apuestaEnc) values('12345',2,0,'Pepe88','Fútbol','22/11/20 13:00','Estadio Los Carmenes,SN,GRANADA','Un balón de futbol, botellas de agua, un fisio y un arbitro',2000);
insert into encuentros(codEnc,puntuacionLocal,puntuacionVisitante,usuarioLider,deporteEnc,horaEnc,ubicacionEncuentro,material_Personal,apuestaEnc) values('23456',100,80,'Willy777','Baloncesto','20/12/21 14:00','Poligono industrial Motril','Un balón de baloncesto y redes de canasta',1000);
insert into encuentros(codEnc,usuarioLider,deporteEnc,horaEnc,ubicacionEncuentro,material_Personal,apuestaEnc) values('34567','Julian1234','Baloncesto','13/12/20 12:00','Polideportivo Maracena, SN, Maracena','Un balón de futbol ',1000);
insert into premios(codPre,nombre,descripcion,cantidad,precio) values(10101010,'PS5','La ultima consola de Sony, con un SSD super rapido y un mando con tecnologia DualSense',3,2000000);
insert into premios(codPre,nombre,descripcion,cantidad,precio) values(10101011,'Camiseta Futbol PSG','Camiseta del famoso equipo frances con el numero 7 a la espalda y el nombre de MBAPPE',5,250000);
insert into premios(codPre,nombre,descripcion,cantidad,precio) values(10101012,'NVIDIA GeForce RTX 3070','Tarjeta grafica para que tu ordenador vuele en terminos de velocidad de procesamiento de graficos',2,1500000);

insert into valoraciones (codVal,titulo,nomUsuario,comentario) values('12345','Mejor jugador,mejor persona', 'Pepe88', 'Muy amable...');
insert into valoraciones (codVal,titulo,nomUsuario,comentario) values('12347','Me alegro de jugar con el', 'Willy777', 'Un placer de persona');
insert into valoraciones (codVal,titulo,nomUsuario,comentario) values('12346','muy amable', 'Julian1234', 'Muy respetuoso');

insert into quejas (codQuej,titulo,incidente,nomUsuario,comentario) values('12ABC','Falto al respeto','LESION', 'Pepe88', 'Todo el partido insultando');
insert into quejas (codQuej,titulo,incidente,nomUsuario,comentario) values('12AB5','Jugo muy sucio', 'LESION','Julian1234', 'Casi me lesiona');
insert into quejas (codQuej,titulo,incidente,nomUsuario,comentario) values('12ABF','Falto al respeto','LESION', 'Willy777', 'Todo el partido insultando');

insert into pertenece(equipo, jugador) values( 'alaves', 'Pepe88');
insert into pertenece(equipo, jugador) values( 'numanciafc', 'Willy777');
insert into pertenece(equipo, jugador) values( 'betis', 'Julian1234');


insert into inscripcionE(codEnc, equipo) values('12345', 'betis');
insert into inscripcionE(codEnc, equipo) values('23456', 'numanciafc');
insert into inscripcionE(codEnc, equipo) values('34567', 'alaves');

insert into inscripciónJ(nombreUsuario, codEnc) values('Pepe88', '12345');
insert into inscripciónJ(nombreUsuario, codEnc) values('Julian1234', '23456');
 insert into inscripciónJ(nombreUsuario, codEnc) values('Willy777', '34567');

insert into alquiler(codUbi,Usuario,fechaAlq,horaInicio,horaFin,deporteAlq) values ('10002','Willy777','20/11/21','12:00','13:30','Baloncesto');
insert into alquiler(codUbi,Usuario,fechaAlq,horaInicio,horaFin,deporteAlq) values ('10001','Pepe88','20/12/20','13:00','14:00','Fútbol');
insert into alquiler(codUbi,Usuario,fechaAlq,horaInicio,horaFin,deporteAlq) values ('10003','Julian1234','20/11/21','10:00','11:20','Baloncesto');


insert into consigue(nomUsuario,codigoPremio,codPre) values('Pepe88','ABCD1234','10101011');
insert into consigue(nomUsuario,codigoPremio,codPre) values('Julian1234','ABCD1235','10101012');
insert into consigue(nomUsuario,codigoPremio,codPre) values('Willy777','ABCD1236','10101010');

insert into adquiere(nomUsuario,codEnc,cantidadPuntos) values('Willy777','34567',2000000);
insert into adquiere(nomUsuario,codEnc,cantidadPuntos) values('Julian1234','23456',2000000);
insert into adquiere(nomUsuario,codEnc,cantidadPuntos) values('Pepe88','12345',2000000);


