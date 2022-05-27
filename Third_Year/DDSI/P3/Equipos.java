/*
SUBSISTEMA EQUIPOS de Ángel Gómez Ferrer
*/

package meetnmatch;


import java.sql.*;
import java.util.Scanner;
import java.sql.SQLException;
import java.lang.*;


public class Equipos {
    
    public static String comillas(String a){
        return "'"+a+"'";
    }
    
    
    public static void excepcion(SQLException e){
        System.out.println(
                "Código de Error: " + e.getErrorCode() + "\n" +
                        "SQLState: " + e.getSQLState() + "\n" +
                        "Mensaje: " + e.getMessage()
        );
        Throwable t = e.getCause();
        while(t != null) {
            System.out.println("Causa: " + t + "\n");
            t = t.getCause();
        }
    }

    public static void crearEquipo(Connection con, String user){
        String nombreEquipo="", deporte="", tag="", lider = user;
        try {
            Statement stmt = con.createStatement();
            Scanner sc = new Scanner(System.in);

            ResultSet rs;
            do {

                System.out.println("Nombre del equipo: ");
                nombreEquipo = sc.nextLine();
                rs = stmt.executeQuery("SELECT * FROM equipos WHERE nombreEquipo="+comillas(nombreEquipo));

            } while (nombreEquipo.length() > 20 || nombreEquipo.length() < 3 || rs.next());

            do {
                System.out.println("Deporte: ");
                deporte = sc.nextLine();
            } while (!deporte.equals("Fútbol") && !deporte.equals("Baloncesto") && !deporte.equals("Pádel"));

            do {
                System.out.println("Tag del equipo (3 letras): ");
                tag = sc.nextLine();
            } while (tag.length() != 3);


            //Se añade
            stmt.executeQuery("insert into equipos (nombreEquipo, tag, deporte, lider) values("+comillas(nombreEquipo)+","+comillas(tag)+","+comillas(deporte)+","+comillas(lider)+")");
            stmt.executeQuery("insert into pertenece(equipo, jugador) values("+comillas(nombreEquipo)+", "+comillas(lider)+")");
            con.commit();
        }catch(SQLException e){
            excepcion(e);
        }

    }
    
    public static void mostrarEquipo(Connection con){
        try{
            Statement stmt;
            stmt=con.createStatement();
            /*stmt.executeQuery("insert into Jugadores (nombre,apellidos,teléfono,nombreUsuario,edad,altura,peso,carreraProfesional,deportesPreferentes,disponibilidadMaterial,descripcionMaterial) values('"+"Juan"+"','"+"aperese"+"',"+"607607608"+",'"+"Juan1"+"',"+"35"+","+"170"+","+"60"+",'"+"Muy listo"+"','"+"Baloncesto"+"','"+"1"+"','"+"Un yoyo"+"')");
            con.commit();*/
            //ResultSet rs = stmt.executeQuery("SELECT * FROM equipos");
            
            String nombreEquipo="";
            Scanner sc = new Scanner(System.in);
            System.out.println("Inserte el nombre del equipo a mostrar: ");
            nombreEquipo= sc.nextLine();
            ResultSet rs = stmt.executeQuery("SELECT * FROM equipos WHERE nombreEquipo="+comillas(nombreEquipo));
            if(rs.next()){//Cambiado
            
                System.out.println("\tDatos del equipo\nNombre del equipo: "+rs.getString(1)+"\nDeporte: "+rs.getString(2)+"\nTag: "+rs.getString(3)+"\nSancionado?(0 no o 1 si) : "+rs.getString(4)+"\nLider: "+rs.getString(5)+"\nDescripcion de sancion (si existe): "+rs.getString(6));

                ResultSet rs1= stmt.executeQuery("SELECT jugador from pertenece where equipo="+comillas(nombreEquipo));
                System.out.println("Miembros:");
                while(rs1.next()){
                    System.out.println(rs1.getString(1));
                }
            }else{
                System.out.println("El equipo no existe.");
			}
        }catch(SQLException e){ excepcion(e); }
    }

