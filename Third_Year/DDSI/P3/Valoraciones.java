/*
SUBSISTEMA VALORACIONES de Francisco J. Jiménez Legaza
*/

package meetnmatch;


import java.sql.*;
import java.util.Scanner;
import java.sql.SQLException;
import java.lang.*;

public  class Valoraciones{ 



    public static void crearValoracion(Connection con){
        String titulo;
        String nombreUsuario;
        String comentario;
        String cValoracion;
        Statement stmt;

    try{
       
        stmt=con.createStatement();

        Scanner sc=new Scanner(System.in);

        Savepoint save1=con.setSavepoint();
        
        do{
        System.out.println("Introducir titulo de la valoracion (Max 50 caracteres)");
        titulo=sc.nextLine();
        }while(titulo.length()>50 || titulo.length()==0);    
        
        ResultSet rs1;
        do{
        System.out.println("Introducir nombre de usuario a quien va referenciada la valoraion (Max 20 caracteres)");
        nombreUsuario=sc.nextLine();
        rs1 = stmt.executeQuery("SELECT nombreUsuario FROM Jugadores WHERE nombreUsuario='"+nombreUsuario+"'");
        }while(nombreUsuario.length()>20 || nombreUsuario.length()==0 || !rs1.next());

        
        do{
        System.out.println("Introducir comentario de la valoracion (Max 500 caracteres)");
        comentario=sc.nextLine();
        }while(comentario.length()>500 || comentario.length()==0 );
        
        ResultSet rs;
        do{
            cValoracion=MeetNMatch.generateRandomString(5);
            rs=stmt.executeQuery("select codVal  from Valoraciones where codVal= '"+cValoracion+"'");
            
        }while(rs.next()); 

        System.out.println("Se va a crear la valoracion  ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                stmt.executeQuery(" insert into valoraciones (codVal,titulo,nomUsuario,comentario) values('"+cValoracion+"','"+titulo+"','"+nombreUsuario+"','"+comentario+"')");
                con.commit();
                System.out.println("Creacion efectuada con éxito");
            }

    
    }catch(SQLException e){ System.out.println("Código de Error: " + e.getErrorCode() + "\n" +
     "SQLState: " + e.getSQLState() + "\n" +
     "Mensaje: " + e.getMessage());
    Throwable t = e.getCause();
    while(t != null) {
      System.out.println("Causa: " + t + "\n");
      t = t.getCause();
    }}
    catch(Exception e){ System.out.println(e);}
    }


    public static void crearQueja(Connection con){
        String titulo;
        String nombreUsuario;
        String comentario;
        String tipoIncidente;
        String cQuej;
        Statement stmt;

    try{
       
        stmt=con.createStatement();

        Scanner sc=new Scanner(System.in);

        Savepoint save1=con.setSavepoint();

        
        do{
            System.out.println("Introducir titulo de la queja (Max 50 caracteres)");
            titulo=sc.nextLine();
        }while(titulo.length()>50 || titulo.length()==0);
        
        do{
            System.out.println("Introducir tipo de Incidente (Max 100 caracteres)");
            tipoIncidente=sc.nextLine();
        }while(tipoIncidente.length()>100 ||  tipoIncidente.length()==0);
        
        ResultSet rs1;
        do{
        System.out.println("Introducir nombre de usuario a quien va referenciada la queja (Max 20 caracteres)");
        nombreUsuario=sc.nextLine();
        rs1 = stmt.executeQuery("SELECT nombreUsuario FROM Jugadores WHERE nombreUsuario='"+nombreUsuario+"'");
        }while(nombreUsuario.length()>20 || nombreUsuario.length()==0 || !rs1.next());

        
        do{
            System.out.println("Introducir comentario de la queja (Max 500 caracteres)");
            comentario=sc.nextLine();
        }while(comentario.length()>500 ||  comentario.length()==0);
        
        //Codigo Valoracion alfanumerico
        ResultSet rs;
        do{
            cQuej=MeetNMatch.generateRandomString(5);
            rs=stmt.executeQuery("select codQuej   from quejas where codQuej= '"+cQuej+"'");
            
        }while(rs.next()); 

        System.out.println("Se va a crear la queja  ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                stmt.executeQuery(" insert into quejas (codQuej,titulo,incidente,nomUsuario,comentario) values('"+cQuej+"','"+titulo+"','"+tipoIncidente+"','"+nombreUsuario+"','"+comentario+"')");
                con.commit();
                System.out.println("Creacion efectuada con éxito");
            }

                                           
        
    
    }catch(SQLException e){ System.out.println("Código de Error: " + e.getErrorCode() + "\n" +
     "SQLState: " + e.getSQLState() + "\n" +
     "Mensaje: " + e.getMessage());
    Throwable t = e.getCause();
    while(t != null) {
      System.out.println("Causa: " + t + "\n");
      t = t.getCause();
    }}
    catch(Exception e){ System.out.println(e);}
    }




