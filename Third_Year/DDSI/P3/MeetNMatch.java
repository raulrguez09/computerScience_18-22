/*
Grupo MATARRATAS (A2):
	Francisco Javier Jiménez Legaza
	Ángel Gómez Ferrer
	Cristian Fernández Jiménez
	Santiago Muñoz Castro
	Raúl Rodríguez Pérez
	Raúl Castro Moreno
*/

package meetnmatch;

import java.security.SecureRandom;
import java.sql.*;
import java.util.Scanner;
import java.lang.*;
public  class MeetNMatch{ 

    public static String generateRandomString(int length) {
        String CHAR_LOWER = "abcdefghijklmnopqrstuvwxyz";
        String CHAR_UPPER = CHAR_LOWER.toUpperCase();
        String NUMBER = "0123456789";

        String DATA_FOR_RANDOM_STRING = CHAR_LOWER + CHAR_UPPER + NUMBER;
        SecureRandom random = new SecureRandom();
    
        if (length < 1) throw new IllegalArgumentException();

        StringBuilder sb = new StringBuilder(length);
        
        for (int i = 0; i < length; i++) {
            // 0-62 (exclusivo), retorno aleatorio 0-61
            int rndCharAt = random.nextInt(DATA_FOR_RANDOM_STRING.length());
            char rndChar = DATA_FOR_RANDOM_STRING.charAt(rndCharAt);

            sb.append(rndChar);
        }

        return sb.toString();
	}
	

	public static String identificacionUsuario(Connection con){

		Statement stmt;
		Scanner sc=new Scanner(System.in);
		String datosLeidos="";
		ResultSet rs;
		try{
		stmt=con.createStatement();
		do{
                    
                System.out.println("Introducir nombre de usuario: ");
                datosLeidos=sc.nextLine();
                rs=stmt.executeQuery("select nombreusuario from jugadores where nombreusuario='"+datosLeidos+"'");
		}while(datosLeidos.length()>15 || !rs.next());
		} catch(Exception e){ System.out.println(e);}       


		return datosLeidos;
	}



    public static void main(String args[]){
        
		Scanner sc=new Scanner(System.in);
		int op;
		Connection con;
	   
	   try{

	   Class.forName("oracle.jdbc.driver.OracleDriver");          
	   
	   con = DriverManager.getConnection("jdbc:oracle:thin:@//oracle0.ugr.es:1521/practbd.oracle0.ugr.es", "x0623057","x0623057");
	   con.setAutoCommit (false);
		
		Boolean salir=false;
                System.out.println("Bienvenido a Meet N Match.");

	   do{
		   do{
			   System.out.println("\nSeleccione el campo para la operacion: \n" + "\t 1: Jugadores. \n" + "\t 2: Equipos. \n" + "\t 3: Ubicaciones. \n" +"\t 4: Encuentros. \n"+"\t 5: Valoraciones y quejas. \n" +"\t 6: Premios.\n"+"\t 7: Desconexión. \n" );
			   op = Integer.parseInt(sc.nextLine());
			   if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5 && op!=6 && op!=7)
			   System.out.println("La opcion elegida no es valida");
		   }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5 && op!=6 && op!=7);
	   
		   	switch(op){
			   case 1:
				   Jugadores.Menu(con);
			   break;

			   case 2:
				   Equipos.Menu(con);
			   break;

			   case 3:
				   Ubicaciones.Menu(con);
			   break;

			   case 4:
				   Encuentros.Menu(con);
			   break;

			   case 5:
				   Valoraciones.Menu(con);
			   break;
			   
			   case 6:
				   Premios.Menu(con);
			   break;                
			   case 7:
				   System.out.println("Se ha desconectado con éxito.");
				   salir=true;
				   break;
		   }

	   }while(!salir);
	   
	   con.close();
	   }catch(Exception e){ System.out.println(e);}
   }
}  
