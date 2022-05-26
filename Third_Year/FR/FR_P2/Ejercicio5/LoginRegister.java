import java.util.HashMap;
import java.util.Map;
import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

class LoginRegister{

    File leer; 
    Map<String, String> usuCont; 
    FileWriter escribir; 
    Scanner s;

    public LoginRegister(){ //Constructor

        this.leer = new File("./data/usuarios.txt");
        this.usuCont = new HashMap<String, String>();
        this.escribir = null;
        this.s = null;
    
        leerArchivo();

    }

    private void leerArchivo(){ //Método para leer un archivo

        try{
            
			s = new Scanner(leer);
            String usuario, contra;

			while (s.hasNextLine()){

                usuario = s.nextLine(); 	
                contra = s.nextLine();
                usuCont.put(usuario, contra);

            }

        }catch (Exception ex){}

        if(s != null){

            s.close();

        }              

    }

    private void escribirArchivo(String usuario, String contra){ //Método para escribir en un archivo
        
        try{

			escribir = new FileWriter("./data/usuarios.txt",true);
            escribir.write(usuario + "\n");
            escribir.write(contra + "\n");
			escribir.close();

        }catch (Exception ex) {}
        
    }

    public boolean register(String usuario, String contra){ //Metodo para añadir un usuario y una contraseña al archivo

        if(usuCont.containsKey(usuario)){

            System.out.println("Usuario pillado");
            return false;

        }else{
            
            this.usuCont = new HashMap<String, String>();
            escribirArchivo(usuario, contra);
            leerArchivo();
            return true;

        }
    }

    public boolean login(String usuario, String contra){ //Método que nos dice si un usuario y su contraseña se encuentran en el archivo

        if(usuCont.containsKey(usuario)){

            String aux = usuCont.get(usuario); 
            
            if(aux.equals(contra)){

                return true;

            }else{

                return false;

            }

        }else{

            return false;

        }
    }

}
