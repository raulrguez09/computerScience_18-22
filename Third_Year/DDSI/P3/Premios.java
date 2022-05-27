/*
SUBSISTEMA ENCUENTROS de Raúl Castro Moreno
*/

package meetnmatch;


import java.sql.*;
import java.util.Scanner;
import java.util.Random;
import java.lang.*;
import java.util.Date;
import java.text.SimpleDateFormat;
import java.util.Calendar;


public  class Premios{ 

   
    
    public static void anadirPremio(Connection con){
        String codPre="";
        String nombre="";
        String descripcion;
        int cantidad,precio;  
        Scanner sc=new Scanner(System.in);
        Random random = new Random();
        Statement stmt;

        try{

            stmt=con.createStatement();
            do{
                System.out.println("Introduzca el nombre del premio(Máximo 50 caracteres):");
                nombre = sc.nextLine();
                if(nombre.length() > 50 || nombre.length() == 0)
                    System.out.println("Se ha introducido mal el dato:");        
            }while(nombre.length() > 50 || nombre.length() == 0);

            do{
                System.out.println("Introduzca la descripción del premio(Máximo 300 caracteres):");
                descripcion = sc.nextLine();
                if(descripcion.length() > 300 || descripcion.length() == 0)
                    System.out.println("Se ha introducido mal el dato:");        
            }while(descripcion.length() > 300 || descripcion.length() == 0);
            
            do{
                System.out.println("Introduzca la cantidad disponible del premio(Máximo 5 dígitos):");
                cantidad = Integer.parseInt(sc.nextLine());
                if(String.valueOf(cantidad).length() > 5 || String.valueOf(cantidad).length() == 0 || cantidad < 0)
                    System.out.println("Se ha introducido mal el dato:");        
            }while(String.valueOf(cantidad).length() > 5 || String.valueOf(cantidad).length() == 0 || cantidad < 0);
        
            do{
                System.out.println("Introduzca el precio en puntos del premio(Máximo 20 dígitos):");
                precio = Integer.parseInt(sc.nextLine());
                if(String.valueOf(precio).length() > 5 || String.valueOf(precio).length() == 0 || precio < 0)
                    System.out.println("Se ha introducido mal el dato:");        
            }while(String.valueOf(precio).length() > 5 || String.valueOf(precio).length() == 0 || precio < 0);

            ResultSet rs;
            do{
                codPre = MeetNMatch.generateRandomString(8);
                rs=stmt.executeQuery("SELECT codPre FROM premios WHERE codPre='"+codPre+"'");
            }while(rs.next());
            
            System.out.println("Se va a añadir el premio " + nombre + " con codigo "+codPre+" y todos sus detalles. ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                stmt.executeQuery("INSERT INTO Premios (codPre,nombre,descripcion,cantidad,precio) values('"+codPre+"','"+nombre+"','"+descripcion+"',"+cantidad+","+precio+")");
                con.commit();
                System.out.println("Se ha añadido el premio con éxito");
            } 
            
        }catch(Exception e){ System.out.println(e);}    

    }

