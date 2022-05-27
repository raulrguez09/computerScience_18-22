/*
SUBSISTEMA UBICACIONES de Cristian Fernández Jiménez
*/

package meetnmatch;

import java.sql.*;
import java.util.Scanner;
import java.sql.SQLException;
import java.lang.*;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Ubicaciones{ 



    public static void bajaUbicacion(Connection con){
        String datosLeidos;
        Scanner sc=new Scanner(System.in);
        Statement stmt;
      
        String codUbi;
        String justificacion;
        ResultSet rs1;

        try{

            stmt=con.createStatement();
            
            do{
            System.out.println("Introducir codigo de ubicacion a establecer como fuera de servicio: ");
            
                codUbi=sc.nextLine();
                rs1=stmt.executeQuery("select codUbi from ubicacion where codUbi='"+codUbi+"' AND fueraServicio=0");
            }while(!rs1.next());

            do{
                System.out.println("Añada una justificacion para la baja de la ubicacion (500 caracteres): ");
                justificacion=sc.nextLine();
            }while(justificacion.length()>500);

           
            System.out.println("Va a establecer como fuera de servicio la ubicacion: " + codUbi);

            System.out.println("\n¿Esta seguro? (s/n)");
            do{
            datosLeidos=sc.nextLine();
            }while(!datosLeidos.equals("S") && !datosLeidos.equals("s") && !datosLeidos.equals("n") && !datosLeidos.equals("N") );
            
            if(datosLeidos.equals("S") || datosLeidos.equals("s")){

            stmt.executeQuery("update ubicacion set justBaja='"+justificacion+"', fueraServicio=1 where codUbi='"+codUbi+"'");
            System.out.println("Ubicacion " + codUbi + " fuera de servicio.");
            con.commit();
            }
            else{
                System.out.println("Baja descartada");

            }
        }catch(Exception e){ System.out.println(e);}       
    }

    
    
     public static void rehabilitadoUbicacion(Connection con){
        String datosLeidos;
        Scanner sc=new Scanner(System.in);
        Statement stmt;
      
        String codUbi;
        ResultSet rs1;
   
        try{

            stmt=con.createStatement();
            
            do{
            System.out.println("Introducir codigo de ubicacion a establecer de nuevo en el servicio: ");
            
                codUbi=sc.nextLine();
                rs1=stmt.executeQuery("select codUbi from ubicacion where codUbi='"+codUbi+"' AND fueraServicio=1");
            }while(!rs1.next());

           
            System.out.println("Va a establecer de nuevo la ubicacion: " + codUbi);

            System.out.println("\n¿Esta seguro? (s/n)");
            do{
            datosLeidos=sc.nextLine();
            }while(!datosLeidos.equals("S") && !datosLeidos.equals("s") && !datosLeidos.equals("n") && !datosLeidos.equals("N") );
            
            if(datosLeidos.equals("S") || datosLeidos.equals("s")){

            stmt.executeQuery("update ubicacion set justBaja='', fueraServicio=0 where codUbi='"+codUbi+"'");
            System.out.println("Ubicacion " + codUbi + " de nuevo en el servicio.");
            con.commit();
            }
            else{
                System.out.println("Renovacion descartada");

            }
        }catch(Exception e){ System.out.println(e);}       
    }
    public static void altaUbicacion(Connection con){
        String datosLeidos;
        Scanner sc=new Scanner(System.in);
        Statement stmt;
      
        String codUbi;
        String localizacion;
        String deporteUbi;
        String descripcion;
        int necesarioPago=0;
        int pagoAlquiler=0;
        String horaApertura="00:00";
        String horaCierre="00:00";

        
        try{

            stmt=con.createStatement();
            
            System.out.println("Introducir datos de ubicacion\n");
            do{
                System.out.println("Localizacion (100 caracteres): ");
                localizacion=sc.nextLine();
            }while(localizacion.length()>100);

            do{
                System.out.println("Deporte disponible (20 caracteres): ");
                deporteUbi=sc.nextLine();
            }while(deporteUbi.length()>20);

            do{
                System.out.println("Descripcion actual del lugar (500 caracteres): ");
                descripcion=sc.nextLine();
            }while(descripcion.length()>500);

            do{
                System.out.println("Necesario pago para el alquiler (1 SI - 0 NO): ");
                datosLeidos=sc.nextLine();
                necesarioPago=Integer.parseInt(datosLeidos);
            }while(necesarioPago!=0 && necesarioPago!=1);

            if(necesarioPago==1){
                System.out.println("Cantidad a pagar por alquiler: ");
                datosLeidos=sc.nextLine();
                pagoAlquiler=Integer.parseInt(datosLeidos);
            }

            System.out.println("Hora de apertura(HH:MM): ");
            horaApertura=sc.nextLine();

            System.out.println("Hora de cierre(HH:MM): ");
            horaCierre=sc.nextLine();

            ResultSet rs1;
            do{
            codUbi=MeetNMatch.generateRandomString(5);
            rs1=stmt.executeQuery("select codUbi from ubicacion where codUbi='"+codUbi+"'");

            }while(rs1.next());
            
            System.out.println("Va a insertar la siguiente ubicacion: ");
            System.out.println("Codigo ubicacion: " + codUbi);
            System.out.println("Localizacion: " + localizacion);
            System.out.println("Descripcion: " + descripcion);
            System.out.println("Deporte: " + deporteUbi);
            System.out.println("Necesario Pago: " + necesarioPago);
            if(necesarioPago==1)
            System.out.println("A pagar por alquiler: " + pagoAlquiler);
            System.out.println("Hora de apertura: " + horaApertura);
            System.out.println("Hora de cierre: " + horaCierre);

            do{
            System.out.println("\n¿Esta seguro de su insercion? (s/n)");
            datosLeidos=sc.nextLine();
            }while(!datosLeidos.equals("S") && !datosLeidos.equals("s") && !datosLeidos.equals("n") && !datosLeidos.equals("N") );
            
            if(datosLeidos.equals("S") || datosLeidos.equals("s")){

            stmt.executeQuery("insert into ubicacion (codUbi,localizacion,deportesUbi,descAct,necesarioPago,pagoAlquiler,horaApertura,horaCierre) values('"+codUbi+"','"+localizacion+"','"+deporteUbi+"','"+descripcion+"','"+necesarioPago+"','"+pagoAlquiler+"',TO_DATE('"+horaApertura+"','HH24:MI'),TO_DATE('"+horaCierre+"','HH24:MI'))");
            System.out.println("Ubicacion " + codUbi + " añadida.");
            con.commit();
            }
            else{
                System.out.println("Insercion descartada");

            }
        }catch(Exception e){ System.out.println(e);}       
    }

        
    public static void mostrarDatosUbicacion(Connection con){
        try{
            Statement stmt;
            stmt=con.createStatement();
            ResultSet rs;
            Scanner sc=new Scanner(System.in);
            String datosLeidos;
            do{
            System.out.println("Introducir codigo de ubicacion a mostrar: ");
            
                datosLeidos=sc.nextLine();
                rs=stmt.executeQuery("select fueraServicio from ubicacion where codUbi='"+datosLeidos+"'");
            }while(!rs.next());
            
            if(rs.getInt(1)==0){
            System.out.println("La ubicacion se encuentra ACTIVA");
            }
            else{
                System.out.println("La ubicacion se encuentra FUERA DE SERVICIO");
                rs=stmt.executeQuery("select justBaja from ubicacion where codUbi='"+datosLeidos+"'");
                if(rs.next())
                    System.out.println("Debido a: " + rs.getString(1));
            }
            rs = stmt.executeQuery("SELECT codUbi,localizacion,deportesUbi,descAct,necesarioPago,pagoAlquiler,horaApertura,horaCierre FROM ubicacion WHERE codUbi='"+datosLeidos+"'");
            if(rs.next())
                System.out.println("\nCodigo: "+rs.getString(1)+"\nLocalizacion: " +rs.getString(2)+"\nDeportes: " +rs.getString(3)+"\nDescripcion: " +rs.getString(4)+"\nNecesarioPago: " +rs.getInt(5)+"\nPago Alquiler: " +rs.getInt(6)+"\nHoraApertura: " +rs.getString(7).substring(11,16)+"\nHoraCierre: " +rs.getString(8).substring(11,16));
        } catch(Exception e){ System.out.println(e);}
    }
         
    
    public static void consultarDisponibilidad(Connection con, Boolean insertar, String usuario){
        try{
            Statement stmt;
            stmt=con.createStatement();
            ResultSet rs;
            Scanner sc=new Scanner(System.in);
            String datosLeidos, fecha, horaA, horaC, deporte;
            String horaApertura, horaCierre, deportesDisponibles;
            SimpleDateFormat formatoHora=new SimpleDateFormat("HH:mm");

            do{
            System.out.println("Introducir codigo de ubicacion a consultar: ");
                datosLeidos=sc.nextLine();
                rs=stmt.executeQuery("select fueraServicio,horaApertura,horaCierre,deportesUbi from ubicacion where codUbi='"+datosLeidos+"'");
            }while(!rs.next());
            
            if(rs.getInt(1)==0){
            System.out.println("La ubicacion se encuentra ACTIVA");
            horaApertura=rs.getString(2).substring(11,16);
            horaCierre=rs.getString(3).substring(11,16);
            System.out.println("Hora de apertura: "+horaApertura+" Hora de cierre: "+horaCierre);
            deportesDisponibles= rs.getString(4);
            System.out.println("Deportes: " +deportesDisponibles);
            Date hora1, hora2;
            Date horaAp=formatoHora.parse(horaApertura);
            Date horaCi=formatoHora.parse(horaCierre);   

            System.out.println("Introduzca la fecha que desea consultar (DD/MM/YY): ");
            fecha=sc.nextLine();

            do{
                System.out.println("Introduzca la hora de inicio del alquiler (HH:MM): ");
                horaA=sc.nextLine();
                hora1=formatoHora.parse(horaA);
            }while(hora1.before(horaAp));

            do{
                System.out.println("Introduzca la hora de salida del alquiler (HH:MM): ");
                horaC=sc.nextLine();
                hora2=formatoHora.parse(horaC);
            }while(hora2.after(horaCi) || hora2.before(hora1) || hora2.equals(hora1));

            do{
                System.out.println("Introduzca el deporte para el alquiler: ");
                deporte=sc.nextLine();
            }while(!deportesDisponibles.contains(deporte));
            
            System.out.println("Realizando la consulta...");
            Thread.sleep(1000);
            
            ResultSet rs2=stmt.executeQuery("select codUbi from alquiler where codUbi='"+datosLeidos+"' AND fechaAlq='"+fecha+"' AND horaInicio=TO_DATE('"+horaA+"','HH24:MI') AND horaFin=TO_DATE('"+horaC+"','HH24:MI') AND deporteAlq='"+deporte+"'");
            
            if(rs2.next()){
                System.out.println("\nLo sentimos, en ese tramo NO ESTA DISPONIBLE esa ubicacion");
            }else{ 
                
                rs2=stmt.executeQuery("select horaInicio,horaFin from alquiler where codUbi='"+datosLeidos+"' AND fechaAlq='"+fecha+"' AND deporteAlq='"+deporte+"'");
                while(rs2.next()){
                    horaAp=formatoHora.parse(rs2.getString(1).substring(11,16));
                    horaCi=formatoHora.parse(rs2.getString(2).substring(11,16));
                    
                    if((hora1.after(horaAp) && hora2.before(horaCi)) ||(hora1.after(horaAp) && hora1.before(horaCi)) ||(hora2.after(horaAp) && hora2.before(horaCi)) ||(hora1.equals(horaAp)) || (hora2.equals(horaCi))){
                        System.out.println("\nLo sentimos, en ese tramo NO ESTA DISPONIBLE esa ubicacion");
                    }
                }       
                

                System.out.println("\nLa ubicacion ESTA DISPONIBLE en ese tramo");
                
                if(!insertar){
                String respuesta;
                do{
                System.out.println("\n¿Desea alquilarla? (s/n)");
                respuesta=sc.nextLine();
                }while(!respuesta.equals("S") && !respuesta.equals("s") && !respuesta.equals("n") && !respuesta.equals("N") );

                if(respuesta.equals("S") || respuesta.equals("s"))
                      insertar=true;
                

                    usuario=MeetNMatch.identificacionUsuario(con);
                }
                
                if(insertar){
                    stmt.executeQuery("insert into alquiler (codUbi,usuario,fechaAlq,horaInicio,horaFin,deporteAlq) values('"+datosLeidos+"','"+usuario+"','"+fecha+"',TO_DATE('"+horaA+"','HH24:MI'),TO_DATE('"+horaC+"','HH24:MI'),'"+deporte+"')"); 
                    con.commit();
                    System.out.println("Se ha realizado el alquiler satisfactoriamente");
                }
            }

            }
            else
                System.out.println("La ubicacion se encuentra FUERA DE SERVICIO");

        } catch(Exception e){ System.out.println(e);}       
    }
    
    public static void alquilarUbicacion(Connection con){
        try{
            String usuario=MeetNMatch.identificacionUsuario(con);
            
            consultarDisponibilidad(con,true,usuario);
            
        } catch(Exception e){ System.out.println(e);}       
        }
    
    public static void Menu(Connection con){
        
         Scanner sc=new Scanner(System.in);
         int op;
         
        
        try{

         
         Boolean salir=false;

        do{
            do{
                System.out.println("Menú Ubicacion: \n" + "\t 1: Baja ubicacion. \n" + "\t 2: Añadir Ubicacion. \n" + "\t 3: Mostrar datos ubicacion \n" +"\t 4: Rehabilitar ubicacion \n"+"\t 5: Consultar disponibilidad \n" +"\t 6: Alquilar ubicacion\n"+"\t 7: DESCONECTAR \n" );
                op = Integer.parseInt(sc.nextLine());
                if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5 && op!=6 && op!=7)
                System.out.println("La opcion elegida no es valida");
            }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5 && op!=6 && op!=7);
        
            switch(op){
                case 1:
                    bajaUbicacion(con);
                break;

                case 2:
                    altaUbicacion(con);
                break;

                case 3:
                    mostrarDatosUbicacion(con);
                break;

                case 4:
                    rehabilitadoUbicacion(con);               
                break;

                case 5:
                    consultarDisponibilidad(con,false,"");               
                break;
                
                case 6:
                    alquilarUbicacion(con);               
                break;                
                case 7:
                    System.out.println("Saliendo de Ubicaciones...");
                    salir=true;
                    break;
          
                
          
            }

        }while(!salir);
        
        }catch(Exception e){ System.out.println(e);}
    }
}  