    public static void borrarValoracion(Connection con){
        try{
            Statement stmt;
            ResultSet result;
            stmt= con.createStatement();             
         Scanner sc=new Scanner(System.in);
            Savepoint save1=con.setSavepoint();
            String cValoracion="";

            try{

                do{
                System.out.println("Introducir el Codigo de la valoracion (5 caracteres)");
                cValoracion=sc.nextLine();
                }while(cValoracion.length()!=5);
                
                stmt.executeUpdate("DELETE FROM valoraciones WHERE codVal='"+cValoracion+"'");
	    
            
            }catch(SQLException e){ System.out.println("Código de Error: " + e.getErrorCode() + "\n" +
            "SQLState: " + e.getSQLState() + "\n" +
            "Mensaje: " + e.getMessage());
            
            Throwable t = e.getCause();
            while(t != null) {
                System.out.println("Causa: " + t + "\n");
                t = t.getCause();
            }
            }


            System.out.println("Se va a eliminar la valoracion " + cValoracion + " y todos sus detalles. ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                con.commit();
                System.out.println("Borrado efectuado con éxito");
            }
            
        }catch(SQLException e){ System.out.println("Código de Error: " + e.getErrorCode() + "\n" +
            "SQLState: " + e.getSQLState() + "\n" +
            "Mensaje: " + e.getMessage());
            
            Throwable t = e.getCause();
            while(t != null) {
                System.out.println("Causa: " + t + "\n");
                t = t.getCause();
           }
        }
        catch(Exception e){ System.out.println(e);}
    }
    
    public static void mostrarValoraciones(Connection con){
        try{
            Statement stmt;
            String nomUsuario="";
            stmt=con.createStatement();

            	Scanner sc= new Scanner(System.in);
		        ResultSet rs;
                    
                System.out.println("Introducir nombre de usuario a conocer las valoraciones: ");
                nomUsuario=sc.nextLine();
                rs=stmt.executeQuery("select nombreusuario from jugadores where nombreusuario='"+nomUsuario+"'");

                if(rs.next()){
                    rs = stmt.executeQuery("SELECT * FROM valoraciones WHERE nomUsuario='"+ nomUsuario+"'");
                    System.out.println("\tcodVal\ttitulo\tnomUsuario\tcomentario\n");
                    while(rs.next())
                        System.out.println("\t"+rs.getString(1)+"\t" +rs.getString(2)+"\t" +rs.getString(3)+"\t" +rs.getString(4));

                }else{
                    System.out.println("El usuario insertado no existe. ");
				}
                
        } catch(Exception e){ System.out.println(e);}
    }
                                     
    public static void modificarValoracion(Connection con){
        String comentario;
        Statement stmt;
         Scanner sc=new Scanner(System.in);
        try{
            
            stmt=con.createStatement();

            String cValoracion;

            do{
                System.out.println("Introducir el Codigo de la valoracion a modificar (5 caracteres)");
                cValoracion=sc.nextLine();
            }while(cValoracion.length()!=5);

            do{
                System.out.println("Introducir nuevo comentario de la valoracion (Max 500 caracteres)");
                comentario=sc.nextLine();
            }while(comentario.length()>500 || comentario.length()==0);

            ResultSet rs = stmt.executeQuery("UPDATE valoraciones SET comentario='"+comentario+"' WHERE codVal='"+cValoracion+"'");

            con.commit();
        } catch(Exception e){ System.out.println(e);}
    }




    public static void Menu(Connection con){
        
         Scanner sc=new Scanner(System.in);
         int op;
        
        try{
        
         Boolean salir=false;
        do{
            do{
                System.out.println("Menú Valoraciones y quejas: \n" + "\t 1: Crear Valoracion \n" + "\t 2: Consultar Valoraciones \n" + "\t 3: Modificar valoracion. \n" +"\t 4: Borrar Valoracion. \n"+ "\t 5: Crear Queja \n" + "\t 6: Salir. \n" );
                op = Integer.parseInt(sc.nextLine());
                if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5 && op!=6)
                System.out.println("La opcion elegida no es valida");
            }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5  && op!=6);
        
            switch(op){
                case 1:
                    crearValoracion(con);
                   
                break;

                case 2:
                    mostrarValoraciones(con);
                break;

                case 3:
                    modificarValoracion(con);
                break;

                case 4:
                    borrarValoracion(con);
                break;
                case 5:
                    crearQueja(con);
                break;
                case 6:
                    System.out.println("Saliendo de Valoraciones y quejas...");
                    salir=true;
                break;
          
            }

        }while(!salir);
        }catch(Exception e){ System.out.println(e);}
    }
}

/*


CREATE OR REPLACE TRIGGER <nombre>
{BEFORE | AFTER}
{INSERT | [OR] DELETE | [OR] UPDATE [OF <lista
nombres columna>]}
ON <nombre tabla>
[FOR EACH ROW]
<bloque>

CREATE OR REPLACE TRIGGER nuevoSaldo
AFTER INSERT ON movimiento
FOR EACH ROW
BEGIN
UPDATE saldo SET saldo = saldo + :new.cantidad WHERE
identificador = :new.identificador;
END;

CREATE OR REPLACE TRIGGER modificarCantidadValoraciones
    AFTER INSERT OR DELETE ON valoraciones
    FOR EACH ROW
    BEGIN
    
    IF INSERTING THEN
        UPDATE cantidadVal SET cantidadVal = cantidadVal + 1 WHERE codVal =
        :old.codVal;
    ELSE
        UPDATE cantidadVal SET cantidadVal = cantidadVal - 1 WHERE codVal =
        :old.codVal;
    END IF;

END;


CREATE OR REPLACE TRIGGER comprobacionBorrado
    AFTER
    DELETE ON valoraciones
    FOR EACH ROW

BEGIN
    IF (SELECT codVal FROM valoraciones WHERE codVal=':old.codVal' ) THEN 
        raise_application_error(-20600, ' No se ha borrado correctamente');
    END IF;
END;


*/