    public static void mostrarEquipo(Connection con, String nombreEquipo){
        try{
            Statement stmt;
            stmt=con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM equipos WHERE nombreEquipo="+comillas(nombreEquipo));
            rs.next();
            System.out.println("\tDatos del equipo\nNombre del equipo: "+rs.getString(1)+"\nDeporte: "+rs.getString(2)+"\nTag: "+rs.getString(3)+"\nSancionado?(0 no o 1 si) : "+rs.getString(4)+"\nLider: "+rs.getString(5)+"\nDescripcion de sancion (si existe): "+rs.getString(6));
        } catch(SQLException e){ excepcion(e); }
    }


    public static void aplicarSancion(Connection con){
        try{
            //Aqui es necesario ser el ADMIN 8)

            String ne="", descripcion="";
            Statement stmt;
            stmt=con.createStatement();

            Scanner sc = new Scanner(System.in);
            System.out.println("Nombre del equipo a aplicar la sancion: ");
            ne= sc.nextLine();
            ResultSet rs1=stmt.executeQuery("select * from equipos where nombreEquipo="+comillas(ne));
            if(rs1.next()) {
                do{
                    System.out.println("Inserte la descripcion de la sancion (menos de 100 caracteres): ");
                    descripcion= sc.nextLine();
                }while(descripcion.length() > 100 || descripcion.length()==0);
                ResultSet rs = stmt.executeQuery("UPDATE equipos SET equipoSancionado=1, descripcionSancion=" + comillas(descripcion)+" WHERE nombreEquipo=" + comillas(ne));
                System.out.println("La sancion ha sido aplicada.");
            }else{
                System.out.println("El equipo con nombre: "+ne+" no existe.");
            }


        }catch(SQLException e){
            excepcion(e);
        }

    }

    public static void inscribirEquipo(Connection con, String user) {
        try{
            Statement stmt = con.createStatement();
            Savepoint save = con.setSavepoint();
            ResultSet rs1;
            String ne = "";
            String cEnc = "";
            boolean existe= false;
            Scanner sc = new Scanner(System.in);
            System.out.println("Inserte el nombre del equipo a incribir (debes ser usuario lider): ");
            do {
                ne = sc.nextLine();
                rs1 = stmt.executeQuery("SELECT lider FROM equipos WHERE nombreEquipo=" + comillas(ne));
                existe= rs1.next();
            } while (!existe && !rs1.getString(1).equals(user) && !ne.equals(""));//ojo

            System.out.println("Codigo de encuentro: ");
            cEnc = sc.nextLine();
            ResultSet rs2 = stmt.executeQuery("select * from encuentros where codEnc=" + comillas(cEnc));
            if (existe && rs2.next()) {

                stmt.executeQuery("insert into inscripcionE (codEnc, equipo) values("+comillas(cEnc)+","+comillas(ne)+")");
                con.commit();
                System.out.println("El equipo "+ne+" ha sido inscrito al encuentro: "+cEnc);

                ResultSet rs3= stmt.executeQuery("select equipo from inscripcionE where codEnc=" + comillas(cEnc));

                System.out.println("Los equipos inscritos al encuentro: "+cEnc+" actualmente son: ");
                while(rs3.next()){
                    System.out.println("\t"+rs3.getString(1));
                }


            }else{
                System.out.println("El nombre del equipo o el codigo de encuentro no existe.");
            }
        }catch(SQLException e){
            excepcion(e);
        }
    }

