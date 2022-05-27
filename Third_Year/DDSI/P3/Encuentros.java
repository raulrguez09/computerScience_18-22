/*
SUBSISTEMA ENCUENTROS de Santiago Muñoz Castro
*/

package meetnmatch;


import java.sql.*;
import java.util.Scanner;
import java.lang.*;
import java.util.Date;
import java.text.SimpleDateFormat;

public class Encuentros{


public static void CrearEncuentro(Connection con,String usuarioActual){

String Deporte,MaterialyPersonal,fechaEnc,ubicacion,codEnc;
Date fecEnc=null;
SimpleDateFormat formato=new SimpleDateFormat("dd/MM/YY HH:mm");
int apuesta=0;
Scanner sc=new Scanner(System.in);
Statement stmt;



try{

    stmt=con.createStatement();

    Savepoint save1=con.setSavepoint();
    System.out.println("Introducir datos para crear encuentro");
do{
    System.out.println("Introduzca datos del deporte(Fútbol,Baloncesto,Pádel)");
    Deporte=sc.nextLine();
    if(!Deporte.equals("Fútbol") && !Deporte.equals("Baloncesto") && !Deporte.equals("Pádel"))
        System.out.println("Lo sentimos, el deporte "+Deporte+" no existe en nuestro sistema");

}while( !Deporte.equals("Fútbol") && !Deporte.equals("Baloncesto") && !Deporte.equals("Pádel"));

ResultSet rs10;
Boolean existe2=false;
do{
    System.out.println("Introduzca fecha y hora del encuentro(Formato:dd/MM/yy HH:mm), tiene que ser despues de la actual");
    fechaEnc=sc.nextLine();
    rs10=stmt.executeQuery("select codEnc from encuentros where TO_DATE('"+fechaEnc+"','DD/MM/RR HH24:MI')> TO_DATE(sysdate,'DD/MM/RR HH24:MI')");
    existe2=rs10.next();
    if(fechaEnc.length()!=14)
    System.out.println("Formato de fecha mal introducido");
    if(!existe2)
    System.out.println("La fecha del encuentro tiene que ser despues de la actual");

    

}while(fechaEnc.length()!=14 || !existe2);

ResultSet rs1;
Boolean existe=true;
do{
    System.out.println("Introduzca ubicacion donde se vaya a llevar a cabo el encuentro(maximo 100 caracteres)");
    ubicacion=sc.nextLine();
    rs1=stmt.executeQuery("select codUbi from ubicacion where localizacion='"+ubicacion+"'");
    existe=rs1.next();
    if(!existe)
    System.out.println("Ubicacion no registrada en nuestra base de datos");
    if(ubicacion.length()>100)
    System.out.println("Nombre ubicación demasiado largo,sobrepasa los 100 caracteres");

}while(ubicacion.length()>100 || !existe);

do{
    System.out.println("Introduzca material y personal necesario(maximo 100 caracteres)");
    MaterialyPersonal=sc.nextLine();
    if(MaterialyPersonal.length()>100)
    System.out.println("Descripcion del material y personal demasiado largo,sobrepasa los 100 carateres");

}while(MaterialyPersonal.length()>100);

do{
    System.out.println("Introduzca apuesta en puntos,puede ser 0");
    apuesta=Integer.parseInt(sc.nextLine());
    if(apuesta<0)
    System.out.println("No puedes hacer una apuesta negativa");

}while(apuesta<0);


int respuesta;
ResultSet rs2;
do{
    codEnc=MeetNMatch.generateRandomString(5);
    rs2=stmt.executeQuery("select codEnc from encuentros where codEnc='"+codEnc+"'");
}while(rs2.next());

stmt.executeUpdate("insert into encuentros (codEnc,usuarioLider,deporteEnc,horaEnc,ubicacionEncuentro,material_Personal,apuestaEnc) values('"+codEnc+"','"+usuarioActual+"','"+Deporte+"',TO_DATE('"+fechaEnc+"','DD/MM/RR HH24:MI'),'"+ubicacion+"','"+MaterialyPersonal+"',"+apuesta+")");

System.out.println("Datos de encuentro válidos, quieres crear el encuentro: 1-SI 2-NO");
respuesta=Integer.parseInt(sc.nextLine());
if(respuesta==1)
{
    con.commit();
    System.out.println("Encuentro creado.");
}
    
else if(respuesta==2)
    con.rollback(save1);

}catch(Exception e){ System.out.println(e);}


}

public static void CancelarEncuentro(Connection con,String usuarioActual){
    int motivo;
    String codigo;
    Scanner sc=new Scanner(System.in);
    Statement stmt;
    int respuesta;

    
    try{

        stmt=con.createStatement();
        Savepoint save2=con.setSavepoint();
        System.out.println("Introducir datos para cancelar encuentro");

        ResultSet rs2;
        rs2=stmt.executeQuery("select codEnc from encuentros where usuarioLider='"+usuarioActual+"'");
        if(!rs2.next())
        {
            System.out.println("No eres el usuario lider de ningun encuentro, por lo que no puedes cancelar ninguno");
            return;
        }
        else{
        Boolean existe=false;
        ResultSet rs1;
        do{
            System.out.println("Introduzca el código del encuentro que quieras cancelar(5 caracteres)");
            codigo=sc.nextLine();
            rs1=stmt.executeQuery("select codEnc from encuentros where codEnc='"+codigo+"'"+" and usuarioLider='"+usuarioActual+"'");

            existe=rs1.next();
            if(!existe)
            {
                System.out.println("Este encuentro no existe o no eres el usuario lider del mismo, pruebe con otro");
            }
            else if(codigo.length()!=5)
            {
                System.out.println("La longitud del código tiene que ser de 5");
            }
            
        }while(!existe || codigo.length()!=5 );

        System.out.println("El encuentro existe.");

        do{
            System.out.println("Eliga un motivo para cancelar el encuentro: 1-No hay gente suficiente 2-No tenemos el material requerido 3-Circunstancias meteorologicas 4-Problemas personales");
            motivo=Integer.parseInt(sc.nextLine());

            if(motivo!=1 && motivo!=2 && motivo!=3 && motivo!=4)
                System.out.println("Opción elegida no válida");
            
            
        }while(motivo!=1 && motivo!=2 && motivo!=3 && motivo!=4);

        stmt.executeUpdate("delete from encuentros where codEnc='"+codigo+"'");
        
        System.out.println("Estas segur@ de que quieres borrar el encuentro: 1-SI 2-NO");
        respuesta=Integer.parseInt(sc.nextLine());

        if(respuesta==1)
        {
            con.commit();
            System.out.println("Encuentro borrado.");
        }
    
        else if(respuesta==2)
        con.rollback(save2);

    }

    }catch(Exception e){ System.out.println(e);}


}


public static void ModificarEncuentro(Connection con,String usuarioActual){
    int opcion,apuesta,respuesta;
    String codigo;
    String Deporte,fechaEnc,ubicacion,MaterialyPersonal;
    SimpleDateFormat formato=new SimpleDateFormat("dd/MM/yy HH:mm");
    Date fecEnc=null;
    Statement stmt;
    Scanner sc=new Scanner(System.in);
    
    try{

        stmt=con.createStatement();
        Savepoint save3=con.setSavepoint();
        System.out.println("Introducir datos para modificar encuentro");

        ResultSet rs2;
        rs2=stmt.executeQuery("select codEnc from encuentros where usuarioLider='"+usuarioActual+"'");
        if(!rs2.next())
        {
            System.out.println("No eres el usuario lider de ningun encuentro, por lo que no puedes modificar ninguno");
            return;
        }

        else{
            
            ResultSet rs1;
            Boolean existe=false;
            do{
                System.out.println("Introduzca el código del encuentro que quieras modificar(5 caracteres)");
                codigo=sc.nextLine();
                rs1=stmt.executeQuery("select codEnc from encuentros where codEnc='"+codigo+"'"+" and usuarioLider='"+usuarioActual+"'");
                existe=rs1.next();
                if(!existe)
                {
                    System.out.println("Este encuentro no existe o no eres el usuario lider del mismo, pruebe con otro");
                }
                else if(codigo.length()!=5)
                {
                    System.out.println("La longitud del código tiene que ser de 5");
                }
            
            }while(!existe || codigo.length()!=5 );

        


            System.out.println("El encuentro existe.");
            do{

                System.out.println("Eliga opcion sobre lo que quieras modifciar: 1-Deporte 2-Hora 3-ubicación 4-Material y Personal 5-Apuesta 6-No modificar nada mas");
                opcion=Integer.parseInt(sc.nextLine());

                if(opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4 && opcion!=5 && opcion!=6)
                    System.out.println("Opcion no válida, pruebe con otra");

                if(opcion==1)
                {
                    do{
                        System.out.println("Introduzca el deporte a cambiar(Fútbol,Baloncesto,Pádel)");
                        Deporte=sc.nextLine();
                        if(!Deporte.equals("Fútbol") && !Deporte.equals("Baloncesto") && !Deporte.equals("Pádel"))
                        System.out.println("Lo sentimos, el deporte "+Deporte+" no existe en nuestro sistema");

                    }while( !Deporte.equals("Fútbol") && !Deporte.equals("Baloncesto") && !Deporte.equals("Pádel"));

                    stmt.executeUpdate("update encuentros set deporteEnc='"+Deporte+"' where codEnc='"+codigo+"'"); 
                }

                if(opcion==2)
                {
                    do{
                        System.out.println("Introduzca la nueva fecha y hora del encuentro(Formato:dd/MM/yy HH:mm),tiene que ser posterior a la actual si no se hace el cambio");
                        fechaEnc=sc.nextLine();
                    
                        if(fechaEnc.length()!=14)
                        System.out.println("Formato de fecha mal introducido");
                        else
                            fecEnc=formato.parse(fechaEnc);
                        
                    }while(fechaEnc.length()!=14 );

                    stmt.executeUpdate("update encuentros set horaEnc=TO_DATE('"+fechaEnc+"','DD/MM/RR HH24:MI')"+" where codEnc='"+codigo+"' and TO_DATE('"+fechaEnc+"','DD/MM/RR HH24:MI')> TO_DATE(sysdate,'DD/MM/RR HH24:MI')"); 
                }

                if(opcion==3)
                {
                    ResultSet rs3;
                    do{
                        System.out.println("Introduzca nueva ubicacion del encuentro(maximo 100 caracteres)");
                        ubicacion=sc.nextLine();
                        rs3=stmt.executeQuery("select codUbi from ubicacion where localizacion='"+ubicacion+"'");
                        existe=rs3.next();
                        if(!existe)
                        System.out.println("Ubicacion no registrada en nuestra base de datos");
                        if(ubicacion.length()>100)
                        System.out.println("Nombre ubicación demasiado largo,sobrepasa los 100 caracteres");
                    
                    }while(ubicacion.length()>100 || !existe);

                    stmt.executeUpdate("update encuentros set ubicacionEncuentro='"+ubicacion+"' where codEnc='"+codigo+"'"); 
                }

                if(opcion==4)
                {
                    do{
                        System.out.println("Introduzca material y personal a cambiar (maximo 100 caracteres)");
                        MaterialyPersonal=sc.nextLine();
                        if(MaterialyPersonal.length()>100)
                        System.out.println("Descripcion del material y personal demasiado largo,sobrepasa los 100 carateres");
                    
                    }while(MaterialyPersonal.length()>100);

                    stmt.executeQuery("update encuentros set material_Personal='"+MaterialyPersonal+"' where codEnc='"+codigo+"'"); 
                }

                if(opcion==5)
                {
                    do{
                        System.out.println("Introduzca la nueva apuesta en puntos,puede ser 0");
                        apuesta=Integer.parseInt(sc.nextLine());
                        if(apuesta<0)
                        System.out.println("No puedes hacer una apuesta negativa");
                    
                    }while(apuesta<0);

                    stmt.executeUpdate("update encuentros set apuestaEnc="+apuesta+" where codEnc='"+codigo+"'"); 
                }

                if(opcion==6)
                    System.out.println("Salimos del modo modificar.");

            }while(opcion!=6);

        System.out.println("Antes de salir, ¿quieres confirmar todos las modificaciones realizadas?: 1-SI 2-NO");
        respuesta=Integer.parseInt(sc.nextLine());

        if(respuesta==1)
        {
            con.commit();
            System.out.println("Encuentro modificado.");
        }
    
        else if(respuesta==2)
        con.rollback(save3);


        }



    }catch(Exception e){ System.out.println(e);}
}

public static void MostrarEncuentro(Connection con)
{
    String codigo;
    Statement stmt; 
    Scanner sc=new Scanner(System.in);

    try{
        stmt=con.createStatement();

        ResultSet rs1;
        Boolean existe;
        do{
            System.out.println("Introduzca el código del encuentro que quieras ver (5 caracteres)");
            codigo=sc.nextLine();
            rs1=stmt.executeQuery("select codEnc from encuentros where codEnc='"+codigo+"'");
            existe=rs1.next();
            if(!existe)
            {
                System.out.println("Este encuentro no existe, pruebe con otro");
            }
            else if(codigo.length()!=5)
            {
                System.out.println("La longitud del código tiene que ser de 5");
            }
        
        }while(!existe || codigo.length()!=5 );


        ResultSet rs2=stmt.executeQuery("select * from encuentros where codEnc='"+codigo+"'");
        System.out.println("\tcodEnc\tpuntuacionLocal\tpuntuacionVisitante\tusuarioLider\tdeporte\thora\tubicacion\tmaterial y Personal\tapuesta");
        while(rs2.next())
            System.out.println("\t"+rs2.getString(1)+"\t"+rs2.getInt(2)+"\t"+rs2.getInt(3)+"\t"+rs2.getString(4)+"\t"+rs2.getString(5)+"\t"+rs2.getString(6)+"\t"+rs2.getString(7)+"\t"+rs2.getString(8)+"\t"+rs2.getInt(9));

    }catch(Exception e){ System.out.println(e);}


}

public static void EstablecerResultado(Connection con,String usuarioActual){
    String codigo;
    int puntLocal,puntVis; 
    Scanner sc=new Scanner(System.in);
    Statement stmt;
    int respuesta;

    try{

        stmt=con.createStatement();

        Savepoint save3=con.setSavepoint();
        System.out.println("Introducir datos para establecer resultado");

        ResultSet rs2;
        rs2=stmt.executeQuery("select codEnc from encuentros where usuarioLider='"+usuarioActual+"'");
        if(!rs2.next())
        {
            System.out.println("No eres el usuario lider de ningun encuentro, por lo que no puedes establecer el resultado de ninguno");
            return;
        }
        else{
            Boolean existe=false;
            ResultSet rs1;
            do{
                System.out.println("Introduzca el código del encuentro del que quieras establecer el resultado(5 caracteres)");
                codigo=sc.nextLine();
                rs1=stmt.executeQuery("select codEnc from encuentros where codEnc='"+codigo+"'"+" and usuarioLider='"+usuarioActual+"'");
                existe=rs1.next();
                if(!existe)
                {
                    System.out.println("Este encuentro no existe, pruebe con otro");
                }
                else if(codigo.length()!=5)
                {
                    System.out.println("La longitud del código tiene que ser de 5");
                }
            
            }while(!existe || codigo.length()!=5 );

            do{
                System.out.println("Introduzca la puntuacion local(equipo del usuario lider)");
                puntLocal=Integer.parseInt(sc.nextLine());
                if(puntLocal<0)
                System.out.println("La puntuacion no puede ser negativa");

            }while(puntLocal<0);

            do{
                System.out.println("Introduzca la puntuacion visitante");
                puntVis=Integer.parseInt(sc.nextLine());
                if(puntVis<0)
                System.out.println("La puntuacion no puede ser negativa");

            }while(puntVis<0);

            stmt.executeUpdate("update encuentros set puntuacionLocal="+puntLocal+", puntuacionVisitante="+puntVis+" where codEnc='"+codigo+"'");

            System.out.println("Seguro que quieres establecer este resultado, después no se podra cambiar: 1-SI 2-NO");
            respuesta=Integer.parseInt(sc.nextLine());
    
            if(respuesta==1)
            {
                con.commit();
                System.out.println("Resultado establecido.");
            }
        
            else if(respuesta==2)
            con.rollback(save3);
    

        }

        

        

    }catch(Exception e){ System.out.println(e);}

}

public static void busquedaEncuentro(Connection con){

    Scanner sc=new Scanner(System.in);
    Statement stmt;
    int opcion,apuesta;
    Date fecEnc=null;
    String ubicacion,fechaEnc,Deporte;
    SimpleDateFormat formato=new SimpleDateFormat("dd/MM/yy HH:mm");

    try{
        stmt=con.createStatement();
        
        do{
            System.out.println("Eliga el filtro de búsqueda: 1-Ubicación 2-Hora 3-Apuesta 4-Deporte");
            opcion=Integer.parseInt(sc.nextLine());
            if(opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4)
                System.out.println("Opción no válida");

        }while(opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4);

        if(opcion==1)
        {
            ResultSet rs3;
            Boolean existe=false;
            do{
                System.out.println("Introduzca la ubicacion (maximo 100 caracteres)");
                ubicacion=sc.nextLine();
                rs3=stmt.executeQuery("select codUbi from ubicacion where localizacion='"+ubicacion+"'");
                existe=rs3.next();
                if(!existe)
                System.out.println("Ubicacion no registrada en nuestra base de datos,pruebe otra");
                if(ubicacion.length()>100)
                System.out.println("Nombre ubicación demasiado largo,sobrepasa los 100 caracteres");
            
            }while(ubicacion.length()>100 || !existe);

            ResultSet rs1=stmt.executeQuery("select * from encuentros where ubicacionEncuentro='"+ubicacion+"'");
            System.out.println("\tcodEnc\tpuntuacionLocal\tpuntuacionVisitante\tusuarioLider\tdeporte\thora\tubicacion\tmaterial y Personal\tapuesta");
            
           
            while(rs1.next()){
                System.out.println("\t"+rs1.getString(1)+"\t"+rs1.getInt(2)+"\t"+rs1.getInt(3)+"\t"+rs1.getString(4)+"\t"+rs1.getString(5)+"\t"+rs1.getString(6)+"\t"+rs1.getString(7)+"\t"+rs1.getString(8)+"\t"+rs1.getInt(9));
                }
            }

        if(opcion==2)
        {
            do{
                System.out.println("Introduzca fecha y hora de filtro(Formato:dd/MM/yy HH:mm)");
                fechaEnc=sc.nextLine();
            
                if(fechaEnc.length()!=14)
                System.out.println("Formato de fecha mal introducido");
                else
                    fecEnc=formato.parse(fechaEnc);
                
            }while(fechaEnc.length()!=14 );

            ResultSet rs2=stmt.executeQuery("select * from encuentros where horaEnc=TO_DATE('"+fechaEnc+"','DD/MM/RR HH24:MI')");
            System.out.println("\tcodEnc\tpuntuacionLocal\tpuntuacionVisitante\tusuarioLider\tdeporte\thora\tubicacion\tmaterial y Personal\tapuesta");
            while(rs2.next()){
            System.out.println("\t"+rs2.getString(1)+"\t"+rs2.getInt(2)+"\t"+rs2.getInt(3)+"\t"+rs2.getString(4)+"\t"+rs2.getString(5)+"\t"+rs2.getString(6)+"\t"+rs2.getString(7)+"\t"+rs2.getString(8)+"\t"+rs2.getInt(9));
            }
        }

        if(opcion==3)
        {
            do{
                System.out.println("Introduzca la apuesta minima a buscar(mostrara todas las apuestas entre un rango de 100 puntos),puede ser 0");
                apuesta=Integer.parseInt(sc.nextLine());
                if(apuesta<0)
                System.out.println("No puedes hacer una apuesta negativa");
            
            }while(apuesta<0);

            ResultSet rs4=stmt.executeQuery("select * from encuentros where apuestaEnc>="+apuesta+"-100 and apuestaEnc<="+apuesta+"+100");
            System.out.println("\tcodEnc\tpuntuacionLocal\tpuntuacionVisitante\tusuarioLider\tdeporte\thora\tubicacion\tmaterial y Personal\tapuesta");
            while(rs4.next()){
            System.out.println("\t"+rs4.getString(1)+"\t"+rs4.getInt(2)+"\t"+rs4.getInt(3)+"\t"+rs4.getString(4)+"\t"+rs4.getString(5)+"\t"+rs4.getString(6)+"\t"+rs4.getString(7)+"\t"+rs4.getString(8)+"\t"+rs4.getInt(9));
            }

        }

        if(opcion==4)
        {
            do{
                System.out.println("Introduzca el deporte para buscar (Fútbol,Baloncesto,Pádel)");
                Deporte=sc.nextLine();
                 if(!Deporte.equals("Fútbol") && !Deporte.equals("Baloncesto") && !Deporte.equals("Pádel"))
                     System.out.println("Lo sentimos, el deporte "+Deporte+" no existe en nuestro sistema");

            }while( !Deporte.equals("Fútbol") && !Deporte.equals("Baloncesto") && !Deporte.equals("Pádel"));

            ResultSet rs5=stmt.executeQuery("select * from encuentros where deporteEnc='"+Deporte+"'");
            System.out.println("\tcodEnc\tpuntuacionLocal\tpuntuacionVisitante\tusuarioLider\tdeporte\thora\tubicacion\tmaterial y Personal\tapuesta");
            while(rs5.next()){
            System.out.println("\t"+rs5.getString(1)+"\t"+rs5.getInt(2)+"\t"+rs5.getInt(3)+"\t"+rs5.getString(4)+"\t"+rs5.getString(5)+"\t"+rs5.getString(6)+"\t"+rs5.getString(7)+"\t"+rs5.getString(8)+"\t"+rs5.getInt(9));
            }

        }


        


    }catch(Exception e){ System.out.println(e);}
}


                                                    
    public static void Menu(Connection con){
        
         Scanner sc=new Scanner(System.in);
         int op;
         
         String usuario=MeetNMatch.identificacionUsuario(con);
         try{    
            do{
                System.out.println("Menú Encuentros:\n 1-Crear encuentro\n 2-Borrar encuentro\n 3-Modificar encuentro\n 4-Mostrar encuentro mediante código\n 5-Buscar encuentro por filtro\n 6-Establecer resultado\n 7-Salir\n");
                op=Integer.parseInt(sc.nextLine());
            switch(op)
            {
                  
                case 1:
                    CrearEncuentro(con,usuario);
                    break;
                    
                case 2:
                    CancelarEncuentro(con,usuario);
                    break;
                case 3:
                    ModificarEncuentro(con,usuario);
                    break;
                    
                case 4:
                    MostrarEncuentro(con);
                    break;
                case 5:
                    busquedaEncuentro(con);   
                    break;
                case 6:
                    EstablecerResultado(con,usuario);
                    break;
                    
                case 7:
                    System.out.println("Saliendo de Encuentros...");
                    break;
            }
            
            }while(op!=7);
            
             
         }catch(Exception e){ System.out.println(e);}
    }
  
}


    


    
    
    