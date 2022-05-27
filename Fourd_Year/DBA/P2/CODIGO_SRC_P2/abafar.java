package abafar;

import appboot.LARVABoot;


public class Abafar {
    public static void main(String[] args) {
        LARVABoot connection = new LARVABoot();
        
        connection.Boot("isg2.ugr.es", 1099);
        connection.launchAgent("CLONE36", MyFirstAbafar.class);
        connection.WaitToShutDown();
       
    }
    
}