import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Scanner;

public class Cliente {
    public static void main(String args[]) {
        Scanner teclado = new Scanner(System.in);
        String nombre, dinero;
        int opc;
        boolean salir = false;
        String nombre_objeto_remoto = "";

        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        
        if(args.length < 2)
        {
            System.out.println("Error: uso correcto -> java Cliente <IP> <0|1|2|3>");
            System.exit(0);
        }
                
        try {
                switch(args[1]){
                    case "0":
                        nombre_objeto_remoto = "Original";
                    break;

                    case "1":
                        nombre_objeto_remoto = "Replica";
                    break;

                    case "2":
                        nombre_objeto_remoto = "Replica2";
                    break;
                }

                System.out.println("Buscando el servidor...");
                Registry registry = LocateRegistry.getRegistry(args[0]);
                I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                System.out.println("Invocando el servidor");
            
            while(!salir){
                System.out.println("\nMenú sistema RMI cliente-servidor:");
                System.out.println("[1] Registrar" + "\n[2] Donar" + "\n[3] Consultar usuarios locales" + 
                "\n[4] Consultar usuarios globales" + "\n[5] Consultar total local" + "\n[6] Consultar total global" +"\n[7] Salir");
                System.out.println("\nElige la opción que quieras realizar: ");
                opc = Integer.parseInt(teclado.nextLine());
                switch(opc){
                    case 1:
                        System.out.println("Introduzca el nombre de usuario: ");
                        nombre = teclado.nextLine();
                        instancia_local.registrar(nombre);
                    break;

                    case 2:
                        System.out.println("Introduzca el nombre de usuario: ");
                        nombre = teclado.nextLine();
                        System.out.println("Introduzca la cantidad a donar por "+ nombre +" : ");
                        dinero = teclado.nextLine();
                        instancia_local.donar(nombre, Double.parseDouble(dinero));
                    break;

                    case 3:
                        ArrayList<String> usuariosLocales = new ArrayList<String>();
                        usuariosLocales = instancia_local.getUsuarioLocales();

                        for(int i = 0; i < usuariosLocales.size(); i++){
                            System.out.print(usuariosLocales.get(i) + " ");
                        }
                        System.out.println("");
                    break;

                    case 4:
                        ArrayList<String> usuariosGlobales = new ArrayList<String>();
                        usuariosGlobales = instancia_local.getUsuarioGlobales();

                        for(int i = 0; i < usuariosGlobales.size(); i++){
                            System.out.print(usuariosGlobales.get(i) + " ");
                        }
                        System.out.println("");
                    break;

                    case 5:
                        System.out.println("Introduzca el nombre de usuario: ");
                        nombre = teclado.nextLine();
                        System.out.println("El total local donado por los usuarios es "+instancia_local.getTotal(nombre)+" euros");
                    break;

                    case 6:
                        System.out.println("Introduzca el nombre de usuario: ");
                        nombre = teclado.nextLine();
                        System.out.println("El total global donado por los usuarios es "+instancia_local.getTotalGlobal(nombre)+" euros");
                    break;

                    case 7:
                        System.out.println("Hasta luego!");
                        salir = true;
                    break;
                }
            }
        } catch (Exception e) {
                System.err.println("Error al invocar el servidor");
                e.printStackTrace();
            }
        teclado.close();
    }
}