    public static void borrarPremio(Connection con, String codPre){
        Statement stmt;
        Scanner sc=new Scanner(System.in);

        try{
            stmt= con.createStatement();

            Savepoint save = con.setSavepoint();
            
            stmt.executeUpdate("DELETE FROM premios WHERE codPre='"+codPre+"'");
            
            System.out.println("Se va a borrar el premio " + codPre + " y todos sus detalles. ¿Esta seguro de hacerlo? (Y/N): ");
            String opcionElegida=sc.nextLine();
            if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                con.rollback(save);
                System.out.println("Deshaciendo cambios");
            }
            else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                con.commit();
                System.out.println("Se ha borrado el premio con éxito");
            }
        


        }catch(Exception e){ System.out.println(e);}
    }

    public static void mostrarListaPremios(Connection con){
        Statement stmt;
        try{
            stmt=con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT codPre,nombre,descripcion,cantidad,precio FROM premios");
            System.out.println("\tCodigo del Premio\tNombre\tDescripcion\tCantidad disponible\tPrecio en Puntos");
            while(rs.next())
                System.out.println("\t"+rs.getString(1)+"\t" +rs.getString(2)+"\t" +rs.getString(3)+"\t" +rs.getInt(4)+"\t" +rs.getInt(5));
        } catch(Exception e){ System.out.println(e);}
    }

    public static void obtenerPuntos(Connection con,String usuario,String codEnc){
        Statement stmt;
        ResultSet rs;
        boolean adquirido=false,liderEsta = false,usuarioEsta = false,usuarioLocal = false,encuentroTerminado = false;
        int cantPunt = 0,puntos = 0,resultado = 0; //0 gana local , 1 empate, 2 gana visitante
        Calendar hoy = Calendar.getInstance();
        String usuarioLider="";
        String horaEnc="";
        String codEquipo="";
        int puntLoc = 0,puntVis = 0;
        Scanner sc=new Scanner(System.in);
    
        try{
            stmt=con.createStatement();

            rs=stmt.executeQuery("SELECT nomUsuario,codEnc FROM adquiere WHERE nomUsuario='"+usuario+"' AND codEnc='"+codEnc+"'");
            if(rs.next())
                adquirido = true;

            if(!adquirido){
                rs = stmt.executeQuery("SELECT usuarioLider,horaEnc,puntuacionLocal,puntuacionVisitante FROM encuentros WHERE codEnc='"+codEnc+"'");
                if(rs.next()){
                    usuarioLider = rs.getString(1);
                    horaEnc = rs.getString(2);
                    puntLoc = rs.getInt(3); 
                    puntVis = rs.getInt(4);
                }else
                    System.out.println("Fallo, no hay ningun encuentro idenficado por: "+codEnc);

                
                
                String fecha = hoy.get(Calendar.YEAR)+"-"+(hoy.get(Calendar.MONTH) + 1)+"-"+hoy.get(Calendar.DATE);
                String hora = hoy.get(Calendar.HOUR_OF_DAY)+":"+hoy.get(Calendar.MINUTE)+":"+hoy.get(Calendar.SECOND);
                int h = Integer.parseInt(horaEnc.substring(11,13));
                int n = h+2;
                String aux1 = horaEnc.substring(0,10);
                String aux2 = horaEnc.substring(11,18);
                aux2 = aux2.replaceAll(h+"",n+"");
                horaEnc = aux1+" "+aux2;
                
                SimpleDateFormat formatoFecha=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                Date dateEncuentro=formatoFecha.parse(horaEnc);
                Date dateActual = formatoFecha.parse(fecha+" "+hora);
                

                if(dateActual.after(dateEncuentro))                    
                    encuentroTerminado = true;

                    
                if(encuentroTerminado){
                    rs = stmt.executeQuery("SELECT equipo FROM inscripcionE WHERE codEnc='"+codEnc+"'");
                    if(rs.next()){
                        codEquipo=rs.getString(1);
                    

                        rs = stmt.executeQuery("SELECT jugador FROM pertenece WHERE equipo='"+codEquipo+"'");
                        while(rs.next()){
                            if(rs.getString(1).equals(usuario))
                                usuarioEsta = true;
                            if(rs.getString(1).equals(usuarioLider))
                                liderEsta = true;    
                        }
    
                        if((liderEsta && usuarioEsta) || (!liderEsta && !usuarioEsta))
                            usuarioLocal = true;

                        if(puntLoc < puntVis)
                            resultado = 2;
                        else if(puntLoc == puntVis) 
                            resultado = 1;
                    
                        rs = stmt.executeQuery("SELECT puntos FROM jugadores WHERE nombreUsuario='"+usuario+"'");
                        if(rs.next())
                            puntos = rs.getInt(1);

                        if((resultado == 0 && usuarioLocal) || (resultado == 2 && !usuarioLocal)){
                            cantPunt = 5000;
                            puntos += cantPunt;
                        }
                        else if((resultado == 2 && usuarioLocal) || (resultado == 0 && !usuarioLocal)){
                            cantPunt = 2500;
                            puntos += cantPunt;
                        }
                        else if( resultado == 1){
                            cantPunt = 4000;
                            puntos += cantPunt;
                        }
                        
                        Savepoint save = con.setSavepoint();  

                        stmt.executeQuery("INSERT INTO adquiere (nomUsuario,codEnc,cantidadPuntos) values('"+usuario+"','"+codEnc+"',"+cantPunt+")");
                        stmt.executeQuery("UPDATE jugadores SET puntos="+puntos+" WHERE nombreUsuario='"+usuario+"'");
                        
                        System.out.println("Se van a obtener puntos del encuentro: " + codEnc + " por parte del usuario: "+usuario+". ¿Esta seguro de hacerlo? (Y/N): ");
                        String opcionElegida=sc.nextLine();
                        if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                            con.rollback(save);
                            System.out.println("Deshaciendo cambios");
                        }
                        else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                            con.commit();
                            System.out.println("Puntos obtenidos con éxito");
                        }

                    }else
                        System.out.println("Fallo, no hay ningun equipo inscrito en el encuentro: "+codEnc);
            
                }else
                    System.out.println("No se pueden obtener puntos puesto que el encuentro no ha finalizado");
            
            }else
                System.out.println("No se pueden obtener puntos puesto que ya se han recibido de este encuentro"); 

        } catch(Exception e){ System.out.println(e);}
    }

    public static void obtenerPremio(Connection con,String usuario,String codPre){
        Statement stmt;
        String codigoPremio="";
        ResultSet rs;
        int puntos = 0,cantidad = 0,precio = 0;
        Scanner sc=new Scanner(System.in);

        try{
            stmt=con.createStatement();
            rs = stmt.executeQuery("SELECT cantidad,precio FROM premios WHERE codPre='"+codPre+"'");
            if(rs.next()){
                cantidad = rs.getInt(1);
                precio = rs.getInt(2);
            }else
                System.out.println("Fallo en leer premio");


            if(cantidad > 0){
                cantidad = cantidad - 1;
                rs = stmt.executeQuery("SELECT puntos FROM jugadores WHERE nombreUsuario='"+usuario+"'");
                if(rs.next()){
                    puntos = rs.getInt(1); 
                }else
                     System.out.println("Fallo en leer puntos del jugador");

                if(puntos >= precio){
                    puntos = puntos - precio;
                    
                    do{
                        codigoPremio = MeetNMatch.generateRandomString(16);
                        rs=stmt.executeQuery("SELECT codigoPremio FROM premios WHERE codigoPremio='"+codigoPremio+"'");
                    }while(rs.next());    
                
                    Savepoint save = con.setSavepoint();  

                    stmt.executeQuery("UPDATE premios SET cantidad="+cantidad+" WHERE codPre='"+codPre+"'");
                    stmt.executeQuery("UPDATE jugadores SET puntos="+puntos+" WHERE nombreUsuario='"+usuario+"'");
                    stmt.executeQuery("INSERT INTO consigue (nomUsuario,codigoPremio,codPre) values('"+usuario+"','"+codigoPremio+"',"+codPre+")");

                    System.out.println("Se va a canjear el premio: " + codPre + ". ¿Esta seguro de hacerlo? (Y/N): ");
                    String opcionElegida=sc.nextLine();
                    if(opcionElegida.equals("N") || opcionElegida.equals("n")){
                        con.rollback(save);
                        System.out.println("Deshaciendo cambios");
                    }
                    else if(opcionElegida.equals("Y") || opcionElegida.equals("y")){
                        con.commit();
                        System.out.println("Se ha canjeado el premio con éxito");
                    }

                }else
                    System.out.println("El usuario no dispone de puntos suficientes para obtener el premio"); 
            }else
                System.out.println("No hay stock disponible del premio solicitado"); 

        } catch(Exception e){ System.out.println(e);}
    }

    public static void Menu(Connection con){

       Scanner sc=new Scanner(System.in);
         int op;
       
        try{

        
         Boolean salir=false;
        do{
            do{
                System.out.println("Menú Premios: \n" + "\t 1: Añadir premio. \n" + "\t 2: Borrar Premio. \n" + "\t 3: Mostrar premio. \n" +"\t 4: Obtener puntos. \n"+ "\t 5: Obtener premio. \n" + "\t 6: Salir. \n" );
                op = Integer.parseInt(sc.nextLine());
                if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5 && op!=6)
                System.out.println("La opcion elegida no es valida");
            }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5 && op!=6);
        
            switch(op){
                case 1:
                    anadirPremio(con);
                break;

                case 2:
                    String codPre;
                    System.out.println("Introduzca el código del premio a borrar:");
                    codPre = sc.nextLine();
                    borrarPremio(con,codPre);
                break;

                case 3:
        
                    mostrarListaPremios(con);
                break;

                case 4:
                    String usuario,codEnc;
                    System.out.println("Introduzca el código usuario:");
                    usuario = sc.nextLine();
                    System.out.println("Introduzca el código encuentro:");
                    codEnc = sc.nextLine();
                    obtenerPuntos(con,usuario,codEnc);
                break;

                case 5:
                    System.out.println("Introduzca el código usuario:");
                    usuario = sc.nextLine();
                    System.out.println("Introduzca el código premio:");
                    codPre = sc.nextLine();
                    obtenerPremio(con,usuario,codPre);
                break;

                case 6:
                    System.out.println("Saliendo de Premios...");
                    salir=true;
                break;
          
            }

        }while(!salir);

        }catch(Exception e){ System.out.println(e);}
    }
   
    }

    
