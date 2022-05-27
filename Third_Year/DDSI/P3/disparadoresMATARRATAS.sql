/*RAÚL R*/

CREATE OR REPLACE TRIGGER deleteJugador
  BEFORE 
  DELETE ON JUGADORES 
  FOR EACH ROW
  
  DECLARE
    equipoBorrar varchar2(20);
BEGIN
    DELETE FROM inscripciónJ WHERE nombreUsuario=:old.nombreUsuario;
    DELETE FROM adquiere WHERE nomusuario=:old.nombreUsuario;
    DELETE FROM consigue WHERE nomusuario=:old.nombreUsuario;
    DELETE FROM encuentros WHERE usuarioLider=:old.nombreUsuario;
    DELETE FROM alquiler WHERE usuario=:old.nombreUsuario;
    DELETE FROM pertenece WHERE jugador=:old.nombreUsuario;
BEGIN
    SELECT nombreequipo into equipoBorrar FROM equipos WHERE lider=:old.nombreUsuario;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        equipoBorrar:=NULL;
END;
    DELETE FROM inscripcionE WHERE equipo=equipoBorrar;
    DELETE FROM equipos WHERE nombreequipo=equipoBorrar;
    DELETE FROM valoraciones WHERE nomusuario=:old.nombreUsuario;
    DELETE FROM quejas WHERE nomusuario=:old.nombreUsuario;
END;


CREATE OR REPLACE TRIGGER controlSancion
  BEFORE 
  UPDATE OR INSERT on inscripciónJ
  FOR EACH ROW
  DECLARE
    sancionado number(1,0);
  
BEGIN
    SELECT jugSancionado INTO sancionado FROM jugadores WHERE nombreUsuario=:new.nombreUsuario;
    	IF(sancionado = 1) THEN
    		raise_application_error(-20600, ' El usuario está sancionado y no puede inscribirse al encuentro.');
	END IF;
END;


/*ANGEL*/

create or replace trigger deletePertenece
  BEFORE DELETE on equipos 
  FOR EACH ROW

BEGIN
    DELETE FROM pertenece WHERE equipo=:old.nombreEquipo;
    DELETE FROM inscripcionE WHERE equipo=:old.nombreEquipo;
END;

CREATE OR REPLACE TRIGGER controlInscripcion
	BEFORE INSERT on inscripcionE
    FOR EACH ROW
    DECLARE 
        cnt number;
BEGIN

    SELECT COUNT(codEnc) INTO cnt from inscripcionE  where codEnc=:new.codEnc;
	IF (cnt>=2) THEN 
		raise_application_error(-20600, ' Ya hay 2 participantes inscriptos en este encuentro.');
	END IF;
END;


/*CRISTIAN*/

CREATE OR REPLACE TRIGGER correccionHoraAlquiler
	BEFORE
	UPDATE OR INSERT ON alquiler
	FOR EACH ROW
	
BEGIN
	IF (TO_DATE(:new.horainicio,'HH24:MI')>= TO_DATE(:new.horafin,'HH24:MI')) THEN 
		raise_application_error(-20600, ' Las horas de alquiler y finalizado no se pueden pisar');
	END IF;
END;

CREATE OR REPLACE TRIGGER correccionHoraApertura
	BEFORE
	UPDATE OR INSERT ON ubicacion
	FOR EACH ROW
	
BEGIN
	IF (TO_DATE(:new.horaapertura,'HH24:MI')>= TO_DATE(:new.horacierre,'HH24:MI')) THEN 
		raise_application_error(-20600, ' Las horas de apertura y cierre no se pueden pisar');
	END IF;
END;


/*SANTI*/
create or replace trigger deleteEncuentros
  BEFORE DELETE on encuentros
  FOR EACH ROW

BEGIN
    DELETE FROM inscripcionE WHERE codEnc=:old.codEnc;
    DELETE FROM adquiere WHERE codEnc=:old.codEnc;
    DELETE FROM  inscripciónJ WHERE codEnc=:old.codEnc;
END;

/*FRAN*/
CREATE OR REPLACE TRIGGER evitarMismoTitulo
    BEFORE 
    UPDATE OR INSERT ON valoraciones
    FOR EACH ROW
    DECLARE
    aux varchar2(50);
BEGIN
BEGIN
    SELECT titulo into aux from quejas where nomUsuario=:new.nomUsuario AND titulo=:new.titulo;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        aux:=NULL; 
END;
    IF (aux=:new.titulo) THEN
            raise_application_error(-20600, ' El título coincide con una queja ya registrada a ese jugador.');
    END IF;
END;


CREATE OR REPLACE TRIGGER evitarMismoTitulo2
    BEFORE 
    UPDATE OR INSERT ON quejas
    FOR EACH ROW
    DECLARE
    aux varchar2(50);
BEGIN

BEGIN
    SELECT titulo into aux from valoraciones where nomUsuario=:new.nomUsuario AND titulo=:new.titulo;
    EXCEPTION
    WHEN NO_DATA_FOUND THEN
        aux:=NULL;
END;
    IF (aux=:new.titulo) THEN
            raise_application_error(-20600, ' El título coincide con una valoracion ya registrada a ese jugador.');
    END IF;
END;

/*RAUL C*/

CREATE OR REPLACE TRIGGER borradoPremio
	BEFORE 
	DELETE ON premios
	FOR EACH ROW

BEGIN
	DELETE FROM consigue  WHERE codPre=:old.codpre;
END;
