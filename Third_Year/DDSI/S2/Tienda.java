/*
Seminario 2:  Acceso a bases de datos

Grupo MATARRATAS (A2):
	Francisco Javier Jiménez Legaza
	Ángel Gómez Ferrer
	Cristian Fernández Jiménez
	Santiago Muñoz Castro
	Raúl Rodríguez Pérez
	Raúl Castro Moreno

*/


import java.sql.*;
import static java.lang.System.exit;
import java.util.Scanner;
import java.util.Random;
import java.sql.SQLException;
import java.lang.*;


public  class Tienda{ 

    
    //Realiza el borrado y nueva creación de las tablas e inserción de 10 tuplas predefinidas en el código en la tabla Stock
    public static void borrarYcrear(Connection con){
        
    try{

        Statement stmt;
    
        stmt=con.createStatement();

        stmt.executeUpdate("DROP TABLE DetallePedido");
        stmt.executeUpdate("DROP TABLE Pedido");
        stmt.executeUpdate("DROP TABLE Stock");

        stmt.executeUpdate("CREATE TABLE Stock(Cproducto NUMBER(5) NOT NULL PRIMARY KEY,Cantidad INT NOT NULL)");
        
        stmt.executeUpdate("CREATE TABLE Pedido(Cpedido NUMBER(5) NOT NULL PRIMARY KEY,Ccliente NUMBER(5) NOT NULL,FechaPedido DATE NOT NULL)");
        
        stmt.executeUpdate("CREATE TABLE DetallePedido(Cpedido NUMBER(5) NOT NULL REFERENCES Pedido(Cpedido),Cproducto NUMBER(5) NOT NULL REFERENCES Stock(Cproducto),Cantidad INT NOT NULL,PRIMARY KEY(Cpedido,Cproducto))");

        for(int i = 0; i < 10; i++){
            Random random = new Random();
            int cprod = 10000;
            int cant = random.nextInt(10) + 1; 
            cprod += i;
            stmt.executeUpdate("INSERT INTO Stock VALUES("+cprod+","+cant+")");                                              
        }   
        
    
        con.commit();                                      
        
    
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


    public static void altaPedido(Connection con){
        String datosLeidos;
        String pedido;
        int opcionElegida;
        int Cpedido=0;
        Scanner sc=new Scanner(System.in);
        Boolean quedarnosMenu=true;
        Statement stmt;
        
        try{

            stmt=con.createStatement();
            
            do{
            System.out.println("Introducir datos de pedido de la forma: Cpedido(5),Ccliente(5)");
            pedido=sc.nextLine();
            Cpedido=Integer.parseInt(pedido.substring(0,5));
            
            if(pedido.length()!=11)
            System.out.println("Se han introducido mal los datos");

            }while(pedido.length()!=11);


            Savepoint save2=con.setSavepoint();
            stmt.executeQuery("insert into Pedido (Cpedido,Ccliente,FechaPedido) values("+pedido+",SYSDATE)");
            Savepoint save1 = con.setSavepoint();
            do{
            do{
            System.out.println("Eliga una de estas opciones :\n"+"\t1: Añadir detalle de producto\n"+"\t2: Eliminar todos los detalles del producto\n"+"\t3: Cancelar pedido\n"+"\t4: Finalizar pedido ");
            datosLeidos=sc.nextLine();
            opcionElegida=Integer.parseInt(datosLeidos);
            if(opcionElegida!=1 && opcionElegida!=2 && opcionElegida!=3 && opcionElegida!=4)
            System.out.println("La opcion elegida no es valida");
            }while(opcionElegida!=1 && opcionElegida!=2 && opcionElegida!=3 && opcionElegida!=4);
            
        switch(opcionElegida)
        {
            case 1: 
                String articulo;
                int cantidad;
                int stock=0;
                int Cproducto;
                String codProd=" ";
                do{
                    System.out.println("Introduzca los datos de un articulo: Cproducto(5),Cantidad");
                    articulo=sc.nextLine();
                    Cproducto=Integer.parseInt(articulo.substring(0,5));
                    cantidad=Integer.parseInt(articulo.substring(6,articulo.length()));
                    codProd=articulo.substring(0,5);
                    ResultSet rs3=stmt.executeQuery("select * from Stock where "+Cproducto+"=Cproducto");
                    if(articulo.length()<7)
                    System.out.println("Se han introducido mal los datos");
                    if(codProd=="")
                    System.out.println("El producto no existe");
                    if(cantidad<1)
                    System.out.println("Introduzca una cantidad valida");
                    
                }while(articulo.length()<7 || codProd=="" || cantidad<1);
               

                ResultSet rs1=stmt.executeQuery("select cantidad from stock where "+Cproducto+"=Cproducto");
                if(rs1.next())
                    stock=rs1.getInt(1);
                if((stock-cantidad)>=0)
                {
                    System.out.println("Hay stock del pedido, se inserta los detalles del pedido: "+Cpedido+","+articulo);
                    stmt.executeQuery("insert into DetallePedido (Cpedido,Cproducto,Cantidad) values("+Cpedido+","+articulo+")");
                    stock-=cantidad;
                    System.out.println("Actualizamos stock:"+stock);
                    stmt.executeQuery("UPDATE Stock SET Cantidad="+stock+" WHERE Cproducto="+Cproducto);
                 
                }
                else
                {
                    System.out.println("No hay stock suficiente del pedido");
                    con.rollback(save1);
                }
            
            break;

            case 2:
                con.rollback(save1);
            break;

            case 3:
                System.out.println("Pedido eliminado");
                quedarnosMenu=false;
                con.rollback(save2);
            break;

            case 4:
                System.out.println("Pedido guardado en la base de datos");
                con.commit();
                quedarnosMenu=false;
            break;
        
        }
        }while(quedarnosMenu);
        ResultSet rs2=stmt.executeQuery("select * from stock");
        while(rs2.next())
        System.out.println(rs2.getInt(1)+"  "+rs2.getInt(2));
        
       
        }catch(Exception e){ System.out.println(e);}
        
        
    }



    public static void borrarPedido(int Cpedido, Connection con, Scanner sc){
        try{
            Statement stmt;
            stmt= con.createStatement();             

            int result,Cproducto = 0,cantidad = 0;
            ResultSet rs1, rs2;
            
            Savepoint save1=con.setSavepoint();

            try{
                rs1 = stmt.executeQuery("SELECT Cproducto, Cantidad FROM DetallePedido WHERE Cpedido="+Cpedido);
                
                if(rs1.next()){
                    Cproducto = rs1.getInt(1);
                    cantidad = rs1.getInt(2);
                }

                rs2 = stmt.executeQuery("SELECT Cantidad FROM Stock WHERE Cproducto="+Cproducto);

                if(rs2.next()){
                    cantidad += rs2.getInt(1);
                    stmt.executeQuery("UPDATE Stock SET Cantidad="+cantidad+" WHERE Cproducto="+Cproducto);
                }
                
                result= stmt.executeUpdate("DELETE FROM DetallePedido WHERE Cpedido="+Cpedido);
	            result+= stmt.executeUpdate("DELETE FROM Pedido WHERE Cpedido="+Cpedido);
                System.out.println("\n"+result+" registros afectados.");
            
            }catch(SQLException e){ System.out.println("Código de Error: " + e.getErrorCode() + "\n" +
            "SQLState: " + e.getSQLState() + "\n" +
            "Mensaje: " + e.getMessage());
            
            Throwable t = e.getCause();
            while(t != null) {
                System.out.println("Causa: " + t + "\n");
                t = t.getCause();
            }
            }
            System.out.println("Se va a eliminar el pedido " + Cpedido + " y todos sus detalles. ¿Esta seguro de hacerlo? (Y/N): ");
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
    
    public static void mostrarListaPedidos(Connection con){
        try{
            Statement stmt;
            stmt=con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT Cpedido,Ccliente FROM Pedido");
            System.out.println("\tCpedido\tCcliente");
            while(rs.next())
                System.out.println("\t"+rs.getInt(1)+"\t" +rs.getInt(2));
        } catch(Exception e){ System.out.println(e);}
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
        do{
            do{
                System.out.println("Menu Tienda: \n" + "\t 1: Borrar y Creacion de tablas. \n" + "\t 2: Añadir Pedido. \n" + "\t 3: Eliminar pedido. \n" +"\t 4: Mostrar listas de pedidos. \n"+ "\t 5: Salir. \n" );
                op = Integer.parseInt(sc.nextLine());
                if(op!=1 && op!=2  && op!=3 && op!=4 && op!=5)
                System.out.println("La opcion elegida no es valida");
            }while(op!=1 && op!=2 && op!=3  && op!=4 && op!=5 );
        
            switch(op){
                case 1:
                    borrarYcrear(con);
                    System.out.println("Se han borrado y creado las tablas de nuevo");
                break;

                case 2:
                    altaPedido(con);
                break;

                case 3:
                    int cpedido;

                    do{
                        System.out.println("Introduzca el código del pedido a borrar:");

                        cpedido=Integer.parseInt(sc.nextLine());
                        
                    }while(cpedido < 10000 && cpedido > 100000 );
                
                    borrarPedido(cpedido,con,sc);
                break;

                case 4:
                    mostrarListaPedidos(con);
                break;

                case 5:
                    System.out.println("Se ha desconectado con éxito.");
                    salir=true;
                break;
          
            }

        }while(!salir);
        
        con.close();
        }catch(Exception e){ System.out.println(e);}
    }
}  



    


    
    
    
