/*
SUBSISTEMA JUGADORES de Raúl Rodríguez Pérez
*/

package meetnmatch;



import java.sql.*;
import java.util.Scanner;
import java.sql.SQLException;
import java.lang.*;


public  class Jugadores{ 

    public static void altaJugador(Connection con){
        String datosLeidos;
        String nombre, apellidos, telefono, nombreUsuario, edad, altura, peso, carrera, deportesPreferentes, disponibilidadMaterial; 
        String equipo, puntos, jugSancionado, descripcionMaterial="", descripcionSancion;
        int disponibleMaterial=0;
        
        int Edad, Altura, Peso;
        boolean malEscrito = false;
        ResultSet rs;
        
        int opcionElegida;
        Scanner sc = new Scanner(System.in);
        Statement stmt;
        
        try{
            
            stmt = con.createStatement();
            
            do{
                System.out.println("Introduce tu nombre (max 20 caracteres): ");
                nombre = sc.nextLine();
            
                if(nombre.length() <= 0 || nombre.length() > 20)
                System.out.println("Se han introducido mal el nombre, intentelo de nuevo");
                System.out.println();
                
            }while(nombre.length() <= 0 || nombre.length() > 20);

            do{
                System.out.println("Introduce tus apellidos (max 40 caracteres): ");
                apellidos = sc.nextLine();
                
                if(apellidos.length() <= 0 || apellidos.length() > 40)
                System.out.println("Se han introducido mal los apellidos, intentelo de nuevo");
                System.out.println();

            }while(apellidos.length() <= 0 || apellidos.length() > 40);

            do{
                System.out.println("Introduce tu numero de telefono (max 20 caracteres (puede tener '+' al principio)): ");
                telefono = sc.nextLine();
                
                if(telefono.length() <= 0 || telefono.length() > 20)
                System.out.println("Se han introducido mal el telefono, intentelo de nuevo");
                System.out.println();
                
            }while(telefono.length() <= 0 || telefono.length() > 20);
            
            do{
                System.out.println("Introduce tu nombre de usuario (max 15 caracteres): ");
                System.out.println("Recuerde que el nombre de usuario puede incluir letras (a-z), números (0-9) y puntos (.)");
                System.out.println("Pero no pueden incluir signos como et (&), igual (=), guiones bajos (_), apóstrofes ('), guiones (-), corchetes (< >), el signo más (+), comas (,), ni dos o más puntos seguidos");
                
                malEscrito = false;
                nombreUsuario = sc.nextLine();
                
                rs = stmt.executeQuery("SELECT nombreUsuario FROM Jugadores WHERE nombreUsuario='"+ nombreUsuario + "'");
                
                for(int i = 0; i < nombreUsuario.length() && !malEscrito; i++){
                    char letra = nombreUsuario.charAt(i);
                    if(letra == '&' || letra == '=' || letra == '_' || letra == '\'' || letra == '-' || letra == '<' || letra == '>' || letra == '+' || letra == '-' || letra == ','){
                        malEscrito = true;
                    }
                    if(letra == '.' && nombreUsuario.charAt(i+1) == '.'){
                        malEscrito = true;
                    }
                }
                
                if(malEscrito == true){
                    System.out.println("Se han introducido mal el nombre de usuario, intentelo de nuevo");
                    System.out.println();
                }
                
            }while(nombreUsuario.length() <= 0 || nombreUsuario.length() > 15 || malEscrito == true || rs.next());

            do{
                System.out.println("Introduce tu edad: ");
                edad = sc.nextLine();
                Edad = Integer.parseInt(edad);
                
                if(Edad <= 0 || Edad > 99)
                System.out.println("Se han introducido mal el Edad, intentelo de nuevo");
                System.out.println();
                
            }while(Edad <= 0 || Edad > 99);
            
            do{
                System.out.println("Introduce tu altura: ");
                altura = sc.nextLine();
                Altura = Integer.parseInt(altura);

                if(Altura <= 140 || Altura > 220)
                System.out.println("Se han introducido mal la altura, intentelo de nuevo");
                    System.out.println();
                    
                }while(Altura <= 140 || Altura > 220);

                do{
                System.out.println("Introduce tu peso: ");
                peso = sc.nextLine();
                Peso = Integer.parseInt(peso);

                if(Peso <= 40 || Peso > 150)
                System.out.println("Se han introducido mal el peso, intentelo de nuevo");
                System.out.println();
                
            }while(Peso <= 40 || Peso > 150);

            do{
                System.out.println("Introduce el nombre del equipo profesional en el que has jugado (max 30 caracteres): ");
                System.out.println("Si no has jugado profesionalmente a ningun deporte, simplemente introduce 'no'");
                carrera = sc.nextLine();
                
                if(carrera.length() <= 0 || carrera.length() > 30){
                    System.out.println("Se han introducido mal la carrera profesional, intentelo de nuevo");
                    System.out.println();
                }
                
            }while(carrera.length() <= 0 || carrera.length() > 30);    
            
            equipo = null;
            
            puntos = "0";
            int Puntos = Integer.parseInt(puntos);
            
            jugSancionado = "0";
            int JugSancionado = Integer.parseInt(jugSancionado);
            
            do{
                System.out.println("Introduce los deportes que más te interese jugar: (max 100 caracteres): ");
                deportesPreferentes = sc.nextLine();
                
                if(deportesPreferentes.length() <= 0 || deportesPreferentes.length() > 100){
                    System.out.println("Se han introducido mal los deportes preferentes, intentelo de nuevo");
                    System.out.println();
                }
                
            }while(deportesPreferentes.length() <= 0 || deportesPreferentes.length() > 100);  
            
            System.out.println("¿Dispones de algun tipo de material para jugar? (si/no)");
            disponibilidadMaterial = sc.nextLine();
            if(disponibilidadMaterial.equals("si")){
                disponibleMaterial=1;
                
                do{
                    System.out.println("Introduce la descripcion del material (500 caracteres): ");
                    descripcionMaterial = sc.nextLine();
                    
                    if(descripcionMaterial.length() <= 0 || descripcionMaterial.length() > 500){
                        System.out.println("Se han introducido mal la descripcion del material, intentelo de nuevo");
                        System.out.println();
                    }
                }while(descripcionMaterial.length() <= 0 || descripcionMaterial.length() > 500);
                
            }else if (disponibilidadMaterial.equals("no")){
                descripcionMaterial = "NO TIENE MATERIAL";
            } 
            
            descripcionSancion = "NO HAY";
            
            Savepoint save = con.setSavepoint();
            //stmt.executeQuery("insert into Jugadores (nombre, apellidos, teléfono, nombreUsuario, edad, altura, peso, carreraProfesional, equipo, deportesPreferentes, disponibilidadMaterial, descripcionMaterial) values('"+nombre+"', '"+apellidos+"', "+telefono+", '"+nombreUsuario+"', "+Edad+", "+Altura+", "+Peso+", '"+carrera+"', '"+equipo+"','"+deportesPreferentes+"', '"+disponibilidadMaterial+"', '"+descripcionMaterial+"')"); 
            stmt.executeQuery("insert into Jugadores (nombre,apellidos,teléfono,nombreUsuario,edad,altura,peso,carreraProfesional,deportesPreferentes,disponibilidadMaterial,descripcionMaterial) values('"+nombre+"','"+apellidos+"',"+telefono+",'"+nombreUsuario+"',"+Edad+","+Altura+","+Peso+",'"+carrera+"','"+deportesPreferentes+"','"+disponibleMaterial+"','"+descripcionMaterial+"')"); 
            
            con.commit();
            
            
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

    public static void bajaJugador(Connection con){
        try{
            ResultSet rs1;
            Statement stmt;
            stmt = con.createStatement();   
            Scanner sc = new Scanner(System.in);          
            Savepoint save1 = con.setSavepoint();
            String nombreUsuario;
            Boolean existe;
            do{
                System.out.println("Introduce el nombre del jugador para dar de baja: ");
                nombreUsuario = sc.nextLine();
                rs1 = stmt.executeQuery("SELECT nombreUsuario FROM Jugadores WHERE nombreUsuario='"+nombreUsuario+"'");
                
                existe=rs1.next();  
                if(!existe){
                    System.out.println("El nombre de usuario introducido no se encuentra, intentelo de nuevo: "); 
                }
                
            }while(!existe);

            rs1 = stmt.executeQuery("SELECT jugador FROM Pertenece WHERE jugador='"+nombreUsuario+"'");

            while(rs1.next()){

                stmt.executeUpdate("DELETE FROM Pertenece WHERE jugador='"+nombreUsuario+"'");
            }

            stmt.executeUpdate("DELETE FROM jugadores WHERE nombreusuario='"+nombreUsuario+"'");
            System.out.println("Se va a dar de baja el jugador con nombre de usuario: " + nombreUsuario + ". ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                con.commit();
                System.out.println("Baja efectuada con éxito");
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
    }
    
    public static void modificarJugador(Connection con){
        String datosLeidos;
        String nombreUsuario, nombre, apellidos, telefono, edad, altura, peso, deportesPreferentes, disponibilidadMaterial, descripcionMaterial="";
        int disponibleMaterial=0;
        
        int Edad, Altura, Peso;
        boolean fin = false;
        ResultSet rs;
        
        int opcion;
        Scanner sc = new Scanner(System.in);
        Statement stmt;
        try{
            Savepoint save1 = con.setSavepoint();
            stmt = con.createStatement();
            do{
                System.out.println("Escribame su nombre de usuario: ");
                nombreUsuario = sc.nextLine();

                System.out.println("Elige uno de los campos que quiera modificar: ");
                System.out.println("\t1) Nombre" + "\t2) Apellidos" + "\t3) Telefono" + "\t4) Edad" + "\t5) altura" + "\t6) peso" + "\t7) deportesPreferentes" + "\t8) Material" + "\t9) salir");
                opcion = Integer.parseInt(sc.nextLine());
                
                switch(opcion){
                    case 1:
                        do{
                            System.out.println("Introduce tu nuevo nombre (max 20 caracteres): ");
                            nombre = sc.nextLine();
                        
                            if(nombre.length() <= 0 || nombre.length() > 20)
                            System.out.println("Se han introducido mal el nuevo nombre, intentelo de nuevo");
                            System.out.println();
                            
                        }while(nombre.length() <= 0 || nombre.length() > 20);

                        stmt.executeQuery("UPDATE Jugadores SET nombre='"+nombre+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 2:
                        do{
                            System.out.println("Introduce tus nuevos apellidos (max 40 caracteres): ");
                            apellidos = sc.nextLine();
                            
                            if(apellidos.length() <= 0 || apellidos.length() > 40)
                            System.out.println("Se han introducido mal los nuevos apellidos, intentelo de nuevo");
                            System.out.println();
            
                        }while(apellidos.length() <= 0 || apellidos.length() > 40);

                        stmt.executeQuery("UPDATE Jugadores SET apellidos='"+apellidos+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 3:
                        do{
                            System.out.println("Introduce tu nuevo numero de telefono (max 20 caracteres (puede tener '+' al principio)): ");
                            telefono = sc.nextLine();
                            
                            if(telefono.length() <= 0 || telefono.length() > 20)
                            System.out.println("Se han introducido mal el nuevo telefono, intentelo de nuevo");
                            System.out.println();
                            
                        }while(telefono.length() <= 0 || telefono.length() > 20);

                        stmt.executeQuery("UPDATE Jugadores SET telefono='"+telefono+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 4:
                        do{
                            System.out.println("Introduce tu nueva edad: ");
                            edad = sc.nextLine();
                            Edad = Integer.parseInt(edad);
                            
                            if(Edad <= 0 || Edad > 99)
                            System.out.println("Se han introducido mal la nueva Edad, intentelo de nuevo");
                            System.out.println();
                            
                        }while(Edad <= 0 || Edad > 99);

                        stmt.executeQuery("UPDATE Jugadores SET edad='"+Edad+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 5:
                        do{
                            System.out.println("Introduce tu altura: ");
                            altura = sc.nextLine();
                            Altura = Integer.parseInt(altura);
            
                            if(Altura <= 140 || Altura > 220)
                                System.out.println("Se han introducido mal la altura, intentelo de nuevo");
                                System.out.println();
                                
                        }while(Altura <= 140 || Altura > 220);

                        stmt.executeQuery("UPDATE Jugadores SET altura='"+Altura+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 6:
                        do{
                            System.out.println("Introduce tu peso: ");
                            peso = sc.nextLine();
                            Peso = Integer.parseInt(peso);
            
                            if(Peso <= 40 || Peso > 150)
                            System.out.println("Se han introducido mal el peso, intentelo de nuevo");
                            System.out.println();
                            
                        }while(Peso <= 40 || Peso > 150);

                        stmt.executeQuery("UPDATE Jugadores SET peso='"+Peso+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 7:
                        do{
                            System.out.println("Introduce los deportes que más te interese jugar: (max 100 caracteres): ");
                            deportesPreferentes = sc.nextLine();
                            
                            if(deportesPreferentes.length() <= 0 || deportesPreferentes.length() > 100){
                                System.out.println("Se han introducido mal los deportes preferentes, intentelo de nuevo");
                                System.out.println();
                            }
                            
                        }while(deportesPreferentes.length() <= 0 || deportesPreferentes.length() > 100);
                        
                        stmt.executeQuery("UPDATE Jugadores SET desportesPreferentes='"+deportesPreferentes+"' WHERE nombreUsuario='"+nombreUsuario+"'");
                    break;

                    case 8:
                        System.out.println("¿Dispones de algun tipo nuevo de material para jugar? (si/no)");
                        disponibilidadMaterial = sc.nextLine();
                        if(disponibilidadMaterial.equals("si")){
                            disponibleMaterial=1;
                            
                            do{
                                System.out.println("Introduce la descripcion del nuevo material (500 caracteres): ");
                                descripcionMaterial = sc.nextLine();
                                
                                if(descripcionMaterial.length() <= 0 || descripcionMaterial.length() > 500){
                                    System.out.println("Se han introducido mal la descripcion del material, intentelo de nuevo");
                                    System.out.println();
                                }
                            }while(descripcionMaterial.length() <= 0 || descripcionMaterial.length() > 500);
                            
                        }else if (disponibilidadMaterial.equals("no")){
                            descripcionMaterial = "NO TIENE MATERIAL";
                        }

                        stmt.executeQuery("UPDATE Jugadores SET disponibilidadMaterial='"+disponibleMaterial+"' WHERE codVal='"+nombreUsuario+"'");
                        stmt.executeQuery("UPDATE Jugadores SET descripcionMaterial='"+descripcionMaterial+"' WHERE codVal='"+nombreUsuario+"'");
                    break;
                    case 9:
                        fin = true;
                    break;
                }
            } while(!fin);
 
            System.out.println("Se va a establecer todas las modificciones que has realizado, ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                con.commit();
                System.out.println("Modificaciones efectuadas con éxito");
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

    public static void mostrarJugador(Connection con){
        try{
            Statement stmt;
            stmt=con.createStatement();
            String nombreUsuario; 
            Scanner sc=new Scanner(System.in);
            System.out.println("Introduce el nombre del jugador para mostrar: ");
            nombreUsuario = sc.nextLine();

            ResultSet rs = stmt.executeQuery("SELECT * FROM jugadores WHERE nombreUsuario='"+nombreUsuario+"'");
            if(rs.next())
            System.out.println("\tDatos del usuario\nNombre del jugador: "+rs.getString(1)+"\nApellidos: "+rs.getString(2)+"\nTelefono: "+rs.getString(3)+"\nNombreUsuario: "+rs.getString(4)+"\nEdad: "+rs.getInt(5)+"\nAltura: "+rs.getInt(6)+"\nPeso: "+rs.getInt(7)+
            "\nCarrera: "+rs.getString(8)+ "\nEquipo: "+rs.getString(9)+"\nPuntos: "+rs.getInt(10)+"\ndeportesPreferentes: "+rs.getString(12)+"\ndescripcionMaterial: "+rs.getString(14));
        } catch(SQLException e){ System.out.println(e); }
    }

    public static void inscribirEncuentro(String codEnc, String nombreUsuario, Connection con){
        try{
            ResultSet rs1, rs2;
            Statement stmt;
            Scanner sc=new Scanner(System.in);
            stmt = con.createStatement();             
            Savepoint save1 = con.setSavepoint();

            rs1 = stmt.executeQuery("SELECT nombreUsuario FROM Jugadores WHERE nombreUsuario='"+nombreUsuario+"'");    
            if(!rs1.next()){
                System.out.println("El nombre de usuario introducido no se encuentra"); 
            }
            else{
                rs2 = stmt.executeQuery("SELECT codEnc FROM encuentros WHERE codEnc='"+codEnc+"'");
                if(!rs2.next()){
                    System.out.println("El codigo de encuentro introducido no se encuentra"); 
                }
                else{
                    stmt.executeQuery("INSERT INTO inscripciónJ (nombreUsuario, codEnc) values('"+nombreUsuario+"','"+codEnc+"')");
                
            
            
            System.out.println("Se va a inscribir al jugador con nombre de usuario: " + nombreUsuario + " en el encuentro: " + codEnc + ". ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                con.commit();
                System.out.println("Inscripcion efectuada con éxito");
            }
            }}
            
        }catch(SQLException e){ System.out.println("Código de Error: " + e.getErrorCode() + "\n" +
            "SQLState: " + e.getSQLState() + "\n" +
            "Mensaje: " + e.getMessage());
            
            Throwable t = e.getCause();
            while(t != null) {
                System.out.println("Causa: " + t + "\n");
                t = t.getCause();
            }
        }
    }

    public static void aplicarSancion(Connection con){
        String descripcionSancion, nombreUsuario;
        int jugSancionado;
        ResultSet rs;
        Scanner sc = new Scanner(System.in);
        Statement stmt;
        try{
            Savepoint save1 = con.setSavepoint();
            stmt = con.createStatement();
            System.out.println("Escribe su nombre de usuario: ");
            nombreUsuario = sc.nextLine();
                
            jugSancionado = 1;
            do{
                System.out.println("Introduce la descripcion de la sancion (max 500 caracteres): ");
                descripcionSancion = sc.nextLine();
                
                if(descripcionSancion.length() <= 0 || descripcionSancion.length() > 500){
                    System.out.println("Se han introducido mal la descripcion de sancion, intentelo de nuevo");
                    System.out.println();
                }
            }while(descripcionSancion.length() <= 0 || descripcionSancion.length() > 500);

            stmt.executeQuery("UPDATE Jugadores SET jugSancionado='"+jugSancionado+"' WHERE nombreUsuario='"+nombreUsuario+"'");
            stmt.executeQuery("UPDATE Jugadores SET descripcionSancion='"+descripcionSancion+"' WHERE nombreUsuario='"+nombreUsuario+"'");
            
            System.out.println("Se va a establecer todas las modificciones que has realizado, ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save1);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                con.commit();
                System.out.println("Modificaciones efectuadas con éxito");
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

    public static void Menu(Connection con){
        String nombreUsuario, codEnc;   
        Scanner sc=new Scanner(System.in);
        int op;
    
    try{
       
        Boolean salir=false;
    do{
        do{
            System.out.println("Menú jugadores: \n" + "\t 1: AltaJugador \n" + "\t 2: BajaJugador \n" + "\t 3: ModificarJugador. \n" +"\t 4: MostrarJugador. \n"+ "\t 5: InscribirEncuentro \n" + "\t 6: AplicarSancion \n" + "\t 7: Salir. \n" );
            op = Integer.parseInt(sc.nextLine());
            if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5 && op!=6 && op!=7)
            System.out.println("La opcion elegida no es valida");
        }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5  && op!=6 && op!=7);
    
        switch(op){
            case 1:
                altaJugador(con);
            break;

            case 2:
                bajaJugador(con);
            break;

            case 3:
                modificarJugador(con);
            break;

            case 4:
                mostrarJugador(con);
            break;
            case 5:
                System.out.println("Escribe el nombre de usuario: ");
                nombreUsuario = sc.nextLine();
                System.out.println("Escribe el codigo del encuentro: ");
                codEnc = sc.nextLine();
                inscribirEncuentro(codEnc, nombreUsuario, con);
            break;
            case 6:
                aplicarSancion(con);
            break;
            case 7:
                System.out.println("Saliendo de Jugadores...");
                salir=true;
            break;
        
        }

    }while(!salir);
    
    }catch(Exception e){ System.out.println(e);}
    }
};

    


    
    
    