    public static void bajaEquipo(Connection con, String user){
        try{
            ResultSet rs, rs1;
            Scanner sc= new Scanner(System.in);
            Statement stmt= con.createStatement();

            Savepoint save= con.setSavepoint();
            String ne="";
            System.out.println("Introducir nombre del equipo a dar de baja: ");
            ne= sc.nextLine();
            
            rs1= stmt.executeQuery("SELECT lider FROM equipos WHERE nombreEquipo="+comillas(ne));
            //Cambiado
            if(rs1.next() && rs1.getString(1).equals(user)){
                //stmt.executeUpdate("DELETE FROM pertenece WHERE equipo="+comillas(ne));
                stmt.executeUpdate("DELETE FROM equipos WHERE nombreEquipo="+comillas(ne));

                System.out.println("Se va a dar de baja al equipo: " + ne + " ¿Esta seguro de hacerlo? (Y/N): ");
                String opcionElegida=sc.nextLine();

                if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                    con.rollback(save);
                    System.out.println("Cancelando operacion... ");
                }
                else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                    con.commit();
                    System.out.println("El equipo ha sido dado de baja. ");
                }
                //System.out.println("\n"+result+" registros afectados.");
            }else{
                System.out.println("El equipo no existe o no eres el lider para realizar esta operacion.");
            }

        }catch(SQLException e){
            excepcion(e);
        }

    }



    public static void agregarJugador(Connection con, String user){
        try{

            Statement stmt= con.createStatement();
            Scanner sc= new Scanner(System.in);
            String nequipo="", njugador="";
            System.out.println("Introducir nombre del equipo al que desea invitar el jugador: ");
            nequipo= sc.nextLine();
                
            ResultSet rs1= stmt.executeQuery("SELECT lider FROM equipos WHERE nombreEquipo='"+nequipo+"'");
            
            if(rs1.next() && rs1.getString(1).equals(user)){

                System.out.println("Introducir nombre del jugador: ");
                njugador= sc.nextLine();
                ResultSet rs2= stmt.executeQuery("SELECT nombreUsuario FROM jugadores WHERE nombreUsuario=" + comillas(njugador));
                if(rs2.next()){
                    stmt.executeQuery("insert into pertenece(equipo, jugador) values("+comillas(nequipo)+", "+comillas(njugador)+")");
                    System.out.println("El jugador "+njugador+" ahora forma parte del equipo "+nequipo);
                    con.commit();
                }else{
                    System.out.println("El nombre de jugador no es valido. ");
                }
            }else{
                System.out.println("Para realizar esta operacion debes ser el lider del equipo. ");
            }
        }catch(SQLException e){
            excepcion(e);
        }

    }

    public static void echarJugador(Connection con, String user){
        try{

            Statement stmt= con.createStatement();
            String nequipo="", njugador="";
            Scanner sc= new Scanner(System.in);
            System.out.println("Introducir nombre del equipo del que desea eliminar el jugador: ");
            nequipo= sc.nextLine();

            ResultSet rs1= stmt.executeQuery("SELECT lider FROM equipos WHERE nombreEquipo=" + comillas(nequipo));
            
            if(rs1.next() && rs1.getString(1).equals(user)){

                Savepoint save= con.setSavepoint();
                System.out.println("Introducir nombre del jugador: ");
                njugador= sc.nextLine();
                ResultSet rs2= stmt.executeQuery("SELECT nombreUsuario FROM jugadores WHERE nombreUsuario=" + comillas(njugador));
                if(rs2.next()){
                    stmt.executeUpdate("DELETE FROM pertenece WHERE jugador="+comillas(njugador)+" AND equipo="+comillas(nequipo));

                    System.out.println("Se va a echar al jugador: " + njugador + " ¿Esta seguro de hacerlo? (Y/N): ");
                    String opcionElegida= sc.nextLine();

                    if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                        con.rollback(save);
                        System.out.println("Cancelando operacion... ");
                    }
                    else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                        con.commit();
                        System.out.println("El jugador "+njugador+" ha sido expulsado del equipo "+nequipo+". ");
                    }
                }else{
                    System.out.println("Para realizar esta operacion debes ser el lider del equipo. ");
                }

            }else{
                System.out.println("Para realizar esta operacion debes ser el lider del equipo o el nombre del equipo no es correcto ");
            }

        }catch(SQLException e){
            excepcion(e);
        }

    }

    public static void modificarEquipo(Connection con, String user){
        try {

            Statement stmt = con.createStatement();
            Savepoint save= con.setSavepoint();
            String ne="", nombreEquipo="", deporte="", tag="", lider="";
            Scanner sc= new Scanner(System.in);
            System.out.println("Inserte el nombre del equipo a modificar:");
            ResultSet rs1, rs;

            do {
                ne = sc.nextLine();
                rs1 = stmt.executeQuery("SELECT lider FROM equipos WHERE nombreEquipo=" + comillas(ne));
                rs1.next();
            }while(!rs1.getString(1).equals(user) && !ne.equals(""));
            if(!ne.equals("")){
                System.out.println("Datos actuales del equipo: ");
                mostrarEquipo(con, ne);

                do {
                    System.out.println("Nuevo (o poner el actual) deporte: ");
                    deporte = sc.nextLine();
                } while (!deporte.equals("Fútbol") && !deporte.equals("Baloncesto") && !deporte.equals("Tenis"));

                do {
                    System.out.println("Nuevo (o poner el actual) tag del equipo (3 letras): ");
                    tag = sc.nextLine();
                } while (tag.length() != 3);

                do{
                    System.out.println("Nuevo (o poner el actual) lider: ");
                    lider= sc.nextLine();
                    rs1 = stmt.executeQuery("SELECT nombreUsuario FROM jugadores WHERE nombreUsuario=" + comillas(lider));
                }while(!lider.equals(user) || !rs1.next());//Ojo
                stmt.executeQuery("UPDATE equipos SET deporte="+comillas(deporte)+", tag="+comillas(tag)+", lider="+comillas(lider)+" WHERE nombreEquipo="+comillas(ne));
                

                System.out.println("Se van a modificar los datos del equipo: " + ne + " ¿Esta seguro de hacerlo? (Y/N): ");
                String opcionElegida=sc.nextLine();

                if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                    con.rollback(save);
                    System.out.println("Cancelando operacion... ");
                }else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                    con.commit();
                    System.out.println("El equipo ha sido modificado.");
                    System.out.println("Nuevos datos: ");
                    mostrarEquipo(con, nombreEquipo);
                }


            }else{
                System.out.println("Saliendo de modificar equipo... ");
            }

        }catch(SQLException e){
            excepcion(e);
        }

    }




    public static void Menu(Connection con){

        Scanner sc=new Scanner(System.in);
        int op;
        String user=MeetNMatch.identificacionUsuario(con);
        try{

            Boolean salir=false;
            do{
                do{
                    System.out.println("Menú Gestion de Equipos: \n" + "\t 1: Crear Equipo \n" + "\t 2: Baja Equipo \n" + "\t 3: Añadir Jugador. \n" +"\t 4: Expulsar Jugador. \n"+ "\t 5: Modificar Jugador \n"+ "\t 6: Inscribir a encuentro \n"+ "\t 7: Aplicar sancion \n"+ "\t 8: Mostrar Equipo \n" + "\t 9: Salir. \n" );
                    op = Integer.parseInt(sc.nextLine());
                    if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5 && op!=6 && op!=7 && op!=8 && op!=9)
                        System.out.println("La opcion elegida no es valida");
                }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5 && op!=6 && op!=7 && op!=8 && op!=9);

                switch(op){
                    case 1:
                        crearEquipo(con, user);

                        break;
                    case 2:
                        bajaEquipo(con, user);
                        break;
                    case 3:
                        agregarJugador(con, user);
                        break;
                    case 4:
                        echarJugador(con, user);
                        break;
                    case 5:
                        modificarEquipo(con, user);
                        break;
                    case 6:
                        inscribirEquipo(con, user);
                        break;
                    case 7:
                        aplicarSancion(con);
                        break;
                    case 8:
                        mostrarEquipo(con);
                        break;
                    case 9:
                        System.out.println("Saliendo de Equipos...");
                        salir=true;
                        break;

                }

            }while(!salir);

       }catch(Exception e){ System.out.println(e); }
    }
}