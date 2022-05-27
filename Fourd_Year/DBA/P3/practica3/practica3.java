package practica3;

import appboot.LARVABoot;
import crypto.Keygen;

/**
 *
 * @author Agustin Ruben Raul Angel
 */
public class practica3 {

    public static void main(String[] args) {
            LARVABoot myboot = new LARVABoot();
            myboot.Boot("isg2.ugr.es",1099);
            myboot.launchAgent("Destroyer"+Keygen.getHexaKey(4), Destroyer.class);
            myboot.launchAgent("Fighter"+Keygen.getHexaKey(4), TieFighter.class);
            myboot.launchAgent("Fighter"+Keygen.getHexaKey(4), TieFighter.class);
            myboot.launchAgent("Corellian"+Keygen.getHexaKey(4), Corellian.class);
            myboot.launchAgent("Corellian"+Keygen.getHexaKey(4), Corellian.class);
            myboot.WaitToShutDown();    
    }
    
}
 
